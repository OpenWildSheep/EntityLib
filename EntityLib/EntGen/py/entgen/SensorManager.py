
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.Manager import *

from EntityLibPy import Node

class SensorManager(HelperObject):
    schema_name = "SensorManager"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->SensorManager
        return SensorManager(entlib.load_node_file(sourcefile, entlib.get_schema(SensorManager.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->SensorManager
        return SensorManager(entlib.make_node(SensorManager.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def SensorPoolSize(self):  # type: ()->Int
        return Int(self._node.at("SensorPoolSize"))
    @SensorPoolSize.setter
    def SensorPoolSize(self, val): self.SensorPoolSize.set(val)
    @property
    def Super(self):  # type: ()->Manager
        return Manager(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




