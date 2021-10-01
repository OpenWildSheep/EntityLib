
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node

class ActorState(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ActorState"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActorState
        return ActorState(entlib.load_node_file(sourcefile, entlib.get_schema(ActorState.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActorState
        return ActorState(entlib.make_node(ActorState.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    pass




