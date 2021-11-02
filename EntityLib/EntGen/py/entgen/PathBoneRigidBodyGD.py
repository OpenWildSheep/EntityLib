
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *

from EntityLibPy import Node

class PathBoneRigidBodyGD(HelperObject):
    schema_name = "PathBoneRigidBodyGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PathBoneRigidBodyGD
        return PathBoneRigidBodyGD(entlib.load_node_file(sourcefile, entlib.get_schema(PathBoneRigidBodyGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PathBoneRigidBodyGD
        return PathBoneRigidBodyGD(entlib.make_node(PathBoneRigidBodyGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




