
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.ComponentGD import *
from entgen.Float import *
from entgen.String import *

from EntityLibPy import Node

class StaffVertebrasGD(HelperObject):
    schema_name = "StaffVertebrasGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->StaffVertebrasGD
        return StaffVertebrasGD(entlib.load_node_file(sourcefile, entlib.get_schema(StaffVertebrasGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->StaffVertebrasGD
        return StaffVertebrasGD(entlib.make_node(StaffVertebrasGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def BeginVertebraRefillThreshold(self):  # type: ()->Int
        return Int(self._node.at("BeginVertebraRefillThreshold"))
    @BeginVertebraRefillThreshold.setter
    def BeginVertebraRefillThreshold(self, val): self.BeginVertebraRefillThreshold.set(val)
    @property
    def EndVertebraRefillThreshold(self):  # type: ()->Int
        return Int(self._node.at("EndVertebraRefillThreshold"))
    @EndVertebraRefillThreshold.setter
    def EndVertebraRefillThreshold(self, val): self.EndVertebraRefillThreshold.set(val)
    @property
    def HotspotNames(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("HotspotNames"))
    @HotspotNames.setter
    def HotspotNames(self, val): self.HotspotNames.set(val)
    @property
    def MaxVertebraCount(self):  # type: ()->Int
        return Int(self._node.at("MaxVertebraCount"))
    @MaxVertebraCount.setter
    def MaxVertebraCount(self, val): self.MaxVertebraCount.set(val)
    @property
    def OwnedVertebraStartCount(self):  # type: ()->Int
        return Int(self._node.at("OwnedVertebraStartCount"))
    @OwnedVertebraStartCount.setter
    def OwnedVertebraStartCount(self, val): self.OwnedVertebraStartCount.set(val)
    @property
    def RefillVertebraTimer(self):  # type: ()->Float
        return Float(self._node.at("RefillVertebraTimer"))
    @RefillVertebraTimer.setter
    def RefillVertebraTimer(self, val): self.RefillVertebraTimer.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def VertebraGRCPath1(self):  # type: ()->String
        return String(self._node.at("VertebraGRCPath1"))
    @VertebraGRCPath1.setter
    def VertebraGRCPath1(self, val): self.VertebraGRCPath1.set(val)
    @property
    def VertebraGRCPath2(self):  # type: ()->String
        return String(self._node.at("VertebraGRCPath2"))
    @VertebraGRCPath2.setter
    def VertebraGRCPath2(self, val): self.VertebraGRCPath2.set(val)
    @property
    def VertebraGRCPath3(self):  # type: ()->String
        return String(self._node.at("VertebraGRCPath3"))
    @VertebraGRCPath3.setter
    def VertebraGRCPath3(self, val): self.VertebraGRCPath3.set(val)
    @property
    def VertebraGRCPath4(self):  # type: ()->String
        return String(self._node.at("VertebraGRCPath4"))
    @VertebraGRCPath4.setter
    def VertebraGRCPath4(self, val): self.VertebraGRCPath4.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




