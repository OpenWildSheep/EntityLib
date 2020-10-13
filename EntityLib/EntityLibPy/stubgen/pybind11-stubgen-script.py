#!X:\Tools\Python37\python.exe
# EASY-INSTALL-ENTRY-SCRIPT: 'pybind11-stubgen==0.8.3','console_scripts','pybind11-stubgen'
__requires__ = 'pybind11-stubgen==0.8.3'
import re
import sys
from pkg_resources import load_entry_point

if __name__ == '__main__':
    sys.argv[0] = re.sub(r'(-script\.pyw?|\.exe)?$', '', sys.argv[0])
    sys.exit(
        load_entry_point('pybind11-stubgen==0.8.3', 'console_scripts', 'pybind11-stubgen')()
    )
