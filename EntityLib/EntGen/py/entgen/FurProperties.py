
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.Float import *

from EntityLibPy import Node

class FurProperties(HelperObject):
    schema_name = "FurProperties"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->FurProperties
        return FurProperties(entlib.load_node_file(sourcefile, entlib.get_schema(FurProperties.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->FurProperties
        return FurProperties(entlib.make_node(FurProperties.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def FinsMaskUScale(self):  # type: ()->Float
        return Float(self._node.at("FinsMaskUScale"))
    @FinsMaskUScale.setter
    def FinsMaskUScale(self, val): self.FinsMaskUScale.set(val)
    @property
    def FinsTextureArrayIndex(self):  # type: ()->Int
        return Int(self._node.at("FinsTextureArrayIndex"))
    @FinsTextureArrayIndex.setter
    def FinsTextureArrayIndex(self, val): self.FinsTextureArrayIndex.set(val)
    @property
    def Roughness(self):  # type: ()->Float
        return Float(self._node.at("Roughness"))
    @Roughness.setter
    def Roughness(self, val): self.Roughness.set(val)
    @property
    def Stiffness(self):  # type: ()->Float
        return Float(self._node.at("Stiffness"))
    @Stiffness.setter
    def Stiffness(self, val): self.Stiffness.set(val)
    @property
    def Thickness(self):  # type: ()->Float
        return Float(self._node.at("Thickness"))
    @Thickness.setter
    def Thickness(self, val): self.Thickness.set(val)
    @property
    def Weight(self):  # type: ()->Float
        return Float(self._node.at("Weight"))
    @Weight.setter
    def Weight(self, val): self.Weight.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




