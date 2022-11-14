
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.EntityRef import *
from entgen.String import *
from entgen.ComponentGD import *
from entgen.EnergySideData import *
from entgen.EnergySide import *

from EntityLibPy import Node

class EnergySideSwitcherGD(HelperObject):
    schema_name = "EnergySideSwitcherGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EnergySideSwitcherGD
        return EnergySideSwitcherGD(entlib.load_node_file(sourcefile, entlib.get_schema(EnergySideSwitcherGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EnergySideSwitcherGD
        return EnergySideSwitcherGD(entlib.make_node(EnergySideSwitcherGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def EnergySideData(self):  # type: ()->Map[EnergySideEnum, EnergySideData]
        return (lambda n: Map(EnergySideEnum, EnergySideData, n))(self._node.at("EnergySideData"))
    @property
    def ReviveEnergyEntityRef(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("ReviveEnergyEntityRef"))
    @ReviveEnergyEntityRef.setter
    def ReviveEnergyEntityRef(self, val): self.ReviveEnergyEntityRef.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




