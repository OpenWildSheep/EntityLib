
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *

from EntityLibPy import Node

class RegenMeshBone(HelperObject):
    schema_name = "RegenMeshBone"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->RegenMeshBone
        return RegenMeshBone(entlib.load_node_file(sourcefile, entlib.get_schema(RegenMeshBone.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->RegenMeshBone
        return RegenMeshBone(entlib.make_node(RegenMeshBone.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def BoneName(self):  # type: ()->String
        return String(self._node.at("BoneName"))
    @BoneName.setter
    def BoneName(self, val): self.BoneName.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




