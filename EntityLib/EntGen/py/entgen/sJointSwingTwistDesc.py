
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Vector2 import *

from EntityLibPy import Node

class sJointSwingTwistDesc(HelperObject):
    schema_name = "sJointSwingTwistDesc"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->sJointSwingTwistDesc
        return sJointSwingTwistDesc(entlib.load_node_file(sourcefile, entlib.get_schema(sJointSwingTwistDesc.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->sJointSwingTwistDesc
        return sJointSwingTwistDesc(entlib.make_node(sJointSwingTwistDesc.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def swingAngle(self):  # type: ()->Vector2
        return Vector2(self._node.at("swingAngle"))
    @swingAngle.setter
    def swingAngle(self, val): self.swingAngle.set(val)
    @property
    def twistAngle(self):  # type: ()->Vector2
        return Vector2(self._node.at("twistAngle"))
    @twistAngle.setter
    def twistAngle(self, val): self.twistAngle.set(val)
    pass




