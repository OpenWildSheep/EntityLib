
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.EntityEnteredEntityState import *
from entgen.EntityExitedEntityState import *
from entgen.String import *

from EntityLibPy import Node

class PhysicsTriggerGD(HelperObject):
    schema_name = "PhysicsTriggerGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PhysicsTriggerGD
        return PhysicsTriggerGD(entlib.load_node_file(sourcefile, entlib.get_schema(PhysicsTriggerGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PhysicsTriggerGD
        return PhysicsTriggerGD(entlib.make_node(PhysicsTriggerGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def EntityEnteredEntityState(self):  # type: ()->EntityEnteredEntityState
        return EntityEnteredEntityState(self._node.at("EntityEnteredEntityState"))
    @property
    def EntityExitedEntityState(self):  # type: ()->EntityExitedEntityState
        return EntityExitedEntityState(self._node.at("EntityExitedEntityState"))
    @property
    def RequiredComponents(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("RequiredComponents"))
    @RequiredComponents.setter
    def RequiredComponents(self, val): self.RequiredComponents.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




