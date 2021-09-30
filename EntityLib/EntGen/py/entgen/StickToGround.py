
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *


class StickToGround(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/StickToGround"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(StickToGround.schema_name))
    @property
    def BoneNameEnd(self): return String(self._node.at("BoneNameEnd"))
    @BoneNameEnd.setter
    def BoneNameEnd(self, val): self.BoneNameEnd.set(val)
    @property
    def BoneNameStart(self): return String(self._node.at("BoneNameStart"))
    @BoneNameStart.setter
    def BoneNameStart(self, val): self.BoneNameStart.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




