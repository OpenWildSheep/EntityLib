
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *
from entgen.Manager import *

from EntityLibPy import Node

class QualityManager(HelperObject):
    schema_name = "QualityManager"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->QualityManager
        return QualityManager(entlib.load_node_file(sourcefile, entlib.get_schema(QualityManager.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->QualityManager
        return QualityManager(entlib.make_node(QualityManager.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def EntityLODDistanceHysteresis(self):  # type: ()->Float
        return Float(self._node.at("EntityLODDistanceHysteresis"))
    @EntityLODDistanceHysteresis.setter
    def EntityLODDistanceHysteresis(self, val): self.EntityLODDistanceHysteresis.set(val)
    @property
    def Super(self):  # type: ()->Manager
        return Manager(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




