
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *
from entgen.Quat import *
from entgen.Vector3 import *
from entgen.sPhysicsShapeBox import *
from entgen.sPhysicsShapeCapsule import *
from entgen.sPhysicsShapeCylinder import *
from entgen.sPhysicsShapeMesh import *
from entgen.sPhysicsShapeSphere import *


class sPhysicShape(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/sPhysicShape"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(sPhysicShape.schema_name))
    @property
    def Box(self): return sPhysicsShapeBox(self._node.at("Box"))
    @property
    def Capsule(self): return sPhysicsShapeCapsule(self._node.at("Capsule"))
    @property
    def Cylinder(self): return sPhysicsShapeCylinder(self._node.at("Cylinder"))
    @property
    def Mesh(self): return sPhysicsShapeMesh(self._node.at("Mesh"))
    @property
    def PhysicsMaterial(self): return String(self._node.at("PhysicsMaterial"))
    @PhysicsMaterial.setter
    def PhysicsMaterial(self, val): self.PhysicsMaterial.set(val)
    @property
    def Sphere(self): return sPhysicsShapeSphere(self._node.at("Sphere"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def angles(self): return Vector3(self._node.at("angles"))
    @angles.setter
    def angles(self, val): self.angles.set(val)
    @property
    def orientation(self): return Quat(self._node.at("orientation"))
    @orientation.setter
    def orientation(self, val): self.orientation.set(val)
    @property
    def scale(self): return Float(self._node.at("scale"))
    @scale.setter
    def scale(self, val): self.scale.set(val)
    @property
    def translation(self): return Vector3(self._node.at("translation"))
    @translation.setter
    def translation(self, val): self.translation.set(val)
    pass




