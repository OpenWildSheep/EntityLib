
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *

from EntityLibPy import Node

class ConditionalRigidityAttribute_ActorStateName(HelperObject):
    schema_name = "ConditionalRigidityAttribute::ActorStateName"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ConditionalRigidityAttribute_ActorStateName
        return ConditionalRigidityAttribute_ActorStateName(entlib.load_node_file(sourcefile, entlib.get_schema(ConditionalRigidityAttribute_ActorStateName.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ConditionalRigidityAttribute_ActorStateName
        return ConditionalRigidityAttribute_ActorStateName(entlib.make_node(ConditionalRigidityAttribute_ActorStateName.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def ActionName(self):  # type: ()->String
        return String(self._node.at("ActionName"))
    @ActionName.setter
    def ActionName(self, val): self.ActionName.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




