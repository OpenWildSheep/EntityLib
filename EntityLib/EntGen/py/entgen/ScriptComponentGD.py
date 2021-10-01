
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.ScriptPathAndDataSet import *
from entgen.String import *
from entgen.TypedValue import *
from entgen.String import *

from EntityLibPy import Node

class ScriptComponentGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ScriptComponentGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ScriptComponentGD
        return ScriptComponentGD(entlib.load_node_file(sourcefile, entlib.get_schema(ScriptComponentGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ScriptComponentGD
        return ScriptComponentGD(entlib.make_node(ScriptComponentGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def CommonDataMap(self):  # type: ()->Map[str, TypedValue]
        return (lambda n: Map(str, TypedValue, n))(self._node.at("CommonDataMap"))
    @property
    def ScriptsMap(self):  # type: ()->Map[str, ScriptPathAndDataSet]
        return (lambda n: Map(str, ScriptPathAndDataSet, n))(self._node.at("ScriptsMap"))
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




