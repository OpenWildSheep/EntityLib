
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.WaveRenderingType import *
from entgen.String import *
from entgen.Int import *
from entgen.Bool import *
from entgen.Float import *
from entgen.WaveRendererProperties import *

from EntityLibPy import Node

class WaveProperties(HelperObject):
    schema_name = "WaveProperties"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->WaveProperties
        return WaveProperties(entlib.load_node_file(sourcefile, entlib.get_schema(WaveProperties.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->WaveProperties
        return WaveProperties(entlib.make_node(WaveProperties.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Duration(self):  # type: ()->Float
        return Float(self._node.at("Duration"))
    @Duration.setter
    def Duration(self, val): self.Duration.set(val)
    @property
    def IntervalBetweenWaveFronts(self):  # type: ()->Float
        return Float(self._node.at("IntervalBetweenWaveFronts"))
    @IntervalBetweenWaveFronts.setter
    def IntervalBetweenWaveFronts(self, val): self.IntervalBetweenWaveFronts.set(val)
    @property
    def Looping(self):  # type: ()->Bool
        return Bool(self._node.at("Looping"))
    @Looping.setter
    def Looping(self, val): self.Looping.set(val)
    @property
    def Luminosity(self):  # type: ()->Float
        return Float(self._node.at("Luminosity"))
    @Luminosity.setter
    def Luminosity(self, val): self.Luminosity.set(val)
    @property
    def LuminosityCurvePath(self):  # type: ()->String
        return String(self._node.at("LuminosityCurvePath"))
    @LuminosityCurvePath.setter
    def LuminosityCurvePath(self, val): self.LuminosityCurvePath.set(val)
    @property
    def LuminosityVariability(self):  # type: ()->Float
        return Float(self._node.at("LuminosityVariability"))
    @LuminosityVariability.setter
    def LuminosityVariability(self, val): self.LuminosityVariability.set(val)
    @property
    def RenderingProperties(self):  # type: ()->Array[WaveRendererProperties]
        return (lambda n: Array(WaveRendererProperties, n))(self._node.at("RenderingProperties"))
    @property
    def RenderingType(self):  # type: ()->WaveRenderingType
        return WaveRenderingType(self._node.at("RenderingType"))
    @RenderingType.setter
    def RenderingType(self, val): self.RenderingType.set(val)
    @property
    def Width(self):  # type: ()->Int
        return Int(self._node.at("Width"))
    @Width.setter
    def Width(self, val): self.Width.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




