
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.TrailRenderingAttribute import *
from entgen.TrailRenderingSides import *
from entgen.String import *
from entgen.Int import *
from entgen.Float import *
from entgen.Vector2 import *
from entgen.Vector3 import *

from EntityLibPy import Node

class TrailRendererProperties(HelperObject):
    schema_name = "TrailRendererProperties"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->TrailRendererProperties
        return TrailRendererProperties(entlib.load_node_file(sourcefile, entlib.get_schema(TrailRendererProperties.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->TrailRendererProperties
        return TrailRendererProperties(entlib.make_node(TrailRendererProperties.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Attribute(self):  # type: ()->TrailRenderingAttribute
        return TrailRenderingAttribute(self._node.at("Attribute"))
    @Attribute.setter
    def Attribute(self, val): self.Attribute.set(val)
    @property
    def MaterialPath(self):  # type: ()->String
        return String(self._node.at("MaterialPath"))
    @MaterialPath.setter
    def MaterialPath(self, val): self.MaterialPath.set(val)
    @property
    def MeshPath(self):  # type: ()->String
        return String(self._node.at("MeshPath"))
    @MeshPath.setter
    def MeshPath(self, val): self.MeshPath.set(val)
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
    def NbTrailPointsBetweenFrontQuads(self):  # type: ()->Int
        return Int(self._node.at("NbTrailPointsBetweenFrontQuads"))
    @NbTrailPointsBetweenFrontQuads.setter
    def NbTrailPointsBetweenFrontQuads(self, val): self.NbTrailPointsBetweenFrontQuads.set(val)
    @property
    def NbVertices(self):  # type: ()->Int
        return Int(self._node.at("NbVertices"))
    @NbVertices.setter
    def NbVertices(self, val): self.NbVertices.set(val)
    @property
    def Offset(self):  # type: ()->Vector3
        return Vector3(self._node.at("Offset"))
    @Offset.setter
    def Offset(self, val): self.Offset.set(val)
    @property
    def RandomAxialRotationAmplitude(self):  # type: ()->Vector2
        return Vector2(self._node.at("RandomAxialRotationAmplitude"))
    @RandomAxialRotationAmplitude.setter
    def RandomAxialRotationAmplitude(self, val): self.RandomAxialRotationAmplitude.set(val)
    @property
    def RandomUVOffset(self):  # type: ()->Float
        return Float(self._node.at("RandomUVOffset"))
    @RandomUVOffset.setter
    def RandomUVOffset(self, val): self.RandomUVOffset.set(val)
    @property
    def Sides(self):  # type: ()->TrailRenderingSides
        return TrailRenderingSides(self._node.at("Sides"))
    @Sides.setter
    def Sides(self, val): self.Sides.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




