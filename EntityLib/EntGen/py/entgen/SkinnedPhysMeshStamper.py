
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.GeometryStamper import *

from EntityLibPy import Node

class SkinnedPhysMeshStamper(HelperObject):
    schema_name = "SkinnedPhysMeshStamper"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->SkinnedPhysMeshStamper
        return SkinnedPhysMeshStamper(entlib.load_node_file(sourcefile, entlib.get_schema(SkinnedPhysMeshStamper.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->SkinnedPhysMeshStamper
        return SkinnedPhysMeshStamper(entlib.make_node(SkinnedPhysMeshStamper.schema_name))
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




