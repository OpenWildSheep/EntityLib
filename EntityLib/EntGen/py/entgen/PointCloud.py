
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node

class PointCloud(HelperObject):
    schema_name = "PointCloud"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PointCloud
        return PointCloud(entlib.load_node_file(sourcefile, entlib.get_schema(PointCloud.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PointCloud
        return PointCloud(entlib.make_node(PointCloud.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    pass




