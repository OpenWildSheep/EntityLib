
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Manager import *
from entgen.FactionData import *
from entgen.FactionRelationData import *
from entgen.FactionSpecieRelationData import *

from EntityLibPy import Node

class FactionManager(HelperObject):
    schema_name = "FactionManager"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->FactionManager
        return FactionManager(entlib.load_node_file(sourcefile, entlib.get_schema(FactionManager.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->FactionManager
        return FactionManager(entlib.make_node(FactionManager.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def FactionSpecieRelations(self):  # type: ()->Array[FactionSpecieRelationData]
        return (lambda n: Array(FactionSpecieRelationData, n))(self._node.at("FactionSpecieRelations"))
    @property
    def Factions(self):  # type: ()->Array[FactionData]
        return (lambda n: Array(FactionData, n))(self._node.at("Factions"))
    @property
    def Relations(self):  # type: ()->Array[FactionRelationData]
        return (lambda n: Array(FactionRelationData, n))(self._node.at("Relations"))
    @property
    def Super(self):  # type: ()->Manager
        return Manager(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




