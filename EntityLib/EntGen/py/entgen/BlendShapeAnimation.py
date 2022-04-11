
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *

from EntityLibPy import Node

class BlendShapeAnimation(HelperObject):
    schema_name = "BlendShapeAnimation"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->BlendShapeAnimation
        return BlendShapeAnimation(entlib.load_node_file(sourcefile, entlib.get_schema(BlendShapeAnimation.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->BlendShapeAnimation
        return BlendShapeAnimation(entlib.make_node(BlendShapeAnimation.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Name(self):  # type: ()->String
        return String(self._node.at("Name"))
    @Name.setter
    def Name(self, val): self.Name.set(val)
    @property
    def Weights(self):  # type: ()->PrimArray[Float]
        return (lambda n: PrimArray(Float, n))(self._node.at("Weights"))
    @Weights.setter
    def Weights(self, val): self.Weights.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




