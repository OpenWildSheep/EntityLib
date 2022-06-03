
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *

from EntityLibPy import Node

class FactionSpecieRelationData(HelperObject):
    schema_name = "FactionSpecieRelationData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->FactionSpecieRelationData
        return FactionSpecieRelationData(entlib.load_node_file(sourcefile, entlib.get_schema(FactionSpecieRelationData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->FactionSpecieRelationData
        return FactionSpecieRelationData(entlib.make_node(FactionSpecieRelationData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def name(self):  # type: ()->String
        return String(self._node.at("name"))
    @name.setter
    def name(self, val): self.name.set(val)
    @property
    def specie(self):  # type: ()->String
        return String(self._node.at("specie"))
    @specie.setter
    def specie(self, val): self.specie.set(val)
    pass




