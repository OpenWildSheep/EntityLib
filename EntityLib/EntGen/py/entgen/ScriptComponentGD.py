
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.ScriptPathAndDataSet import *
from entgen.String import *
from entgen.TypedValue import *
from entgen.String import *


class ScriptComponentGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ScriptComponentGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(ScriptComponentGD.schema_name))
    @property
    def CommonDataMap(self): return (lambda n: Map(str, TypedValue, n))(self._node.at("CommonDataMap"))
    @property
    def ScriptsMap(self): return (lambda n: Map(str, ScriptPathAndDataSet, n))(self._node.at("ScriptsMap"))
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




