
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node

class ClassRef(HelperObject):
    schema_name = "ClassRef"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ClassRef
        return ClassRef(entlib.load_node_file(sourcefile, entlib.get_schema(ClassRef.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ClassRef
        return ClassRef(entlib.make_node(ClassRef.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    pass




