
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.GeometryStamper import *

from EntityLibPy import Node

class VolumeConstraintStamper(HelperObject):
    schema_name = "VolumeConstraintStamper"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->VolumeConstraintStamper
        return VolumeConstraintStamper(entlib.load_node_file(sourcefile, entlib.get_schema(VolumeConstraintStamper.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->VolumeConstraintStamper
        return VolumeConstraintStamper(entlib.make_node(VolumeConstraintStamper.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->GeometryStamper
        return GeometryStamper(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




