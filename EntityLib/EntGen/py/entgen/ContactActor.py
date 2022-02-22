
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node

class ContactActor(HelperObject):
    schema_name = "ContactActor"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ContactActor
        return ContactActor(entlib.load_node_file(sourcefile, entlib.get_schema(ContactActor.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ContactActor
        return ContactActor(entlib.make_node(ContactActor.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    pass




