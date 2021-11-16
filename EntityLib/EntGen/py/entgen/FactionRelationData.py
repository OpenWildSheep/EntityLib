
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *

from EntityLibPy import Node

class FactionRelationData(HelperObject):
    schema_name = "FactionRelationData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->FactionRelationData
        return FactionRelationData(entlib.load_node_file(sourcefile, entlib.get_schema(FactionRelationData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->FactionRelationData
        return FactionRelationData(entlib.make_node(FactionRelationData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def faction1(self):  # type: ()->String
        return String(self._node.at("faction1"))
    @faction1.setter
    def faction1(self, val): self.faction1.set(val)
    @property
    def faction2(self):  # type: ()->String
        return String(self._node.at("faction2"))
    @faction2.setter
    def faction2(self, val): self.faction2.set(val)
    @property
    def relation(self):  # type: ()->String
        return String(self._node.at("relation"))
    @relation.setter
    def relation(self, val): self.relation.set(val)
    pass




