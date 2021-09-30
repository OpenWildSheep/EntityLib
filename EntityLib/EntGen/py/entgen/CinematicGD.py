
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.CinematicUpdateType import *
from entgen.String import *
from entgen.Bool import *
from entgen.ComponentGD import *
from entgen.Float import *
from entgen.ResponsiblePointer_CineEvent_ import *
from entgen.Sequence import *


class CinematicGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/CinematicGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(CinematicGD.schema_name))
    @property
    def ActivationDistance(self): return Float(self._node.at("ActivationDistance"))
    @ActivationDistance.setter
    def ActivationDistance(self, val): self.ActivationDistance.set(val)
    @property
    def ScriptEvents(self): return (lambda n: Array(ResponsiblePointer_CineEvent_, n))(self._node.at("ScriptEvents"))
    @property
    def Sequences(self): return (lambda n: Array(Sequence, n))(self._node.at("Sequences"))
    @property
    def Skippable(self): return Bool(self._node.at("Skippable"))
    @Skippable.setter
    def Skippable(self, val): self.Skippable.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def UpdateType(self): return CinematicUpdateType(self._node.at("UpdateType"))
    @UpdateType.setter
    def UpdateType(self, val): self.UpdateType.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




