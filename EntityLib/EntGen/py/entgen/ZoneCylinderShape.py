
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class ZoneCylinderShape(HelperObject):
    schema_name = "ZoneCylinderShape"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ZoneCylinderShape
        return ZoneCylinderShape(entlib.load_node_file(sourcefile, entlib.get_schema(ZoneCylinderShape.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ZoneCylinderShape
        return ZoneCylinderShape(entlib.make_node(ZoneCylinderShape.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def DistanceBetweenPoints(self):  # type: ()->Float
        return Float(self._node.at("DistanceBetweenPoints"))
    @DistanceBetweenPoints.setter
    def DistanceBetweenPoints(self, val): self.DistanceBetweenPoints.set(val)
    @property
    def Radius(self):  # type: ()->Float
        return Float(self._node.at("Radius"))
    @Radius.setter
    def Radius(self, val): self.Radius.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




