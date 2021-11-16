
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node

class ActorStateStack(HelperObject):
    schema_name = "ActorStateStack"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActorStateStack
        return ActorStateStack(entlib.load_node_file(sourcefile, entlib.get_schema(ActorStateStack.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActorStateStack
        return ActorStateStack(entlib.make_node(ActorStateStack.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    pass




