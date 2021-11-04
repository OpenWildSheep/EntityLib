
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.EntityRef import *
from entgen.Float import *

from EntityLibPy import Node

class SpiritAnimalGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/SpiritAnimalGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->SpiritAnimalGD
        return SpiritAnimalGD(entlib.load_node_file(sourcefile, entlib.get_schema(SpiritAnimalGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->SpiritAnimalGD
        return SpiritAnimalGD(entlib.make_node(SpiritAnimalGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def DeadDurationBeforeRevive(self):  # type: ()->Float
        return Float(self._node.at("DeadDurationBeforeRevive"))
    @DeadDurationBeforeRevive.setter
    def DeadDurationBeforeRevive(self, val): self.DeadDurationBeforeRevive.set(val)
    @property
    def EntityRef(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("EntityRef"))
    @EntityRef.setter
    def EntityRef(self, val): self.EntityRef.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




