
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.EntityRef import *

from EntityLibPy import Node

class MountableData(HelperObject):
    schema_name = "MountableData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->MountableData
        return MountableData(entlib.load_node_file(sourcefile, entlib.get_schema(MountableData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->MountableData
        return MountableData(entlib.make_node(MountableData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def HotspotID(self):  # type: ()->Int
        return Int(self._node.at("HotspotID"))
    @HotspotID.setter
    def HotspotID(self, val): self.HotspotID.set(val)
    @property
    def MountableEntity(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("MountableEntity"))
    @MountableEntity.setter
    def MountableEntity(self, val): self.MountableEntity.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




