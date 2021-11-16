
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.BillboardRenderingType import *
from entgen.String import *
from entgen.Bool import *
from entgen.Float import *
from entgen.Vector3 import *
from entgen.BillboardRendererProperties import *

from EntityLibPy import Node

class BillboardProperties(HelperObject):
    schema_name = "BillboardProperties"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->BillboardProperties
        return BillboardProperties(entlib.load_node_file(sourcefile, entlib.get_schema(BillboardProperties.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->BillboardProperties
        return BillboardProperties(entlib.make_node(BillboardProperties.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Duration(self):  # type: ()->Float
        return Float(self._node.at("Duration"))
    @Duration.setter
    def Duration(self, val): self.Duration.set(val)
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
    def RenderingProperties(self):  # type: ()->Array[BillboardRendererProperties]
        return (lambda n: Array(BillboardRendererProperties, n))(self._node.at("RenderingProperties"))
    @property
    def RenderingType(self):  # type: ()->BillboardRenderingType
        return BillboardRenderingType(self._node.at("RenderingType"))
    @RenderingType.setter
    def RenderingType(self, val): self.RenderingType.set(val)
    @property
    def Size(self):  # type: ()->Vector3
        return Vector3(self._node.at("Size"))
    @Size.setter
    def Size(self, val): self.Size.set(val)
    @property
    def SizeCurvePath(self):  # type: ()->String
        return String(self._node.at("SizeCurvePath"))
    @SizeCurvePath.setter
    def SizeCurvePath(self, val): self.SizeCurvePath.set(val)
    @property
    def SizeVariability(self):  # type: ()->Vector3
        return Vector3(self._node.at("SizeVariability"))
    @SizeVariability.setter
    def SizeVariability(self, val): self.SizeVariability.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




