
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *

from EntityLibPy import Node

class HealerGD(HelperObject):
    schema_name = "HealerGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->HealerGD
        return HealerGD(entlib.load_node_file(sourcefile, entlib.get_schema(HealerGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->HealerGD
        return HealerGD(entlib.make_node(HealerGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




