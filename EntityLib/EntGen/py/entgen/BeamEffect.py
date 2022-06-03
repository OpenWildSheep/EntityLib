
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.EnergySide import *
from entgen.String import *
from entgen.Bool import *
from entgen.Float import *
from entgen.FreezeData import *
from entgen.GameEffect import *

from EntityLibPy import Node

class BeamEffect(HelperObject):
    schema_name = "BeamEffect"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->BeamEffect
        return BeamEffect(entlib.load_node_file(sourcefile, entlib.get_schema(BeamEffect.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->BeamEffect
        return BeamEffect(entlib.make_node(BeamEffect.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AlwaysActive(self):  # type: ()->Bool
        return Bool(self._node.at("AlwaysActive"))
    @AlwaysActive.setter
    def AlwaysActive(self, val): self.AlwaysActive.set(val)
    @property
    def AutoChose(self):  # type: ()->Bool
        return Bool(self._node.at("AutoChose"))
    @AutoChose.setter
    def AutoChose(self, val): self.AutoChose.set(val)
    @property
    def CheckForTrees(self):  # type: ()->Bool
        return Bool(self._node.at("CheckForTrees"))
    @CheckForTrees.setter
    def CheckForTrees(self, val): self.CheckForTrees.set(val)
    @property
    def EmittedByEnvironment(self):  # type: ()->Bool
        return Bool(self._node.at("EmittedByEnvironment"))
    @EmittedByEnvironment.setter
    def EmittedByEnvironment(self, val): self.EmittedByEnvironment.set(val)
    @property
    def FreezeData(self):  # type: ()->FreezeData
        return FreezeData(self._node.at("FreezeData"))
    @property
    def Impact(self):  # type: ()->Float
        return Float(self._node.at("Impact"))
    @Impact.setter
    def Impact(self, val): self.Impact.set(val)
    @property
    def OneShot(self):  # type: ()->Bool
        return Bool(self._node.at("OneShot"))
    @OneShot.setter
    def OneShot(self, val): self.OneShot.set(val)
    @property
    def Power(self):  # type: ()->Float
        return Float(self._node.at("Power"))
    @Power.setter
    def Power(self, val): self.Power.set(val)
    @property
    def ProjectileShieldRadius(self):  # type: ()->Float
        return Float(self._node.at("ProjectileShieldRadius"))
    @ProjectileShieldRadius.setter
    def ProjectileShieldRadius(self, val): self.ProjectileShieldRadius.set(val)
    @property
    def Side(self):  # type: ()->EnergySide
        return EnergySide(self._node.at("Side"))
    @Side.setter
    def Side(self, val): self.Side.set(val)
    @property
    def Super(self):  # type: ()->GameEffect
        return GameEffect(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




