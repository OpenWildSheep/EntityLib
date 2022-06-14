
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.WindTurbulenceType import *
from entgen.String import *
from entgen.Bool import *
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
    def BendStrength(self):  # type: ()->Float
        return Float(self._node.at("BendStrength"))
    @BendStrength.setter
    def BendStrength(self, val): self.BendStrength.set(val)
    @property
    def GlobalStrength(self):  # type: ()->Float
        return Float(self._node.at("GlobalStrength"))
    @GlobalStrength.setter
    def GlobalStrength(self, val): self.GlobalStrength.set(val)
    @property
    def Super(self):  # type: ()->GameEffect
        return GameEffect(self._node.at("Super"))
    @property
    def TurbulenceStrength(self):  # type: ()->Float
        return Float(self._node.at("TurbulenceStrength"))
    @TurbulenceStrength.setter
    def TurbulenceStrength(self, val): self.TurbulenceStrength.set(val)
    @property
    def UseGlobalStrength(self):  # type: ()->Bool
        return Bool(self._node.at("UseGlobalStrength"))
    @UseGlobalStrength.setter
    def UseGlobalStrength(self, val): self.UseGlobalStrength.set(val)
    @property
    def WindShakeStrength(self):  # type: ()->Float
        return Float(self._node.at("WindShakeStrength"))
    @WindShakeStrength.setter
    def WindShakeStrength(self, val): self.WindShakeStrength.set(val)
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




