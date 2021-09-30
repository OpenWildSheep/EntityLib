
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.TypedValue import *
from entgen.String import *
from entgen.ScriptPathAndDataSet import *


class ScriptPathAndDataSet(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ScriptPathAndDataSet"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(ScriptPathAndDataSet.schema_name))
    @property
    def AutoLaunch(self): return Bool(self._node.at("AutoLaunch"))
    @AutoLaunch.setter
    def AutoLaunch(self, val): self.AutoLaunch.set(val)
    @property
    def DataMap(self): return (lambda n: Map(str, TypedValue, n))(self._node.at("DataMap"))
    @property
    def NickName(self): return String(self._node.at("NickName"))
    @NickName.setter
    def NickName(self, val): self.NickName.set(val)
    @property
    def Path(self): return String(self._node.at("Path"))
    @Path.setter
    def Path(self, val): self.Path.set(val)
    @property
    def SpawnDataSets(self): return (lambda n: Array(ScriptPathAndDataSet, n))(self._node.at("SpawnDataSets"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




