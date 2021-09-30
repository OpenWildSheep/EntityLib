
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Int import *
from entgen.Bool import *
from entgen.Float import *


class AnimationTreeConstraintsGD_BendData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/AnimationTreeConstraintsGD::BendData"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(AnimationTreeConstraintsGD_BendData.schema_name))
    @property
    def AcceptDrag(self): return Bool(self._node.at("AcceptDrag"))
    @AcceptDrag.setter
    def AcceptDrag(self, val): self.AcceptDrag.set(val)
    @property
    def AcceptDragOnBaseBone(self): return Bool(self._node.at("AcceptDragOnBaseBone"))
    @AcceptDragOnBaseBone.setter
    def AcceptDragOnBaseBone(self, val): self.AcceptDragOnBaseBone.set(val)
    @property
    def AttractDuration(self): return Float(self._node.at("AttractDuration"))
    @AttractDuration.setter
    def AttractDuration(self, val): self.AttractDuration.set(val)
    @property
    def DragOnBaseBoneAttractionStartFactor(self): return Float(self._node.at("DragOnBaseBoneAttractionStartFactor"))
    @DragOnBaseBoneAttractionStartFactor.setter
    def DragOnBaseBoneAttractionStartFactor(self, val): self.DragOnBaseBoneAttractionStartFactor.set(val)
    @property
    def MaxBendAngleFirstBone(self): return Int(self._node.at("MaxBendAngleFirstBone"))
    @MaxBendAngleFirstBone.setter
    def MaxBendAngleFirstBone(self, val): self.MaxBendAngleFirstBone.set(val)
    @property
    def MaxBendAngleValueAtFirstBone(self): return Float(self._node.at("MaxBendAngleValueAtFirstBone"))
    @MaxBendAngleValueAtFirstBone.setter
    def MaxBendAngleValueAtFirstBone(self, val): self.MaxBendAngleValueAtFirstBone.set(val)
    @property
    def MaxBendAngleValueAtLastBone(self): return Float(self._node.at("MaxBendAngleValueAtLastBone"))
    @MaxBendAngleValueAtLastBone.setter
    def MaxBendAngleValueAtLastBone(self, val): self.MaxBendAngleValueAtLastBone.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




