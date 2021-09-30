
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *


class StateGauge(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/StateGauge"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(StateGauge.schema_name))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def m_amount(self): return Float(self._node.at("m_amount"))
    @m_amount.setter
    def m_amount(self, val): self.m_amount.set(val)
    @property
    def m_maxAmount(self): return Float(self._node.at("m_maxAmount"))
    @m_maxAmount.setter
    def m_maxAmount(self, val): self.m_maxAmount.set(val)
    @property
    def m_pendingDiff(self): return Float(self._node.at("m_pendingDiff"))
    @m_pendingDiff.setter
    def m_pendingDiff(self, val): self.m_pendingDiff.set(val)
    pass




