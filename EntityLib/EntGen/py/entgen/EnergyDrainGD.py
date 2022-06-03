
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.EntityRef import *

from EntityLibPy import Node

class EnergyDrainGD(HelperObject):
    schema_name = "EnergyDrainGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EnergyDrainGD
        return EnergyDrainGD(entlib.load_node_file(sourcefile, entlib.get_schema(EnergyDrainGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EnergyDrainGD
        return EnergyDrainGD(entlib.make_node(EnergyDrainGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def PoolEntityRef(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("PoolEntityRef"))
    @PoolEntityRef.setter
    def PoolEntityRef(self, val): self.PoolEntityRef.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




