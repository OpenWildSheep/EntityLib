
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.ReviveSide import *
from entgen.String import *
from entgen.Int import *
from entgen.ComponentGD import *
from entgen.EntityRef import *
from entgen.String import *


class ShamanItemGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ShamanItemGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(ShamanItemGD.schema_name))
    @property
    def BoneNames(self): return (lambda n: PrimArray(String, n))(self._node.at("BoneNames"))
    @BoneNames.setter
    def BoneNames(self, val): self.BoneNames.set(val)
    @property
    def OppositeItemEntityRef(self): return EntityRef(self._node.at("OppositeItemEntityRef"))
    @OppositeItemEntityRef.setter
    def OppositeItemEntityRef(self, val): self.OppositeItemEntityRef.set(val)
    @property
    def ReviveSide(self): return ReviveSide(self._node.at("ReviveSide"))
    @ReviveSide.setter
    def ReviveSide(self, val): self.ReviveSide.set(val)
    @property
    def StartPartCount(self): return Int(self._node.at("StartPartCount"))
    @StartPartCount.setter
    def StartPartCount(self, val): self.StartPartCount.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




