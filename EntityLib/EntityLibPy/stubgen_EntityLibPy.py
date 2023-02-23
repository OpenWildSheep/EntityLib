#
# pybind seems to output typing info in docstrings, which VsCode/Pylance doesn't support (no autocompletion).
# This script uses pybind11-stubgen to generate .pyi files (MyPy typing hint format),
# then reprocesses the output a little to make it even more VsCode-compliant.
#
# NOTE: we use the executable/CLI version, but pybind11-stugen also comes with a Python script
# that would probably allow us to control the output directly.
# This typing info is purely IDE-side though (no runtime side-effect),
# so as long as autocompletion works, it doesn't need to be pretty.
#

import os
import sys
import traceback
import subprocess

print(sys.version)

# change the working dir to this script's dir
script_dir = os.path.dirname(__file__)
os.chdir(script_dir)
print("Current working dir:")
print(os.getcwd())


stubgen_path = os.path.abspath("../../../ExternalTools/Python37/stubgen/pybind11-stubgen-script.py")
input_path = os.path.abspath("../x64/Release-3.7")	# the path to the EntityLibPy.pyd module
output_path = os.path.abspath("../x64")				# the path where stubgen will generate its output

# we need to add the EntityLibPy module's directory to PYTHONPATH so that stubgen can access it
os.environ["PYTHONPATH"] = f"{input_path};{os.environ['PYTHONPATH']}" if "PYTHONPATH" in os.environ else input_path
subprocess.run(f"{sys.executable} {stubgen_path} EntityLibPy -o {output_path}", encoding="oem", check=True)
print("stubgen done")


# stubgen's output isn't good enough for VsCode/Pylance, we'll need to unfuck it...

# read stubgen's output
with open(output_path + "/EntityLibPy-stubs/__init__.pyi", "r") as file:
	content = file.read()

import re
def replace_all(regex, subst):
	global content
	content = re.sub(regex, subst, content, 0, re.MULTILINE)

# replace 'typing.Bla' with just 'Bla' to make it less ugly
replace_all("import typing", "from typing import *")
replace_all("typing\.", "")

# for some reason DataType isn't self-referencing, fix it...
replace_all("import EntityLibPy", "#import EntityLibPy")
replace_all("EntityLibPy\.DataType", "DataType")
replace_all("EntityLibPy\.ActivationLevel", "ActivationLevel")

# remove docstring type comment (redundant, and conflicting!), eg:
#  		"""
# 		:type: Bla
#		"""
# --> replace with <pass>
# https://regex101.com/r/kNrvEp/1/
replace_all(r"^(\s*)\"\"\"\n^\s*:type:.*\n^\s*\"\"\"\n", "\\1pass\\n")

""" quoting forward references isn't necessary anymore after I removed the docstrings!
class_names = [
	"Color",
	"Component",
	"ComponentsSchema",
	"DataType",
	"Entity",
	"EntityLib",
	"EntityRef",
	"JsonValidation",
	"Node",
	"Scene",
	"Schema",
	"SubSceneComponent",
	"Subschema",
	"SubschemaRef",
]
for class_name in class_names:
	# replace direct type references with quoted references, to avoid forward-reference issues: https://www.python.org/dev/peps/pep-0484/#forward-references
	# https://regex101.com/r/9ZPXuN/1
	regex = r"(?<!class )\b%s\b(?!\")" % class_name	# matches a whole word, not preceded by <class >, and not followed by <"> (to avoid catching the __all__ array)
	subst = "'%s'" % class_name
	replace_all(regex, subst)
"""

print("reformat done")


# write back to a location that Pylance can parse: EntityLibPy.pyi side-by-side with each of the .pyd versions
try:
	with open(f"{output_path}/Release-3.7/EntityLibPy.pyi", "w") as file:
		file.write(content)
	print(f"EntityLibPy.pyi generated for version 3.7")
except:
	traceback.print_exc()

print("all done!")
