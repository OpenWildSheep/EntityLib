
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Manager import *
from entgen.Int import *
from entgen.AIOrderType import *
from entgen.AIAggroInitAndDecValue import *

from EntityLibPy import Node

class AIKnowledgeManager(HelperObject):
    schema_name = "AIKnowledgeManager"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AIKnowledgeManager
        return AIKnowledgeManager(entlib.load_node_file(sourcefile, entlib.get_schema(AIKnowledgeManager.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AIKnowledgeManager
        return AIKnowledgeManager(entlib.make_node(AIKnowledgeManager.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AggroValues(self):  # type: ()->Array[AIAggroInitAndDecValue]
        return (lambda n: Array(AIAggroInitAndDecValue, n))(self._node.at("AggroValues"))
    @property
    def OrderPriorities(self):  # type: ()->Map[AIOrderTypeEnum, Int]
        return (lambda n: Map(AIOrderTypeEnum, Int, n))(self._node.at("OrderPriorities"))
    @property
    def Super(self):  # type: ()->Manager
        return Manager(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




