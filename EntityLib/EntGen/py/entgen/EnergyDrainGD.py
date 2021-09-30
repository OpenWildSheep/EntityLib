
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.EntityRef import *


class EnergyDrainGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/EnergyDrainGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(EnergyDrainGD.schema_name))
    @property
    def PoolEntityRef(self): return EntityRef(self._node.at("PoolEntityRef"))
    @PoolEntityRef.setter
    def PoolEntityRef(self, val): self.PoolEntityRef.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




