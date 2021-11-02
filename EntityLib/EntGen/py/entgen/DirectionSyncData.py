
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.DirectionSync import *

from EntityLibPy import Node

class DirectionSyncData(HelperObject):
    schema_name = "DirectionSyncData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->DirectionSyncData
        return DirectionSyncData(entlib.load_node_file(sourcefile, entlib.get_schema(DirectionSyncData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->DirectionSyncData
        return DirectionSyncData(entlib.make_node(DirectionSyncData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def datas(self):  # type: ()->Array[DirectionSync]
        return (lambda n: Array(DirectionSync, n))(self._node.at("datas"))
    @property
    def name(self):  # type: ()->String
        return String(self._node.at("name"))
    @name.setter
    def name(self, val): self.name.set(val)
    pass




