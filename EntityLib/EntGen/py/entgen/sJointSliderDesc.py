
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Vector2 import *
from entgen.Vector3 import *

from EntityLibPy import Node

class sJointSliderDesc(HelperObject):
    schema_name = "sJointSliderDesc"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->sJointSliderDesc
        return sJointSliderDesc(entlib.load_node_file(sourcefile, entlib.get_schema(sJointSliderDesc.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->sJointSliderDesc
        return sJointSliderDesc(entlib.make_node(sJointSliderDesc.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def direction(self):  # type: ()->Vector3
        return Vector3(self._node.at("direction"))
    @direction.setter
    def direction(self, val): self.direction.set(val)
    @property
    def distance(self):  # type: ()->Vector2
        return Vector2(self._node.at("distance"))
    @distance.setter
    def distance(self, val): self.distance.set(val)
    pass




