
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *
from entgen.Vector3 import *
from entgen.EntityRef import *

from EntityLibPy import Node

class WallRunData(HelperObject):
    schema_name = "WallRunData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->WallRunData
        return WallRunData(entlib.load_node_file(sourcefile, entlib.get_schema(WallRunData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->WallRunData
        return WallRunData(entlib.make_node(WallRunData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def JumpAngle(self):  # type: ()->Float
        return Float(self._node.at("JumpAngle"))
    @JumpAngle.setter
    def JumpAngle(self, val): self.JumpAngle.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def moveDirection(self):  # type: ()->Vector3
        return Vector3(self._node.at("moveDirection"))
    @moveDirection.setter
    def moveDirection(self, val): self.moveDirection.set(val)
    @property
    def wallRunLinks(self):  # type: ()->PrimArray[EntityRef]
        return (lambda n: PrimArray(EntityRef, n))(self._node.at("wallRunLinks"))
    @wallRunLinks.setter
    def wallRunLinks(self, val): self.wallRunLinks.set(val)
    pass




