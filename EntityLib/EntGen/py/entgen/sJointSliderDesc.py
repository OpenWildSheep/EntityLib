
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Vector2 import *
from entgen.Vector3 import *


class sJointSliderDesc(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/sJointSliderDesc"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(sJointSliderDesc.schema_name))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def direction(self): return Vector3(self._node.at("direction"))
    @direction.setter
    def direction(self, val): self.direction.set(val)
    @property
    def distance(self): return Vector2(self._node.at("distance"))
    @distance.setter
    def distance(self, val): self.distance.set(val)
    pass




