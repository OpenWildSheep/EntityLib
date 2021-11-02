
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.sNodeBoneInfluenceDataTemplate import *

from EntityLibPy import Node

class PathBoneInfluenceGD(HelperObject):
    schema_name = "PathBoneInfluenceGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PathBoneInfluenceGD
        return PathBoneInfluenceGD(entlib.load_node_file(sourcefile, entlib.get_schema(PathBoneInfluenceGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PathBoneInfluenceGD
        return PathBoneInfluenceGD(entlib.make_node(PathBoneInfluenceGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Data(self):  # type: ()->Array[sNodeBoneInfluenceDataTemplate]
        return (lambda n: Array(sNodeBoneInfluenceDataTemplate, n))(self._node.at("Data"))
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




