
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.RegenMeshBone import *

from EntityLibPy import Node

class RegenMeshBoneNeighbours(HelperObject):
    schema_name = "RegenMeshBoneNeighbours"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->RegenMeshBoneNeighbours
        return RegenMeshBoneNeighbours(entlib.load_node_file(sourcefile, entlib.get_schema(RegenMeshBoneNeighbours.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->RegenMeshBoneNeighbours
        return RegenMeshBoneNeighbours(entlib.make_node(RegenMeshBoneNeighbours.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def BoneName(self):  # type: ()->String
        return String(self._node.at("BoneName"))
    @BoneName.setter
    def BoneName(self, val): self.BoneName.set(val)
    @property
    def Neighbours(self):  # type: ()->Array[RegenMeshBone]
        return (lambda n: Array(RegenMeshBone, n))(self._node.at("Neighbours"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




