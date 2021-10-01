
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.ComponentGD import *
from entgen.EDITOR_Mesh import *
from entgen.sPhysicsJointDesc import *
from entgen.sRigidBodyDesc import *

from EntityLibPy import Node

class PhysicsDataGD(HelperObject):
    schema_name = "./MergedComponents.json#/definitions/PhysicsDataGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PhysicsDataGD
        return PhysicsDataGD(entlib.load_node_file(sourcefile, entlib.get_schema(PhysicsDataGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PhysicsDataGD
        return PhysicsDataGD(entlib.make_node(PhysicsDataGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def EDITOR_Shapes(self):  # type: ()->Array[EDITOR_Mesh]
        return (lambda n: Array(EDITOR_Mesh, n))(self._node.at("EDITOR_Shapes"))
    @property
    def EDITOR_isTrigger(self):  # type: ()->Bool
        return Bool(self._node.at("EDITOR_isTrigger"))
    @EDITOR_isTrigger.setter
    def EDITOR_isTrigger(self, val): self.EDITOR_isTrigger.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def joints(self):  # type: ()->Array[sPhysicsJointDesc]
        return (lambda n: Array(sPhysicsJointDesc, n))(self._node.at("joints"))
    @property
    def rigidBodies(self):  # type: ()->Array[sRigidBodyDesc]
        return (lambda n: Array(sRigidBodyDesc, n))(self._node.at("rigidBodies"))
    pass




