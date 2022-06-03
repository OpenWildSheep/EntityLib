
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *

from EntityLibPy import Node

class SideMapGateGD(HelperObject):
    schema_name = "SideMapGateGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->SideMapGateGD
        return SideMapGateGD(entlib.load_node_file(sourcefile, entlib.get_schema(SideMapGateGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->SideMapGateGD
        return SideMapGateGD(entlib.make_node(SideMapGateGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def SideMapName(self):  # type: ()->String
        return String(self._node.at("SideMapName"))
    @SideMapName.setter
    def SideMapName(self, val): self.SideMapName.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




