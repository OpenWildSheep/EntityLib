
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.Float import *
from entgen.CollectibleType import *

from EntityLibPy import Node

class CollectorGD(HelperObject):
    schema_name = "CollectorGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CollectorGD
        return CollectorGD(entlib.load_node_file(sourcefile, entlib.get_schema(CollectorGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CollectorGD
        return CollectorGD(entlib.make_node(CollectorGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def CollectorRangeByType(self):  # type: ()->Map[CollectibleTypeEnum, Float]
        return (lambda n: Map(CollectibleTypeEnum, Float, n))(self._node.at("CollectorRangeByType"))
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




