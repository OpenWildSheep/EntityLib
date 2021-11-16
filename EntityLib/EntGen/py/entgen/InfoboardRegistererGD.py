
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *

from EntityLibPy import Node

class InfoboardRegistererGD(HelperObject):
    schema_name = "InfoboardRegistererGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->InfoboardRegistererGD
        return InfoboardRegistererGD(entlib.load_node_file(sourcefile, entlib.get_schema(InfoboardRegistererGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->InfoboardRegistererGD
        return InfoboardRegistererGD(entlib.make_node(InfoboardRegistererGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def InfoboardName(self):  # type: ()->String
        return String(self._node.at("InfoboardName"))
    @InfoboardName.setter
    def InfoboardName(self, val): self.InfoboardName.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




