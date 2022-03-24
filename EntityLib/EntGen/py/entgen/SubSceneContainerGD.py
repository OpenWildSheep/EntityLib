
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.EntityRef import *

from EntityLibPy import Node

class SubSceneContainerGD(HelperObject):
    schema_name = "SubSceneContainerGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->SubSceneContainerGD
        return SubSceneContainerGD(entlib.load_node_file(sourcefile, entlib.get_schema(SubSceneContainerGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->SubSceneContainerGD
        return SubSceneContainerGD(entlib.make_node(SubSceneContainerGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def SubEntities(self):  # type: ()->PrimArray[EntityRef]
        return (lambda n: PrimArray(EntityRef, n))(self._node.at("SubEntities"))
    @SubEntities.setter
    def SubEntities(self, val): self.SubEntities.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




