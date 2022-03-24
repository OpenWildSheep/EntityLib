
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

from EntityLibPy import Node

class sPhysicShape(HelperObject):
    schema_name = "sPhysicShape"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->sPhysicShape
        return sPhysicShape(entlib.load_node_file(sourcefile, entlib.get_schema(sPhysicShape.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->sPhysicShape
        return sPhysicShape(entlib.make_node(sPhysicShape.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Box(self):  # type: ()->sPhysicsShapeBox
        return sPhysicsShapeBox(self._node.at("Box"))
    @property
    def Capsule(self):  # type: ()->sPhysicsShapeCapsule
        return sPhysicsShapeCapsule(self._node.at("Capsule"))
    @property
    def Cylinder(self):  # type: ()->sPhysicsShapeCylinder
        return sPhysicsShapeCylinder(self._node.at("Cylinder"))
    @property
    def Mesh(self):  # type: ()->sPhysicsShapeMesh
        return sPhysicsShapeMesh(self._node.at("Mesh"))
    @property
    def PhysicsMaterial(self):  # type: ()->String
        return String(self._node.at("PhysicsMaterial"))
    @PhysicsMaterial.setter
    def PhysicsMaterial(self, val): self.PhysicsMaterial.set(val)
    @property
    def Sphere(self):  # type: ()->sPhysicsShapeSphere
        return sPhysicsShapeSphere(self._node.at("Sphere"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def angles(self):  # type: ()->Vector3
        return Vector3(self._node.at("angles"))
    @angles.setter
    def angles(self, val): self.angles.set(val)
    @property
    def orientation(self):  # type: ()->Quat
        return Quat(self._node.at("orientation"))
    @orientation.setter
    def orientation(self, val): self.orientation.set(val)
    @property
    def scale(self):  # type: ()->Float
        return Float(self._node.at("scale"))
    @scale.setter
    def scale(self, val): self.scale.set(val)
    @property
    def translation(self):  # type: ()->Vector3
        return Vector3(self._node.at("translation"))
    @translation.setter
    def translation(self, val): self.translation.set(val)
    pass




