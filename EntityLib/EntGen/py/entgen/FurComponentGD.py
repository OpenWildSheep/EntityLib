
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.FurProperties import *

from EntityLibPy import Node

class FurComponentGD(HelperObject):
    schema_name = "FurComponentGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->FurComponentGD
        return FurComponentGD(entlib.load_node_file(sourcefile, entlib.get_schema(FurComponentGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->FurComponentGD
        return FurComponentGD(entlib.make_node(FurComponentGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Properties(self):  # type: ()->FurProperties
        return FurProperties(self._node.at("Properties"))
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




