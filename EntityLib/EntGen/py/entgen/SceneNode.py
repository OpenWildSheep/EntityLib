
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node

class SceneNode(HelperObject):
    schema_name = "SceneNode"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->SceneNode
        return SceneNode(entlib.load_node_file(sourcefile, entlib.get_schema(SceneNode.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->SceneNode
        return SceneNode(entlib.make_node(SceneNode.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    pass




