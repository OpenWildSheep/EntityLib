
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.EntityRef import *
from entgen.ReviveSideData import *
from entgen.ReviveSide import *


class ReviveSideSwitcherGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ReviveSideSwitcherGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(ReviveSideSwitcherGD.schema_name))
    @property
    def ReviveEnergyEntityRef(self): return EntityRef(self._node.at("ReviveEnergyEntityRef"))
    @ReviveEnergyEntityRef.setter
    def ReviveEnergyEntityRef(self, val): self.ReviveEnergyEntityRef.set(val)
    @property
    def ReviveSideData(self): return (lambda n: Map(ReviveSideEnum, ReviveSideData, n))(self._node.at("ReviveSideData"))
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




