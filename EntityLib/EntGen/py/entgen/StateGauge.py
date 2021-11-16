
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class StateGauge(HelperObject):
    schema_name = "StateGauge"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->StateGauge
        return StateGauge(entlib.load_node_file(sourcefile, entlib.get_schema(StateGauge.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->StateGauge
        return StateGauge(entlib.make_node(StateGauge.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def m_amount(self):  # type: ()->Float
        return Float(self._node.at("m_amount"))
    @m_amount.setter
    def m_amount(self, val): self.m_amount.set(val)
    @property
    def m_maxAmount(self):  # type: ()->Float
        return Float(self._node.at("m_maxAmount"))
    @m_maxAmount.setter
    def m_maxAmount(self, val): self.m_maxAmount.set(val)
    @property
    def m_pendingDiff(self):  # type: ()->Float
        return Float(self._node.at("m_pendingDiff"))
    @m_pendingDiff.setter
    def m_pendingDiff(self, val): self.m_pendingDiff.set(val)
    pass




