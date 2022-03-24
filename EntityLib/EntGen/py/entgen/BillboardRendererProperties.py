
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.BillboardCameraFacingQuadType import *
from entgen.BillboardRenderingAttribute import *
from entgen.BillboardRenderingSides import *
from entgen.String import *
from entgen.Int import *
from entgen.Vector3 import *
from entgen.String import *

from EntityLibPy import Node

class BillboardRendererProperties(HelperObject):
    schema_name = "BillboardRendererProperties"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->BillboardRendererProperties
        return BillboardRendererProperties(entlib.load_node_file(sourcefile, entlib.get_schema(BillboardRendererProperties.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->BillboardRendererProperties
        return BillboardRendererProperties(entlib.make_node(BillboardRendererProperties.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Attribute(self):  # type: ()->BillboardRenderingAttribute
        return BillboardRenderingAttribute(self._node.at("Attribute"))
    @Attribute.setter
    def Attribute(self, val): self.Attribute.set(val)
    @property
    def BillboardType(self):  # type: ()->BillboardCameraFacingQuadType
        return BillboardCameraFacingQuadType(self._node.at("BillboardType"))
    @BillboardType.setter
    def BillboardType(self, val): self.BillboardType.set(val)
    @property
    def ExtraMaterialPathArray(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("ExtraMaterialPathArray"))
    @ExtraMaterialPathArray.setter
    def ExtraMaterialPathArray(self, val): self.ExtraMaterialPathArray.set(val)
    @property
    def MaterialPath(self):  # type: ()->String
        return String(self._node.at("MaterialPath"))
    @MaterialPath.setter
    def MaterialPath(self, val): self.MaterialPath.set(val)
    @property
    def NbMeshInstances(self):  # type: ()->Int
        return Int(self._node.at("NbMeshInstances"))
    @NbMeshInstances.setter
    def NbMeshInstances(self, val): self.NbMeshInstances.set(val)
    @property
    def NbQuads(self):  # type: ()->Int
        return Int(self._node.at("NbQuads"))
    @NbQuads.setter
    def NbQuads(self, val): self.NbQuads.set(val)
    @property
    def Offset(self):  # type: ()->Vector3
        return Vector3(self._node.at("Offset"))
    @Offset.setter
    def Offset(self, val): self.Offset.set(val)
    @property
    def Sides(self):  # type: ()->BillboardRenderingSides
        return BillboardRenderingSides(self._node.at("Sides"))
    @Sides.setter
    def Sides(self, val): self.Sides.set(val)
    @property
    def VisualPath(self):  # type: ()->String
        return String(self._node.at("VisualPath"))
    @VisualPath.setter
    def VisualPath(self, val): self.VisualPath.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




