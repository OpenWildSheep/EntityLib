
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node

class GVoxelVolumeCollection(HelperObject):
    schema_name = "GVoxelVolumeCollection"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->GVoxelVolumeCollection
        return GVoxelVolumeCollection(entlib.load_node_file(sourcefile, entlib.get_schema(GVoxelVolumeCollection.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->GVoxelVolumeCollection
        return GVoxelVolumeCollection(entlib.make_node(GVoxelVolumeCollection.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    pass




