
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.ComponentGD import *
from entgen.SpawnState import *
from entgen.EntityRef import *

from EntityLibPy import Node

class ChildEntityPoolComponentGD(HelperObject):
    schema_name = "ChildEntityPoolComponentGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ChildEntityPoolComponentGD
        return ChildEntityPoolComponentGD(entlib.load_node_file(sourcefile, entlib.get_schema(ChildEntityPoolComponentGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ChildEntityPoolComponentGD
        return ChildEntityPoolComponentGD(entlib.make_node(ChildEntityPoolComponentGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AddStateAtStart(self):  # type: ()->Bool
        return Bool(self._node.at("AddStateAtStart"))
    @AddStateAtStart.setter
    def AddStateAtStart(self, val): self.AddStateAtStart.set(val)
    @property
    def AttachToParent(self):  # type: ()->Bool
        return Bool(self._node.at("AttachToParent"))
    @AttachToParent.setter
    def AttachToParent(self, val): self.AttachToParent.set(val)
    @property
    def EntityRefs(self):  # type: ()->PrimArray[EntityRef]
        return (lambda n: PrimArray(EntityRef, n))(self._node.at("EntityRefs"))
    @EntityRefs.setter
    def EntityRefs(self, val): self.EntityRefs.set(val)
    @property
    def SpawnState(self):  # type: ()->SpawnState
        return SpawnState(self._node.at("SpawnState"))
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




