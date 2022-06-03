
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *
from entgen.Manager import *

from EntityLibPy import Node

class WaterManager(HelperObject):
    schema_name = "WaterManager"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->WaterManager
        return WaterManager(entlib.load_node_file(sourcefile, entlib.get_schema(WaterManager.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->WaterManager
        return WaterManager(entlib.make_node(WaterManager.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->Manager
        return Manager(self._node.at("Super"))
    @property
    def WaterHeight(self):  # type: ()->Float
        return Float(self._node.at("WaterHeight"))
    @WaterHeight.setter
    def WaterHeight(self, val): self.WaterHeight.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




