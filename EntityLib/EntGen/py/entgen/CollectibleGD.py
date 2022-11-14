
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.CollectibleType import *
from entgen.Size import *
from entgen.String import *
from entgen.ComponentGD import *
from entgen.StateCollectibleCollected import *
from entgen.StateCollectibleCollecting import *
from entgen.StateCollectorCollected import *
from entgen.StateCollectorCollecting import *

from EntityLibPy import Node

class CollectibleGD(HelperObject):
    schema_name = "CollectibleGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CollectibleGD
        return CollectibleGD(entlib.load_node_file(sourcefile, entlib.get_schema(CollectibleGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CollectibleGD
        return CollectibleGD(entlib.make_node(CollectibleGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def CollectibleType(self):  # type: ()->CollectibleType
        return CollectibleType(self._node.at("CollectibleType"))
    @CollectibleType.setter
    def CollectibleType(self, val): self.CollectibleType.set(val)
    @property
    def CollectorSize(self):  # type: ()->Size
        return Size(self._node.at("CollectorSize"))
    @CollectorSize.setter
    def CollectorSize(self, val): self.CollectorSize.set(val)
    @property
    def StateCollectibleCollected(self):  # type: ()->StateCollectibleCollected
        return StateCollectibleCollected(self._node.at("StateCollectibleCollected"))
    @property
    def StateCollectibleCollecting(self):  # type: ()->StateCollectibleCollecting
        return StateCollectibleCollecting(self._node.at("StateCollectibleCollecting"))
    @property
    def StateCollectorCollected(self):  # type: ()->StateCollectorCollected
        return StateCollectorCollected(self._node.at("StateCollectorCollected"))
    @property
    def StateCollectorCollecting(self):  # type: ()->StateCollectorCollecting
        return StateCollectorCollecting(self._node.at("StateCollectorCollecting"))
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




