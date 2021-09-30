
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.ComponentGD import *
from entgen.VomitData import *
from entgen.String import *


class StaffVertebrasGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/StaffVertebrasGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(StaffVertebrasGD.schema_name))
    @property
    def HotspotNames(self): return (lambda n: PrimArray(String, n))(self._node.at("HotspotNames"))
    @HotspotNames.setter
    def HotspotNames(self, val): self.HotspotNames.set(val)
    @property
    def MaxVertebraCount(self): return Int(self._node.at("MaxVertebraCount"))
    @MaxVertebraCount.setter
    def MaxVertebraCount(self, val): self.MaxVertebraCount.set(val)
    @property
    def OwnedVertebraStartCount(self): return Int(self._node.at("OwnedVertebraStartCount"))
    @OwnedVertebraStartCount.setter
    def OwnedVertebraStartCount(self, val): self.OwnedVertebraStartCount.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def VertebraGRCPath1(self): return String(self._node.at("VertebraGRCPath1"))
    @VertebraGRCPath1.setter
    def VertebraGRCPath1(self, val): self.VertebraGRCPath1.set(val)
    @property
    def VertebraGRCPath2(self): return String(self._node.at("VertebraGRCPath2"))
    @VertebraGRCPath2.setter
    def VertebraGRCPath2(self, val): self.VertebraGRCPath2.set(val)
    @property
    def VertebraGRCPath3(self): return String(self._node.at("VertebraGRCPath3"))
    @VertebraGRCPath3.setter
    def VertebraGRCPath3(self, val): self.VertebraGRCPath3.set(val)
    @property
    def VertebraGRCPath4(self): return String(self._node.at("VertebraGRCPath4"))
    @VertebraGRCPath4.setter
    def VertebraGRCPath4(self, val): self.VertebraGRCPath4.set(val)
    @property
    def VomitData(self): return VomitData(self._node.at("VomitData"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




