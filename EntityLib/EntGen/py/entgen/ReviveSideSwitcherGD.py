
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.EntityRef import *
from entgen.ReviveSideData import *
from entgen.ReviveSide import *

from EntityLibPy import Node

class ReviveSideSwitcherGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ReviveSideSwitcherGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ReviveSideSwitcherGD
        return ReviveSideSwitcherGD(entlib.load_node_file(sourcefile, entlib.get_schema(ReviveSideSwitcherGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ReviveSideSwitcherGD
        return ReviveSideSwitcherGD(entlib.make_node(ReviveSideSwitcherGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def ReviveEnergyEntityRef(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("ReviveEnergyEntityRef"))
    @ReviveEnergyEntityRef.setter
    def ReviveEnergyEntityRef(self, val): self.ReviveEnergyEntityRef.set(val)
    @property
    def ReviveSideData(self):  # type: ()->Map[ReviveSideEnum, ReviveSideData]
        return (lambda n: Map(ReviveSideEnum, ReviveSideData, n))(self._node.at("ReviveSideData"))
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




