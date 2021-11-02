
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Vector2 import *

from EntityLibPy import Node

class sJointUniversalDesc(HelperObject):
    schema_name = "sJointUniversalDesc"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->sJointUniversalDesc
        return sJointUniversalDesc(entlib.load_node_file(sourcefile, entlib.get_schema(sJointUniversalDesc.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->sJointUniversalDesc
        return sJointUniversalDesc(entlib.make_node(sJointUniversalDesc.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def angleSwing1(self):  # type: ()->Vector2
        return Vector2(self._node.at("angleSwing1"))
    @angleSwing1.setter
    def angleSwing1(self, val): self.angleSwing1.set(val)
    @property
    def angleSwing2(self):  # type: ()->Vector2
        return Vector2(self._node.at("angleSwing2"))
    @angleSwing2.setter
    def angleSwing2(self, val): self.angleSwing2.set(val)
    pass




