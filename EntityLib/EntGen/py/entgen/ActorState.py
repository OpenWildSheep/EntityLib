
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy



class ActorState(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ActorState"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(ActorState.schema_name))
    pass




