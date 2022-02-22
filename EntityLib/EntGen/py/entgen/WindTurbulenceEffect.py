
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.WindTurbulenceType import *
from entgen.String import *
from entgen.Float import *
from entgen.GameEffect import *

from EntityLibPy import Node

class WindTurbulenceEffect(HelperObject):
    schema_name = "WindTurbulenceEffect"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->WindTurbulenceEffect
        return WindTurbulenceEffect(entlib.load_node_file(sourcefile, entlib.get_schema(WindTurbulenceEffect.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->WindTurbulenceEffect
        return WindTurbulenceEffect(entlib.make_node(WindTurbulenceEffect.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Strength(self):  # type: ()->Float
        return Float(self._node.at("Strength"))
    @Strength.setter
    def Strength(self, val): self.Strength.set(val)
    @property
    def Super(self):  # type: ()->GameEffect
        return GameEffect(self._node.at("Super"))
    @property
    def WindTurbulenceType(self):  # type: ()->WindTurbulenceType
        return WindTurbulenceType(self._node.at("WindTurbulenceType"))
    @WindTurbulenceType.setter
    def WindTurbulenceType(self, val): self.WindTurbulenceType.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




