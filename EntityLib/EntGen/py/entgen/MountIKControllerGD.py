
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.Float import *

from EntityLibPy import Node

class MountIKControllerGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/MountIKControllerGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->MountIKControllerGD
        return MountIKControllerGD(entlib.load_node_file(sourcefile, entlib.get_schema(MountIKControllerGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->MountIKControllerGD
        return MountIKControllerGD(entlib.make_node(MountIKControllerGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def horizontalSpineLeanFactor(self):  # type: ()->Float
        return Float(self._node.at("horizontalSpineLeanFactor"))
    @horizontalSpineLeanFactor.setter
    def horizontalSpineLeanFactor(self, val): self.horizontalSpineLeanFactor.set(val)
    pass




