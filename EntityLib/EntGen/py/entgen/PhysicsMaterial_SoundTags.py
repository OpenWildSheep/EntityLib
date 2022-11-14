
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.String import *

from EntityLibPy import Node

class PhysicsMaterial_SoundTags(HelperObject):
    schema_name = "PhysicsMaterial::SoundTags"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PhysicsMaterial_SoundTags
        return PhysicsMaterial_SoundTags(entlib.load_node_file(sourcefile, entlib.get_schema(PhysicsMaterial_SoundTags.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PhysicsMaterial_SoundTags
        return PhysicsMaterial_SoundTags(entlib.make_node(PhysicsMaterial_SoundTags.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Common(self):  # type: ()->PrimitiveSet[str]
        return (lambda n: PrimitiveSet(str, n))(self._node.at("Common"))
    @property
    def Corrupted(self):  # type: ()->PrimitiveSet[str]
        return (lambda n: PrimitiveSet(str, n))(self._node.at("Corrupted"))
    @property
    def Lush(self):  # type: ()->PrimitiveSet[str]
        return (lambda n: PrimitiveSet(str, n))(self._node.at("Lush"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




