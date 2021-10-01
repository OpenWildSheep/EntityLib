
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class MountData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/MountData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->MountData
        return MountData(entlib.load_node_file(sourcefile, entlib.get_schema(MountData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->MountData
        return MountData(entlib.make_node(MountData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def acrobaticJumpDistance(self):  # type: ()->Float
        return Float(self._node.at("acrobaticJumpDistance"))
    @acrobaticJumpDistance.setter
    def acrobaticJumpDistance(self, val): self.acrobaticJumpDistance.set(val)
    @property
    def angle(self):  # type: ()->Float
        return Float(self._node.at("angle"))
    @angle.setter
    def angle(self, val): self.angle.set(val)
    @property
    def blindAngle(self):  # type: ()->Float
        return Float(self._node.at("blindAngle"))
    @blindAngle.setter
    def blindAngle(self, val): self.blindAngle.set(val)
    @property
    def distance(self):  # type: ()->Float
        return Float(self._node.at("distance"))
    @distance.setter
    def distance(self, val): self.distance.set(val)
    @property
    def offset(self):  # type: ()->Float
        return Float(self._node.at("offset"))
    @offset.setter
    def offset(self, val): self.offset.set(val)
    pass




