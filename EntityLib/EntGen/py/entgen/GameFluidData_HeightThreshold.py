
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.HitStyle import *
from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class GameFluidData_HeightThreshold(HelperObject):
    schema_name = "GameFluidData::HeightThreshold"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->GameFluidData_HeightThreshold
        return GameFluidData_HeightThreshold(entlib.load_node_file(sourcefile, entlib.get_schema(GameFluidData_HeightThreshold.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->GameFluidData_HeightThreshold
        return GameFluidData_HeightThreshold(entlib.make_node(GameFluidData_HeightThreshold.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Damage(self):  # type: ()->Float
        return Float(self._node.at("Damage"))
    @Damage.setter
    def Damage(self, val): self.Damage.set(val)
    @property
    def Depth(self):  # type: ()->Float
        return Float(self._node.at("Depth"))
    @Depth.setter
    def Depth(self, val): self.Depth.set(val)
    @property
    def HitStyle(self):  # type: ()->HitStyle
        return HitStyle(self._node.at("HitStyle"))
    @HitStyle.setter
    def HitStyle(self, val): self.HitStyle.set(val)
    @property
    def Impact(self):  # type: ()->Float
        return Float(self._node.at("Impact"))
    @Impact.setter
    def Impact(self, val): self.Impact.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




