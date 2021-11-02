
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.RegenMeshBoneNeighbours import *

from EntityLibPy import Node

class RegenMeshBonesNeighbourHood(HelperObject):
    schema_name = "RegenMeshBonesNeighbourHood"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->RegenMeshBonesNeighbourHood
        return RegenMeshBonesNeighbourHood(entlib.load_node_file(sourcefile, entlib.get_schema(RegenMeshBonesNeighbourHood.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->RegenMeshBonesNeighbourHood
        return RegenMeshBonesNeighbourHood(entlib.make_node(RegenMeshBonesNeighbourHood.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Bones(self):  # type: ()->Array[RegenMeshBoneNeighbours]
        return (lambda n: Array(RegenMeshBoneNeighbours, n))(self._node.at("Bones"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




