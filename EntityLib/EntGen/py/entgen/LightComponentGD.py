
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.LightType import *
from entgen.String import *
from entgen.Bool import *
from entgen.Color import *
from entgen.ComponentGD import *
from entgen.Float import *
from entgen.Vector3 import *

from EntityLibPy import Node

class LightComponentGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/LightComponentGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->LightComponentGD
        return LightComponentGD(entlib.load_node_file(sourcefile, entlib.get_schema(LightComponentGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->LightComponentGD
        return LightComponentGD(entlib.make_node(LightComponentGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AngleOffset(self):  # type: ()->Vector3
        return Vector3(self._node.at("AngleOffset"))
    @AngleOffset.setter
    def AngleOffset(self, val): self.AngleOffset.set(val)
    @property
    def Brightness(self):  # type: ()->Float
        return Float(self._node.at("Brightness"))
    @Brightness.setter
    def Brightness(self, val): self.Brightness.set(val)
    @property
    def CastShadow(self):  # type: ()->Bool
        return Bool(self._node.at("CastShadow"))
    @CastShadow.setter
    def CastShadow(self, val): self.CastShadow.set(val)
    @property
    def Color(self):  # type: ()->Color
        return Color(self._node.at("Color"))
    @Color.setter
    def Color(self, val): self.Color.set(val)
    @property
    def Direction(self):  # type: ()->Vector3
        return Vector3(self._node.at("Direction"))
    @Direction.setter
    def Direction(self, val): self.Direction.set(val)
    @property
    def Enabled(self):  # type: ()->Bool
        return Bool(self._node.at("Enabled"))
    @Enabled.setter
    def Enabled(self, val): self.Enabled.set(val)
    @property
    def LinearAttenuationStart(self):  # type: ()->Float
        return Float(self._node.at("LinearAttenuationStart"))
    @LinearAttenuationStart.setter
    def LinearAttenuationStart(self, val): self.LinearAttenuationStart.set(val)
    @property
    def LinearAttenuationStop(self):  # type: ()->Float
        return Float(self._node.at("LinearAttenuationStop"))
    @LinearAttenuationStop.setter
    def LinearAttenuationStop(self, val): self.LinearAttenuationStop.set(val)
    @property
    def Offset(self):  # type: ()->Vector3
        return Vector3(self._node.at("Offset"))
    @Offset.setter
    def Offset(self, val): self.Offset.set(val)
    @property
    def RadialAttenuationStart(self):  # type: ()->Float
        return Float(self._node.at("RadialAttenuationStart"))
    @RadialAttenuationStart.setter
    def RadialAttenuationStart(self, val): self.RadialAttenuationStart.set(val)
    @property
    def RadialAttenuationStop(self):  # type: ()->Float
        return Float(self._node.at("RadialAttenuationStop"))
    @RadialAttenuationStop.setter
    def RadialAttenuationStop(self, val): self.RadialAttenuationStop.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def Type_(self):  # type: ()->LightType
        return LightType(self._node.at("Type_"))
    @Type_.setter
    def Type_(self, val): self.Type_.set(val)
    @property
    def VolumetricFog(self):  # type: ()->Bool
        return Bool(self._node.at("VolumetricFog"))
    @VolumetricFog.setter
    def VolumetricFog(self, val): self.VolumetricFog.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




