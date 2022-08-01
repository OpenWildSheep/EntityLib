
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.NavMeshCapability import *
from entgen.NavMeshTag import *

from EntityLibPy import Node

class CapabilitiesAndTags(HelperObject):
    schema_name = "CapabilitiesAndTags"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CapabilitiesAndTags
        return CapabilitiesAndTags(entlib.load_node_file(sourcefile, entlib.get_schema(CapabilitiesAndTags.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CapabilitiesAndTags
        return CapabilitiesAndTags(entlib.make_node(CapabilitiesAndTags.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Capabilities(self):  # type: ()->PrimitiveSet[NavMeshCapabilityEnum]
        return (lambda n: PrimitiveSet(NavMeshCapabilityEnum, n))(self._node.at("Capabilities"))
    @property
    def Tags(self):  # type: ()->PrimitiveSet[NavMeshTagEnum]
        return (lambda n: PrimitiveSet(NavMeshTagEnum, n))(self._node.at("Tags"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




