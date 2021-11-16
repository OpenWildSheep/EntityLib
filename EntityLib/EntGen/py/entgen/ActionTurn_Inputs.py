
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.Vector3 import *

from EntityLibPy import Node

class ActionTurn_Inputs(HelperObject):
    schema_name = "ActionTurn::Inputs"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActionTurn_Inputs
        return ActionTurn_Inputs(entlib.load_node_file(sourcefile, entlib.get_schema(ActionTurn_Inputs.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActionTurn_Inputs
        return ActionTurn_Inputs(entlib.make_node(ActionTurn_Inputs.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def checkDir(self):  # type: ()->Bool
        return Bool(self._node.at("checkDir"))
    @checkDir.setter
    def checkDir(self, val): self.checkDir.set(val)
    @property
    def directionREQUIRED(self):  # type: ()->Vector3
        return Vector3(self._node.at("directionREQUIRED"))
    @directionREQUIRED.setter
    def directionREQUIRED(self, val): self.directionREQUIRED.set(val)
    @property
    def speedModeUpdateAllowed(self):  # type: ()->Bool
        return Bool(self._node.at("speedModeUpdateAllowed"))
    @speedModeUpdateAllowed.setter
    def speedModeUpdateAllowed(self, val): self.speedModeUpdateAllowed.set(val)
    @property
    def useRequest(self):  # type: ()->Bool
        return Bool(self._node.at("useRequest"))
    @useRequest.setter
    def useRequest(self, val): self.useRequest.set(val)
    pass




