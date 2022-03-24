
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *

from EntityLibPy import Node

class AnimationGDData(HelperObject):
    schema_name = "AnimationGDData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AnimationGDData
        return AnimationGDData(entlib.load_node_file(sourcefile, entlib.get_schema(AnimationGDData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AnimationGDData
        return AnimationGDData(entlib.make_node(AnimationGDData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def animationDatabasePath(self):  # type: ()->String
        return String(self._node.at("animationDatabasePath"))
    @animationDatabasePath.setter
    def animationDatabasePath(self, val): self.animationDatabasePath.set(val)
    @property
    def skeletonPath(self):  # type: ()->String
        return String(self._node.at("skeletonPath"))
    @skeletonPath.setter
    def skeletonPath(self, val): self.skeletonPath.set(val)
    pass




