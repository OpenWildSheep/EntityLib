
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.AnimAdditionalTag import *
from entgen.String import *
from entgen.FloatRange import *

from EntityLibPy import Node

class StrongAttackChargedData(HelperObject):
    schema_name = "StrongAttackChargedData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->StrongAttackChargedData
        return StrongAttackChargedData(entlib.load_node_file(sourcefile, entlib.get_schema(StrongAttackChargedData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->StrongAttackChargedData
        return StrongAttackChargedData(entlib.make_node(StrongAttackChargedData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AnimationTag(self):  # type: ()->AnimAdditionalTag
        return AnimAdditionalTag(self._node.at("AnimationTag"))
    @AnimationTag.setter
    def AnimationTag(self, val): self.AnimationTag.set(val)
    @property
    def ChargeRatio(self):  # type: ()->FloatRange
        return FloatRange(self._node.at("ChargeRatio"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




