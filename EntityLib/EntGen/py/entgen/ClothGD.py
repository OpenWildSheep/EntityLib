
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ActorGD import *
from entgen.SoundEventMapping import *
from entgen.String import *

from EntityLibPy import Node

class ClothGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ClothGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ClothGD
        return ClothGD(entlib.load_node_file(sourcefile, entlib.get_schema(ClothGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ClothGD
        return ClothGD(entlib.make_node(ClothGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def BodyEventsPath(self):  # type: ()->String
        return String(self._node.at("BodyEventsPath"))
    @BodyEventsPath.setter
    def BodyEventsPath(self, val): self.BodyEventsPath.set(val)
    @property
    def BodyNamePath(self):  # type: ()->String
        return String(self._node.at("BodyNamePath"))
    @BodyNamePath.setter
    def BodyNamePath(self, val): self.BodyNamePath.set(val)
    @property
    def SoundBanks(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("SoundBanks"))
    @SoundBanks.setter
    def SoundBanks(self, val): self.SoundBanks.set(val)
    @property
    def SoundEventMappingRules(self):  # type: ()->SoundEventMapping
        return SoundEventMapping(self._node.at("SoundEventMappingRules"))
    @property
    def Super(self):  # type: ()->ActorGD
        return ActorGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




