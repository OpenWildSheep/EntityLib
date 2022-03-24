
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *

from EntityLibPy import Node

class EnergyPoolTaggerGD(HelperObject):
    schema_name = "EnergyPoolTaggerGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EnergyPoolTaggerGD
        return EnergyPoolTaggerGD(entlib.load_node_file(sourcefile, entlib.get_schema(EnergyPoolTaggerGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EnergyPoolTaggerGD
        return EnergyPoolTaggerGD(entlib.make_node(EnergyPoolTaggerGD.schema_name))
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




