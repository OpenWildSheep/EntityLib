
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.InterpolationMethod import *
from entgen.TrailRenderingType import *
from entgen.TrailUVUnwrappingMode import *
from entgen.String import *
from entgen.Int import *
from entgen.Bool import *
from entgen.Float import *
from entgen.Vector2 import *
from entgen.Vector3 import *
from entgen.Int import *
from entgen.TrailRendererProperties import *

from EntityLibPy import Node

class TrailProperties(HelperObject):
    schema_name = "TrailProperties"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->TrailProperties
        return TrailProperties(entlib.load_node_file(sourcefile, entlib.get_schema(TrailProperties.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->TrailProperties
        return TrailProperties(entlib.make_node(TrailProperties.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def ComputeSplineCurvilinearUV(self):  # type: ()->Bool
        return Bool(self._node.at("ComputeSplineCurvilinearUV"))
    @ComputeSplineCurvilinearUV.setter
    def ComputeSplineCurvilinearUV(self, val): self.ComputeSplineCurvilinearUV.set(val)
    @property
    def Duration(self):  # type: ()->Float
        return Float(self._node.at("Duration"))
    @Duration.setter
    def Duration(self, val): self.Duration.set(val)
    @property
    def FadeLuminosity(self):  # type: ()->PrimArray[Int]
        return (lambda n: PrimArray(Int, n))(self._node.at("FadeLuminosity"))
    @FadeLuminosity.setter
    def FadeLuminosity(self, val): self.FadeLuminosity.set(val)
    @property
    def FadeSize(self):  # type: ()->PrimArray[Int]
        return (lambda n: PrimArray(Int, n))(self._node.at("FadeSize"))
    @FadeSize.setter
    def FadeSize(self, val): self.FadeSize.set(val)
    @property
    def FrontalAxis(self):  # type: ()->Vector3
        return Vector3(self._node.at("FrontalAxis"))
    @FrontalAxis.setter
    def FrontalAxis(self, val): self.FrontalAxis.set(val)
    @property
    def HorizontalAxis(self):  # type: ()->Vector3
        return Vector3(self._node.at("HorizontalAxis"))
    @HorizontalAxis.setter
    def HorizontalAxis(self, val): self.HorizontalAxis.set(val)
    @property
    def InterpolationMethod(self):  # type: ()->InterpolationMethod
        return InterpolationMethod(self._node.at("InterpolationMethod"))
    @InterpolationMethod.setter
    def InterpolationMethod(self, val): self.InterpolationMethod.set(val)
    @property
    def IntervalBetweenTrailPoints(self):  # type: ()->Float
        return Float(self._node.at("IntervalBetweenTrailPoints"))
    @IntervalBetweenTrailPoints.setter
    def IntervalBetweenTrailPoints(self, val): self.IntervalBetweenTrailPoints.set(val)
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
    def NbSplinePointsBetweenTrailPoints(self):  # type: ()->Int
        return Int(self._node.at("NbSplinePointsBetweenTrailPoints"))
    @NbSplinePointsBetweenTrailPoints.setter
    def NbSplinePointsBetweenTrailPoints(self, val): self.NbSplinePointsBetweenTrailPoints.set(val)
    @property
    def RenderingProperties(self):  # type: ()->Array[TrailRendererProperties]
        return (lambda n: Array(TrailRendererProperties, n))(self._node.at("RenderingProperties"))
    @property
    def RenderingType(self):  # type: ()->TrailRenderingType
        return TrailRenderingType(self._node.at("RenderingType"))
    @RenderingType.setter
    def RenderingType(self, val): self.RenderingType.set(val)
    @property
    def Size(self):  # type: ()->Vector2
        return Vector2(self._node.at("Size"))
    @Size.setter
    def Size(self, val): self.Size.set(val)
    @property
    def SizeCurvePath(self):  # type: ()->String
        return String(self._node.at("SizeCurvePath"))
    @SizeCurvePath.setter
    def SizeCurvePath(self, val): self.SizeCurvePath.set(val)
    @property
    def SizeVariability(self):  # type: ()->Vector2
        return Vector2(self._node.at("SizeVariability"))
    @SizeVariability.setter
    def SizeVariability(self, val): self.SizeVariability.set(val)
    @property
    def TrimTransparentPoints(self):  # type: ()->Bool
        return Bool(self._node.at("TrimTransparentPoints"))
    @TrimTransparentPoints.setter
    def TrimTransparentPoints(self, val): self.TrimTransparentPoints.set(val)
    @property
    def UVUnwrappingMode(self):  # type: ()->TrailUVUnwrappingMode
        return TrailUVUnwrappingMode(self._node.at("UVUnwrappingMode"))
    @UVUnwrappingMode.setter
    def UVUnwrappingMode(self, val): self.UVUnwrappingMode.set(val)
    @property
    def UVZoomCurvilinearCurvePath(self):  # type: ()->String
        return String(self._node.at("UVZoomCurvilinearCurvePath"))
    @UVZoomCurvilinearCurvePath.setter
    def UVZoomCurvilinearCurvePath(self, val): self.UVZoomCurvilinearCurvePath.set(val)
    @property
    def VerticalAxis(self):  # type: ()->Vector3
        return Vector3(self._node.at("VerticalAxis"))
    @VerticalAxis.setter
    def VerticalAxis(self, val): self.VerticalAxis.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




