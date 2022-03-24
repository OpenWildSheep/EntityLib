
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node

class TextureHeightMap(HelperObject):
    schema_name = "TextureHeightMap"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->TextureHeightMap
        return TextureHeightMap(entlib.load_node_file(sourcefile, entlib.get_schema(TextureHeightMap.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->TextureHeightMap
        return TextureHeightMap(entlib.make_node(TextureHeightMap.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    pass




