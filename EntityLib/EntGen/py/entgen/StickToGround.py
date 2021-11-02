
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *

from EntityLibPy import Node

class StickToGround(HelperObject):
    schema_name = "StickToGround"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->StickToGround
        return StickToGround(entlib.load_node_file(sourcefile, entlib.get_schema(StickToGround.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->StickToGround
        return StickToGround(entlib.make_node(StickToGround.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def BoneNameEnd(self):  # type: ()->String
        return String(self._node.at("BoneNameEnd"))
    @BoneNameEnd.setter
    def BoneNameEnd(self, val): self.BoneNameEnd.set(val)
    @property
    def BoneNameStart(self):  # type: ()->String
        return String(self._node.at("BoneNameStart"))
    @BoneNameStart.setter
    def BoneNameStart(self, val): self.BoneNameStart.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




