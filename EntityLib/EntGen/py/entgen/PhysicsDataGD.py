
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.ComponentGD import *
from entgen.EDITOR_Mesh import *
from entgen.sPhysicsJointDesc import *
from entgen.sRigidBodyDesc import *


class PhysicsDataGD(HelperObject):
    schema_name = "./MergedComponents.json#/definitions/PhysicsDataGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(PhysicsDataGD.schema_name))
    @property
    def EDITOR_Shapes(self): return (lambda n: Array(EDITOR_Mesh, n))(self._node.at("EDITOR_Shapes"))
    @property
    def EDITOR_isTrigger(self): return Bool(self._node.at("EDITOR_isTrigger"))
    @EDITOR_isTrigger.setter
    def EDITOR_isTrigger(self, val): self.EDITOR_isTrigger.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def joints(self): return (lambda n: Array(sPhysicsJointDesc, n))(self._node.at("joints"))
    @property
    def rigidBodies(self): return (lambda n: Array(sRigidBodyDesc, n))(self._node.at("rigidBodies"))
    pass




