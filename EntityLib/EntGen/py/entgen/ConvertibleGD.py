
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.EntityRef import *
from entgen.String import *
from entgen.ComponentGD import *

from EntityLibPy import Node

class ConvertibleGD(HelperObject):
    schema_name = "ConvertibleGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ConvertibleGD
        return ConvertibleGD(entlib.load_node_file(sourcefile, entlib.get_schema(ConvertibleGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ConvertibleGD
        return ConvertibleGD(entlib.make_node(ConvertibleGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def ConvertedEntity(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("ConvertedEntity"))
    @ConvertedEntity.setter
    def ConvertedEntity(self, val): self.ConvertedEntity.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




