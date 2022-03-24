
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.TaggedSDF import *

from EntityLibPy import Node

class SensorVoxelsGD(HelperObject):
    schema_name = "SensorVoxelsGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->SensorVoxelsGD
        return SensorVoxelsGD(entlib.load_node_file(sourcefile, entlib.get_schema(SensorVoxelsGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->SensorVoxelsGD
        return SensorVoxelsGD(entlib.make_node(SensorVoxelsGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def TaggedSDFs(self):  # type: ()->Array[TaggedSDF]
        return (lambda n: Array(TaggedSDF, n))(self._node.at("TaggedSDFs"))
    @property
    def VoxelsDataPath(self):  # type: ()->String
        return String(self._node.at("VoxelsDataPath"))
    @VoxelsDataPath.setter
    def VoxelsDataPath(self, val): self.VoxelsDataPath.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




