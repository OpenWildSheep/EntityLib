
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.BehaviorTypedValue import *
from entgen.String import *
from entgen.ShootSequenceData import *

from EntityLibPy import Node

class BehaviorScriptData(HelperObject):
    schema_name = "BehaviorScriptData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->BehaviorScriptData
        return BehaviorScriptData(entlib.load_node_file(sourcefile, entlib.get_schema(BehaviorScriptData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->BehaviorScriptData
        return BehaviorScriptData(entlib.make_node(BehaviorScriptData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def DataMap(self):  # type: ()->Map[str, BehaviorTypedValue]
        return (lambda n: Map(str, BehaviorTypedValue, n))(self._node.at("DataMap"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def attackAggressivityDecrease(self):  # type: ()->Int
        return Int(self._node.at("attackAggressivityDecrease"))
    @attackAggressivityDecrease.setter
    def attackAggressivityDecrease(self, val): self.attackAggressivityDecrease.set(val)
    @property
    def hardFeelingsFriendlyHitCount(self):  # type: ()->Int
        return Int(self._node.at("hardFeelingsFriendlyHitCount"))
    @hardFeelingsFriendlyHitCount.setter
    def hardFeelingsFriendlyHitCount(self, val): self.hardFeelingsFriendlyHitCount.set(val)
    @property
    def hardFeelingsNotFriendlyHitCount(self):  # type: ()->Int
        return Int(self._node.at("hardFeelingsNotFriendlyHitCount"))
    @hardFeelingsNotFriendlyHitCount.setter
    def hardFeelingsNotFriendlyHitCount(self, val): self.hardFeelingsNotFriendlyHitCount.set(val)
    @property
    def panicAggressivityDecrease(self):  # type: ()->Int
        return Int(self._node.at("panicAggressivityDecrease"))
    @panicAggressivityDecrease.setter
    def panicAggressivityDecrease(self, val): self.panicAggressivityDecrease.set(val)
    @property
    def shootSequence(self):  # type: ()->Array[ShootSequenceData]
        return (lambda n: Array(ShootSequenceData, n))(self._node.at("shootSequence"))
    pass




