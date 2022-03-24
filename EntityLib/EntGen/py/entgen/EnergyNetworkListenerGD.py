
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *

from EntityLibPy import Node

class EnergyNetworkListenerGD(HelperObject):
    schema_name = "EnergyNetworkListenerGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EnergyNetworkListenerGD
        return EnergyNetworkListenerGD(entlib.load_node_file(sourcefile, entlib.get_schema(EnergyNetworkListenerGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EnergyNetworkListenerGD
        return EnergyNetworkListenerGD(entlib.make_node(EnergyNetworkListenerGD.schema_name))
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




