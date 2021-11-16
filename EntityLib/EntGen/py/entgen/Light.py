
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.LightType import *
from entgen.String import *
from entgen.Bool import *
from entgen.Float import *
from entgen.Vector3 import *

from EntityLibPy import Node

class Light(HelperObject):
    schema_name = "Light"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->Light
        return Light(entlib.load_node_file(sourcefile, entlib.get_schema(Light.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->Light
        return Light(entlib.make_node(Light.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Brightness(self):  # type: ()->Float
        return Float(self._node.at("Brightness"))
    @Brightness.setter
    def Brightness(self, val): self.Brightness.set(val)
    @property
    def Cast_Shadows(self):  # type: ()->Bool
        return Bool(self._node.at("Cast Shadows"))
    @Cast_Shadows.setter
    def Cast_Shadows(self, val): self.Cast_Shadows.set(val)
    @property
    def Color(self):  # type: ()->Vector3
        return Vector3(self._node.at("Color"))
    @Color.setter
    def Color(self, val): self.Color.set(val)
    @property
    def Dpsm_Plane_Threshold(self):  # type: ()->Float
        return Float(self._node.at("Dpsm Plane Threshold"))
    @Dpsm_Plane_Threshold.setter
    def Dpsm_Plane_Threshold(self, val): self.Dpsm_Plane_Threshold.set(val)
    @property
    def Dpsm_Seam_Offset(self):  # type: ()->Float
        return Float(self._node.at("Dpsm Seam Offset"))
    @Dpsm_Seam_Offset.setter
    def Dpsm_Seam_Offset(self, val): self.Dpsm_Seam_Offset.set(val)
    @property
    def Enabled(self):  # type: ()->Bool
        return Bool(self._node.at("Enabled"))
    @Enabled.setter
    def Enabled(self, val): self.Enabled.set(val)
    @property
    def Linear_attenuation_start(self):  # type: ()->Float
        return Float(self._node.at("Linear attenuation start"))
    @Linear_attenuation_start.setter
    def Linear_attenuation_start(self, val): self.Linear_attenuation_start.set(val)
    @property
    def Linear_attenuation_stop(self):  # type: ()->Float
        return Float(self._node.at("Linear attenuation stop"))
    @Linear_attenuation_stop.setter
    def Linear_attenuation_stop(self, val): self.Linear_attenuation_stop.set(val)
    @property
    def Radial_attenuation_start(self):  # type: ()->Float
        return Float(self._node.at("Radial attenuation start"))
    @Radial_attenuation_start.setter
    def Radial_attenuation_start(self, val): self.Radial_attenuation_start.set(val)
    @property
    def Radial_attenuation_stop(self):  # type: ()->Float
        return Float(self._node.at("Radial attenuation stop"))
    @Radial_attenuation_stop.setter
    def Radial_attenuation_stop(self, val): self.Radial_attenuation_stop.set(val)
    @property
    def Shadow_Depth_Bias(self):  # type: ()->Float
        return Float(self._node.at("Shadow Depth Bias"))
    @Shadow_Depth_Bias.setter
    def Shadow_Depth_Bias(self, val): self.Shadow_Depth_Bias.set(val)
    @property
    def Shadow_Depth_Bias_Factor(self):  # type: ()->Float
        return Float(self._node.at("Shadow Depth Bias Factor"))
    @Shadow_Depth_Bias_Factor.setter
    def Shadow_Depth_Bias_Factor(self, val): self.Shadow_Depth_Bias_Factor.set(val)
    @property
    def Type_(self):  # type: ()->LightType
        return LightType(self._node.at("Type"))
    @Type_.setter
    def Type_(self, val): self.Type_.set(val)
    @property
    def Volumetric_Fog(self):  # type: ()->Bool
        return Bool(self._node.at("Volumetric Fog"))
    @Volumetric_Fog.setter
    def Volumetric_Fog(self, val): self.Volumetric_Fog.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




