
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node

class SceneNodeGraph(HelperObject):
    schema_name = "SceneNodeGraph"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->SceneNodeGraph
        return SceneNodeGraph(entlib.load_node_file(sourcefile, entlib.get_schema(SceneNodeGraph.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->SceneNodeGraph
        return SceneNodeGraph(entlib.make_node(SceneNodeGraph.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    pass




