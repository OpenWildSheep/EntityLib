
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.ComponentGD import *
from entgen.Float import *


class MountIKControllerGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/MountIKControllerGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(MountIKControllerGD.schema_name))
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def horizontalSpineLeanFactor(self): return Float(self._node.at("horizontalSpineLeanFactor"))
    @horizontalSpineLeanFactor.setter
    def horizontalSpineLeanFactor(self, val): self.horizontalSpineLeanFactor.set(val)
    pass




