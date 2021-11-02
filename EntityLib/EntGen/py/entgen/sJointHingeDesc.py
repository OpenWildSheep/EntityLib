
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Vector2 import *
from entgen.Vector3 import *

from EntityLibPy import Node

class sJointHingeDesc(HelperObject):
    schema_name = "sJointHingeDesc"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->sJointHingeDesc
        return sJointHingeDesc(entlib.load_node_file(sourcefile, entlib.get_schema(sJointHingeDesc.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->sJointHingeDesc
        return sJointHingeDesc(entlib.make_node(sJointHingeDesc.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def angle(self):  # type: ()->Vector2
        return Vector2(self._node.at("angle"))
    @angle.setter
    def angle(self, val): self.angle.set(val)
    @property
    def axis(self):  # type: ()->Vector3
        return Vector3(self._node.at("axis"))
    @axis.setter
    def axis(self, val): self.axis.set(val)
    pass




