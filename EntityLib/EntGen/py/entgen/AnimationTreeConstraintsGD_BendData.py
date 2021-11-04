
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.Bool import *
from entgen.Float import *

from EntityLibPy import Node

class AnimationTreeConstraintsGD_BendData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/AnimationTreeConstraintsGD::BendData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AnimationTreeConstraintsGD_BendData
        return AnimationTreeConstraintsGD_BendData(entlib.load_node_file(sourcefile, entlib.get_schema(AnimationTreeConstraintsGD_BendData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AnimationTreeConstraintsGD_BendData
        return AnimationTreeConstraintsGD_BendData(entlib.make_node(AnimationTreeConstraintsGD_BendData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AcceptDrag(self):  # type: ()->Bool
        return Bool(self._node.at("AcceptDrag"))
    @AcceptDrag.setter
    def AcceptDrag(self, val): self.AcceptDrag.set(val)
    @property
    def AcceptDragOnBaseBone(self):  # type: ()->Bool
        return Bool(self._node.at("AcceptDragOnBaseBone"))
    @AcceptDragOnBaseBone.setter
    def AcceptDragOnBaseBone(self, val): self.AcceptDragOnBaseBone.set(val)
    @property
    def AttractDuration(self):  # type: ()->Float
        return Float(self._node.at("AttractDuration"))
    @AttractDuration.setter
    def AttractDuration(self, val): self.AttractDuration.set(val)
    @property
    def DragOnBaseBoneAttractionStartFactor(self):  # type: ()->Float
        return Float(self._node.at("DragOnBaseBoneAttractionStartFactor"))
    @DragOnBaseBoneAttractionStartFactor.setter
    def DragOnBaseBoneAttractionStartFactor(self, val): self.DragOnBaseBoneAttractionStartFactor.set(val)
    @property
    def MaxBendAngleFirstBone(self):  # type: ()->Int
        return Int(self._node.at("MaxBendAngleFirstBone"))
    @MaxBendAngleFirstBone.setter
    def MaxBendAngleFirstBone(self, val): self.MaxBendAngleFirstBone.set(val)
    @property
    def MaxBendAngleValueAtFirstBone(self):  # type: ()->Float
        return Float(self._node.at("MaxBendAngleValueAtFirstBone"))
    @MaxBendAngleValueAtFirstBone.setter
    def MaxBendAngleValueAtFirstBone(self, val): self.MaxBendAngleValueAtFirstBone.set(val)
    @property
    def MaxBendAngleValueAtLastBone(self):  # type: ()->Float
        return Float(self._node.at("MaxBendAngleValueAtLastBone"))
    @MaxBendAngleValueAtLastBone.setter
    def MaxBendAngleValueAtLastBone(self, val): self.MaxBendAngleValueAtLastBone.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




