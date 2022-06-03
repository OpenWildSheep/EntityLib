
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node

class TextureGroundTypeMap(HelperObject):
    schema_name = "TextureGroundTypeMap"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->TextureGroundTypeMap
        return TextureGroundTypeMap(entlib.load_node_file(sourcefile, entlib.get_schema(TextureGroundTypeMap.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->TextureGroundTypeMap
        return TextureGroundTypeMap(entlib.make_node(TextureGroundTypeMap.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    pass




