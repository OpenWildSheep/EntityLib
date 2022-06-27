
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.EntityRef import *
from entgen.Float import *
from entgen.Vector3 import *
from entgen.EntityRef import *
from entgen.EntityRef import *
from entgen.String import *

from EntityLibPy import Node

class StreamableUnitGD(HelperObject):
    schema_name = "StreamableUnitGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->StreamableUnitGD
        return StreamableUnitGD(entlib.load_node_file(sourcefile, entlib.get_schema(StreamableUnitGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->StreamableUnitGD
        return StreamableUnitGD(entlib.make_node(StreamableUnitGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def BaseImpostor(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("BaseImpostor"))
    @BaseImpostor.setter
    def BaseImpostor(self, val): self.BaseImpostor.set(val)
    @property
    def BoxSize(self):  # type: ()->Vector3
        return Vector3(self._node.at("BoxSize"))
    @BoxSize.setter
    def BoxSize(self, val): self.BoxSize.set(val)
    @property
    def CenterOffset(self):  # type: ()->Vector3
        return Vector3(self._node.at("CenterOffset"))
    @CenterOffset.setter
    def CenterOffset(self, val): self.CenterOffset.set(val)
    @property
    def EnergyPool(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("EnergyPool"))
    @EnergyPool.setter
    def EnergyPool(self, val): self.EnergyPool.set(val)
    @property
    def FullEntities(self):  # type: ()->PrimArray[EntityRef]
        return (lambda n: PrimArray(EntityRef, n))(self._node.at("FullEntities"))
    @FullEntities.setter
    def FullEntities(self, val): self.FullEntities.set(val)
    @property
    def FullEntitiesHolder(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("FullEntitiesHolder"))
    @FullEntitiesHolder.setter
    def FullEntitiesHolder(self, val): self.FullEntitiesHolder.set(val)
    @property
    def Hysteresis(self):  # type: ()->Float
        return Float(self._node.at("Hysteresis"))
    @Hysteresis.setter
    def Hysteresis(self, val): self.Hysteresis.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def VariantImpostors(self):  # type: ()->Map[str, EntityRef]
        return (lambda n: Map(str, EntityRef, n))(self._node.at("VariantImpostors"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




