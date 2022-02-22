
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.EnergyIntensity import *
from entgen.String import *
from entgen.Int import *
from entgen.Vector3 import *
from entgen.variant_ShapeSDF_ShapeSphere_ShapeBox_ import *

from EntityLibPy import Node

class EnergyPoolGD_EnergyArea(HelperObject):
    schema_name = "EnergyPoolGD::EnergyArea"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EnergyPoolGD_EnergyArea
        return EnergyPoolGD_EnergyArea(entlib.load_node_file(sourcefile, entlib.get_schema(EnergyPoolGD_EnergyArea.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EnergyPoolGD_EnergyArea
        return EnergyPoolGD_EnergyArea(entlib.make_node(EnergyPoolGD_EnergyArea.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Intensity(self):  # type: ()->EnergyIntensity
        return EnergyIntensity(self._node.at("Intensity"))
    @Intensity.setter
    def Intensity(self, val): self.Intensity.set(val)
    @property
    def Offset(self):  # type: ()->Vector3
        return Vector3(self._node.at("Offset"))
    @Offset.setter
    def Offset(self, val): self.Offset.set(val)
    @property
    def Priority(self):  # type: ()->Int
        return Int(self._node.at("Priority"))
    @Priority.setter
    def Priority(self, val): self.Priority.set(val)
    @property
    def Shape(self):  # type: ()->variant_ShapeSDF_ShapeSphere_ShapeBox_
        return variant_ShapeSDF_ShapeSphere_ShapeBox_(self._node.at("Shape"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




