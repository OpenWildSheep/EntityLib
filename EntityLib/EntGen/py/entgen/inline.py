
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy
from enum import Enum



from entgen_helpers import *

class Bool(Primitive[bool]):
    def __init__(self, node):
        super(Bool, self).__init__(bool, node)

    def set(self, val):  # type: (bool) -&gt; None
        return self._node.set_bool(val)


import EntityLibPy
from entgen_helpers import *

class EntityRef(Primitive[EntityLibPy.EntityRef]):
    def __init__(self, node):
        super(EntityRef, self).__init__(EntityLibPy.EntityRef, node)

    def set(self, val):  # type: (EntityLibPy.EntityRef) -&gt; None
        return self._node.set_entityref(val)



from entgen_helpers import *

class Float(Primitive[float]):
    def __init__(self, node):
        super(Float, self).__init__(float, node)

    def set(self, val):  # type: (float) -&gt; None
        return self._node.set_float(val)



from entgen_helpers import *


class Int(Primitive[int]):
    def __init__(self, node):
        super(Int, self).__init__(int, node)

    def set(self, val):  # type: (int) -&gt; None
        return self._node.set_int(val)



from entgen_helpers import *

class String(Primitive[str]):
    def __init__(self, node):
        super(String, self).__init__(str, node)

    def set(self, val):  # type: (str) -&gt; None
        return self._node.set_string(val)

    def __str__(self):
        return self._node.value

    def __len__(self):
        return len(self._node.value)


from EntityLibPy import Node
class variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_(Union):
    pass


from EntityLibPy import Node

class TypedValue(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/TypedValue"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->TypedValue
        return TypedValue(entlib.load_node_file(sourcefile, entlib.get_schema(TypedValue.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->TypedValue
        return TypedValue(entlib.make_node(TypedValue.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Alias(self):  # type: ()->String
        return String(self._node.at("Alias"))
    @Alias.setter
    def Alias(self, val): self.Alias.set(val)
    @property
    def Reference(self):  # type: ()->String
        return String(self._node.at("Reference"))
    @Reference.setter
    def Reference(self, val): self.Reference.set(val)
    @property
    def Value(self):  # type: ()->variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_
        return variant_string_bool_s32_float_EntityRef_Vector2_Vector3_Position_stringVec_boolVec_s32Vec_floatVec_EntityRefVec_Vector2Vec_Vector3Vec_PositionVec_(self._node.at("Value"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node
class variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_(Union):
    pass


from EntityLibPy import Node
class variant_Pasta_Easing_Curve_string_(Union):
    pass


from EntityLibPy import Node

class sPhysicsShapeSphere(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/sPhysicsShapeSphere"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->sPhysicsShapeSphere
        return sPhysicsShapeSphere(entlib.load_node_file(sourcefile, entlib.get_schema(sPhysicsShapeSphere.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->sPhysicsShapeSphere
        return sPhysicsShapeSphere(entlib.make_node(sPhysicsShapeSphere.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def radius(self):  # type: ()->Float
        return Float(self._node.at("radius"))
    @radius.setter
    def radius(self, val): self.radius.set(val)
    pass


from EntityLibPy import Node

class sPhysicsShapeMesh(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/sPhysicsShapeMesh"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->sPhysicsShapeMesh
        return sPhysicsShapeMesh(entlib.load_node_file(sourcefile, entlib.get_schema(sPhysicsShapeMesh.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->sPhysicsShapeMesh
        return sPhysicsShapeMesh(entlib.make_node(sPhysicsShapeMesh.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def path(self):  # type: ()->String
        return String(self._node.at("path"))
    @path.setter
    def path(self, val): self.path.set(val)
    pass


from EntityLibPy import Node

class sPhysicsShapeCylinder(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/sPhysicsShapeCylinder"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->sPhysicsShapeCylinder
        return sPhysicsShapeCylinder(entlib.load_node_file(sourcefile, entlib.get_schema(sPhysicsShapeCylinder.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->sPhysicsShapeCylinder
        return sPhysicsShapeCylinder(entlib.make_node(sPhysicsShapeCylinder.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def length(self):  # type: ()->Float
        return Float(self._node.at("length"))
    @length.setter
    def length(self, val): self.length.set(val)
    @property
    def radius(self):  # type: ()->Float
        return Float(self._node.at("radius"))
    @radius.setter
    def radius(self, val): self.radius.set(val)
    pass


from EntityLibPy import Node

class sPhysicsShapeCapsule(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/sPhysicsShapeCapsule"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->sPhysicsShapeCapsule
        return sPhysicsShapeCapsule(entlib.load_node_file(sourcefile, entlib.get_schema(sPhysicsShapeCapsule.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->sPhysicsShapeCapsule
        return sPhysicsShapeCapsule(entlib.make_node(sPhysicsShapeCapsule.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def length(self):  # type: ()->Float
        return Float(self._node.at("length"))
    @length.setter
    def length(self, val): self.length.set(val)
    @property
    def radius(self):  # type: ()->Float
        return Float(self._node.at("radius"))
    @radius.setter
    def radius(self, val): self.radius.set(val)
    pass


from EntityLibPy import Node

class sJointFixedDesc(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/sJointFixedDesc"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->sJointFixedDesc
        return sJointFixedDesc(entlib.load_node_file(sourcefile, entlib.get_schema(sJointFixedDesc.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->sJointFixedDesc
        return sJointFixedDesc(entlib.make_node(sJointFixedDesc.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    pass


from EntityLibPy import Node

class sJointBallDesc(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/sJointBallDesc"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->sJointBallDesc
        return sJointBallDesc(entlib.load_node_file(sourcefile, entlib.get_schema(sJointBallDesc.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->sJointBallDesc
        return sJointBallDesc(entlib.make_node(sJointBallDesc.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    pass


from EntityLibPy import Node

class sGameEffectTemplate(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/sGameEffectTemplate"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->sGameEffectTemplate
        return sGameEffectTemplate(entlib.load_node_file(sourcefile, entlib.get_schema(sGameEffectTemplate.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->sGameEffectTemplate
        return sGameEffectTemplate(entlib.make_node(sGameEffectTemplate.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def BoneID(self):  # type: ()->Int
        return Int(self._node.at("BoneID"))
    @BoneID.setter
    def BoneID(self, val): self.BoneID.set(val)
    @property
    def BoneName(self):  # type: ()->String
        return String(self._node.at("BoneName"))
    @BoneName.setter
    def BoneName(self, val): self.BoneName.set(val)
    @property
    def EffectName(self):  # type: ()->String
        return String(self._node.at("EffectName"))
    @EffectName.setter
    def EffectName(self, val): self.EffectName.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class sBoneInfluenceDataTemplate(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/sBoneInfluenceDataTemplate"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->sBoneInfluenceDataTemplate
        return sBoneInfluenceDataTemplate(entlib.load_node_file(sourcefile, entlib.get_schema(sBoneInfluenceDataTemplate.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->sBoneInfluenceDataTemplate
        return sBoneInfluenceDataTemplate(entlib.make_node(sBoneInfluenceDataTemplate.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def BoneName(self):  # type: ()->String
        return String(self._node.at("BoneName"))
    @BoneName.setter
    def BoneName(self, val): self.BoneName.set(val)
    @property
    def Influence(self):  # type: ()->Float
        return Float(self._node.at("Influence"))
    @Influence.setter
    def Influence(self, val): self.Influence.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class sNodeBoneInfluenceDataTemplate(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/sNodeBoneInfluenceDataTemplate"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->sNodeBoneInfluenceDataTemplate
        return sNodeBoneInfluenceDataTemplate(entlib.load_node_file(sourcefile, entlib.get_schema(sNodeBoneInfluenceDataTemplate.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->sNodeBoneInfluenceDataTemplate
        return sNodeBoneInfluenceDataTemplate(entlib.make_node(sNodeBoneInfluenceDataTemplate.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Data(self):  # type: ()->Array[sBoneInfluenceDataTemplate]
        return (lambda n: Array(sBoneInfluenceDataTemplate, n))(self._node.at("Data"))
    @property
    def NodeName(self):  # type: ()->String
        return String(self._node.at("NodeName"))
    @NodeName.setter
    def NodeName(self, val): self.NodeName.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class eventStringHash(HelperObject):

    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def engaged(self):  # type: ()->Bool
        return Bool(self._node.at("engaged"))
    @engaged.setter
    def engaged(self, val): self.engaged.set(val)
    @property
    def val(self):  # type: ()->String
        return String(self._node.at("val"))
    @val.setter
    def val(self, val): self.val.set(val)
    pass


from EntityLibPy import Node
Vector3 = (lambda n: PrimArray(Float, n))
from EntityLibPy import Node

class sPhysicsShapeBox(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/sPhysicsShapeBox"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->sPhysicsShapeBox
        return sPhysicsShapeBox(entlib.load_node_file(sourcefile, entlib.get_schema(sPhysicsShapeBox.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->sPhysicsShapeBox
        return sPhysicsShapeBox(entlib.make_node(sPhysicsShapeBox.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def size(self):  # type: ()->Vector3
        return Vector3(self._node.at("size"))
    @size.setter
    def size(self, val): self.size.set(val)
    pass


from EntityLibPy import Node

class sEnvStamp(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/sEnvStamp"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->sEnvStamp
        return sEnvStamp(entlib.load_node_file(sourcefile, entlib.get_schema(sEnvStamp.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->sEnvStamp
        return sEnvStamp(entlib.make_node(sEnvStamp.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AffectCoverage(self):  # type: ()->Bool
        return Bool(self._node.at("AffectCoverage"))
    @AffectCoverage.setter
    def AffectCoverage(self, val): self.AffectCoverage.set(val)
    @property
    def AffectFogColor(self):  # type: ()->Bool
        return Bool(self._node.at("AffectFogColor"))
    @AffectFogColor.setter
    def AffectFogColor(self, val): self.AffectFogColor.set(val)
    @property
    def AffectFogDensity(self):  # type: ()->Bool
        return Bool(self._node.at("AffectFogDensity"))
    @AffectFogDensity.setter
    def AffectFogDensity(self, val): self.AffectFogDensity.set(val)
    @property
    def AffectFogFalloff(self):  # type: ()->Bool
        return Bool(self._node.at("AffectFogFalloff"))
    @AffectFogFalloff.setter
    def AffectFogFalloff(self, val): self.AffectFogFalloff.set(val)
    @property
    def AffectFogHeight(self):  # type: ()->Bool
        return Bool(self._node.at("AffectFogHeight"))
    @AffectFogHeight.setter
    def AffectFogHeight(self, val): self.AffectFogHeight.set(val)
    @property
    def AffectPull(self):  # type: ()->Bool
        return Bool(self._node.at("AffectPull"))
    @AffectPull.setter
    def AffectPull(self, val): self.AffectPull.set(val)
    @property
    def AffectType(self):  # type: ()->Bool
        return Bool(self._node.at("AffectType"))
    @AffectType.setter
    def AffectType(self, val): self.AffectType.set(val)
    @property
    def AffectWetness(self):  # type: ()->Bool
        return Bool(self._node.at("AffectWetness"))
    @AffectWetness.setter
    def AffectWetness(self, val): self.AffectWetness.set(val)
    @property
    def AtlasID(self):  # type: ()->Int
        return Int(self._node.at("AtlasID"))
    @AtlasID.setter
    def AtlasID(self, val): self.AtlasID.set(val)
    @property
    def FogColor(self):  # type: ()->Vector3
        return Vector3(self._node.at("FogColor"))
    @FogColor.setter
    def FogColor(self, val): self.FogColor.set(val)
    @property
    def IsCloud(self):  # type: ()->Bool
        return Bool(self._node.at("IsCloud"))
    @IsCloud.setter
    def IsCloud(self, val): self.IsCloud.set(val)
    @property
    def PositionOffset(self):  # type: ()->Vector3
        return Vector3(self._node.at("PositionOffset"))
    @PositionOffset.setter
    def PositionOffset(self, val): self.PositionOffset.set(val)
    @property
    def Rotation(self):  # type: ()->Float
        return Float(self._node.at("Rotation"))
    @Rotation.setter
    def Rotation(self, val): self.Rotation.set(val)
    @property
    def Size(self):  # type: ()->Float
        return Float(self._node.at("Size"))
    @Size.setter
    def Size(self, val): self.Size.set(val)
    @property
    def Strength(self):  # type: ()->Float
        return Float(self._node.at("Strength"))
    @Strength.setter
    def Strength(self, val): self.Strength.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node
Vector2 = (lambda n: PrimArray(Float, n))
from EntityLibPy import Node

class sJointUniversalDesc(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/sJointUniversalDesc"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->sJointUniversalDesc
        return sJointUniversalDesc(entlib.load_node_file(sourcefile, entlib.get_schema(sJointUniversalDesc.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->sJointUniversalDesc
        return sJointUniversalDesc(entlib.make_node(sJointUniversalDesc.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def angleSwing1(self):  # type: ()->Vector2
        return Vector2(self._node.at("angleSwing1"))
    @angleSwing1.setter
    def angleSwing1(self, val): self.angleSwing1.set(val)
    @property
    def angleSwing2(self):  # type: ()->Vector2
        return Vector2(self._node.at("angleSwing2"))
    @angleSwing2.setter
    def angleSwing2(self, val): self.angleSwing2.set(val)
    pass


from EntityLibPy import Node

class sJointSwingTwistDesc(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/sJointSwingTwistDesc"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->sJointSwingTwistDesc
        return sJointSwingTwistDesc(entlib.load_node_file(sourcefile, entlib.get_schema(sJointSwingTwistDesc.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->sJointSwingTwistDesc
        return sJointSwingTwistDesc(entlib.make_node(sJointSwingTwistDesc.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def swingAngle(self):  # type: ()->Vector2
        return Vector2(self._node.at("swingAngle"))
    @swingAngle.setter
    def swingAngle(self, val): self.swingAngle.set(val)
    @property
    def twistAngle(self):  # type: ()->Vector2
        return Vector2(self._node.at("twistAngle"))
    @twistAngle.setter
    def twistAngle(self, val): self.twistAngle.set(val)
    pass


from EntityLibPy import Node

class sJointSliderDesc(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/sJointSliderDesc"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->sJointSliderDesc
        return sJointSliderDesc(entlib.load_node_file(sourcefile, entlib.get_schema(sJointSliderDesc.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->sJointSliderDesc
        return sJointSliderDesc(entlib.make_node(sJointSliderDesc.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def direction(self):  # type: ()->Vector3
        return Vector3(self._node.at("direction"))
    @direction.setter
    def direction(self, val): self.direction.set(val)
    @property
    def distance(self):  # type: ()->Vector2
        return Vector2(self._node.at("distance"))
    @distance.setter
    def distance(self, val): self.distance.set(val)
    pass


from EntityLibPy import Node

class sJointHingeDesc(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/sJointHingeDesc"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->sJointHingeDesc
        return sJointHingeDesc(entlib.load_node_file(sourcefile, entlib.get_schema(sJointHingeDesc.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->sJointHingeDesc
        return sJointHingeDesc(entlib.make_node(sJointHingeDesc.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def angle(self):  # type: ()->Vector2
        return Vector2(self._node.at("angle"))
    @angle.setter
    def angle(self, val): self.angle.set(val)
    @property
    def axis(self):  # type: ()->Vector3
        return Vector3(self._node.at("axis"))
    @axis.setter
    def axis(self, val): self.axis.set(val)
    pass


from EntityLibPy import Node

class VomitData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/VomitData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->VomitData
        return VomitData(entlib.load_node_file(sourcefile, entlib.get_schema(VomitData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->VomitData
        return VomitData(entlib.make_node(VomitData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AngleRangeHysteresis(self):  # type: ()->Vector2
        return Vector2(self._node.at("AngleRangeHysteresis"))
    @AngleRangeHysteresis.setter
    def AngleRangeHysteresis(self, val): self.AngleRangeHysteresis.set(val)
    @property
    def AngleRangeMax(self):  # type: ()->Vector2
        return Vector2(self._node.at("AngleRangeMax"))
    @AngleRangeMax.setter
    def AngleRangeMax(self, val): self.AngleRangeMax.set(val)
    @property
    def CanVomit(self):  # type: ()->Bool
        return Bool(self._node.at("CanVomit"))
    @CanVomit.setter
    def CanVomit(self, val): self.CanVomit.set(val)
    @property
    def ProjectileName(self):  # type: ()->String
        return String(self._node.at("ProjectileName"))
    @ProjectileName.setter
    def ProjectileName(self, val): self.ProjectileName.set(val)
    @property
    def VomitCost(self):  # type: ()->Float
        return Float(self._node.at("VomitCost"))
    @VomitCost.setter
    def VomitCost(self, val): self.VomitCost.set(val)
    @property
    def VomitMinTimer(self):  # type: ()->Float
        return Float(self._node.at("VomitMinTimer"))
    @VomitMinTimer.setter
    def VomitMinTimer(self, val): self.VomitMinTimer.set(val)
    @property
    def VomitRate(self):  # type: ()->Float
        return Float(self._node.at("VomitRate"))
    @VomitRate.setter
    def VomitRate(self, val): self.VomitRate.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class UnionObjectArrayItem(HelperObject):

    @property
    def Union(self):  # type: ()->variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_
        return variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_(self._node.at("Union"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class TransitionNeighborData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/TransitionNeighborData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->TransitionNeighborData
        return TransitionNeighborData(entlib.load_node_file(sourcefile, entlib.get_schema(TransitionNeighborData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->TransitionNeighborData
        return TransitionNeighborData(entlib.make_node(TransitionNeighborData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Backward(self):  # type: ()->PrimArray[Int]
        return (lambda n: PrimArray(Int, n))(self._node.at("Backward"))
    @Backward.setter
    def Backward(self, val): self.Backward.set(val)
    @property
    def Forward(self):  # type: ()->PrimArray[Int]
        return (lambda n: PrimArray(Int, n))(self._node.at("Forward"))
    @Forward.setter
    def Forward(self, val): self.Forward.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node
ThumbPath = String
from EntityLibPy import Node

class TestPropertyDefaultValues(HelperObject):
    schema_name = "./EditionComponents.json#/definitions/TestPropertyDefaultValues"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->TestPropertyDefaultValues
        return TestPropertyDefaultValues(entlib.load_node_file(sourcefile, entlib.get_schema(TestPropertyDefaultValues.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->TestPropertyDefaultValues
        return TestPropertyDefaultValues(entlib.make_node(TestPropertyDefaultValues.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def A(self):  # type: ()->Int
        return Int(self._node.at("A"))
    @A.setter
    def A(self, val): self.A.set(val)
    @property
    def B(self):  # type: ()->Int
        return Int(self._node.at("B"))
    @B.setter
    def B(self, val): self.B.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class TestPropertyDefaultValues2(HelperObject):
    schema_name = "./EditionComponents.json#/definitions/TestPropertyDefaultValues2"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->TestPropertyDefaultValues2
        return TestPropertyDefaultValues2(entlib.load_node_file(sourcefile, entlib.get_schema(TestPropertyDefaultValues2.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->TestPropertyDefaultValues2
        return TestPropertyDefaultValues2(entlib.make_node(TestPropertyDefaultValues2.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def propertyWithDefault2(self):  # type: ()->TestPropertyDefaultValues
        return TestPropertyDefaultValues(self._node.at("propertyWithDefault2"))
    @property
    def propertyWithDefault3(self):  # type: ()->TestPropertyDefaultValues
        return TestPropertyDefaultValues(self._node.at("propertyWithDefault3"))
    pass


from EntityLibPy import Node

class Terrain_TerrainMeta(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/Terrain::TerrainMeta"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->Terrain_TerrainMeta
        return Terrain_TerrainMeta(entlib.load_node_file(sourcefile, entlib.get_schema(Terrain_TerrainMeta.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->Terrain_TerrainMeta
        return Terrain_TerrainMeta(entlib.make_node(Terrain_TerrainMeta.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def DataPath(self):  # type: ()->String
        return String(self._node.at("DataPath"))
    @DataPath.setter
    def DataPath(self, val): self.DataPath.set(val)
    @property
    def HeightScaleMeters(self):  # type: ()->Float
        return Float(self._node.at("HeightScaleMeters"))
    @HeightScaleMeters.setter
    def HeightScaleMeters(self, val): self.HeightScaleMeters.set(val)
    @property
    def Material(self):  # type: ()->String
        return String(self._node.at("Material"))
    @Material.setter
    def Material(self, val): self.Material.set(val)
    @property
    def RegionWidthMeters(self):  # type: ()->Float
        return Float(self._node.at("RegionWidthMeters"))
    @RegionWidthMeters.setter
    def RegionWidthMeters(self, val): self.RegionWidthMeters.set(val)
    @property
    def SkirtScale(self):  # type: ()->Float
        return Float(self._node.at("SkirtScale"))
    @SkirtScale.setter
    def SkirtScale(self, val): self.SkirtScale.set(val)
    @property
    def TexelsPerMeter(self):  # type: ()->Float
        return Float(self._node.at("TexelsPerMeter"))
    @TexelsPerMeter.setter
    def TexelsPerMeter(self, val): self.TexelsPerMeter.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class TagsList(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/TagsList"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->TagsList
        return TagsList(entlib.load_node_file(sourcefile, entlib.get_schema(TagsList.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->TagsList
        return TagsList(entlib.make_node(TagsList.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Tags(self):  # type: ()->Map[str, PrimitiveSet[str]]
        return (lambda n: Map(str, (lambda n: PrimitiveSet(str, n)), n))(self._node.at("Tags"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class TaggedEntityRef(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/TaggedEntityRef"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->TaggedEntityRef
        return TaggedEntityRef(entlib.load_node_file(sourcefile, entlib.get_schema(TaggedEntityRef.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->TaggedEntityRef
        return TaggedEntityRef(entlib.make_node(TaggedEntityRef.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def EntityRef(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("EntityRef"))
    @EntityRef.setter
    def EntityRef(self, val): self.EntityRef.set(val)
    @property
    def Tags(self):  # type: ()->PrimArray[InventoryTags]
        return (lambda n: PrimArray(InventoryTags, n))(self._node.at("Tags"))
    @Tags.setter
    def Tags(self, val): self.Tags.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node
class SyncTempoModeEnum(Enum):
    None_ = "None"
    OnGrid = "OnGrid"
    OnBeat = "OnBeat"
    OnBar = "OnBar"
    OnEnterCue = "OnEnterCue"
    OnExitCue = "OnExitCue"
    OnCustomCue = "OnCustomCue"
    OnSwitchTransition = "OnSwitchTransition"
    SyncTempoMode_COUNT = "SyncTempoMode_COUNT"
    SyncTempoMode_FIRST = "SyncTempoMode_FIRST"


class SyncTempoMode(Primitive[SyncTempoModeEnum]):  # Enum
    def __init__(self, node):
        super().__init__(SyncTempoModeEnum, node)
    schema_name = "SyncTempoMode"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> SyncTempoMode
        return SyncTempoMode(node)
    def set(self, val):  # type: (SyncTempoModeEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)


from EntityLibPy import Node
class StyleModeEnum(Enum):
    default_ = "default"
    stick = "stick"
    sword = "sword"
    do_ = "do"
    hammer = "hammer"
    knife = "knife"
    squirrel = "squirrel"
    lush = "lush"
    StyleMode_COUNT = "StyleMode_COUNT"


class StyleMode(Primitive[StyleModeEnum]):  # Enum
    def __init__(self, node):
        super().__init__(StyleModeEnum, node)
    schema_name = "StyleMode"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> StyleMode
        return StyleMode(node)
    def set(self, val):  # type: (StyleModeEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)


from EntityLibPy import Node

class StunData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/StunData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->StunData
        return StunData(entlib.load_node_file(sourcefile, entlib.get_schema(StunData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->StunData
        return StunData(entlib.make_node(StunData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def damageHitBig(self):  # type: ()->Int
        return Int(self._node.at("damageHitBig"))
    @damageHitBig.setter
    def damageHitBig(self, val): self.damageHitBig.set(val)
    @property
    def damageHitBite(self):  # type: ()->Int
        return Int(self._node.at("damageHitBite"))
    @damageHitBite.setter
    def damageHitBite(self, val): self.damageHitBite.set(val)
    @property
    def damageHitEject(self):  # type: ()->Int
        return Int(self._node.at("damageHitEject"))
    @damageHitEject.setter
    def damageHitEject(self, val): self.damageHitEject.set(val)
    @property
    def damageHitEjectFar(self):  # type: ()->Int
        return Int(self._node.at("damageHitEjectFar"))
    @damageHitEjectFar.setter
    def damageHitEjectFar(self, val): self.damageHitEjectFar.set(val)
    @property
    def damageHitLight(self):  # type: ()->Int
        return Int(self._node.at("damageHitLight"))
    @damageHitLight.setter
    def damageHitLight(self, val): self.damageHitLight.set(val)
    @property
    def damageHitMedium(self):  # type: ()->Int
        return Int(self._node.at("damageHitMedium"))
    @damageHitMedium.setter
    def damageHitMedium(self, val): self.damageHitMedium.set(val)
    @property
    def malus(self):  # type: ()->Int
        return Int(self._node.at("malus"))
    @malus.setter
    def malus(self, val): self.malus.set(val)
    @property
    def orientHitBig(self):  # type: ()->Float
        return Float(self._node.at("orientHitBig"))
    @orientHitBig.setter
    def orientHitBig(self, val): self.orientHitBig.set(val)
    @property
    def orientHitEject(self):  # type: ()->Float
        return Float(self._node.at("orientHitEject"))
    @orientHitEject.setter
    def orientHitEject(self, val): self.orientHitEject.set(val)
    @property
    def orientHitEjectFar(self):  # type: ()->Float
        return Float(self._node.at("orientHitEjectFar"))
    @orientHitEjectFar.setter
    def orientHitEjectFar(self, val): self.orientHitEjectFar.set(val)
    @property
    def orientHitLight(self):  # type: ()->Float
        return Float(self._node.at("orientHitLight"))
    @orientHitLight.setter
    def orientHitLight(self, val): self.orientHitLight.set(val)
    @property
    def orientHitMedium(self):  # type: ()->Float
        return Float(self._node.at("orientHitMedium"))
    @orientHitMedium.setter
    def orientHitMedium(self, val): self.orientHitMedium.set(val)
    @property
    def recoverTime(self):  # type: ()->Float
        return Float(self._node.at("recoverTime"))
    @recoverTime.setter
    def recoverTime(self, val): self.recoverTime.set(val)
    @property
    def resistance(self):  # type: ()->Int
        return Int(self._node.at("resistance"))
    @resistance.setter
    def resistance(self, val): self.resistance.set(val)
    @property
    def stunTime(self):  # type: ()->Float
        return Float(self._node.at("stunTime"))
    @stunTime.setter
    def stunTime(self, val): self.stunTime.set(val)
    pass


from EntityLibPy import Node

class StickToGround(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/StickToGround"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->StickToGround
        return StickToGround(entlib.load_node_file(sourcefile, entlib.get_schema(StickToGround.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->StickToGround
        return StickToGround(entlib.make_node(StickToGround.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def BoneNameEnd(self):  # type: ()->String
        return String(self._node.at("BoneNameEnd"))
    @BoneNameEnd.setter
    def BoneNameEnd(self, val): self.BoneNameEnd.set(val)
    @property
    def BoneNameStart(self):  # type: ()->String
        return String(self._node.at("BoneNameStart"))
    @BoneNameStart.setter
    def BoneNameStart(self, val): self.BoneNameStart.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class StateGauge(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/StateGauge"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->StateGauge
        return StateGauge(entlib.load_node_file(sourcefile, entlib.get_schema(StateGauge.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->StateGauge
        return StateGauge(entlib.make_node(StateGauge.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def m_amount(self):  # type: ()->Float
        return Float(self._node.at("m_amount"))
    @m_amount.setter
    def m_amount(self, val): self.m_amount.set(val)
    @property
    def m_maxAmount(self):  # type: ()->Float
        return Float(self._node.at("m_maxAmount"))
    @m_maxAmount.setter
    def m_maxAmount(self, val): self.m_maxAmount.set(val)
    @property
    def m_pendingDiff(self):  # type: ()->Float
        return Float(self._node.at("m_pendingDiff"))
    @m_pendingDiff.setter
    def m_pendingDiff(self, val): self.m_pendingDiff.set(val)
    pass


from EntityLibPy import Node

class StunGauge(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/StunGauge"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->StunGauge
        return StunGauge(entlib.load_node_file(sourcefile, entlib.get_schema(StunGauge.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->StunGauge
        return StunGauge(entlib.make_node(StunGauge.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->StateGauge
        return StateGauge(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node
class SpeedModeEnum(Enum):
    speed0 = "speed0"
    speed1 = "speed1"
    speed2 = "speed2"
    speed3 = "speed3"
    speed4 = "speed4"
    SpeedMode_COUNT = "SpeedMode_COUNT"


class SpeedMode(Primitive[SpeedModeEnum]):  # Enum
    def __init__(self, node):
        super().__init__(SpeedModeEnum, node)
    schema_name = "SpeedMode"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> SpeedMode
        return SpeedMode(node)
    def set(self, val):  # type: (SpeedModeEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)


from EntityLibPy import Node

class SpeedFastMinDuration(HelperObject):

    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def engaged(self):  # type: ()->Bool
        return Bool(self._node.at("engaged"))
    @engaged.setter
    def engaged(self, val): self.engaged.set(val)
    @property
    def val(self):  # type: ()->Float
        return Float(self._node.at("val"))
    @val.setter
    def val(self, val): self.val.set(val)
    pass


from EntityLibPy import Node
class SpecieEnum(Enum):
    auroch = "auroch"
    bear = "bear"
    babybear = "babybear"
    catfish = "catfish"
    eagle = "eagle"
    elk = "elk"
    fox = "fox"
    giantbear = "giantbear"
    human = "human"
    cannibal = "cannibal"
    babyhuman = "babyhuman"
    horse = "horse"
    ibex = "ibex"
    rabbit = "rabbit"
    rat = "rat"
    ram = "ram"
    raven = "raven"
    schmetre = "schmetre"
    seagull = "seagull"
    snake = "snake"
    spermwhale = "spermwhale"
    squirrel = "squirrel"
    stag = "stag"
    toad = "toad"
    trout = "trout"
    wildboar = "wildboar"
    babyboar = "babyboar"
    wolf = "wolf"
    shark = "shark"
    dolphin = "dolphin"
    whale = "whale"
    goddess = "goddess"
    clothboots = "clothboots"
    clothbrace = "clothbrace"
    clothhelmet = "clothhelmet"
    clothskirt = "clothskirt"
    clothtorso = "clothtorso"
    clothbody = "clothbody"
    weapon = "weapon"
    outfit = "outfit"
    drivable = "drivable"
    fruit = "fruit"
    darkstone = "darkstone"
    destructible = "destructible"
    environment = "environment"
    regeneration = "regeneration"
    insect = "insect"
    Specie_COUNT = "Specie_COUNT"


class Specie(Primitive[SpecieEnum]):  # Enum
    def __init__(self, node):
        super().__init__(SpecieEnum, node)
    schema_name = "Specie"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> Specie
        return Specie(node)
    def set(self, val):  # type: (SpecieEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)


from EntityLibPy import Node

class SpawningParameter(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/SpawningParameter"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->SpawningParameter
        return SpawningParameter(entlib.load_node_file(sourcefile, entlib.get_schema(SpawningParameter.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->SpawningParameter
        return SpawningParameter(entlib.make_node(SpawningParameter.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def EntityName(self):  # type: ()->String
        return String(self._node.at("EntityName"))
    @EntityName.setter
    def EntityName(self, val): self.EntityName.set(val)
    @property
    def MinimumDepth(self):  # type: ()->Float
        return Float(self._node.at("MinimumDepth"))
    @MinimumDepth.setter
    def MinimumDepth(self, val): self.MinimumDepth.set(val)
    @property
    def PeriodRandomness(self):  # type: ()->Float
        return Float(self._node.at("PeriodRandomness"))
    @PeriodRandomness.setter
    def PeriodRandomness(self, val): self.PeriodRandomness.set(val)
    @property
    def SpawningPeriod(self):  # type: ()->Float
        return Float(self._node.at("SpawningPeriod"))
    @SpawningPeriod.setter
    def SpawningPeriod(self, val): self.SpawningPeriod.set(val)
    @property
    def State(self):  # type: ()->String
        return String(self._node.at("State"))
    @State.setter
    def State(self, val): self.State.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class SoundEventMapping(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/SoundEventMapping"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->SoundEventMapping
        return SoundEventMapping(entlib.load_node_file(sourcefile, entlib.get_schema(SoundEventMapping.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->SoundEventMapping
        return SoundEventMapping(entlib.make_node(SoundEventMapping.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Explicit(self):  # type: ()->Map[str, String]
        return (lambda n: Map(str, String, n))(self._node.at("Explicit"))
    @property
    def Ignored(self):  # type: ()->PrimitiveSet[str]
        return (lambda n: PrimitiveSet(str, n))(self._node.at("Ignored"))
    @property
    def Prefixed(self):  # type: ()->Map[str, String]
        return (lambda n: Map(str, String, n))(self._node.at("Prefixed"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node
class SoundEmissionStrengthEnum(Enum):
    none = "none"
    low = "low"
    medium = "medium"
    high = "high"
    SoundEmissionStrength_COUNT = "SoundEmissionStrength_COUNT"


class SoundEmissionStrength(Primitive[SoundEmissionStrengthEnum]):  # Enum
    def __init__(self, node):
        super().__init__(SoundEmissionStrengthEnum, node)
    schema_name = "SoundEmissionStrength"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> SoundEmissionStrength
        return SoundEmissionStrength(node)
    def set(self, val):  # type: (SoundEmissionStrengthEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)


from EntityLibPy import Node

class ShootSequenceData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ShootSequenceData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ShootSequenceData
        return ShootSequenceData(entlib.load_node_file(sourcefile, entlib.get_schema(ShootSequenceData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ShootSequenceData
        return ShootSequenceData(entlib.make_node(ShootSequenceData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Param(self):  # type: ()->Float
        return Float(self._node.at("Param"))
    @Param.setter
    def Param(self, val): self.Param.set(val)
    @property
    def Type_(self):  # type: ()->String
        return String(self._node.at("Type_"))
    @Type_.setter
    def Type_(self, val): self.Type_.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class ShootData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ShootData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ShootData
        return ShootData(entlib.load_node_file(sourcefile, entlib.get_schema(ShootData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ShootData
        return ShootData(entlib.make_node(ShootData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def ammoName(self):  # type: ()->String
        return String(self._node.at("ammoName"))
    @ammoName.setter
    def ammoName(self, val): self.ammoName.set(val)
    @property
    def anticipationImprecision(self):  # type: ()->Float
        return Float(self._node.at("anticipationImprecision"))
    @anticipationImprecision.setter
    def anticipationImprecision(self, val): self.anticipationImprecision.set(val)
    @property
    def canShoot(self):  # type: ()->Bool
        return Bool(self._node.at("canShoot"))
    @canShoot.setter
    def canShoot(self, val): self.canShoot.set(val)
    @property
    def chargeTierCount(self):  # type: ()->Int
        return Int(self._node.at("chargeTierCount"))
    @chargeTierCount.setter
    def chargeTierCount(self, val): self.chargeTierCount.set(val)
    @property
    def gravity(self):  # type: ()->Float
        return Float(self._node.at("gravity"))
    @gravity.setter
    def gravity(self, val): self.gravity.set(val)
    @property
    def lifeCost(self):  # type: ()->Float
        return Float(self._node.at("lifeCost"))
    @lifeCost.setter
    def lifeCost(self, val): self.lifeCost.set(val)
    @property
    def lifeCostCharged(self):  # type: ()->Float
        return Float(self._node.at("lifeCostCharged"))
    @lifeCostCharged.setter
    def lifeCostCharged(self, val): self.lifeCostCharged.set(val)
    @property
    def maxChargeDuration(self):  # type: ()->Float
        return Float(self._node.at("maxChargeDuration"))
    @maxChargeDuration.setter
    def maxChargeDuration(self, val): self.maxChargeDuration.set(val)
    @property
    def maxShootDistance(self):  # type: ()->Float
        return Float(self._node.at("maxShootDistance"))
    @maxShootDistance.setter
    def maxShootDistance(self, val): self.maxShootDistance.set(val)
    @property
    def minDelayBetweenShots(self):  # type: ()->Float
        return Float(self._node.at("minDelayBetweenShots"))
    @minDelayBetweenShots.setter
    def minDelayBetweenShots(self, val): self.minDelayBetweenShots.set(val)
    @property
    def randomAngleShoot(self):  # type: ()->Bool
        return Bool(self._node.at("randomAngleShoot"))
    @randomAngleShoot.setter
    def randomAngleShoot(self, val): self.randomAngleShoot.set(val)
    @property
    def shootMaxAngle(self):  # type: ()->Float
        return Float(self._node.at("shootMaxAngle"))
    @shootMaxAngle.setter
    def shootMaxAngle(self, val): self.shootMaxAngle.set(val)
    @property
    def shootSpeed(self):  # type: ()->Float
        return Float(self._node.at("shootSpeed"))
    @shootSpeed.setter
    def shootSpeed(self, val): self.shootSpeed.set(val)
    @property
    def zoneImprecision(self):  # type: ()->Float
        return Float(self._node.at("zoneImprecision"))
    @zoneImprecision.setter
    def zoneImprecision(self, val): self.zoneImprecision.set(val)
    pass


from EntityLibPy import Node

class SeedPatchData(HelperObject):
    schema_name = "./EditionComponents.json#/definitions/SeedPatchData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->SeedPatchData
        return SeedPatchData(entlib.load_node_file(sourcefile, entlib.get_schema(SeedPatchData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->SeedPatchData
        return SeedPatchData(entlib.make_node(SeedPatchData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def NoiseBlur(self):  # type: ()->Float
        return Float(self._node.at("NoiseBlur"))
    @NoiseBlur.setter
    def NoiseBlur(self, val): self.NoiseBlur.set(val)
    @property
    def NoiseContrast(self):  # type: ()->Float
        return Float(self._node.at("NoiseContrast"))
    @NoiseContrast.setter
    def NoiseContrast(self, val): self.NoiseContrast.set(val)
    @property
    def NoiseInvert(self):  # type: ()->Bool
        return Bool(self._node.at("NoiseInvert"))
    @NoiseInvert.setter
    def NoiseInvert(self, val): self.NoiseInvert.set(val)
    @property
    def NoiseName(self):  # type: ()->String
        return String(self._node.at("NoiseName"))
    @NoiseName.setter
    def NoiseName(self, val): self.NoiseName.set(val)
    @property
    def NoiseOffsetX(self):  # type: ()->Float
        return Float(self._node.at("NoiseOffsetX"))
    @NoiseOffsetX.setter
    def NoiseOffsetX(self, val): self.NoiseOffsetX.set(val)
    @property
    def NoiseOffsetY(self):  # type: ()->Float
        return Float(self._node.at("NoiseOffsetY"))
    @NoiseOffsetY.setter
    def NoiseOffsetY(self, val): self.NoiseOffsetY.set(val)
    @property
    def NoiseOpacity(self):  # type: ()->Float
        return Float(self._node.at("NoiseOpacity"))
    @NoiseOpacity.setter
    def NoiseOpacity(self, val): self.NoiseOpacity.set(val)
    @property
    def NoisePosition(self):  # type: ()->Float
        return Float(self._node.at("NoisePosition"))
    @NoisePosition.setter
    def NoisePosition(self, val): self.NoisePosition.set(val)
    @property
    def NoiseSizeX(self):  # type: ()->Float
        return Float(self._node.at("NoiseSizeX"))
    @NoiseSizeX.setter
    def NoiseSizeX(self, val): self.NoiseSizeX.set(val)
    @property
    def NoiseSizeY(self):  # type: ()->Float
        return Float(self._node.at("NoiseSizeY"))
    @NoiseSizeY.setter
    def NoiseSizeY(self, val): self.NoiseSizeY.set(val)
    @property
    def SeedName(self):  # type: ()->String
        return String(self._node.at("SeedName"))
    @SeedName.setter
    def SeedName(self, val): self.SeedName.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class SeedPatchDataList(HelperObject):
    schema_name = "./EditionComponents.json#/definitions/SeedPatchDataList"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->SeedPatchDataList
        return SeedPatchDataList(entlib.load_node_file(sourcefile, entlib.get_schema(SeedPatchDataList.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->SeedPatchDataList
        return SeedPatchDataList(entlib.make_node(SeedPatchDataList.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Data(self):  # type: ()->Array[SeedPatchData]
        return (lambda n: Array(SeedPatchData, n))(self._node.at("Data"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class ScriptPathAndDataSet(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ScriptPathAndDataSet"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ScriptPathAndDataSet
        return ScriptPathAndDataSet(entlib.load_node_file(sourcefile, entlib.get_schema(ScriptPathAndDataSet.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ScriptPathAndDataSet
        return ScriptPathAndDataSet(entlib.make_node(ScriptPathAndDataSet.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AutoLaunch(self):  # type: ()->Bool
        return Bool(self._node.at("AutoLaunch"))
    @AutoLaunch.setter
    def AutoLaunch(self, val): self.AutoLaunch.set(val)
    @property
    def DataMap(self):  # type: ()->Map[str, TypedValue]
        return (lambda n: Map(str, TypedValue, n))(self._node.at("DataMap"))
    @property
    def NickName(self):  # type: ()->String
        return String(self._node.at("NickName"))
    @NickName.setter
    def NickName(self, val): self.NickName.set(val)
    @property
    def Path(self):  # type: ()->String
        return String(self._node.at("Path"))
    @Path.setter
    def Path(self, val): self.Path.set(val)
    @property
    def SpawnDataSets(self):  # type: ()->Array[ScriptPathAndDataSet]
        return (lambda n: Array(ScriptPathAndDataSet, n))(self._node.at("SpawnDataSets"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class ScaleConverter(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ScaleConverter"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ScaleConverter
        return ScaleConverter(entlib.load_node_file(sourcefile, entlib.get_schema(ScaleConverter.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ScaleConverter
        return ScaleConverter(entlib.make_node(ScaleConverter.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def easing(self):  # type: ()->variant_Pasta_Easing_Curve_string_
        return variant_Pasta_Easing_Curve_string_(self._node.at("easing"))
    @property
    def in_(self):  # type: ()->Vector2
        return Vector2(self._node.at("in_"))
    @in_.setter
    def in_(self, val): self.in_.set(val)
    @property
    def inText(self):  # type: ()->String
        return String(self._node.at("inText"))
    @inText.setter
    def inText(self, val): self.inText.set(val)
    @property
    def out(self):  # type: ()->Vector2
        return Vector2(self._node.at("out"))
    @out.setter
    def out(self, val): self.out.set(val)
    @property
    def outText(self):  # type: ()->String
        return String(self._node.at("outText"))
    @outText.setter
    def outText(self, val): self.outText.set(val)
    pass


from EntityLibPy import Node
class ReviveSideEnum(Enum):
    neutral = "neutral"
    sacred = "sacred"
    cursed = "cursed"
    ReviveSide_COUNT = "ReviveSide_COUNT"


class ReviveSide(Primitive[ReviveSideEnum]):  # Enum
    def __init__(self, node):
        super().__init__(ReviveSideEnum, node)
    schema_name = "ReviveSide"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> ReviveSide
        return ReviveSide(node)
    def set(self, val):  # type: (ReviveSideEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)


from EntityLibPy import Node

class RevivedData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/RevivedData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->RevivedData
        return RevivedData(entlib.load_node_file(sourcefile, entlib.get_schema(RevivedData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->RevivedData
        return RevivedData(entlib.make_node(RevivedData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def CanBeFreed(self):  # type: ()->Bool
        return Bool(self._node.at("CanBeFreed"))
    @CanBeFreed.setter
    def CanBeFreed(self, val): self.CanBeFreed.set(val)
    @property
    def DecreaseOverTimeSpeed(self):  # type: ()->Float
        return Float(self._node.at("DecreaseOverTimeSpeed"))
    @DecreaseOverTimeSpeed.setter
    def DecreaseOverTimeSpeed(self, val): self.DecreaseOverTimeSpeed.set(val)
    @property
    def LifeMinHysteresis(self):  # type: ()->Float
        return Float(self._node.at("LifeMinHysteresis"))
    @LifeMinHysteresis.setter
    def LifeMinHysteresis(self, val): self.LifeMinHysteresis.set(val)
    @property
    def LifeMinReviveSideNeutral(self):  # type: ()->Float
        return Float(self._node.at("LifeMinReviveSideNeutral"))
    @LifeMinReviveSideNeutral.setter
    def LifeMinReviveSideNeutral(self, val): self.LifeMinReviveSideNeutral.set(val)
    @property
    def NonCreatureConvertRatio(self):  # type: ()->Float
        return Float(self._node.at("NonCreatureConvertRatio"))
    @NonCreatureConvertRatio.setter
    def NonCreatureConvertRatio(self, val): self.NonCreatureConvertRatio.set(val)
    @property
    def RequestReviveLocked(self):  # type: ()->Bool
        return Bool(self._node.at("RequestReviveLocked"))
    @RequestReviveLocked.setter
    def RequestReviveLocked(self, val): self.RequestReviveLocked.set(val)
    @property
    def ReviveEnergyMax(self):  # type: ()->Float
        return Float(self._node.at("ReviveEnergyMax"))
    @ReviveEnergyMax.setter
    def ReviveEnergyMax(self, val): self.ReviveEnergyMax.set(val)
    @property
    def ReviveSinAmplitude(self):  # type: ()->Float
        return Float(self._node.at("ReviveSinAmplitude"))
    @ReviveSinAmplitude.setter
    def ReviveSinAmplitude(self, val): self.ReviveSinAmplitude.set(val)
    @property
    def StartSide(self):  # type: ()->ReviveSide
        return ReviveSide(self._node.at("StartSide"))
    @StartSide.setter
    def StartSide(self, val): self.StartSide.set(val)
    @property
    def StateThresholds(self):  # type: ()->PrimArray[Float]
        return (lambda n: PrimArray(Float, n))(self._node.at("StateThresholds"))
    @StateThresholds.setter
    def StateThresholds(self, val): self.StateThresholds.set(val)
    @property
    def TimeBeforeFree(self):  # type: ()->Float
        return Float(self._node.at("TimeBeforeFree"))
    @TimeBeforeFree.setter
    def TimeBeforeFree(self, val): self.TimeBeforeFree.set(val)
    @property
    def VomitData(self):  # type: ()->VomitData
        return VomitData(self._node.at("VomitData"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class ReviveSideEvent(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ReviveSideEvent"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ReviveSideEvent
        return ReviveSideEvent(entlib.load_node_file(sourcefile, entlib.get_schema(ReviveSideEvent.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ReviveSideEvent
        return ReviveSideEvent(entlib.make_node(ReviveSideEvent.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def ElapsedTime(self):  # type: ()->Float
        return Float(self._node.at("ElapsedTime"))
    @ElapsedTime.setter
    def ElapsedTime(self, val): self.ElapsedTime.set(val)
    @property
    def ReviveSide(self):  # type: ()->ReviveSide
        return ReviveSide(self._node.at("ReviveSide"))
    @ReviveSide.setter
    def ReviveSide(self, val): self.ReviveSide.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node
class ResponsiblePointer_CineEvent_(Union):
    pass


from EntityLibPy import Node
class ResponsiblePointer_ActorState_(Union):
    pass


from EntityLibPy import Node
class RegenSwitchBehaviorEnum(Enum):
    CrossFade = "CrossFade"
    CrossMetamorphosis = "CrossMetamorphosis"
    SequentialMetamorphosis = "SequentialMetamorphosis"


class RegenSwitchBehavior(Primitive[RegenSwitchBehaviorEnum]):  # Enum
    def __init__(self, node):
        super().__init__(RegenSwitchBehaviorEnum, node)
    schema_name = "RegenSwitchBehavior"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> RegenSwitchBehavior
        return RegenSwitchBehavior(node)
    def set(self, val):  # type: (RegenSwitchBehaviorEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)


from EntityLibPy import Node
Quat = (lambda n: PrimArray(Float, n))
from EntityLibPy import Node

class sPhysicsJointDesc(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/sPhysicsJointDesc"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->sPhysicsJointDesc
        return sPhysicsJointDesc(entlib.load_node_file(sourcefile, entlib.get_schema(sPhysicsJointDesc.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->sPhysicsJointDesc
        return sPhysicsJointDesc(entlib.make_node(sPhysicsJointDesc.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Ball(self):  # type: ()->sJointBallDesc
        return sJointBallDesc(self._node.at("Ball"))
    @property
    def Fixed(self):  # type: ()->sJointFixedDesc
        return sJointFixedDesc(self._node.at("Fixed"))
    @property
    def Hinge(self):  # type: ()->sJointHingeDesc
        return sJointHingeDesc(self._node.at("Hinge"))
    @property
    def JointType(self):  # type: ()->String
        return String(self._node.at("JointType"))
    @JointType.setter
    def JointType(self, val): self.JointType.set(val)
    @property
    def Slider(self):  # type: ()->sJointSliderDesc
        return sJointSliderDesc(self._node.at("Slider"))
    @property
    def SwingTwist(self):  # type: ()->sJointSwingTwistDesc
        return sJointSwingTwistDesc(self._node.at("SwingTwist"))
    @property
    def Universal(self):  # type: ()->sJointUniversalDesc
        return sJointUniversalDesc(self._node.at("Universal"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def flags(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("flags"))
    @flags.setter
    def flags(self, val): self.flags.set(val)
    @property
    def idRigodBodyA(self):  # type: ()->Int
        return Int(self._node.at("idRigodBodyA"))
    @idRigodBodyA.setter
    def idRigodBodyA(self, val): self.idRigodBodyA.set(val)
    @property
    def idRigodBodyB(self):  # type: ()->Int
        return Int(self._node.at("idRigodBodyB"))
    @idRigodBodyB.setter
    def idRigodBodyB(self, val): self.idRigodBodyB.set(val)
    @property
    def orientation(self):  # type: ()->Quat
        return Quat(self._node.at("orientation"))
    @orientation.setter
    def orientation(self, val): self.orientation.set(val)
    @property
    def parent(self):  # type: ()->String
        return String(self._node.at("parent"))
    @parent.setter
    def parent(self, val): self.parent.set(val)
    @property
    def translation(self):  # type: ()->Vector3
        return Vector3(self._node.at("translation"))
    @translation.setter
    def translation(self, val): self.translation.set(val)
    pass


from EntityLibPy import Node

class sPhysicShape(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/sPhysicShape"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->sPhysicShape
        return sPhysicShape(entlib.load_node_file(sourcefile, entlib.get_schema(sPhysicShape.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->sPhysicShape
        return sPhysicShape(entlib.make_node(sPhysicShape.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Box(self):  # type: ()->sPhysicsShapeBox
        return sPhysicsShapeBox(self._node.at("Box"))
    @property
    def Capsule(self):  # type: ()->sPhysicsShapeCapsule
        return sPhysicsShapeCapsule(self._node.at("Capsule"))
    @property
    def Cylinder(self):  # type: ()->sPhysicsShapeCylinder
        return sPhysicsShapeCylinder(self._node.at("Cylinder"))
    @property
    def Mesh(self):  # type: ()->sPhysicsShapeMesh
        return sPhysicsShapeMesh(self._node.at("Mesh"))
    @property
    def PhysicsMaterial(self):  # type: ()->String
        return String(self._node.at("PhysicsMaterial"))
    @PhysicsMaterial.setter
    def PhysicsMaterial(self, val): self.PhysicsMaterial.set(val)
    @property
    def Sphere(self):  # type: ()->sPhysicsShapeSphere
        return sPhysicsShapeSphere(self._node.at("Sphere"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def angles(self):  # type: ()->Vector3
        return Vector3(self._node.at("angles"))
    @angles.setter
    def angles(self, val): self.angles.set(val)
    @property
    def orientation(self):  # type: ()->Quat
        return Quat(self._node.at("orientation"))
    @orientation.setter
    def orientation(self, val): self.orientation.set(val)
    @property
    def scale(self):  # type: ()->Float
        return Float(self._node.at("scale"))
    @scale.setter
    def scale(self, val): self.scale.set(val)
    @property
    def translation(self):  # type: ()->Vector3
        return Vector3(self._node.at("translation"))
    @translation.setter
    def translation(self, val): self.translation.set(val)
    pass


from EntityLibPy import Node

class sRigidBodyDesc(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/sRigidBodyDesc"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->sRigidBodyDesc
        return sRigidBodyDesc(entlib.load_node_file(sourcefile, entlib.get_schema(sRigidBodyDesc.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->sRigidBodyDesc
        return sRigidBodyDesc(entlib.make_node(sRigidBodyDesc.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def angles(self):  # type: ()->Vector3
        return Vector3(self._node.at("angles"))
    @angles.setter
    def angles(self, val): self.angles.set(val)
    @property
    def flags(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("flags"))
    @flags.setter
    def flags(self, val): self.flags.set(val)
    @property
    def id(self):  # type: ()->Int
        return Int(self._node.at("id"))
    @id.setter
    def id(self, val): self.id.set(val)
    @property
    def motionType(self):  # type: ()->String
        return String(self._node.at("motionType"))
    @motionType.setter
    def motionType(self, val): self.motionType.set(val)
    @property
    def orientation(self):  # type: ()->Quat
        return Quat(self._node.at("orientation"))
    @orientation.setter
    def orientation(self, val): self.orientation.set(val)
    @property
    def parent(self):  # type: ()->String
        return String(self._node.at("parent"))
    @parent.setter
    def parent(self, val): self.parent.set(val)
    @property
    def scale(self):  # type: ()->Float
        return Float(self._node.at("scale"))
    @scale.setter
    def scale(self, val): self.scale.set(val)
    @property
    def shapes(self):  # type: ()->Array[sPhysicShape]
        return (lambda n: Array(sPhysicShape, n))(self._node.at("shapes"))
    @property
    def translation(self):  # type: ()->Vector3
        return Vector3(self._node.at("translation"))
    @translation.setter
    def translation(self, val): self.translation.set(val)
    pass


from EntityLibPy import Node

class Transform3D(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/Transform3D"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->Transform3D
        return Transform3D(entlib.load_node_file(sourcefile, entlib.get_schema(Transform3D.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->Transform3D
        return Transform3D(entlib.make_node(Transform3D.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def orientation(self):  # type: ()->Quat
        return Quat(self._node.at("orientation"))
    @orientation.setter
    def orientation(self, val): self.orientation.set(val)
    @property
    def scale(self):  # type: ()->Vector3
        return Vector3(self._node.at("scale"))
    @scale.setter
    def scale(self, val): self.scale.set(val)
    @property
    def translation(self):  # type: ()->Vector3
        return Vector3(self._node.at("translation"))
    @translation.setter
    def translation(self, val): self.translation.set(val)
    pass


from EntityLibPy import Node

class ProgressSoundEventData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ProgressSoundEventData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ProgressSoundEventData
        return ProgressSoundEventData(entlib.load_node_file(sourcefile, entlib.get_schema(ProgressSoundEventData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ProgressSoundEventData
        return ProgressSoundEventData(entlib.make_node(ProgressSoundEventData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def DecreaseEventName(self):  # type: ()->String
        return String(self._node.at("DecreaseEventName"))
    @DecreaseEventName.setter
    def DecreaseEventName(self, val): self.DecreaseEventName.set(val)
    @property
    def DecreaseStartThreshold(self):  # type: ()->Float
        return Float(self._node.at("DecreaseStartThreshold"))
    @DecreaseStartThreshold.setter
    def DecreaseStartThreshold(self, val): self.DecreaseStartThreshold.set(val)
    @property
    def DecreaseStopThreshold(self):  # type: ()->Float
        return Float(self._node.at("DecreaseStopThreshold"))
    @DecreaseStopThreshold.setter
    def DecreaseStopThreshold(self, val): self.DecreaseStopThreshold.set(val)
    @property
    def EventBank(self):  # type: ()->String
        return String(self._node.at("EventBank"))
    @EventBank.setter
    def EventBank(self, val): self.EventBank.set(val)
    @property
    def EventLooping(self):  # type: ()->Bool
        return Bool(self._node.at("EventLooping"))
    @EventLooping.setter
    def EventLooping(self, val): self.EventLooping.set(val)
    @property
    def IncreaseEventName(self):  # type: ()->String
        return String(self._node.at("IncreaseEventName"))
    @IncreaseEventName.setter
    def IncreaseEventName(self, val): self.IncreaseEventName.set(val)
    @property
    def IncreaseStartThreshold(self):  # type: ()->Float
        return Float(self._node.at("IncreaseStartThreshold"))
    @IncreaseStartThreshold.setter
    def IncreaseStartThreshold(self, val): self.IncreaseStartThreshold.set(val)
    @property
    def IncreaseStopThreshold(self):  # type: ()->Float
        return Float(self._node.at("IncreaseStopThreshold"))
    @IncreaseStopThreshold.setter
    def IncreaseStopThreshold(self, val): self.IncreaseStopThreshold.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class PrimitiveData(HelperObject):

    @property
    def Height(self):  # type: ()->Float
        return Float(self._node.at("Height"))
    @Height.setter
    def Height(self, val): self.Height.set(val)
    @property
    def Length(self):  # type: ()->Float
        return Float(self._node.at("Length"))
    @Length.setter
    def Length(self, val): self.Length.set(val)
    @property
    def Radius(self):  # type: ()->Float
        return Float(self._node.at("Radius"))
    @Radius.setter
    def Radius(self, val): self.Radius.set(val)
    @property
    def Width(self):  # type: ()->Float
        return Float(self._node.at("Width"))
    @Width.setter
    def Width(self, val): self.Width.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node
class PrimitiveColliderTypeEnum(Enum):
    Undefined = "Undefined"
    Sphere = "Sphere"
    Box = "Box"
    Capsule = "Capsule"
    Cylinder = "Cylinder"
    Mesh = "Mesh"
    PrimitiveColliderType_COUNT = "PrimitiveColliderType_COUNT"


class PrimitiveColliderType(Primitive[PrimitiveColliderTypeEnum]):  # Enum
    def __init__(self, node):
        super().__init__(PrimitiveColliderTypeEnum, node)
    schema_name = "PrimitiveColliderType"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> PrimitiveColliderType
        return PrimitiveColliderType(node)
    def set(self, val):  # type: (PrimitiveColliderTypeEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)


from EntityLibPy import Node

class PredictionBehaviorDuration(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/PredictionBehaviorDuration"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PredictionBehaviorDuration
        return PredictionBehaviorDuration(entlib.load_node_file(sourcefile, entlib.get_schema(PredictionBehaviorDuration.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PredictionBehaviorDuration
        return PredictionBehaviorDuration(entlib.make_node(PredictionBehaviorDuration.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Locked(self):  # type: ()->Float
        return Float(self._node.at("Locked"))
    @Locked.setter
    def Locked(self, val): self.Locked.set(val)
    @property
    def Step(self):  # type: ()->Float
        return Float(self._node.at("Step"))
    @Step.setter
    def Step(self, val): self.Step.set(val)
    @property
    def Total(self):  # type: ()->Float
        return Float(self._node.at("Total"))
    @Total.setter
    def Total(self, val): self.Total.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class PredictionBehaviorData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/PredictionBehaviorData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PredictionBehaviorData
        return PredictionBehaviorData(entlib.load_node_file(sourcefile, entlib.get_schema(PredictionBehaviorData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PredictionBehaviorData
        return PredictionBehaviorData(entlib.make_node(PredictionBehaviorData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Duration(self):  # type: ()->PredictionBehaviorDuration
        return PredictionBehaviorDuration(self._node.at("Duration"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node
class PrecisionEnum(Enum):
    full = "full"
    half = "half"
    quarter = "quarter"
    eighth = "eighth"
    sixteenth = "sixteenth"
    highest = "highest"
    lowest = "lowest"


class Precision(Primitive[PrecisionEnum]):  # Enum
    def __init__(self, node):
        super().__init__(PrecisionEnum, node)
    schema_name = "Precision"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> Precision
        return Precision(node)
    def set(self, val):  # type: (PrecisionEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)


from EntityLibPy import Node
class Position(TupleNode[Tuple[Type[Int], Type[Int], Type[Float], Type[Float], Type[Float]]]):
    def __init__(self, node=None):  # type: (EntityLibPy.Node) -> None
        super().__init__((Int, Int, Float, Float, Float), node)
    schema_name = "./RuntimeComponents.json#/definitions/Position"

    def get_0(self):  # type: () -> Int
        return Int(self._node.at(0))
    def get_1(self):  # type: () -> Int
        return Int(self._node.at(1))
    def get_2(self):  # type: () -> Float
        return Float(self._node.at(2))
    def get_3(self):  # type: () -> Float
        return Float(self._node.at(3))
    def get_4(self):  # type: () -> Float
        return Float(self._node.at(4))

from EntityLibPy import Node
class OutfitPieceTypeEnum(Enum):
    OutfitPieceType_NONE = "OutfitPieceType_NONE"
    Head = "Head"
    Torso = "Torso"
    Skirt = "Skirt"
    Boots = "Boots"
    Brace = "Brace"
    Body = "Body"
    Hair = "Hair"
    OutfitPieceType_COUNT = "OutfitPieceType_COUNT"


class OutfitPieceType(Primitive[OutfitPieceTypeEnum]):  # Enum
    def __init__(self, node):
        super().__init__(OutfitPieceTypeEnum, node)
    schema_name = "OutfitPieceType"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> OutfitPieceType
        return OutfitPieceType(node)
    def set(self, val):  # type: (OutfitPieceTypeEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)


from EntityLibPy import Node

class OutfitPiece(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/OutfitPiece"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->OutfitPiece
        return OutfitPiece(entlib.load_node_file(sourcefile, entlib.get_schema(OutfitPiece.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->OutfitPiece
        return OutfitPiece(entlib.make_node(OutfitPiece.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def EntityRef(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("EntityRef"))
    @EntityRef.setter
    def EntityRef(self, val): self.EntityRef.set(val)
    @property
    def Slot(self):  # type: ()->OutfitPieceType
        return OutfitPieceType(self._node.at("Slot"))
    @Slot.setter
    def Slot(self, val): self.Slot.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class Orientation(HelperObject):

    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def engaged(self):  # type: ()->Bool
        return Bool(self._node.at("engaged"))
    @engaged.setter
    def engaged(self, val): self.engaged.set(val)
    @property
    def val(self):  # type: ()->Quat
        return Quat(self._node.at("val"))
    @val.setter
    def val(self, val): self.val.set(val)
    pass


from EntityLibPy import Node
class Object_MaxActivationLevelEnum(Enum):
    Created = "Created"
    InWorld = "InWorld"
    Loading = "Loading"
    Started = "Started"


class Object_MaxActivationLevel(Primitive[Object_MaxActivationLevelEnum]):  # Enum
    def __init__(self, node):
        super().__init__(Object_MaxActivationLevelEnum, node)
    
    def __call__(self, node):  # type: (EntityLibPy.Node) -> Object_MaxActivationLevel
        return Object_MaxActivationLevel(node)
    def set(self, val):  # type: (Object_MaxActivationLevelEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)


from EntityLibPy import Node

class NavmeshGenerationParameters(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/NavmeshGenerationParameters"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->NavmeshGenerationParameters
        return NavmeshGenerationParameters(entlib.load_node_file(sourcefile, entlib.get_schema(NavmeshGenerationParameters.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->NavmeshGenerationParameters
        return NavmeshGenerationParameters(entlib.make_node(NavmeshGenerationParameters.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def CreatureHeight(self):  # type: ()->Float
        return Float(self._node.at("CreatureHeight"))
    @CreatureHeight.setter
    def CreatureHeight(self, val): self.CreatureHeight.set(val)
    @property
    def CreatureRadius(self):  # type: ()->Float
        return Float(self._node.at("CreatureRadius"))
    @CreatureRadius.setter
    def CreatureRadius(self, val): self.CreatureRadius.set(val)
    @property
    def MarkWaterAreas(self):  # type: ()->Bool
        return Bool(self._node.at("MarkWaterAreas"))
    @MarkWaterAreas.setter
    def MarkWaterAreas(self, val): self.MarkWaterAreas.set(val)
    @property
    def MaxClimbHeight(self):  # type: ()->Float
        return Float(self._node.at("MaxClimbHeight"))
    @MaxClimbHeight.setter
    def MaxClimbHeight(self, val): self.MaxClimbHeight.set(val)
    @property
    def MaxWalkableSlopeAngle(self):  # type: ()->Float
        return Float(self._node.at("MaxWalkableSlopeAngle"))
    @MaxWalkableSlopeAngle.setter
    def MaxWalkableSlopeAngle(self, val): self.MaxWalkableSlopeAngle.set(val)
    @property
    def MinWaterDepth(self):  # type: ()->Float
        return Float(self._node.at("MinWaterDepth"))
    @MinWaterDepth.setter
    def MinWaterDepth(self, val): self.MinWaterDepth.set(val)
    @property
    def SizeLayerMask(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("SizeLayerMask"))
    @SizeLayerMask.setter
    def SizeLayerMask(self, val): self.SizeLayerMask.set(val)
    @property
    def TileWorldSize(self):  # type: ()->Float
        return Float(self._node.at("TileWorldSize"))
    @TileWorldSize.setter
    def TileWorldSize(self, val): self.TileWorldSize.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class MoveCapacityData_OrientationSpeed(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/MoveCapacityData::OrientationSpeed"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->MoveCapacityData_OrientationSpeed
        return MoveCapacityData_OrientationSpeed(entlib.load_node_file(sourcefile, entlib.get_schema(MoveCapacityData_OrientationSpeed.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->MoveCapacityData_OrientationSpeed
        return MoveCapacityData_OrientationSpeed(entlib.make_node(MoveCapacityData_OrientationSpeed.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def factor(self):  # type: ()->Vector3
        return Vector3(self._node.at("factor"))
    @factor.setter
    def factor(self, val): self.factor.set(val)
    @property
    def rate(self):  # type: ()->Vector3
        return Vector3(self._node.at("rate"))
    @rate.setter
    def rate(self, val): self.rate.set(val)
    @property
    def rotationRollFromAngularSpeed(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("rotationRollFromAngularSpeed"))
    @property
    def speedFactorFromSpeedSlow(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("speedFactorFromSpeedSlow"))
    @property
    def speedMax(self):  # type: ()->Vector3
        return Vector3(self._node.at("speedMax"))
    @speedMax.setter
    def speedMax(self, val): self.speedMax.set(val)
    @property
    def steeringAngle(self):  # type: ()->Vector3
        return Vector3(self._node.at("steeringAngle"))
    @steeringAngle.setter
    def steeringAngle(self, val): self.steeringAngle.set(val)
    pass


from EntityLibPy import Node

class MountableSnapLine_ControlPoint(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/MountableSnapLine::ControlPoint"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->MountableSnapLine_ControlPoint
        return MountableSnapLine_ControlPoint(entlib.load_node_file(sourcefile, entlib.get_schema(MountableSnapLine_ControlPoint.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->MountableSnapLine_ControlPoint
        return MountableSnapLine_ControlPoint(entlib.make_node(MountableSnapLine_ControlPoint.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def boneId(self):  # type: ()->Int
        return Int(self._node.at("boneId"))
    @boneId.setter
    def boneId(self, val): self.boneId.set(val)
    @property
    def offset(self):  # type: ()->Vector3
        return Vector3(self._node.at("offset"))
    @offset.setter
    def offset(self, val): self.offset.set(val)
    @property
    def radius(self):  # type: ()->Float
        return Float(self._node.at("radius"))
    @radius.setter
    def radius(self, val): self.radius.set(val)
    pass


from EntityLibPy import Node

class MountData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/MountData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->MountData
        return MountData(entlib.load_node_file(sourcefile, entlib.get_schema(MountData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->MountData
        return MountData(entlib.make_node(MountData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def acrobaticJumpDistance(self):  # type: ()->Float
        return Float(self._node.at("acrobaticJumpDistance"))
    @acrobaticJumpDistance.setter
    def acrobaticJumpDistance(self, val): self.acrobaticJumpDistance.set(val)
    @property
    def angle(self):  # type: ()->Float
        return Float(self._node.at("angle"))
    @angle.setter
    def angle(self, val): self.angle.set(val)
    @property
    def blindAngle(self):  # type: ()->Float
        return Float(self._node.at("blindAngle"))
    @blindAngle.setter
    def blindAngle(self, val): self.blindAngle.set(val)
    @property
    def distance(self):  # type: ()->Float
        return Float(self._node.at("distance"))
    @distance.setter
    def distance(self, val): self.distance.set(val)
    @property
    def offset(self):  # type: ()->Float
        return Float(self._node.at("offset"))
    @offset.setter
    def offset(self, val): self.offset.set(val)
    pass


from EntityLibPy import Node

class MeshesItem(HelperObject):

    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def mesh(self):  # type: ()->String
        return String(self._node.at("mesh"))
    @mesh.setter
    def mesh(self, val): self.mesh.set(val)
    pass


from EntityLibPy import Node

class RUNTIME_LODsItem(HelperObject):

    @property
    def Meshes(self):  # type: ()->Array[MeshesItem]
        return (lambda n: Array(MeshesItem, n))(self._node.at("Meshes"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node
class MeshNavigationAllowedModeEnum(Enum):
    Never = "Never"
    PlayerOnly = "PlayerOnly"
    Always = "Always"
    MeshNavigationAllowedMode_COUNT = "MeshNavigationAllowedMode_COUNT"


class MeshNavigationAllowedMode(Primitive[MeshNavigationAllowedModeEnum]):  # Enum
    def __init__(self, node):
        super().__init__(MeshNavigationAllowedModeEnum, node)
    schema_name = "MeshNavigationAllowedMode"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> MeshNavigationAllowedMode
        return MeshNavigationAllowedMode(node)
    def set(self, val):  # type: (MeshNavigationAllowedModeEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)


from EntityLibPy import Node

class MeshNavigationBehaviorData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/MeshNavigationBehaviorData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->MeshNavigationBehaviorData
        return MeshNavigationBehaviorData(entlib.load_node_file(sourcefile, entlib.get_schema(MeshNavigationBehaviorData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->MeshNavigationBehaviorData
        return MeshNavigationBehaviorData(entlib.make_node(MeshNavigationBehaviorData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def EdgeTransitionConstraintAllowed(self):  # type: ()->Bool
        return Bool(self._node.at("EdgeTransitionConstraintAllowed"))
    @EdgeTransitionConstraintAllowed.setter
    def EdgeTransitionConstraintAllowed(self, val): self.EdgeTransitionConstraintAllowed.set(val)
    @property
    def EdgeTransitionConstraintLedgeAngle(self):  # type: ()->Float
        return Float(self._node.at("EdgeTransitionConstraintLedgeAngle"))
    @EdgeTransitionConstraintLedgeAngle.setter
    def EdgeTransitionConstraintLedgeAngle(self, val): self.EdgeTransitionConstraintLedgeAngle.set(val)
    @property
    def EdgeTransitionConstraintWallAngle(self):  # type: ()->Float
        return Float(self._node.at("EdgeTransitionConstraintWallAngle"))
    @EdgeTransitionConstraintWallAngle.setter
    def EdgeTransitionConstraintWallAngle(self, val): self.EdgeTransitionConstraintWallAngle.set(val)
    @property
    def MaxNormalAngle(self):  # type: ()->Float
        return Float(self._node.at("MaxNormalAngle"))
    @MaxNormalAngle.setter
    def MaxNormalAngle(self, val): self.MaxNormalAngle.set(val)
    @property
    def MeshNavigationAllowedMode(self):  # type: ()->MeshNavigationAllowedMode
        return MeshNavigationAllowedMode(self._node.at("MeshNavigationAllowedMode"))
    @MeshNavigationAllowedMode.setter
    def MeshNavigationAllowedMode(self, val): self.MeshNavigationAllowedMode.set(val)
    @property
    def RayCastLengthLegFactor(self):  # type: ()->Float
        return Float(self._node.at("RayCastLengthLegFactor"))
    @RayCastLengthLegFactor.setter
    def RayCastLengthLegFactor(self, val): self.RayCastLengthLegFactor.set(val)
    @property
    def RayCastLengthSpeedFactor(self):  # type: ()->Float
        return Float(self._node.at("RayCastLengthSpeedFactor"))
    @RayCastLengthSpeedFactor.setter
    def RayCastLengthSpeedFactor(self, val): self.RayCastLengthSpeedFactor.set(val)
    @property
    def RollAllowed(self):  # type: ()->Bool
        return Bool(self._node.at("RollAllowed"))
    @RollAllowed.setter
    def RollAllowed(self, val): self.RollAllowed.set(val)
    @property
    def StickToAnyNormalAllowed(self):  # type: ()->Bool
        return Bool(self._node.at("StickToAnyNormalAllowed"))
    @StickToAnyNormalAllowed.setter
    def StickToAnyNormalAllowed(self, val): self.StickToAnyNormalAllowed.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node
class MenaceSelectionEnum(Enum):
    closest = "closest"
    weakest = "weakest"
    strongest = "strongest"
    MenaceSelection_COUNT = "MenaceSelection_COUNT"


class MenaceSelection(Primitive[MenaceSelectionEnum]):  # Enum
    def __init__(self, node):
        super().__init__(MenaceSelectionEnum, node)
    schema_name = "MenaceSelection"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> MenaceSelection
        return MenaceSelection(node)
    def set(self, val):  # type: (MenaceSelectionEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)


from EntityLibPy import Node
class MaxActivationLevelEnum(Enum):
    Created = "Created"
    InWorld = "InWorld"
    Loading = "Loading"
    Started = "Started"


class MaxActivationLevel(Primitive[MaxActivationLevelEnum]):  # Enum
    def __init__(self, node):
        super().__init__(MaxActivationLevelEnum, node)
    
    def __call__(self, node):  # type: (EntityLibPy.Node) -> MaxActivationLevel
        return MaxActivationLevel(node)
    def set(self, val):  # type: (MaxActivationLevelEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)


from EntityLibPy import Node
Matrix44 = (lambda n: PrimArray(Float, n))
from EntityLibPy import Node

class VolumeConstraintDataGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/VolumeConstraintDataGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->VolumeConstraintDataGD
        return VolumeConstraintDataGD(entlib.load_node_file(sourcefile, entlib.get_schema(VolumeConstraintDataGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->VolumeConstraintDataGD
        return VolumeConstraintDataGD(entlib.make_node(VolumeConstraintDataGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Matrix(self):  # type: ()->Matrix44
        return Matrix44(self._node.at("Matrix"))
    @Matrix.setter
    def Matrix(self, val): self.Matrix.set(val)
    @property
    def Neighbors(self):  # type: ()->TransitionNeighborData
        return TransitionNeighborData(self._node.at("Neighbors"))
    @property
    def Size(self):  # type: ()->Vector3
        return Vector3(self._node.at("Size"))
    @Size.setter
    def Size(self, val): self.Size.set(val)
    @property
    def Tags(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("Tags"))
    @Tags.setter
    def Tags(self, val): self.Tags.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node
Matrix33 = (lambda n: PrimArray(Float, n))
from EntityLibPy import Node
class LocomotionModeEnum(Enum):
    standup = "standup"
    quadstandup = "quadstandup"
    crouch = "crouch"
    prone = "prone"
    swim = "swim"
    ride = "ride"
    fly = "fly"
    dive = "dive"
    fall = "fall"
    cinematic = "cinematic"
    ridden = "ridden"
    riddenfly = "riddenfly"
    clamber = "clamber"
    buried = "buried"
    count = "count"


class LocomotionMode(Primitive[LocomotionModeEnum]):  # Enum
    def __init__(self, node):
        super().__init__(LocomotionModeEnum, node)
    schema_name = "LocomotionMode"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> LocomotionMode
        return LocomotionMode(node)
    def set(self, val):  # type: (LocomotionModeEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)


from EntityLibPy import Node

class MoveCapacityData_ReachSpeed(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/MoveCapacityData::ReachSpeed"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->MoveCapacityData_ReachSpeed
        return MoveCapacityData_ReachSpeed(entlib.load_node_file(sourcefile, entlib.get_schema(MoveCapacityData_ReachSpeed.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->MoveCapacityData_ReachSpeed
        return MoveCapacityData_ReachSpeed(entlib.make_node(MoveCapacityData_ReachSpeed.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def acceleration(self):  # type: ()->Float
        return Float(self._node.at("acceleration"))
    @acceleration.setter
    def acceleration(self, val): self.acceleration.set(val)
    @property
    def deceleration(self):  # type: ()->Float
        return Float(self._node.at("deceleration"))
    @deceleration.setter
    def deceleration(self, val): self.deceleration.set(val)
    @property
    def name(self):  # type: ()->LocomotionMode
        return LocomotionMode(self._node.at("name"))
    @name.setter
    def name(self, val): self.name.set(val)
    pass


from EntityLibPy import Node

class ListItem(HelperObject):

    @property
    def EntityPath(self):  # type: ()->String
        return String(self._node.at("EntityPath"))
    @EntityPath.setter
    def EntityPath(self, val): self.EntityPath.set(val)
    @property
    def EntityRef(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("EntityRef"))
    @EntityRef.setter
    def EntityRef(self, val): self.EntityRef.set(val)
    @property
    def Tag(self):  # type: ()->String
        return String(self._node.at("Tag"))
    @Tag.setter
    def Tag(self, val): self.Tag.set(val)
    @property
    def Thumbnail(self):  # type: ()->String
        return String(self._node.at("Thumbnail"))
    @Thumbnail.setter
    def Thumbnail(self, val): self.Thumbnail.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node
class LightTypeEnum(Enum):
    Omni = "Omni"
    Hemi = "Hemi"
    Spot = "Spot"
    Dir = "Dir"
    LightType_Count = "LightType_Count"


class LightType(Primitive[LightTypeEnum]):  # Enum
    def __init__(self, node):
        super().__init__(LightTypeEnum, node)
    schema_name = "LightType"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> LightType
        return LightType(node)
    def set(self, val):  # type: (LightTypeEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)


from EntityLibPy import Node

class LifeAndDamageData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/LifeAndDamageData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->LifeAndDamageData
        return LifeAndDamageData(entlib.load_node_file(sourcefile, entlib.get_schema(LifeAndDamageData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->LifeAndDamageData
        return LifeAndDamageData(entlib.make_node(LifeAndDamageData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def attackCancelThreshold(self):  # type: ()->Float
        return Float(self._node.at("attackCancelThreshold"))
    @attackCancelThreshold.setter
    def attackCancelThreshold(self, val): self.attackCancelThreshold.set(val)
    @property
    def damageThreshold(self):  # type: ()->Float
        return Float(self._node.at("damageThreshold"))
    @damageThreshold.setter
    def damageThreshold(self, val): self.damageThreshold.set(val)
    @property
    def dyingSolidity(self):  # type: ()->Float
        return Float(self._node.at("dyingSolidity"))
    @dyingSolidity.setter
    def dyingSolidity(self, val): self.dyingSolidity.set(val)
    @property
    def energyMax(self):  # type: ()->Float
        return Float(self._node.at("energyMax"))
    @energyMax.setter
    def energyMax(self, val): self.energyMax.set(val)
    @property
    def energyRecoverSpeed(self):  # type: ()->Float
        return Float(self._node.at("energyRecoverSpeed"))
    @energyRecoverSpeed.setter
    def energyRecoverSpeed(self, val): self.energyRecoverSpeed.set(val)
    @property
    def impactPercent(self):  # type: ()->PrimArray[Float]
        return (lambda n: PrimArray(Float, n))(self._node.at("impactPercent"))
    @impactPercent.setter
    def impactPercent(self, val): self.impactPercent.set(val)
    @property
    def lifeInjuredCoeff(self):  # type: ()->Float
        return Float(self._node.at("lifeInjuredCoeff"))
    @lifeInjuredCoeff.setter
    def lifeInjuredCoeff(self, val): self.lifeInjuredCoeff.set(val)
    @property
    def lifeMax(self):  # type: ()->Float
        return Float(self._node.at("lifeMax"))
    @lifeMax.setter
    def lifeMax(self, val): self.lifeMax.set(val)
    @property
    def lifeRecoverSpeed(self):  # type: ()->Float
        return Float(self._node.at("lifeRecoverSpeed"))
    @lifeRecoverSpeed.setter
    def lifeRecoverSpeed(self, val): self.lifeRecoverSpeed.set(val)
    @property
    def lifeStunCoeff(self):  # type: ()->Float
        return Float(self._node.at("lifeStunCoeff"))
    @lifeStunCoeff.setter
    def lifeStunCoeff(self, val): self.lifeStunCoeff.set(val)
    @property
    def minLifeWhenSpending(self):  # type: ()->Float
        return Float(self._node.at("minLifeWhenSpending"))
    @minLifeWhenSpending.setter
    def minLifeWhenSpending(self, val): self.minLifeWhenSpending.set(val)
    @property
    def shouldCrashWhenFlyingInjured(self):  # type: ()->Bool
        return Bool(self._node.at("shouldCrashWhenFlyingInjured"))
    @shouldCrashWhenFlyingInjured.setter
    def shouldCrashWhenFlyingInjured(self, val): self.shouldCrashWhenFlyingInjured.set(val)
    @property
    def solidity(self):  # type: ()->Float
        return Float(self._node.at("solidity"))
    @solidity.setter
    def solidity(self, val): self.solidity.set(val)
    @property
    def unbreakable(self):  # type: ()->Bool
        return Bool(self._node.at("unbreakable"))
    @unbreakable.setter
    def unbreakable(self, val): self.unbreakable.set(val)
    @property
    def velocityDamageMax(self):  # type: ()->Float
        return Float(self._node.at("velocityDamageMax"))
    @velocityDamageMax.setter
    def velocityDamageMax(self, val): self.velocityDamageMax.set(val)
    @property
    def velocityImpactMax(self):  # type: ()->Float
        return Float(self._node.at("velocityImpactMax"))
    @velocityImpactMax.setter
    def velocityImpactMax(self, val): self.velocityImpactMax.set(val)
    pass


from EntityLibPy import Node

class LastAliveReviveSide(HelperObject):

    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def engaged(self):  # type: ()->Bool
        return Bool(self._node.at("engaged"))
    @engaged.setter
    def engaged(self, val): self.engaged.set(val)
    @property
    def val(self):  # type: ()->ReviveSide
        return ReviveSide(self._node.at("val"))
    @val.setter
    def val(self, val): self.val.set(val)
    pass


from EntityLibPy import Node

class InteractData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/InteractData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->InteractData
        return InteractData(entlib.load_node_file(sourcefile, entlib.get_schema(InteractData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->InteractData
        return InteractData(entlib.make_node(InteractData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def distance(self):  # type: ()->Float
        return Float(self._node.at("distance"))
    @distance.setter
    def distance(self, val): self.distance.set(val)
    pass


from EntityLibPy import Node

class InputCollisionBehaviorData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/InputCollisionBehaviorData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->InputCollisionBehaviorData
        return InputCollisionBehaviorData(entlib.load_node_file(sourcefile, entlib.get_schema(InputCollisionBehaviorData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->InputCollisionBehaviorData
        return InputCollisionBehaviorData(entlib.make_node(InputCollisionBehaviorData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AltitudeMax(self):  # type: ()->Float
        return Float(self._node.at("AltitudeMax"))
    @AltitudeMax.setter
    def AltitudeMax(self, val): self.AltitudeMax.set(val)
    @property
    def DepthMax(self):  # type: ()->Float
        return Float(self._node.at("DepthMax"))
    @DepthMax.setter
    def DepthMax(self, val): self.DepthMax.set(val)
    @property
    def FrontAngle(self):  # type: ()->Float
        return Float(self._node.at("FrontAngle"))
    @FrontAngle.setter
    def FrontAngle(self, val): self.FrontAngle.set(val)
    @property
    def RadiusCoeff(self):  # type: ()->Float
        return Float(self._node.at("RadiusCoeff"))
    @RadiusCoeff.setter
    def RadiusCoeff(self, val): self.RadiusCoeff.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class ImmersedBehaviorData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ImmersedBehaviorData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ImmersedBehaviorData
        return ImmersedBehaviorData(entlib.load_node_file(sourcefile, entlib.get_schema(ImmersedBehaviorData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ImmersedBehaviorData
        return ImmersedBehaviorData(entlib.make_node(ImmersedBehaviorData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def depth(self):  # type: ()->Float
        return Float(self._node.at("depth"))
    @depth.setter
    def depth(self, val): self.depth.set(val)
    @property
    def depthHysteresisCoeff(self):  # type: ()->Float
        return Float(self._node.at("depthHysteresisCoeff"))
    @depthHysteresisCoeff.setter
    def depthHysteresisCoeff(self, val): self.depthHysteresisCoeff.set(val)
    @property
    def depthMaxRange(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("depthMaxRange"))
    @property
    def flotation(self):  # type: ()->Float
        return Float(self._node.at("flotation"))
    @flotation.setter
    def flotation(self, val): self.flotation.set(val)
    @property
    def isAllowed(self):  # type: ()->Bool
        return Bool(self._node.at("isAllowed"))
    @isAllowed.setter
    def isAllowed(self, val): self.isAllowed.set(val)
    @property
    def minTooDeepPushSpeed(self):  # type: ()->Float
        return Float(self._node.at("minTooDeepPushSpeed"))
    @minTooDeepPushSpeed.setter
    def minTooDeepPushSpeed(self, val): self.minTooDeepPushSpeed.set(val)
    @property
    def reachSurfaceAccelerationCoeff(self):  # type: ()->Float
        return Float(self._node.at("reachSurfaceAccelerationCoeff"))
    @reachSurfaceAccelerationCoeff.setter
    def reachSurfaceAccelerationCoeff(self, val): self.reachSurfaceAccelerationCoeff.set(val)
    pass


from EntityLibPy import Node
class HotSpotTypeEnum(Enum):
    all = "all"
    none = "none"
    back = "back"
    beam = "beam"
    bite = "bite"
    biter = "biter"
    breakablestrong = "breakablestrong"
    breakableweak = "breakableweak"
    camera = "camera"
    center = "center"
    head = "head"
    heal = "heal"
    ride = "ride"
    root = "root"
    snap = "snap"
    slot = "slot"
    spawnlife = "spawnlife"
    shoot = "shoot"
    take = "take"
    takehandle = "takehandle"
    vertebra = "vertebra"
    respawnslot = "respawnslot"
    HotSpotType_COUNT = "HotSpotType_COUNT"


class HotSpotType(Primitive[HotSpotTypeEnum]):  # Enum
    def __init__(self, node):
        super().__init__(HotSpotTypeEnum, node)
    schema_name = "HotSpotType"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> HotSpotType
        return HotSpotType(node)
    def set(self, val):  # type: (HotSpotTypeEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)


from EntityLibPy import Node

class PickableDistributorComponentData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/PickableDistributorComponentData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PickableDistributorComponentData
        return PickableDistributorComponentData(entlib.load_node_file(sourcefile, entlib.get_schema(PickableDistributorComponentData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PickableDistributorComponentData
        return PickableDistributorComponentData(entlib.make_node(PickableDistributorComponentData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def EntityRef(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("EntityRef"))
    @EntityRef.setter
    def EntityRef(self, val): self.EntityRef.set(val)
    @property
    def HotspotType(self):  # type: ()->HotSpotType
        return HotSpotType(self._node.at("HotspotType"))
    @HotspotType.setter
    def HotspotType(self, val): self.HotspotType.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class HotspotData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/HotspotData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->HotspotData
        return HotspotData(entlib.load_node_file(sourcefile, entlib.get_schema(HotspotData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->HotspotData
        return HotspotData(entlib.make_node(HotspotData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Bone(self):  # type: ()->String
        return String(self._node.at("Bone"))
    @Bone.setter
    def Bone(self, val): self.Bone.set(val)
    @property
    def Offset(self):  # type: ()->Vector3
        return Vector3(self._node.at("Offset"))
    @Offset.setter
    def Offset(self, val): self.Offset.set(val)
    @property
    def Orientation(self):  # type: ()->Quat
        return Quat(self._node.at("Orientation"))
    @Orientation.setter
    def Orientation(self, val): self.Orientation.set(val)
    @property
    def Scale(self):  # type: ()->Float
        return Float(self._node.at("Scale"))
    @Scale.setter
    def Scale(self, val): self.Scale.set(val)
    @property
    def Tags(self):  # type: ()->PrimitiveSet[str]
        return (lambda n: PrimitiveSet(str, n))(self._node.at("Tags"))
    @property
    def TargetEntityRef(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("TargetEntityRef"))
    @TargetEntityRef.setter
    def TargetEntityRef(self, val): self.TargetEntityRef.set(val)
    @property
    def Type_(self):  # type: ()->HotSpotType
        return HotSpotType(self._node.at("Type_"))
    @Type_.setter
    def Type_(self, val): self.Type_.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class HeadCollisionBehaviorData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/HeadCollisionBehaviorData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->HeadCollisionBehaviorData
        return HeadCollisionBehaviorData(entlib.load_node_file(sourcefile, entlib.get_schema(HeadCollisionBehaviorData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->HeadCollisionBehaviorData
        return HeadCollisionBehaviorData(entlib.make_node(HeadCollisionBehaviorData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def disableDuration(self):  # type: ()->Float
        return Float(self._node.at("disableDuration"))
    @disableDuration.setter
    def disableDuration(self, val): self.disableDuration.set(val)
    @property
    def enableDuration(self):  # type: ()->Float
        return Float(self._node.at("enableDuration"))
    @enableDuration.setter
    def enableDuration(self, val): self.enableDuration.set(val)
    @property
    def headOffset(self):  # type: ()->Vector3
        return Vector3(self._node.at("headOffset"))
    @headOffset.setter
    def headOffset(self, val): self.headOffset.set(val)
    @property
    def isEnabled(self):  # type: ()->Bool
        return Bool(self._node.at("isEnabled"))
    @isEnabled.setter
    def isEnabled(self, val): self.isEnabled.set(val)
    @property
    def radiusCoeff(self):  # type: ()->Float
        return Float(self._node.at("radiusCoeff"))
    @radiusCoeff.setter
    def radiusCoeff(self, val): self.radiusCoeff.set(val)
    @property
    def slopeInfluence(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("slopeInfluence"))
    @property
    def softCollisionRigidbodyCoeff(self):  # type: ()->Float
        return Float(self._node.at("softCollisionRigidbodyCoeff"))
    @softCollisionRigidbodyCoeff.setter
    def softCollisionRigidbodyCoeff(self, val): self.softCollisionRigidbodyCoeff.set(val)
    @property
    def softCollisionVisualCoeff(self):  # type: ()->Float
        return Float(self._node.at("softCollisionVisualCoeff"))
    @softCollisionVisualCoeff.setter
    def softCollisionVisualCoeff(self, val): self.softCollisionVisualCoeff.set(val)
    @property
    def speedInfluence(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("speedInfluence"))
    @property
    def visualSmoothOut(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("visualSmoothOut"))
    pass


from EntityLibPy import Node
class GrowingStateEnum(Enum):
    invalid = "invalid"
    nogrow = "nogrow"
    growing = "growing"
    grown = "grown"
    manualgrow = "manualgrow"
    degrowing = "degrowing"
    GrowingState_COUNT = "GrowingState_COUNT"


class GrowingState(Primitive[GrowingStateEnum]):  # Enum
    def __init__(self, node):
        super().__init__(GrowingStateEnum, node)
    schema_name = "GrowingState"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> GrowingState
        return GrowingState(node)
    def set(self, val):  # type: (GrowingStateEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)


from EntityLibPy import Node
class GPETypeEnum(Enum):
    BendTree = "BendTree"
    Geyser = "Geyser"
    PossessFlocking = "PossessFlocking"
    GPEType_COUNT = "GPEType_COUNT"


class GPEType(Primitive[GPETypeEnum]):  # Enum
    def __init__(self, node):
        super().__init__(GPETypeEnum, node)
    schema_name = "GPEType"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> GPEType
        return GPEType(node)
    def set(self, val):  # type: (GPETypeEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)


from EntityLibPy import Node

class FusionData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/FusionData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->FusionData
        return FusionData(entlib.load_node_file(sourcefile, entlib.get_schema(FusionData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->FusionData
        return FusionData(entlib.make_node(FusionData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def IsSoul(self):  # type: ()->Bool
        return Bool(self._node.at("IsSoul"))
    @IsSoul.setter
    def IsSoul(self, val): self.IsSoul.set(val)
    @property
    def SoulEntityRef(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("SoulEntityRef"))
    @SoulEntityRef.setter
    def SoulEntityRef(self, val): self.SoulEntityRef.set(val)
    @property
    def WarriorDamageFactor(self):  # type: ()->Float
        return Float(self._node.at("WarriorDamageFactor"))
    @WarriorDamageFactor.setter
    def WarriorDamageFactor(self, val): self.WarriorDamageFactor.set(val)
    @property
    def WarriorImpactFactor(self):  # type: ()->Float
        return Float(self._node.at("WarriorImpactFactor"))
    @WarriorImpactFactor.setter
    def WarriorImpactFactor(self, val): self.WarriorImpactFactor.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class FreezeData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/FreezeData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->FreezeData
        return FreezeData(entlib.load_node_file(sourcefile, entlib.get_schema(FreezeData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->FreezeData
        return FreezeData(entlib.make_node(FreezeData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def deltaTimeFactor(self):  # type: ()->Float
        return Float(self._node.at("deltaTimeFactor"))
    @deltaTimeFactor.setter
    def deltaTimeFactor(self, val): self.deltaTimeFactor.set(val)
    @property
    def eventStringHash(self):  # type: ()->eventStringHash
        return eventStringHash(self._node.at("eventStringHash"))
    @property
    def stateDuration(self):  # type: ()->Float
        return Float(self._node.at("stateDuration"))
    @stateDuration.setter
    def stateDuration(self, val): self.stateDuration.set(val)
    @property
    def transitionInDuration(self):  # type: ()->Float
        return Float(self._node.at("transitionInDuration"))
    @transitionInDuration.setter
    def transitionInDuration(self, val): self.transitionInDuration.set(val)
    @property
    def transitionOutDuration(self):  # type: ()->Float
        return Float(self._node.at("transitionOutDuration"))
    @transitionOutDuration.setter
    def transitionOutDuration(self, val): self.transitionOutDuration.set(val)
    pass


from EntityLibPy import Node

class ProjectileData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ProjectileData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ProjectileData
        return ProjectileData(entlib.load_node_file(sourcefile, entlib.get_schema(ProjectileData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ProjectileData
        return ProjectileData(entlib.make_node(ProjectileData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def canCollideWithOtherProjectiles(self):  # type: ()->Bool
        return Bool(self._node.at("canCollideWithOtherProjectiles"))
    @canCollideWithOtherProjectiles.setter
    def canCollideWithOtherProjectiles(self, val): self.canCollideWithOtherProjectiles.set(val)
    @property
    def damages(self):  # type: ()->Float
        return Float(self._node.at("damages"))
    @damages.setter
    def damages(self, val): self.damages.set(val)
    @property
    def deleteAfterPlantTimer(self):  # type: ()->Float
        return Float(self._node.at("deleteAfterPlantTimer"))
    @deleteAfterPlantTimer.setter
    def deleteAfterPlantTimer(self, val): self.deleteAfterPlantTimer.set(val)
    @property
    def destroyOnHit(self):  # type: ()->Bool
        return Bool(self._node.at("destroyOnHit"))
    @destroyOnHit.setter
    def destroyOnHit(self, val): self.destroyOnHit.set(val)
    @property
    def distanceFromBodyAtLaunch(self):  # type: ()->Float
        return Float(self._node.at("distanceFromBodyAtLaunch"))
    @distanceFromBodyAtLaunch.setter
    def distanceFromBodyAtLaunch(self, val): self.distanceFromBodyAtLaunch.set(val)
    @property
    def explodeOnFire(self):  # type: ()->Bool
        return Bool(self._node.at("explodeOnFire"))
    @explodeOnFire.setter
    def explodeOnFire(self, val): self.explodeOnFire.set(val)
    @property
    def explosionShockForce(self):  # type: ()->Float
        return Float(self._node.at("explosionShockForce"))
    @explosionShockForce.setter
    def explosionShockForce(self, val): self.explosionShockForce.set(val)
    @property
    def freezeData(self):  # type: ()->FreezeData
        return FreezeData(self._node.at("freezeData"))
    @property
    def gameEffectOnHit(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("gameEffectOnHit"))
    @gameEffectOnHit.setter
    def gameEffectOnHit(self, val): self.gameEffectOnHit.set(val)
    @property
    def gravity(self):  # type: ()->Float
        return Float(self._node.at("gravity"))
    @gravity.setter
    def gravity(self, val): self.gravity.set(val)
    @property
    def hasNoCollision(self):  # type: ()->Bool
        return Bool(self._node.at("hasNoCollision"))
    @hasNoCollision.setter
    def hasNoCollision(self, val): self.hasNoCollision.set(val)
    @property
    def hitSourceOffset(self):  # type: ()->Vector3
        return Vector3(self._node.at("hitSourceOffset"))
    @hitSourceOffset.setter
    def hitSourceOffset(self, val): self.hitSourceOffset.set(val)
    @property
    def homingInRangeAnticipationDist(self):  # type: ()->Float
        return Float(self._node.at("homingInRangeAnticipationDist"))
    @homingInRangeAnticipationDist.setter
    def homingInRangeAnticipationDist(self, val): self.homingInRangeAnticipationDist.set(val)
    @property
    def homingMaxAngle(self):  # type: ()->Float
        return Float(self._node.at("homingMaxAngle"))
    @homingMaxAngle.setter
    def homingMaxAngle(self, val): self.homingMaxAngle.set(val)
    @property
    def homingMaxFlightTime(self):  # type: ()->Float
        return Float(self._node.at("homingMaxFlightTime"))
    @homingMaxFlightTime.setter
    def homingMaxFlightTime(self, val): self.homingMaxFlightTime.set(val)
    @property
    def homingMaxInFrontAnticipationDist(self):  # type: ()->Float
        return Float(self._node.at("homingMaxInFrontAnticipationDist"))
    @homingMaxInFrontAnticipationDist.setter
    def homingMaxInFrontAnticipationDist(self, val): self.homingMaxInFrontAnticipationDist.set(val)
    @property
    def homingMaxTotalAnticipationDist(self):  # type: ()->Float
        return Float(self._node.at("homingMaxTotalAnticipationDist"))
    @homingMaxTotalAnticipationDist.setter
    def homingMaxTotalAnticipationDist(self, val): self.homingMaxTotalAnticipationDist.set(val)
    @property
    def homingTotalAnticipationRatioSpeeds(self):  # type: ()->PrimArray[Float]
        return (lambda n: PrimArray(Float, n))(self._node.at("homingTotalAnticipationRatioSpeeds"))
    @homingTotalAnticipationRatioSpeeds.setter
    def homingTotalAnticipationRatioSpeeds(self, val): self.homingTotalAnticipationRatioSpeeds.set(val)
    @property
    def impact(self):  # type: ()->Float
        return Float(self._node.at("impact"))
    @impact.setter
    def impact(self, val): self.impact.set(val)
    @property
    def isRegenProjectile(self):  # type: ()->Bool
        return Bool(self._node.at("isRegenProjectile"))
    @isRegenProjectile.setter
    def isRegenProjectile(self, val): self.isRegenProjectile.set(val)
    @property
    def isThrowable(self):  # type: ()->Bool
        return Bool(self._node.at("isThrowable"))
    @isThrowable.setter
    def isThrowable(self, val): self.isThrowable.set(val)
    @property
    def launchRotation(self):  # type: ()->Vector3
        return Vector3(self._node.at("launchRotation"))
    @launchRotation.setter
    def launchRotation(self, val): self.launchRotation.set(val)
    @property
    def launchSpeed(self):  # type: ()->Float
        return Float(self._node.at("launchSpeed"))
    @launchSpeed.setter
    def launchSpeed(self, val): self.launchSpeed.set(val)
    @property
    def noiseLevelOnImpact(self):  # type: ()->Float
        return Float(self._node.at("noiseLevelOnImpact"))
    @noiseLevelOnImpact.setter
    def noiseLevelOnImpact(self, val): self.noiseLevelOnImpact.set(val)
    @property
    def shouldBeVisibleBeforeShoot(self):  # type: ()->Bool
        return Bool(self._node.at("shouldBeVisibleBeforeShoot"))
    @shouldBeVisibleBeforeShoot.setter
    def shouldBeVisibleBeforeShoot(self, val): self.shouldBeVisibleBeforeShoot.set(val)
    @property
    def smoothTime(self):  # type: ()->Float
        return Float(self._node.at("smoothTime"))
    @smoothTime.setter
    def smoothTime(self, val): self.smoothTime.set(val)
    @property
    def stopOnWater(self):  # type: ()->Bool
        return Bool(self._node.at("stopOnWater"))
    @stopOnWater.setter
    def stopOnWater(self, val): self.stopOnWater.set(val)
    @property
    def straightDistance(self):  # type: ()->Float
        return Float(self._node.at("straightDistance"))
    @straightDistance.setter
    def straightDistance(self, val): self.straightDistance.set(val)
    @property
    def visibleInFlight(self):  # type: ()->Bool
        return Bool(self._node.at("visibleInFlight"))
    @visibleInFlight.setter
    def visibleInFlight(self, val): self.visibleInFlight.set(val)
    pass


from EntityLibPy import Node

class FluidVolumeComponentGD_SimulationParameters(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/FluidVolumeComponentGD::SimulationParameters"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->FluidVolumeComponentGD_SimulationParameters
        return FluidVolumeComponentGD_SimulationParameters(entlib.load_node_file(sourcefile, entlib.get_schema(FluidVolumeComponentGD_SimulationParameters.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->FluidVolumeComponentGD_SimulationParameters
        return FluidVolumeComponentGD_SimulationParameters(entlib.make_node(FluidVolumeComponentGD_SimulationParameters.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Evaporation(self):  # type: ()->Float
        return Float(self._node.at("Evaporation"))
    @Evaporation.setter
    def Evaporation(self, val): self.Evaporation.set(val)
    @property
    def Momentum(self):  # type: ()->Float
        return Float(self._node.at("Momentum"))
    @Momentum.setter
    def Momentum(self, val): self.Momentum.set(val)
    @property
    def Precision(self):  # type: ()->Float
        return Float(self._node.at("Precision"))
    @Precision.setter
    def Precision(self, val): self.Precision.set(val)
    @property
    def Viscosity(self):  # type: ()->Float
        return Float(self._node.at("Viscosity"))
    @Viscosity.setter
    def Viscosity(self, val): self.Viscosity.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class FluidVolumeComponentGD_HeightMapData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/FluidVolumeComponentGD::HeightMapData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->FluidVolumeComponentGD_HeightMapData
        return FluidVolumeComponentGD_HeightMapData(entlib.load_node_file(sourcefile, entlib.get_schema(FluidVolumeComponentGD_HeightMapData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->FluidVolumeComponentGD_HeightMapData
        return FluidVolumeComponentGD_HeightMapData(entlib.make_node(FluidVolumeComponentGD_HeightMapData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Path(self):  # type: ()->String
        return String(self._node.at("Path"))
    @Path.setter
    def Path(self, val): self.Path.set(val)
    @property
    def TerrainName(self):  # type: ()->String
        return String(self._node.at("TerrainName"))
    @TerrainName.setter
    def TerrainName(self, val): self.TerrainName.set(val)
    @property
    def WorldSize(self):  # type: ()->Vector2
        return Vector2(self._node.at("WorldSize"))
    @WorldSize.setter
    def WorldSize(self, val): self.WorldSize.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class FluidVolumeComponentGD_FluidVolumeData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/FluidVolumeComponentGD::FluidVolumeData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->FluidVolumeComponentGD_FluidVolumeData
        return FluidVolumeComponentGD_FluidVolumeData(entlib.load_node_file(sourcefile, entlib.get_schema(FluidVolumeComponentGD_FluidVolumeData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->FluidVolumeComponentGD_FluidVolumeData
        return FluidVolumeComponentGD_FluidVolumeData(entlib.make_node(FluidVolumeComponentGD_FluidVolumeData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def HeightMap(self):  # type: ()->FluidVolumeComponentGD_HeightMapData
        return FluidVolumeComponentGD_HeightMapData(self._node.at("HeightMap"))
    @property
    def InHeightMapWorldSizeOffset(self):  # type: ()->Vector2
        return Vector2(self._node.at("InHeightMapWorldSizeOffset"))
    @InHeightMapWorldSizeOffset.setter
    def InHeightMapWorldSizeOffset(self, val): self.InHeightMapWorldSizeOffset.set(val)
    @property
    def Material(self):  # type: ()->String
        return String(self._node.at("Material"))
    @Material.setter
    def Material(self, val): self.Material.set(val)
    @property
    def Simulation(self):  # type: ()->FluidVolumeComponentGD_SimulationParameters
        return FluidVolumeComponentGD_SimulationParameters(self._node.at("Simulation"))
    @property
    def WorldSize(self):  # type: ()->Vector2
        return Vector2(self._node.at("WorldSize"))
    @WorldSize.setter
    def WorldSize(self, val): self.WorldSize.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node
class FluidTypeEnum(Enum):
    water = "water"
    lava = "lava"
    mud = "mud"
    FluidType_COUNT = "FluidType_COUNT"


class FluidType(Primitive[FluidTypeEnum]):  # Enum
    def __init__(self, node):
        super().__init__(FluidTypeEnum, node)
    schema_name = "FluidType"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> FluidType
        return FluidType(node)
    def set(self, val):  # type: (FluidTypeEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)


from EntityLibPy import Node

class FloatRange(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/FloatRange"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->FloatRange
        return FloatRange(entlib.load_node_file(sourcefile, entlib.get_schema(FloatRange.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->FloatRange
        return FloatRange(entlib.make_node(FloatRange.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def MinMax(self):  # type: ()->Vector2
        return Vector2(self._node.at("MinMax"))
    @MinMax.setter
    def MinMax(self, val): self.MinMax.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class VegetationPCloudData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/VegetationPCloudData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->VegetationPCloudData
        return VegetationPCloudData(entlib.load_node_file(sourcefile, entlib.get_schema(VegetationPCloudData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->VegetationPCloudData
        return VegetationPCloudData(entlib.make_node(VegetationPCloudData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def PCloudPath(self):  # type: ()->String
        return String(self._node.at("PCloudPath"))
    @PCloudPath.setter
    def PCloudPath(self, val): self.PCloudPath.set(val)
    @property
    def RegenRange(self):  # type: ()->FloatRange
        return FloatRange(self._node.at("RegenRange"))
    @property
    def UsedVegetations(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("UsedVegetations"))
    @UsedVegetations.setter
    def UsedVegetations(self, val): self.UsedVegetations.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class EventCameraData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/EventCameraData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EventCameraData
        return EventCameraData(entlib.load_node_file(sourcefile, entlib.get_schema(EventCameraData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EventCameraData
        return EventCameraData(entlib.make_node(EventCameraData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def BlendCameraTime(self):  # type: ()->Float
        return Float(self._node.at("BlendCameraTime"))
    @BlendCameraTime.setter
    def BlendCameraTime(self, val): self.BlendCameraTime.set(val)
    @property
    def CameraAimTriggerActor(self):  # type: ()->Bool
        return Bool(self._node.at("CameraAimTriggerActor"))
    @CameraAimTriggerActor.setter
    def CameraAimTriggerActor(self, val): self.CameraAimTriggerActor.set(val)
    @property
    def CameraOffsets(self):  # type: ()->Array[Vector3]
        return (lambda n: Array(Vector3, n))(self._node.at("CameraOffsets"))
    @property
    def DOFFarStart(self):  # type: ()->Float
        return Float(self._node.at("DOFFarStart"))
    @DOFFarStart.setter
    def DOFFarStart(self, val): self.DOFFarStart.set(val)
    @property
    def DOFFarStop(self):  # type: ()->Float
        return Float(self._node.at("DOFFarStop"))
    @DOFFarStop.setter
    def DOFFarStop(self, val): self.DOFFarStop.set(val)
    @property
    def DOFMultiplier(self):  # type: ()->Float
        return Float(self._node.at("DOFMultiplier"))
    @DOFMultiplier.setter
    def DOFMultiplier(self, val): self.DOFMultiplier.set(val)
    @property
    def DOFNearStart(self):  # type: ()->Float
        return Float(self._node.at("DOFNearStart"))
    @DOFNearStart.setter
    def DOFNearStart(self, val): self.DOFNearStart.set(val)
    @property
    def DOFNearStop(self):  # type: ()->Float
        return Float(self._node.at("DOFNearStop"))
    @DOFNearStop.setter
    def DOFNearStop(self, val): self.DOFNearStop.set(val)
    @property
    def DOFRelativeTarget(self):  # type: ()->Bool
        return Bool(self._node.at("DOFRelativeTarget"))
    @DOFRelativeTarget.setter
    def DOFRelativeTarget(self, val): self.DOFRelativeTarget.set(val)
    @property
    def EventCameraTime(self):  # type: ()->Float
        return Float(self._node.at("EventCameraTime"))
    @EventCameraTime.setter
    def EventCameraTime(self, val): self.EventCameraTime.set(val)
    @property
    def FOV(self):  # type: ()->Float
        return Float(self._node.at("FOV"))
    @FOV.setter
    def FOV(self, val): self.FOV.set(val)
    @property
    def FixedCam(self):  # type: ()->Bool
        return Bool(self._node.at("FixedCam"))
    @FixedCam.setter
    def FixedCam(self, val): self.FixedCam.set(val)
    @property
    def FollowCam(self):  # type: ()->Bool
        return Bool(self._node.at("FollowCam"))
    @FollowCam.setter
    def FollowCam(self, val): self.FollowCam.set(val)
    @property
    def FollowTarget(self):  # type: ()->Bool
        return Bool(self._node.at("FollowTarget"))
    @FollowTarget.setter
    def FollowTarget(self, val): self.FollowTarget.set(val)
    @property
    def OffsetsBlendTime(self):  # type: ()->Float
        return Float(self._node.at("OffsetsBlendTime"))
    @OffsetsBlendTime.setter
    def OffsetsBlendTime(self, val): self.OffsetsBlendTime.set(val)
    @property
    def PositionsAngularBlend(self):  # type: ()->Bool
        return Bool(self._node.at("PositionsAngularBlend"))
    @PositionsAngularBlend.setter
    def PositionsAngularBlend(self, val): self.PositionsAngularBlend.set(val)
    @property
    def PositionsBlendTime(self):  # type: ()->Float
        return Float(self._node.at("PositionsBlendTime"))
    @PositionsBlendTime.setter
    def PositionsBlendTime(self, val): self.PositionsBlendTime.set(val)
    @property
    def TargetOffsets(self):  # type: ()->Array[Vector3]
        return (lambda n: Array(Vector3, n))(self._node.at("TargetOffsets"))
    @property
    def UseDOF(self):  # type: ()->Bool
        return Bool(self._node.at("UseDOF"))
    @UseDOF.setter
    def UseDOF(self, val): self.UseDOF.set(val)
    @property
    def UseOffsetsSpline(self):  # type: ()->Bool
        return Bool(self._node.at("UseOffsetsSpline"))
    @UseOffsetsSpline.setter
    def UseOffsetsSpline(self, val): self.UseOffsetsSpline.set(val)
    @property
    def UsePositionsSpline(self):  # type: ()->Bool
        return Bool(self._node.at("UsePositionsSpline"))
    @UsePositionsSpline.setter
    def UsePositionsSpline(self, val): self.UsePositionsSpline.set(val)
    @property
    def UseTriggerActorPosition(self):  # type: ()->Bool
        return Bool(self._node.at("UseTriggerActorPosition"))
    @UseTriggerActorPosition.setter
    def UseTriggerActorPosition(self, val): self.UseTriggerActorPosition.set(val)
    @property
    def UseTriggerActorSight(self):  # type: ()->Bool
        return Bool(self._node.at("UseTriggerActorSight"))
    @UseTriggerActorSight.setter
    def UseTriggerActorSight(self, val): self.UseTriggerActorSight.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class EntityLODData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/EntityLODData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityLODData
        return EntityLODData(entlib.load_node_file(sourcefile, entlib.get_schema(EntityLODData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityLODData
        return EntityLODData(entlib.make_node(EntityLODData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def EntityRef(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("EntityRef"))
    @EntityRef.setter
    def EntityRef(self, val): self.EntityRef.set(val)
    @property
    def MaxDist(self):  # type: ()->Float
        return Float(self._node.at("MaxDist"))
    @MaxDist.setter
    def MaxDist(self, val): self.MaxDist.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class RegenData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/RegenData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->RegenData
        return RegenData(entlib.load_node_file(sourcefile, entlib.get_schema(RegenData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->RegenData
        return RegenData(entlib.make_node(RegenData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def LODData(self):  # type: ()->Array[EntityLODData]
        return (lambda n: Array(EntityLODData, n))(self._node.at("LODData"))
    @property
    def RegenRange(self):  # type: ()->FloatRange
        return FloatRange(self._node.at("RegenRange"))
    @property
    def RegenRangeHysteresis(self):  # type: ()->Float
        return Float(self._node.at("RegenRangeHysteresis"))
    @RegenRangeHysteresis.setter
    def RegenRangeHysteresis(self, val): self.RegenRangeHysteresis.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class EDITOR_Mesh(HelperObject):
    schema_name = "./EditionComponents.json#/definitions/EDITOR_Mesh"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EDITOR_Mesh
        return EDITOR_Mesh(entlib.load_node_file(sourcefile, entlib.get_schema(EDITOR_Mesh.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EDITOR_Mesh
        return EDITOR_Mesh(entlib.make_node(EDITOR_Mesh.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def id(self):  # type: ()->Int
        return Int(self._node.at("id"))
    @id.setter
    def id(self, val): self.id.set(val)
    @property
    def path(self):  # type: ()->String
        return String(self._node.at("path"))
    @path.setter
    def path(self, val): self.path.set(val)
    pass


from EntityLibPy import Node

class EDITOR_LODsItem(HelperObject):

    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def lod(self):  # type: ()->Int
        return Int(self._node.at("lod"))
    @lod.setter
    def lod(self, val): self.lod.set(val)
    @property
    def wvis(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("wvis"))
    @wvis.setter
    def wvis(self, val): self.wvis.set(val)
    pass


from EntityLibPy import Node

class DisplaceNoiseListItem(HelperObject):

    @property
    def DisplaceDistance(self):  # type: ()->Float
        return Float(self._node.at("DisplaceDistance"))
    @DisplaceDistance.setter
    def DisplaceDistance(self, val): self.DisplaceDistance.set(val)
    @property
    def LuminanceCenter(self):  # type: ()->Float
        return Float(self._node.at("LuminanceCenter"))
    @LuminanceCenter.setter
    def LuminanceCenter(self, val): self.LuminanceCenter.set(val)
    @property
    def MapChannel(self):  # type: ()->Int
        return Int(self._node.at("MapChannel"))
    @MapChannel.setter
    def MapChannel(self, val): self.MapChannel.set(val)
    @property
    def MotifName(self):  # type: ()->String
        return String(self._node.at("MotifName"))
    @MotifName.setter
    def MotifName(self, val): self.MotifName.set(val)
    @property
    def MotifOffsetX(self):  # type: ()->Float
        return Float(self._node.at("MotifOffsetX"))
    @MotifOffsetX.setter
    def MotifOffsetX(self, val): self.MotifOffsetX.set(val)
    @property
    def MotifOffsetY(self):  # type: ()->Float
        return Float(self._node.at("MotifOffsetY"))
    @MotifOffsetY.setter
    def MotifOffsetY(self, val): self.MotifOffsetY.set(val)
    @property
    def MotifRotationZ(self):  # type: ()->Float
        return Float(self._node.at("MotifRotationZ"))
    @MotifRotationZ.setter
    def MotifRotationZ(self, val): self.MotifRotationZ.set(val)
    @property
    def MotifSizeX(self):  # type: ()->Float
        return Float(self._node.at("MotifSizeX"))
    @MotifSizeX.setter
    def MotifSizeX(self, val): self.MotifSizeX.set(val)
    @property
    def MotifSizeY(self):  # type: ()->Float
        return Float(self._node.at("MotifSizeY"))
    @MotifSizeY.setter
    def MotifSizeY(self, val): self.MotifSizeY.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class CreatureDangerousness(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/CreatureDangerousness"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CreatureDangerousness
        return CreatureDangerousness(entlib.load_node_file(sourcefile, entlib.get_schema(CreatureDangerousness.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CreatureDangerousness
        return CreatureDangerousness(entlib.make_node(CreatureDangerousness.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def dangerousness(self):  # type: ()->Int
        return Int(self._node.at("dangerousness"))
    @dangerousness.setter
    def dangerousness(self, val): self.dangerousness.set(val)
    @property
    def multiplierWhenInjured(self):  # type: ()->Float
        return Float(self._node.at("multiplierWhenInjured"))
    @multiplierWhenInjured.setter
    def multiplierWhenInjured(self, val): self.multiplierWhenInjured.set(val)
    pass


from EntityLibPy import Node

class ConditionalRigidityAttribute_RigidityParameter(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ConditionalRigidityAttribute::RigidityParameter"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ConditionalRigidityAttribute_RigidityParameter
        return ConditionalRigidityAttribute_RigidityParameter(entlib.load_node_file(sourcefile, entlib.get_schema(ConditionalRigidityAttribute_RigidityParameter.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ConditionalRigidityAttribute_RigidityParameter
        return ConditionalRigidityAttribute_RigidityParameter(entlib.make_node(ConditionalRigidityAttribute_RigidityParameter.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Rigidity(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("Rigidity"))
    @property
    def SpeedDown(self):  # type: ()->Float
        return Float(self._node.at("SpeedDown"))
    @SpeedDown.setter
    def SpeedDown(self, val): self.SpeedDown.set(val)
    @property
    def SpeedUp(self):  # type: ()->Float
        return Float(self._node.at("SpeedUp"))
    @SpeedUp.setter
    def SpeedUp(self, val): self.SpeedUp.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class ConditionalRigidityAttribute_Conditions(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ConditionalRigidityAttribute::Conditions"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ConditionalRigidityAttribute_Conditions
        return ConditionalRigidityAttribute_Conditions(entlib.load_node_file(sourcefile, entlib.get_schema(ConditionalRigidityAttribute_Conditions.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ConditionalRigidityAttribute_Conditions
        return ConditionalRigidityAttribute_Conditions(entlib.make_node(ConditionalRigidityAttribute_Conditions.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def ActorCategories(self):  # type: ()->PrimArray[ActorCategory]
        return (lambda n: PrimArray(ActorCategory, n))(self._node.at("ActorCategories"))
    @ActorCategories.setter
    def ActorCategories(self, val): self.ActorCategories.set(val)
    @property
    def ActorStates(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("ActorStates"))
    @ActorStates.setter
    def ActorStates(self, val): self.ActorStates.set(val)
    @property
    def AngularVelocityFactorRange(self):  # type: ()->Vector2
        return Vector2(self._node.at("AngularVelocityFactorRange"))
    @AngularVelocityFactorRange.setter
    def AngularVelocityFactorRange(self, val): self.AngularVelocityFactorRange.set(val)
    @property
    def DirectionDotRange(self):  # type: ()->Vector2
        return Vector2(self._node.at("DirectionDotRange"))
    @DirectionDotRange.setter
    def DirectionDotRange(self, val): self.DirectionDotRange.set(val)
    @property
    def LinearVelocityFactorRange(self):  # type: ()->Vector2
        return Vector2(self._node.at("LinearVelocityFactorRange"))
    @LinearVelocityFactorRange.setter
    def LinearVelocityFactorRange(self, val): self.LinearVelocityFactorRange.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class ConditionalRigidityAttribute_Attributes(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ConditionalRigidityAttribute::Attributes"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ConditionalRigidityAttribute_Attributes
        return ConditionalRigidityAttribute_Attributes(entlib.load_node_file(sourcefile, entlib.get_schema(ConditionalRigidityAttribute_Attributes.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ConditionalRigidityAttribute_Attributes
        return ConditionalRigidityAttribute_Attributes(entlib.make_node(ConditionalRigidityAttribute_Attributes.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def DirectionAngular(self):  # type: ()->ConditionalRigidityAttribute_RigidityParameter
        return ConditionalRigidityAttribute_RigidityParameter(self._node.at("DirectionAngular"))
    @property
    def DirectionLinear(self):  # type: ()->ConditionalRigidityAttribute_RigidityParameter
        return ConditionalRigidityAttribute_RigidityParameter(self._node.at("DirectionLinear"))
    @property
    def OscillationAngular(self):  # type: ()->ConditionalRigidityAttribute_RigidityParameter
        return ConditionalRigidityAttribute_RigidityParameter(self._node.at("OscillationAngular"))
    @property
    def OscillationLinear(self):  # type: ()->ConditionalRigidityAttribute_RigidityParameter
        return ConditionalRigidityAttribute_RigidityParameter(self._node.at("OscillationLinear"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class ConditionalRigidityAttribute(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ConditionalRigidityAttribute"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ConditionalRigidityAttribute
        return ConditionalRigidityAttribute(entlib.load_node_file(sourcefile, entlib.get_schema(ConditionalRigidityAttribute.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ConditionalRigidityAttribute
        return ConditionalRigidityAttribute(entlib.make_node(ConditionalRigidityAttribute.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Attributes(self):  # type: ()->ConditionalRigidityAttribute_Attributes
        return ConditionalRigidityAttribute_Attributes(self._node.at("Attributes"))
    @property
    def Conditions(self):  # type: ()->ConditionalRigidityAttribute_Conditions
        return ConditionalRigidityAttribute_Conditions(self._node.at("Conditions"))
    @property
    def Default(self):  # type: ()->Bool
        return Bool(self._node.at("Default"))
    @Default.setter
    def Default(self, val): self.Default.set(val)
    @property
    def Name(self):  # type: ()->String
        return String(self._node.at("Name"))
    @Name.setter
    def Name(self, val): self.Name.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class ComponentGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ComponentGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ComponentGD
        return ComponentGD(entlib.load_node_file(sourcefile, entlib.get_schema(ComponentGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ComponentGD
        return ComponentGD(entlib.make_node(ComponentGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    pass


from EntityLibPy import Node

class WorldScalePathFindGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/WorldScalePathFindGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->WorldScalePathFindGD
        return WorldScalePathFindGD(entlib.load_node_file(sourcefile, entlib.get_schema(WorldScalePathFindGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->WorldScalePathFindGD
        return WorldScalePathFindGD(entlib.make_node(WorldScalePathFindGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def FilePath(self):  # type: ()->String
        return String(self._node.at("FilePath"))
    @FilePath.setter
    def FilePath(self, val): self.FilePath.set(val)
    @property
    def GenerationParameters(self):  # type: ()->Array[NavmeshGenerationParameters]
        return (lambda n: Array(NavmeshGenerationParameters, n))(self._node.at("GenerationParameters"))
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class WildObject(HelperObject):
    schema_name = "./EditionComponents.json#/definitions/WildObject"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->WildObject
        return WildObject(entlib.load_node_file(sourcefile, entlib.get_schema(WildObject.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->WildObject
        return WildObject(entlib.make_node(WildObject.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def GdPath(self):  # type: ()->String
        return String(self._node.at("GdPath"))
    @GdPath.setter
    def GdPath(self, val): self.GdPath.set(val)
    @property
    def ObjectType(self):  # type: ()->String
        return String(self._node.at("ObjectType"))
    @ObjectType.setter
    def ObjectType(self, val): self.ObjectType.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class VoxelSimulationGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/VoxelSimulationGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->VoxelSimulationGD
        return VoxelSimulationGD(entlib.load_node_file(sourcefile, entlib.get_schema(VoxelSimulationGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->VoxelSimulationGD
        return VoxelSimulationGD(entlib.make_node(VoxelSimulationGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def FilePath(self):  # type: ()->String
        return String(self._node.at("FilePath"))
    @FilePath.setter
    def FilePath(self, val): self.FilePath.set(val)
    @property
    def LossBySecond(self):  # type: ()->Float
        return Float(self._node.at("LossBySecond"))
    @LossBySecond.setter
    def LossBySecond(self, val): self.LossBySecond.set(val)
    @property
    def LostRatio(self):  # type: ()->Float
        return Float(self._node.at("LostRatio"))
    @LostRatio.setter
    def LostRatio(self, val): self.LostRatio.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def TransmissionBySecond(self):  # type: ()->Float
        return Float(self._node.at("TransmissionBySecond"))
    @TransmissionBySecond.setter
    def TransmissionBySecond(self, val): self.TransmissionBySecond.set(val)
    @property
    def TransmittedRatio(self):  # type: ()->Float
        return Float(self._node.at("TransmittedRatio"))
    @TransmittedRatio.setter
    def TransmittedRatio(self, val): self.TransmittedRatio.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class VolumeConstraintGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/VolumeConstraintGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->VolumeConstraintGD
        return VolumeConstraintGD(entlib.load_node_file(sourcefile, entlib.get_schema(VolumeConstraintGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->VolumeConstraintGD
        return VolumeConstraintGD(entlib.make_node(VolumeConstraintGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Constraints(self):  # type: ()->Array[VolumeConstraintDataGD]
        return (lambda n: Array(VolumeConstraintDataGD, n))(self._node.at("Constraints"))
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class VisualGD(HelperObject):
    schema_name = "./MergedComponents.json#/definitions/VisualGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->VisualGD
        return VisualGD(entlib.load_node_file(sourcefile, entlib.get_schema(VisualGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->VisualGD
        return VisualGD(entlib.make_node(VisualGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AlwaysStatic(self):  # type: ()->Bool
        return Bool(self._node.at("AlwaysStatic"))
    @AlwaysStatic.setter
    def AlwaysStatic(self, val): self.AlwaysStatic.set(val)
    @property
    def EDITOR_GenerateFur(self):  # type: ()->Bool
        return Bool(self._node.at("EDITOR_GenerateFur"))
    @EDITOR_GenerateFur.setter
    def EDITOR_GenerateFur(self, val): self.EDITOR_GenerateFur.set(val)
    @property
    def EDITOR_LODs(self):  # type: ()->Array[EDITOR_LODsItem]
        return (lambda n: Array(EDITOR_LODsItem, n))(self._node.at("EDITOR_LODs"))
    @property
    def RUNTIME_LODScale(self):  # type: ()->Float
        return Float(self._node.at("RUNTIME_LODScale"))
    @RUNTIME_LODScale.setter
    def RUNTIME_LODScale(self, val): self.RUNTIME_LODScale.set(val)
    @property
    def RUNTIME_LODs(self):  # type: ()->Array[RUNTIME_LODsItem]
        return (lambda n: Array(RUNTIME_LODsItem, n))(self._node.at("RUNTIME_LODs"))
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def VisualResourcePath(self):  # type: ()->String
        return String(self._node.at("VisualResourcePath"))
    @VisualResourcePath.setter
    def VisualResourcePath(self, val): self.VisualResourcePath.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class VelocityObstacleGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/VelocityObstacleGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->VelocityObstacleGD
        return VelocityObstacleGD(entlib.load_node_file(sourcefile, entlib.get_schema(VelocityObstacleGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->VelocityObstacleGD
        return VelocityObstacleGD(entlib.make_node(VelocityObstacleGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AccelerationAfterAvoidance(self):  # type: ()->Float
        return Float(self._node.at("AccelerationAfterAvoidance"))
    @AccelerationAfterAvoidance.setter
    def AccelerationAfterAvoidance(self, val): self.AccelerationAfterAvoidance.set(val)
    @property
    def Radius(self):  # type: ()->Float
        return Float(self._node.at("Radius"))
    @Radius.setter
    def Radius(self, val): self.Radius.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class UnifiedPhysicsDataGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/UnifiedPhysicsDataGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->UnifiedPhysicsDataGD
        return UnifiedPhysicsDataGD(entlib.load_node_file(sourcefile, entlib.get_schema(UnifiedPhysicsDataGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->UnifiedPhysicsDataGD
        return UnifiedPhysicsDataGD(entlib.make_node(UnifiedPhysicsDataGD.schema_name))
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
    pass


from EntityLibPy import Node

class TriggerEventCameraGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/TriggerEventCameraGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->TriggerEventCameraGD
        return TriggerEventCameraGD(entlib.load_node_file(sourcefile, entlib.get_schema(TriggerEventCameraGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->TriggerEventCameraGD
        return TriggerEventCameraGD(entlib.make_node(TriggerEventCameraGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def EventCameraData(self):  # type: ()->EventCameraData
        return EventCameraData(self._node.at("EventCameraData"))
    @property
    def PlayAnimBeforeTrigger(self):  # type: ()->String
        return String(self._node.at("PlayAnimBeforeTrigger"))
    @PlayAnimBeforeTrigger.setter
    def PlayAnimBeforeTrigger(self, val): self.PlayAnimBeforeTrigger.set(val)
    @property
    def PlayAnimsWhenTriggered(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("PlayAnimsWhenTriggered"))
    @PlayAnimsWhenTriggered.setter
    def PlayAnimsWhenTriggered(self, val): self.PlayAnimsWhenTriggered.set(val)
    @property
    def Radius(self):  # type: ()->Float
        return Float(self._node.at("Radius"))
    @Radius.setter
    def Radius(self, val): self.Radius.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def UseDuration(self):  # type: ()->Bool
        return Bool(self._node.at("UseDuration"))
    @UseDuration.setter
    def UseDuration(self, val): self.UseDuration.set(val)
    @property
    def UsePhysics(self):  # type: ()->Bool
        return Bool(self._node.at("UsePhysics"))
    @UsePhysics.setter
    def UsePhysics(self, val): self.UsePhysics.set(val)
    @property
    def UseRadius(self):  # type: ()->Bool
        return Bool(self._node.at("UseRadius"))
    @UseRadius.setter
    def UseRadius(self, val): self.UseRadius.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class TransformGD(HelperObject):
    schema_name = "./MergedComponents.json#/definitions/TransformGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->TransformGD
        return TransformGD(entlib.load_node_file(sourcefile, entlib.get_schema(TransformGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->TransformGD
        return TransformGD(entlib.make_node(TransformGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def EDITOR_InheritScaleFromSubSceneHolder(self):  # type: ()->Bool
        return Bool(self._node.at("EDITOR_InheritScaleFromSubSceneHolder"))
    @EDITOR_InheritScaleFromSubSceneHolder.setter
    def EDITOR_InheritScaleFromSubSceneHolder(self, val): self.EDITOR_InheritScaleFromSubSceneHolder.set(val)
    @property
    def EDITOR_PropagateScaleToSubScene(self):  # type: ()->Bool
        return Bool(self._node.at("EDITOR_PropagateScaleToSubScene"))
    @EDITOR_PropagateScaleToSubScene.setter
    def EDITOR_PropagateScaleToSubScene(self, val): self.EDITOR_PropagateScaleToSubScene.set(val)
    @property
    def Matrix(self):  # type: ()->Matrix33
        return Matrix33(self._node.at("Matrix"))
    @Matrix.setter
    def Matrix(self, val): self.Matrix.set(val)
    @property
    def Orientation(self):  # type: ()->Quat
        return Quat(self._node.at("Orientation"))
    @Orientation.setter
    def Orientation(self, val): self.Orientation.set(val)
    @property
    def Position(self):  # type: ()->Vector3
        return Vector3(self._node.at("Position"))
    @Position.setter
    def Position(self, val): self.Position.set(val)
    @property
    def Scale(self):  # type: ()->Vector3
        return Vector3(self._node.at("Scale"))
    @Scale.setter
    def Scale(self, val): self.Scale.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class TestUnion(HelperObject):
    schema_name = "./EditionComponents.json#/definitions/TestUnion"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->TestUnion
        return TestUnion(entlib.load_node_file(sourcefile, entlib.get_schema(TestUnion.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->TestUnion
        return TestUnion(entlib.make_node(TestUnion.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def Union(self):  # type: ()->variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_
        return variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_(self._node.at("Union"))
    @property
    def UnionArray(self):  # type: ()->Array[variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_]
        return (lambda n: Array(variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_, n))(self._node.at("UnionArray"))
    @property
    def UnionObjectArray(self):  # type: ()->Array[UnionObjectArrayItem]
        return (lambda n: Array(UnionObjectArrayItem, n))(self._node.at("UnionObjectArray"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class TestSetOfObject(HelperObject):
    schema_name = "./EditionComponents.json#/definitions/TestSetOfObject"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->TestSetOfObject
        return TestSetOfObject(entlib.load_node_file(sourcefile, entlib.get_schema(TestSetOfObject.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->TestSetOfObject
        return TestSetOfObject(entlib.make_node(TestSetOfObject.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def MapOfObject(self):  # type: ()->Map[str, MapOfObjectItem_A]
        return (lambda n: Map(str, MapOfObjectItem_A, n))(self._node.at("MapOfObject"))
    @property
    def SetOfObject(self):  # type: ()->ObjectSet[SetOfObjectItem]
        return (lambda n: ObjectSet(SetOfObjectItem, n))(self._node.at("SetOfObject"))
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class TestEntityRef(HelperObject):
    schema_name = "./EditionComponents.json#/definitions/TestEntityRef"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->TestEntityRef
        return TestEntityRef(entlib.load_node_file(sourcefile, entlib.get_schema(TestEntityRef.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->TestEntityRef
        return TestEntityRef(entlib.make_node(TestEntityRef.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def TestRef(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("TestRef"))
    @TestRef.setter
    def TestRef(self, val): self.TestRef.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class TestDefaultValues(HelperObject):
    schema_name = "./EditionComponents.json#/definitions/TestDefaultValues"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->TestDefaultValues
        return TestDefaultValues(entlib.load_node_file(sourcefile, entlib.get_schema(TestDefaultValues.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->TestDefaultValues
        return TestDefaultValues(entlib.make_node(TestDefaultValues.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Matrix(self):  # type: ()->Matrix33
        return Matrix33(self._node.at("Matrix"))
    @Matrix.setter
    def Matrix(self, val): self.Matrix.set(val)
    @property
    def Matrix2(self):  # type: ()->Matrix33
        return Matrix33(self._node.at("Matrix2"))
    @Matrix2.setter
    def Matrix2(self, val): self.Matrix2.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def propertyWithDefault(self):  # type: ()->TestPropertyDefaultValues2
        return TestPropertyDefaultValues2(self._node.at("propertyWithDefault"))
    pass


from EntityLibPy import Node

class TestCreature(HelperObject):
    schema_name = "./EditionComponents.json#/definitions/TestCreature"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->TestCreature
        return TestCreature(entlib.load_node_file(sourcefile, entlib.get_schema(TestCreature.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->TestCreature
        return TestCreature(entlib.make_node(TestCreature.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def FullCursed(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("FullCursed"))
    @FullCursed.setter
    def FullCursed(self, val): self.FullCursed.set(val)
    @property
    def FullLush(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("FullLush"))
    @FullLush.setter
    def FullLush(self, val): self.FullLush.set(val)
    @property
    def SklCursed(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("SklCursed"))
    @SklCursed.setter
    def SklCursed(self, val): self.SklCursed.set(val)
    @property
    def SklLush(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("SklLush"))
    @SklLush.setter
    def SklLush(self, val): self.SklLush.set(val)
    @property
    def SklNeutral(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("SklNeutral"))
    @SklNeutral.setter
    def SklNeutral(self, val): self.SklNeutral.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class TestArrays(HelperObject):
    schema_name = "./EditionComponents.json#/definitions/TestArrays"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->TestArrays
        return TestArrays(entlib.load_node_file(sourcefile, entlib.get_schema(TestArrays.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->TestArrays
        return TestArrays(entlib.make_node(TestArrays.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def DefaultValue(self):  # type: ()->PrimArray[Float]
        return (lambda n: PrimArray(Float, n))(self._node.at("DefaultValue"))
    @DefaultValue.setter
    def DefaultValue(self, val): self.DefaultValue.set(val)
    @property
    def OverridedDefaultValue(self):  # type: ()->PrimArray[Float]
        return (lambda n: PrimArray(Float, n))(self._node.at("OverridedDefaultValue"))
    @OverridedDefaultValue.setter
    def OverridedDefaultValue(self, val): self.OverridedDefaultValue.set(val)
    @property
    def OverridedPrefabValue(self):  # type: ()->PrimArray[Float]
        return (lambda n: PrimArray(Float, n))(self._node.at("OverridedPrefabValue"))
    @OverridedPrefabValue.setter
    def OverridedPrefabValue(self, val): self.OverridedPrefabValue.set(val)
    @property
    def PrefabValue(self):  # type: ()->PrimArray[Float]
        return (lambda n: PrimArray(Float, n))(self._node.at("PrefabValue"))
    @PrefabValue.setter
    def PrefabValue(self, val): self.PrefabValue.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def Variant(self):  # type: ()->variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_
        return variant_s32_float_bool_string_Vector2_Vector3_Quat_Position_(self._node.at("Variant"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class TerrainSurfaceObject(HelperObject):
    schema_name = "./EditionComponents.json#/definitions/TerrainSurfaceObject"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->TerrainSurfaceObject
        return TerrainSurfaceObject(entlib.load_node_file(sourcefile, entlib.get_schema(TerrainSurfaceObject.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->TerrainSurfaceObject
        return TerrainSurfaceObject(entlib.make_node(TerrainSurfaceObject.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def EDITOR_tso(self):  # type: ()->String
        return String(self._node.at("EDITOR_tso"))
    @EDITOR_tso.setter
    def EDITOR_tso(self, val): self.EDITOR_tso.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class TerrainGD(HelperObject):
    schema_name = "./MergedComponents.json#/definitions/TerrainGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->TerrainGD
        return TerrainGD(entlib.load_node_file(sourcefile, entlib.get_schema(TerrainGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->TerrainGD
        return TerrainGD(entlib.make_node(TerrainGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def EDITOR_AlbedoType(self):  # type: ()->Int
        return Int(self._node.at("EDITOR_AlbedoType"))
    @EDITOR_AlbedoType.setter
    def EDITOR_AlbedoType(self, val): self.EDITOR_AlbedoType.set(val)
    @property
    def EDITOR_CavityAlbedoStrength(self):  # type: ()->Float
        return Float(self._node.at("EDITOR_CavityAlbedoStrength"))
    @EDITOR_CavityAlbedoStrength.setter
    def EDITOR_CavityAlbedoStrength(self, val): self.EDITOR_CavityAlbedoStrength.set(val)
    @property
    def EDITOR_CavityStrength(self):  # type: ()->Float
        return Float(self._node.at("EDITOR_CavityStrength"))
    @EDITOR_CavityStrength.setter
    def EDITOR_CavityStrength(self, val): self.EDITOR_CavityStrength.set(val)
    @property
    def EDITOR_CollisionDecimateHmm(self):  # type: ()->Float
        return Float(self._node.at("EDITOR_CollisionDecimateHmm"))
    @EDITOR_CollisionDecimateHmm.setter
    def EDITOR_CollisionDecimateHmm(self, val): self.EDITOR_CollisionDecimateHmm.set(val)
    @property
    def EDITOR_ComputeSurfaceObjectTerrain(self):  # type: ()->Bool
        return Bool(self._node.at("EDITOR_ComputeSurfaceObjectTerrain"))
    @EDITOR_ComputeSurfaceObjectTerrain.setter
    def EDITOR_ComputeSurfaceObjectTerrain(self, val): self.EDITOR_ComputeSurfaceObjectTerrain.set(val)
    @property
    def EDITOR_DebugMode(self):  # type: ()->Bool
        return Bool(self._node.at("EDITOR_DebugMode"))
    @EDITOR_DebugMode.setter
    def EDITOR_DebugMode(self, val): self.EDITOR_DebugMode.set(val)
    @property
    def EDITOR_DetailMapFalloff(self):  # type: ()->Int
        return Int(self._node.at("EDITOR_DetailMapFalloff"))
    @EDITOR_DetailMapFalloff.setter
    def EDITOR_DetailMapFalloff(self, val): self.EDITOR_DetailMapFalloff.set(val)
    @property
    def EDITOR_DetailScale(self):  # type: ()->Float
        return Float(self._node.at("EDITOR_DetailScale"))
    @EDITOR_DetailScale.setter
    def EDITOR_DetailScale(self, val): self.EDITOR_DetailScale.set(val)
    @property
    def EDITOR_DisableSeedParams(self):  # type: ()->Bool
        return Bool(self._node.at("EDITOR_DisableSeedParams"))
    @EDITOR_DisableSeedParams.setter
    def EDITOR_DisableSeedParams(self, val): self.EDITOR_DisableSeedParams.set(val)
    @property
    def EDITOR_DisplayAlbedo(self):  # type: ()->Bool
        return Bool(self._node.at("EDITOR_DisplayAlbedo"))
    @EDITOR_DisplayAlbedo.setter
    def EDITOR_DisplayAlbedo(self, val): self.EDITOR_DisplayAlbedo.set(val)
    @property
    def EDITOR_DisplayFinal(self):  # type: ()->Bool
        return Bool(self._node.at("EDITOR_DisplayFinal"))
    @EDITOR_DisplayFinal.setter
    def EDITOR_DisplayFinal(self, val): self.EDITOR_DisplayFinal.set(val)
    @property
    def EDITOR_Distributed(self):  # type: ()->Bool
        return Bool(self._node.at("EDITOR_Distributed"))
    @EDITOR_Distributed.setter
    def EDITOR_Distributed(self, val): self.EDITOR_Distributed.set(val)
    @property
    def EDITOR_Erosion(self):  # type: ()->Bool
        return Bool(self._node.at("EDITOR_Erosion"))
    @EDITOR_Erosion.setter
    def EDITOR_Erosion(self, val): self.EDITOR_Erosion.set(val)
    @property
    def EDITOR_ErosionType(self):  # type: ()->Int
        return Int(self._node.at("EDITOR_ErosionType"))
    @EDITOR_ErosionType.setter
    def EDITOR_ErosionType(self, val): self.EDITOR_ErosionType.set(val)
    @property
    def EDITOR_ExportCollision(self):  # type: ()->Bool
        return Bool(self._node.at("EDITOR_ExportCollision"))
    @EDITOR_ExportCollision.setter
    def EDITOR_ExportCollision(self, val): self.EDITOR_ExportCollision.set(val)
    @property
    def EDITOR_ExportQuality(self):  # type: ()->Int
        return Int(self._node.at("EDITOR_ExportQuality"))
    @EDITOR_ExportQuality.setter
    def EDITOR_ExportQuality(self, val): self.EDITOR_ExportQuality.set(val)
    @property
    def EDITOR_LocalSndbs(self):  # type: ()->Bool
        return Bool(self._node.at("EDITOR_LocalSndbs"))
    @EDITOR_LocalSndbs.setter
    def EDITOR_LocalSndbs(self, val): self.EDITOR_LocalSndbs.set(val)
    @property
    def EDITOR_MergeTSOPreview(self):  # type: ()->Bool
        return Bool(self._node.at("EDITOR_MergeTSOPreview"))
    @EDITOR_MergeTSOPreview.setter
    def EDITOR_MergeTSOPreview(self, val): self.EDITOR_MergeTSOPreview.set(val)
    @property
    def EDITOR_MultiLayerHeightmap(self):  # type: ()->Bool
        return Bool(self._node.at("EDITOR_MultiLayerHeightmap"))
    @EDITOR_MultiLayerHeightmap.setter
    def EDITOR_MultiLayerHeightmap(self, val): self.EDITOR_MultiLayerHeightmap.set(val)
    @property
    def EDITOR_Path(self):  # type: ()->String
        return String(self._node.at("EDITOR_Path"))
    @EDITOR_Path.setter
    def EDITOR_Path(self, val): self.EDITOR_Path.set(val)
    @property
    def EDITOR_PreviewQuality(self):  # type: ()->Int
        return Int(self._node.at("EDITOR_PreviewQuality"))
    @EDITOR_PreviewQuality.setter
    def EDITOR_PreviewQuality(self, val): self.EDITOR_PreviewQuality.set(val)
    @property
    def EDITOR_ProcessDetailMap(self):  # type: ()->Bool
        return Bool(self._node.at("EDITOR_ProcessDetailMap"))
    @EDITOR_ProcessDetailMap.setter
    def EDITOR_ProcessDetailMap(self, val): self.EDITOR_ProcessDetailMap.set(val)
    @property
    def EDITOR_SeedTextureSizeReduce(self):  # type: ()->Int
        return Int(self._node.at("EDITOR_SeedTextureSizeReduce"))
    @EDITOR_SeedTextureSizeReduce.setter
    def EDITOR_SeedTextureSizeReduce(self, val): self.EDITOR_SeedTextureSizeReduce.set(val)
    @property
    def EDITOR_SuperimposeSeeds(self):  # type: ()->Bool
        return Bool(self._node.at("EDITOR_SuperimposeSeeds"))
    @EDITOR_SuperimposeSeeds.setter
    def EDITOR_SuperimposeSeeds(self, val): self.EDITOR_SuperimposeSeeds.set(val)
    @property
    def EDITOR_SurfaceObjectDecimate(self):  # type: ()->Float
        return Float(self._node.at("EDITOR_SurfaceObjectDecimate"))
    @EDITOR_SurfaceObjectDecimate.setter
    def EDITOR_SurfaceObjectDecimate(self, val): self.EDITOR_SurfaceObjectDecimate.set(val)
    @property
    def EDITOR_SurfaceObjectDecimateHmm(self):  # type: ()->Float
        return Float(self._node.at("EDITOR_SurfaceObjectDecimateHmm"))
    @EDITOR_SurfaceObjectDecimateHmm.setter
    def EDITOR_SurfaceObjectDecimateHmm(self, val): self.EDITOR_SurfaceObjectDecimateHmm.set(val)
    @property
    def EDITOR_TerrainWildMat(self):  # type: ()->String
        return String(self._node.at("EDITOR_TerrainWildMat"))
    @EDITOR_TerrainWildMat.setter
    def EDITOR_TerrainWildMat(self, val): self.EDITOR_TerrainWildMat.set(val)
    @property
    def EDITOR_TriPerMeter(self):  # type: ()->Int
        return Int(self._node.at("EDITOR_TriPerMeter"))
    @EDITOR_TriPerMeter.setter
    def EDITOR_TriPerMeter(self, val): self.EDITOR_TriPerMeter.set(val)
    @property
    def EDITOR_WMErosionComputeDistant(self):  # type: ()->Bool
        return Bool(self._node.at("EDITOR_WMErosionComputeDistant"))
    @EDITOR_WMErosionComputeDistant.setter
    def EDITOR_WMErosionComputeDistant(self, val): self.EDITOR_WMErosionComputeDistant.set(val)
    @property
    def EDITOR_WMErosionPreview(self):  # type: ()->Bool
        return Bool(self._node.at("EDITOR_WMErosionPreview"))
    @EDITOR_WMErosionPreview.setter
    def EDITOR_WMErosionPreview(self, val): self.EDITOR_WMErosionPreview.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def TerrainMeta(self):  # type: ()->Terrain_TerrainMeta
        return Terrain_TerrainMeta(self._node.at("TerrainMeta"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class TeamGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/TeamGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->TeamGD
        return TeamGD(entlib.load_node_file(sourcefile, entlib.get_schema(TeamGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->TeamGD
        return TeamGD(entlib.make_node(TeamGD.schema_name))
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
    pass


from EntityLibPy import Node

class SystemicCreature(HelperObject):
    schema_name = "./EditionComponents.json#/definitions/SystemicCreature"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->SystemicCreature
        return SystemicCreature(entlib.load_node_file(sourcefile, entlib.get_schema(SystemicCreature.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->SystemicCreature
        return SystemicCreature(entlib.make_node(SystemicCreature.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def BehaviorModifierTagList(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("BehaviorModifierTagList"))
    @BehaviorModifierTagList.setter
    def BehaviorModifierTagList(self, val): self.BehaviorModifierTagList.set(val)
    @property
    def BehaviorPath(self):  # type: ()->String
        return String(self._node.at("BehaviorPath"))
    @BehaviorPath.setter
    def BehaviorPath(self, val): self.BehaviorPath.set(val)
    @property
    def BehaviorState(self):  # type: ()->String
        return String(self._node.at("BehaviorState"))
    @BehaviorState.setter
    def BehaviorState(self, val): self.BehaviorState.set(val)
    @property
    def Burried(self):  # type: ()->Bool
        return Bool(self._node.at("Burried"))
    @Burried.setter
    def Burried(self, val): self.Burried.set(val)
    @property
    def CameraTarget(self):  # type: ()->Bool
        return Bool(self._node.at("CameraTarget"))
    @CameraTarget.setter
    def CameraTarget(self, val): self.CameraTarget.set(val)
    @property
    def CanBeMaster(self):  # type: ()->Bool
        return Bool(self._node.at("CanBeMaster"))
    @CanBeMaster.setter
    def CanBeMaster(self, val): self.CanBeMaster.set(val)
    @property
    def Faction(self):  # type: ()->String
        return String(self._node.at("Faction"))
    @Faction.setter
    def Faction(self, val): self.Faction.set(val)
    @property
    def Inventory(self):  # type: ()->String
        return String(self._node.at("Inventory"))
    @Inventory.setter
    def Inventory(self, val): self.Inventory.set(val)
    @property
    def Invincible(self):  # type: ()->Bool
        return Bool(self._node.at("Invincible"))
    @Invincible.setter
    def Invincible(self, val): self.Invincible.set(val)
    @property
    def Life(self):  # type: ()->Float
        return Float(self._node.at("Life"))
    @Life.setter
    def Life(self, val): self.Life.set(val)
    @property
    def Name(self):  # type: ()->String
        return String(self._node.at("Name"))
    @Name.setter
    def Name(self, val): self.Name.set(val)
    @property
    def PlayerSpawn(self):  # type: ()->Bool
        return Bool(self._node.at("PlayerSpawn"))
    @PlayerSpawn.setter
    def PlayerSpawn(self, val): self.PlayerSpawn.set(val)
    @property
    def ScriptList(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("ScriptList"))
    @ScriptList.setter
    def ScriptList(self, val): self.ScriptList.set(val)
    @property
    def Spawner(self):  # type: ()->String
        return String(self._node.at("Spawner"))
    @Spawner.setter
    def Spawner(self, val): self.Spawner.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def UniqueID(self):  # type: ()->String
        return String(self._node.at("UniqueID"))
    @UniqueID.setter
    def UniqueID(self, val): self.UniqueID.set(val)
    @property
    def Warrior(self):  # type: ()->Bool
        return Bool(self._node.at("Warrior"))
    @Warrior.setter
    def Warrior(self, val): self.Warrior.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class SubScene(HelperObject):
    schema_name = "./EditionComponents.json#/definitions/SubScene"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->SubScene
        return SubScene(entlib.load_node_file(sourcefile, entlib.get_schema(SubScene.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->SubScene
        return SubScene(entlib.make_node(SubScene.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Embedded(self):  # type: ()->ObjectSet[Entity]
        return (lambda n: ObjectSet(Entity, n))(self._node.at("Embedded"))
    @property
    def File(self):  # type: ()->String
        return String(self._node.at("File"))
    @File.setter
    def File(self, val): self.File.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def isEmbedded(self):  # type: ()->Bool
        return Bool(self._node.at("isEmbedded"))
    @isEmbedded.setter
    def isEmbedded(self, val): self.isEmbedded.set(val)
    pass


from EntityLibPy import Node

class StickToTerrain(HelperObject):
    schema_name = "./EditionComponents.json#/definitions/StickToTerrain"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->StickToTerrain
        return StickToTerrain(entlib.load_node_file(sourcefile, entlib.get_schema(StickToTerrain.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->StickToTerrain
        return StickToTerrain(entlib.make_node(StickToTerrain.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def NormalRatio(self):  # type: ()->Float
        return Float(self._node.at("NormalRatio"))
    @NormalRatio.setter
    def NormalRatio(self, val): self.NormalRatio.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def ZOffset(self):  # type: ()->Float
        return Float(self._node.at("ZOffset"))
    @ZOffset.setter
    def ZOffset(self, val): self.ZOffset.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def precisionRadius(self):  # type: ()->Float
        return Float(self._node.at("precisionRadius"))
    @precisionRadius.setter
    def precisionRadius(self, val): self.precisionRadius.set(val)
    @property
    def useNormal(self):  # type: ()->Bool
        return Bool(self._node.at("useNormal"))
    @useNormal.setter
    def useNormal(self, val): self.useNormal.set(val)
    pass


from EntityLibPy import Node

class StaticObjectGD(HelperObject):
    schema_name = "./MergedComponents.json#/definitions/StaticObjectGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->StaticObjectGD
        return StaticObjectGD(entlib.load_node_file(sourcefile, entlib.get_schema(StaticObjectGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->StaticObjectGD
        return StaticObjectGD(entlib.make_node(StaticObjectGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def EDITOR_IsCave(self):  # type: ()->Bool
        return Bool(self._node.at("EDITOR_IsCave"))
    @EDITOR_IsCave.setter
    def EDITOR_IsCave(self, val): self.EDITOR_IsCave.set(val)
    @property
    def EDITOR_UsedInMultiLayerHeightmap(self):  # type: ()->Bool
        return Bool(self._node.at("EDITOR_UsedInMultiLayerHeightmap"))
    @EDITOR_UsedInMultiLayerHeightmap.setter
    def EDITOR_UsedInMultiLayerHeightmap(self, val): self.EDITOR_UsedInMultiLayerHeightmap.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def Visual(self):  # type: ()->Bool
        return Bool(self._node.at("Visual"))
    @Visual.setter
    def Visual(self, val): self.Visual.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class StaffVertebrasGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/StaffVertebrasGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->StaffVertebrasGD
        return StaffVertebrasGD(entlib.load_node_file(sourcefile, entlib.get_schema(StaffVertebrasGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->StaffVertebrasGD
        return StaffVertebrasGD(entlib.make_node(StaffVertebrasGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def HotspotNames(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("HotspotNames"))
    @HotspotNames.setter
    def HotspotNames(self, val): self.HotspotNames.set(val)
    @property
    def MaxVertebraCount(self):  # type: ()->Int
        return Int(self._node.at("MaxVertebraCount"))
    @MaxVertebraCount.setter
    def MaxVertebraCount(self, val): self.MaxVertebraCount.set(val)
    @property
    def OwnedVertebraStartCount(self):  # type: ()->Int
        return Int(self._node.at("OwnedVertebraStartCount"))
    @OwnedVertebraStartCount.setter
    def OwnedVertebraStartCount(self, val): self.OwnedVertebraStartCount.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def VertebraGRCPath1(self):  # type: ()->String
        return String(self._node.at("VertebraGRCPath1"))
    @VertebraGRCPath1.setter
    def VertebraGRCPath1(self, val): self.VertebraGRCPath1.set(val)
    @property
    def VertebraGRCPath2(self):  # type: ()->String
        return String(self._node.at("VertebraGRCPath2"))
    @VertebraGRCPath2.setter
    def VertebraGRCPath2(self, val): self.VertebraGRCPath2.set(val)
    @property
    def VertebraGRCPath3(self):  # type: ()->String
        return String(self._node.at("VertebraGRCPath3"))
    @VertebraGRCPath3.setter
    def VertebraGRCPath3(self, val): self.VertebraGRCPath3.set(val)
    @property
    def VertebraGRCPath4(self):  # type: ()->String
        return String(self._node.at("VertebraGRCPath4"))
    @VertebraGRCPath4.setter
    def VertebraGRCPath4(self, val): self.VertebraGRCPath4.set(val)
    @property
    def VomitData(self):  # type: ()->VomitData
        return VomitData(self._node.at("VomitData"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class SoundEmitterGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/SoundEmitterGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->SoundEmitterGD
        return SoundEmitterGD(entlib.load_node_file(sourcefile, entlib.get_schema(SoundEmitterGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->SoundEmitterGD
        return SoundEmitterGD(entlib.make_node(SoundEmitterGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def ActivationDistance(self):  # type: ()->Float
        return Float(self._node.at("ActivationDistance"))
    @ActivationDistance.setter
    def ActivationDistance(self, val): self.ActivationDistance.set(val)
    @property
    def ActivationSound(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("ActivationSound"))
    @ActivationSound.setter
    def ActivationSound(self, val): self.ActivationSound.set(val)
    @property
    def ActivationSync(self):  # type: ()->SyncTempoMode
        return SyncTempoMode(self._node.at("ActivationSync"))
    @ActivationSync.setter
    def ActivationSync(self, val): self.ActivationSync.set(val)
    @property
    def AuxSend(self):  # type: ()->String
        return String(self._node.at("AuxSend"))
    @AuxSend.setter
    def AuxSend(self, val): self.AuxSend.set(val)
    @property
    def Bank(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("Bank"))
    @Bank.setter
    def Bank(self, val): self.Bank.set(val)
    @property
    def BoidRadius(self):  # type: ()->Float
        return Float(self._node.at("BoidRadius"))
    @BoidRadius.setter
    def BoidRadius(self, val): self.BoidRadius.set(val)
    @property
    def BoidRadiusToInnerEdgeRatio(self):  # type: ()->Float
        return Float(self._node.at("BoidRadiusToInnerEdgeRatio"))
    @BoidRadiusToInnerEdgeRatio.setter
    def BoidRadiusToInnerEdgeRatio(self, val): self.BoidRadiusToInnerEdgeRatio.set(val)
    @property
    def BoidRadiusToOuterEdgeRatio(self):  # type: ()->Float
        return Float(self._node.at("BoidRadiusToOuterEdgeRatio"))
    @BoidRadiusToOuterEdgeRatio.setter
    def BoidRadiusToOuterEdgeRatio(self, val): self.BoidRadiusToOuterEdgeRatio.set(val)
    @property
    def BoidRealPositionComputation(self):  # type: ()->Bool
        return Bool(self._node.at("BoidRealPositionComputation"))
    @BoidRealPositionComputation.setter
    def BoidRealPositionComputation(self, val): self.BoidRealPositionComputation.set(val)
    @property
    def CreatureType(self):  # type: ()->String
        return String(self._node.at("CreatureType"))
    @CreatureType.setter
    def CreatureType(self, val): self.CreatureType.set(val)
    @property
    def Echoes(self):  # type: ()->Bool
        return Bool(self._node.at("Echoes"))
    @Echoes.setter
    def Echoes(self, val): self.Echoes.set(val)
    @property
    def EchoesSend(self):  # type: ()->Float
        return Float(self._node.at("EchoesSend"))
    @EchoesSend.setter
    def EchoesSend(self, val): self.EchoesSend.set(val)
    @property
    def EventDistance(self):  # type: ()->Float
        return Float(self._node.at("EventDistance"))
    @EventDistance.setter
    def EventDistance(self, val): self.EventDistance.set(val)
    @property
    def EventMapping(self):  # type: ()->SoundEventMapping
        return SoundEventMapping(self._node.at("EventMapping"))
    @property
    def ExplicitEventMapping(self):  # type: ()->Map[str, String]
        return (lambda n: Map(str, String, n))(self._node.at("ExplicitEventMapping"))
    @property
    def InEvents(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("InEvents"))
    @InEvents.setter
    def InEvents(self, val): self.InEvents.set(val)
    @property
    def OutEvents(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("OutEvents"))
    @OutEvents.setter
    def OutEvents(self, val): self.OutEvents.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def UnactivationSound(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("UnactivationSound"))
    @UnactivationSound.setter
    def UnactivationSound(self, val): self.UnactivationSound.set(val)
    @property
    def UnactivationSync(self):  # type: ()->SyncTempoMode
        return SyncTempoMode(self._node.at("UnactivationSync"))
    @UnactivationSync.setter
    def UnactivationSync(self, val): self.UnactivationSync.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def dopplerActivated(self):  # type: ()->Bool
        return Bool(self._node.at("dopplerActivated"))
    @dopplerActivated.setter
    def dopplerActivated(self, val): self.dopplerActivated.set(val)
    @property
    def relativeHeightPriority(self):  # type: ()->Int
        return Int(self._node.at("relativeHeightPriority"))
    @relativeHeightPriority.setter
    def relativeHeightPriority(self, val): self.relativeHeightPriority.set(val)
    @property
    def sendSoundAreaEvents(self):  # type: ()->Bool
        return Bool(self._node.at("sendSoundAreaEvents"))
    @sendSoundAreaEvents.setter
    def sendSoundAreaEvents(self, val): self.sendSoundAreaEvents.set(val)
    @property
    def waterDeepAltitude(self):  # type: ()->Float
        return Float(self._node.at("waterDeepAltitude"))
    @waterDeepAltitude.setter
    def waterDeepAltitude(self, val): self.waterDeepAltitude.set(val)
    @property
    def waterPuddleAltitude(self):  # type: ()->Float
        return Float(self._node.at("waterPuddleAltitude"))
    @waterPuddleAltitude.setter
    def waterPuddleAltitude(self, val): self.waterPuddleAltitude.set(val)
    pass


from EntityLibPy import Node

class SoundAreaGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/SoundAreaGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->SoundAreaGD
        return SoundAreaGD(entlib.load_node_file(sourcefile, entlib.get_schema(SoundAreaGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->SoundAreaGD
        return SoundAreaGD(entlib.make_node(SoundAreaGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def EventEnter(self):  # type: ()->String
        return String(self._node.at("EventEnter"))
    @EventEnter.setter
    def EventEnter(self, val): self.EventEnter.set(val)
    @property
    def EventExit(self):  # type: ()->String
        return String(self._node.at("EventExit"))
    @EventExit.setter
    def EventExit(self, val): self.EventExit.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class SoulSpotGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/SoulSpotGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->SoulSpotGD
        return SoulSpotGD(entlib.load_node_file(sourcefile, entlib.get_schema(SoulSpotGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->SoulSpotGD
        return SoulSpotGD(entlib.make_node(SoulSpotGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def Tags(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("Tags"))
    @Tags.setter
    def Tags(self, val): self.Tags.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class SoulRespawnOpportunityGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/SoulRespawnOpportunityGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->SoulRespawnOpportunityGD
        return SoulRespawnOpportunityGD(entlib.load_node_file(sourcefile, entlib.get_schema(SoulRespawnOpportunityGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->SoulRespawnOpportunityGD
        return SoulRespawnOpportunityGD(entlib.make_node(SoulRespawnOpportunityGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def ForceReviveSide(self):  # type: ()->ReviveSide
        return ReviveSide(self._node.at("ForceReviveSide"))
    @ForceReviveSide.setter
    def ForceReviveSide(self, val): self.ForceReviveSide.set(val)
    @property
    def MaxDensityCount(self):  # type: ()->Int
        return Int(self._node.at("MaxDensityCount"))
    @MaxDensityCount.setter
    def MaxDensityCount(self, val): self.MaxDensityCount.set(val)
    @property
    def MaxDensityRadius(self):  # type: ()->Float
        return Float(self._node.at("MaxDensityRadius"))
    @MaxDensityRadius.setter
    def MaxDensityRadius(self, val): self.MaxDensityRadius.set(val)
    @property
    def Offset(self):  # type: ()->Vector3
        return Vector3(self._node.at("Offset"))
    @Offset.setter
    def Offset(self, val): self.Offset.set(val)
    @property
    def SlotCount(self):  # type: ()->Int
        return Int(self._node.at("SlotCount"))
    @SlotCount.setter
    def SlotCount(self, val): self.SlotCount.set(val)
    @property
    def Specie(self):  # type: ()->Specie
        return Specie(self._node.at("Specie"))
    @Specie.setter
    def Specie(self, val): self.Specie.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class SmoothScaleComponentGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/SmoothScaleComponentGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->SmoothScaleComponentGD
        return SmoothScaleComponentGD(entlib.load_node_file(sourcefile, entlib.get_schema(SmoothScaleComponentGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->SmoothScaleComponentGD
        return SmoothScaleComponentGD(entlib.make_node(SmoothScaleComponentGD.schema_name))
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
    pass


from EntityLibPy import Node

class SmallActorSpawnerGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/SmallActorSpawnerGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->SmallActorSpawnerGD
        return SmallActorSpawnerGD(entlib.load_node_file(sourcefile, entlib.get_schema(SmallActorSpawnerGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->SmallActorSpawnerGD
        return SmallActorSpawnerGD(entlib.make_node(SmallActorSpawnerGD.schema_name))
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
    pass


from EntityLibPy import Node

class SmallActorGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/SmallActorGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->SmallActorGD
        return SmallActorGD(entlib.load_node_file(sourcefile, entlib.get_schema(SmallActorGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->SmallActorGD
        return SmallActorGD(entlib.make_node(SmallActorGD.schema_name))
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
    pass


from EntityLibPy import Node

class SideMapGateGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/SideMapGateGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->SideMapGateGD
        return SideMapGateGD(entlib.load_node_file(sourcefile, entlib.get_schema(SideMapGateGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->SideMapGateGD
        return SideMapGateGD(entlib.make_node(SideMapGateGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def SideMapName(self):  # type: ()->String
        return String(self._node.at("SideMapName"))
    @SideMapName.setter
    def SideMapName(self, val): self.SideMapName.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class ShapeshiftStatueGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ShapeshiftStatueGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ShapeshiftStatueGD
        return ShapeshiftStatueGD(entlib.load_node_file(sourcefile, entlib.get_schema(ShapeshiftStatueGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ShapeshiftStatueGD
        return ShapeshiftStatueGD(entlib.make_node(ShapeshiftStatueGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AssociatedEntityRef(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("AssociatedEntityRef"))
    @AssociatedEntityRef.setter
    def AssociatedEntityRef(self, val): self.AssociatedEntityRef.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class ShamanVisionGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ShamanVisionGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ShamanVisionGD
        return ShamanVisionGD(entlib.load_node_file(sourcefile, entlib.get_schema(ShamanVisionGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ShamanVisionGD
        return ShamanVisionGD(entlib.make_node(ShamanVisionGD.schema_name))
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
    pass


from EntityLibPy import Node

class ShamanItemGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ShamanItemGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ShamanItemGD
        return ShamanItemGD(entlib.load_node_file(sourcefile, entlib.get_schema(ShamanItemGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ShamanItemGD
        return ShamanItemGD(entlib.make_node(ShamanItemGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def BoneNames(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("BoneNames"))
    @BoneNames.setter
    def BoneNames(self, val): self.BoneNames.set(val)
    @property
    def OppositeItemEntityRef(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("OppositeItemEntityRef"))
    @OppositeItemEntityRef.setter
    def OppositeItemEntityRef(self, val): self.OppositeItemEntityRef.set(val)
    @property
    def ReviveSide(self):  # type: ()->ReviveSide
        return ReviveSide(self._node.at("ReviveSide"))
    @ReviveSide.setter
    def ReviveSide(self, val): self.ReviveSide.set(val)
    @property
    def StartPartCount(self):  # type: ()->Int
        return Int(self._node.at("StartPartCount"))
    @StartPartCount.setter
    def StartPartCount(self, val): self.StartPartCount.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class SensorControllerGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/SensorControllerGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->SensorControllerGD
        return SensorControllerGD(entlib.load_node_file(sourcefile, entlib.get_schema(SensorControllerGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->SensorControllerGD
        return SensorControllerGD(entlib.make_node(SensorControllerGD.schema_name))
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
    pass


from EntityLibPy import Node

class SeedPatch(HelperObject):
    schema_name = "./EditionComponents.json#/definitions/SeedPatch"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->SeedPatch
        return SeedPatch(entlib.load_node_file(sourcefile, entlib.get_schema(SeedPatch.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->SeedPatch
        return SeedPatch(entlib.make_node(SeedPatch.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AddVertexColor(self):  # type: ()->Bool
        return Bool(self._node.at("AddVertexColor"))
    @AddVertexColor.setter
    def AddVertexColor(self, val): self.AddVertexColor.set(val)
    @property
    def LocalMatrix(self):  # type: ()->Matrix33
        return Matrix33(self._node.at("LocalMatrix"))
    @LocalMatrix.setter
    def LocalMatrix(self, val): self.LocalMatrix.set(val)
    @property
    def MeshFile(self):  # type: ()->String
        return String(self._node.at("MeshFile"))
    @MeshFile.setter
    def MeshFile(self, val): self.MeshFile.set(val)
    @property
    def NoiseName(self):  # type: ()->String
        return String(self._node.at("NoiseName"))
    @NoiseName.setter
    def NoiseName(self, val): self.NoiseName.set(val)
    @property
    def NoiseOffsetX(self):  # type: ()->Float
        return Float(self._node.at("NoiseOffsetX"))
    @NoiseOffsetX.setter
    def NoiseOffsetX(self, val): self.NoiseOffsetX.set(val)
    @property
    def NoiseOffsetY(self):  # type: ()->Float
        return Float(self._node.at("NoiseOffsetY"))
    @NoiseOffsetY.setter
    def NoiseOffsetY(self, val): self.NoiseOffsetY.set(val)
    @property
    def NoiseSizeX(self):  # type: ()->Float
        return Float(self._node.at("NoiseSizeX"))
    @NoiseSizeX.setter
    def NoiseSizeX(self, val): self.NoiseSizeX.set(val)
    @property
    def NoiseSizeY(self):  # type: ()->Float
        return Float(self._node.at("NoiseSizeY"))
    @NoiseSizeY.setter
    def NoiseSizeY(self, val): self.NoiseSizeY.set(val)
    @property
    def SeedName(self):  # type: ()->String
        return String(self._node.at("SeedName"))
    @SeedName.setter
    def SeedName(self, val): self.SeedName.set(val)
    @property
    def SeedOverride(self):  # type: ()->Bool
        return Bool(self._node.at("SeedOverride"))
    @SeedOverride.setter
    def SeedOverride(self, val): self.SeedOverride.set(val)
    @property
    def SeedPatchDataList(self):  # type: ()->SeedPatchDataList
        return SeedPatchDataList(self._node.at("SeedPatchDataList"))
    @property
    def Subdivision(self):  # type: ()->Int
        return Int(self._node.at("Subdivision"))
    @Subdivision.setter
    def Subdivision(self, val): self.Subdivision.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class ScriptComponentGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ScriptComponentGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ScriptComponentGD
        return ScriptComponentGD(entlib.load_node_file(sourcefile, entlib.get_schema(ScriptComponentGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ScriptComponentGD
        return ScriptComponentGD(entlib.make_node(ScriptComponentGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def CommonDataMap(self):  # type: ()->Map[str, TypedValue]
        return (lambda n: Map(str, TypedValue, n))(self._node.at("CommonDataMap"))
    @property
    def ScriptsMap(self):  # type: ()->Map[str, ScriptPathAndDataSet]
        return (lambda n: Map(str, ScriptPathAndDataSet, n))(self._node.at("ScriptsMap"))
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class ReviveSideSwitcherGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ReviveSideSwitcherGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ReviveSideSwitcherGD
        return ReviveSideSwitcherGD(entlib.load_node_file(sourcefile, entlib.get_schema(ReviveSideSwitcherGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ReviveSideSwitcherGD
        return ReviveSideSwitcherGD(entlib.make_node(ReviveSideSwitcherGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def ReviveEnergyEntityRef(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("ReviveEnergyEntityRef"))
    @ReviveEnergyEntityRef.setter
    def ReviveEnergyEntityRef(self, val): self.ReviveEnergyEntityRef.set(val)
    @property
    def ReviveSideData(self):  # type: ()->Map[ReviveSideEnum, ReviveSideData]
        return (lambda n: Map(ReviveSideEnum, ReviveSideData, n))(self._node.at("ReviveSideData"))
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class ReviveEnergyGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ReviveEnergyGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ReviveEnergyGD
        return ReviveEnergyGD(entlib.load_node_file(sourcefile, entlib.get_schema(ReviveEnergyGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ReviveEnergyGD
        return ReviveEnergyGD(entlib.make_node(ReviveEnergyGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def EnergyMinNeutral(self):  # type: ()->Float
        return Float(self._node.at("EnergyMinNeutral"))
    @EnergyMinNeutral.setter
    def EnergyMinNeutral(self, val): self.EnergyMinNeutral.set(val)
    @property
    def HatchingEnergyMinHysteresis(self):  # type: ()->Float
        return Float(self._node.at("HatchingEnergyMinHysteresis"))
    @HatchingEnergyMinHysteresis.setter
    def HatchingEnergyMinHysteresis(self, val): self.HatchingEnergyMinHysteresis.set(val)
    @property
    def HatchingFightBackSpeedModifier(self):  # type: ()->Float
        return Float(self._node.at("HatchingFightBackSpeedModifier"))
    @HatchingFightBackSpeedModifier.setter
    def HatchingFightBackSpeedModifier(self, val): self.HatchingFightBackSpeedModifier.set(val)
    @property
    def HatchingMaxDuration(self):  # type: ()->Float
        return Float(self._node.at("HatchingMaxDuration"))
    @HatchingMaxDuration.setter
    def HatchingMaxDuration(self, val): self.HatchingMaxDuration.set(val)
    @property
    def HatchingMinDuration(self):  # type: ()->Float
        return Float(self._node.at("HatchingMinDuration"))
    @HatchingMinDuration.setter
    def HatchingMinDuration(self, val): self.HatchingMinDuration.set(val)
    @property
    def InitEnergy(self):  # type: ()->Float
        return Float(self._node.at("InitEnergy"))
    @InitEnergy.setter
    def InitEnergy(self, val): self.InitEnergy.set(val)
    @property
    def InitReviveSide(self):  # type: ()->ReviveSide
        return ReviveSide(self._node.at("InitReviveSide"))
    @InitReviveSide.setter
    def InitReviveSide(self, val): self.InitReviveSide.set(val)
    @property
    def MaxEnergy(self):  # type: ()->Float
        return Float(self._node.at("MaxEnergy"))
    @MaxEnergy.setter
    def MaxEnergy(self, val): self.MaxEnergy.set(val)
    @property
    def MaxWaitingTime(self):  # type: ()->Float
        return Float(self._node.at("MaxWaitingTime"))
    @MaxWaitingTime.setter
    def MaxWaitingTime(self, val): self.MaxWaitingTime.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class RespawnPlaceGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/RespawnPlaceGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->RespawnPlaceGD
        return RespawnPlaceGD(entlib.load_node_file(sourcefile, entlib.get_schema(RespawnPlaceGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->RespawnPlaceGD
        return RespawnPlaceGD(entlib.make_node(RespawnPlaceGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AlwaysAvailable(self):  # type: ()->Bool
        return Bool(self._node.at("AlwaysAvailable"))
    @AlwaysAvailable.setter
    def AlwaysAvailable(self, val): self.AlwaysAvailable.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class RegenerableVegetationGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/RegenerableVegetationGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->RegenerableVegetationGD
        return RegenerableVegetationGD(entlib.load_node_file(sourcefile, entlib.get_schema(RegenerableVegetationGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->RegenerableVegetationGD
        return RegenerableVegetationGD(entlib.make_node(RegenerableVegetationGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def PCloudPath(self):  # type: ()->String
        return String(self._node.at("PCloudPath"))
    @PCloudPath.setter
    def PCloudPath(self, val): self.PCloudPath.set(val)
    @property
    def RegenRange(self):  # type: ()->FloatRange
        return FloatRange(self._node.at("RegenRange"))
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def UsedVegetations(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("UsedVegetations"))
    @UsedVegetations.setter
    def UsedVegetations(self, val): self.UsedVegetations.set(val)
    @property
    def VegetationPClouds(self):  # type: ()->Array[VegetationPCloudData]
        return (lambda n: Array(VegetationPCloudData, n))(self._node.at("VegetationPClouds"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class RegenSwitcherGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/RegenSwitcherGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->RegenSwitcherGD
        return RegenSwitcherGD(entlib.load_node_file(sourcefile, entlib.get_schema(RegenSwitcherGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->RegenSwitcherGD
        return RegenSwitcherGD(entlib.make_node(RegenSwitcherGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def ParentTransforms(self):  # type: ()->Bool
        return Bool(self._node.at("ParentTransforms"))
    @ParentTransforms.setter
    def ParentTransforms(self, val): self.ParentTransforms.set(val)
    @property
    def RegenData(self):  # type: ()->Array[RegenData]
        return (lambda n: Array(RegenData, n))(self._node.at("RegenData"))
    @property
    def RegenSwitchBehavior(self):  # type: ()->RegenSwitchBehavior
        return RegenSwitchBehavior(self._node.at("RegenSwitchBehavior"))
    @RegenSwitchBehavior.setter
    def RegenSwitchBehavior(self, val): self.RegenSwitchBehavior.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class RegenMeshGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/RegenMeshGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->RegenMeshGD
        return RegenMeshGD(entlib.load_node_file(sourcefile, entlib.get_schema(RegenMeshGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->RegenMeshGD
        return RegenMeshGD(entlib.make_node(RegenMeshGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def FilePath(self):  # type: ()->String
        return String(self._node.at("FilePath"))
    @FilePath.setter
    def FilePath(self, val): self.FilePath.set(val)
    @property
    def FrontierHeightDetection(self):  # type: ()->Float
        return Float(self._node.at("FrontierHeightDetection"))
    @FrontierHeightDetection.setter
    def FrontierHeightDetection(self, val): self.FrontierHeightDetection.set(val)
    @property
    def FrontierTolerance(self):  # type: ()->Float
        return Float(self._node.at("FrontierTolerance"))
    @FrontierTolerance.setter
    def FrontierTolerance(self, val): self.FrontierTolerance.set(val)
    @property
    def LossBySecond(self):  # type: ()->Float
        return Float(self._node.at("LossBySecond"))
    @LossBySecond.setter
    def LossBySecond(self, val): self.LossBySecond.set(val)
    @property
    def LostRatio(self):  # type: ()->Float
        return Float(self._node.at("LostRatio"))
    @LostRatio.setter
    def LostRatio(self, val): self.LostRatio.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def TransmissionPerSecond(self):  # type: ()->Float
        return Float(self._node.at("TransmissionPerSecond"))
    @TransmissionPerSecond.setter
    def TransmissionPerSecond(self, val): self.TransmissionPerSecond.set(val)
    @property
    def TransmissionRatio(self):  # type: ()->Float
        return Float(self._node.at("TransmissionRatio"))
    @TransmissionRatio.setter
    def TransmissionRatio(self, val): self.TransmissionRatio.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class RegenFXGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/RegenFXGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->RegenFXGD
        return RegenFXGD(entlib.load_node_file(sourcefile, entlib.get_schema(RegenFXGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->RegenFXGD
        return RegenFXGD(entlib.make_node(RegenFXGD.schema_name))
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
    pass


from EntityLibPy import Node

class RagdollGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/RagdollGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->RagdollGD
        return RagdollGD(entlib.load_node_file(sourcefile, entlib.get_schema(RagdollGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->RagdollGD
        return RagdollGD(entlib.make_node(RagdollGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def RagdollType(self):  # type: ()->String
        return String(self._node.at("RagdollType"))
    @RagdollType.setter
    def RagdollType(self, val): self.RagdollType.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class QuickCreatureSwitchGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/QuickCreatureSwitchGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->QuickCreatureSwitchGD
        return QuickCreatureSwitchGD(entlib.load_node_file(sourcefile, entlib.get_schema(QuickCreatureSwitchGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->QuickCreatureSwitchGD
        return QuickCreatureSwitchGD(entlib.make_node(QuickCreatureSwitchGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def CreatureEntityRefs(self):  # type: ()->PrimArray[EntityRef]
        return (lambda n: PrimArray(EntityRef, n))(self._node.at("CreatureEntityRefs"))
    @CreatureEntityRefs.setter
    def CreatureEntityRefs(self, val): self.CreatureEntityRefs.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class ProtoComponentGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ProtoComponentGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ProtoComponentGD
        return ProtoComponentGD(entlib.load_node_file(sourcefile, entlib.get_schema(ProtoComponentGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ProtoComponentGD
        return ProtoComponentGD(entlib.make_node(ProtoComponentGD.schema_name))
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
    pass


from EntityLibPy import Node

class ProjectileShooterGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ProjectileShooterGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ProjectileShooterGD
        return ProjectileShooterGD(entlib.load_node_file(sourcefile, entlib.get_schema(ProjectileShooterGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ProjectileShooterGD
        return ProjectileShooterGD(entlib.make_node(ProjectileShooterGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def ProjectileShooterData(self):  # type: ()->Map[str, ProjectileShooterData]
        return (lambda n: Map(str, ProjectileShooterData, n))(self._node.at("ProjectileShooterData"))
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class PossessableGPEGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/PossessableGPEGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PossessableGPEGD
        return PossessableGPEGD(entlib.load_node_file(sourcefile, entlib.get_schema(PossessableGPEGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PossessableGPEGD
        return PossessableGPEGD(entlib.make_node(PossessableGPEGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def GPEActorStateName(self):  # type: ()->String
        return String(self._node.at("GPEActorStateName"))
    @GPEActorStateName.setter
    def GPEActorStateName(self, val): self.GPEActorStateName.set(val)
    @property
    def GPEType(self):  # type: ()->GPEType
        return GPEType(self._node.at("GPEType"))
    @GPEType.setter
    def GPEType(self, val): self.GPEType.set(val)
    @property
    def HotspotName(self):  # type: ()->String
        return String(self._node.at("HotspotName"))
    @HotspotName.setter
    def HotspotName(self, val): self.HotspotName.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class PlayerComponentGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/PlayerComponentGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PlayerComponentGD
        return PlayerComponentGD(entlib.load_node_file(sourcefile, entlib.get_schema(PlayerComponentGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PlayerComponentGD
        return PlayerComponentGD(entlib.make_node(PlayerComponentGD.schema_name))
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
    pass


from EntityLibPy import Node

class PickableDistributorComponentGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/PickableDistributorComponentGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PickableDistributorComponentGD
        return PickableDistributorComponentGD(entlib.load_node_file(sourcefile, entlib.get_schema(PickableDistributorComponentGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PickableDistributorComponentGD
        return PickableDistributorComponentGD(entlib.make_node(PickableDistributorComponentGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def PickableGrowingTime(self):  # type: ()->Float
        return Float(self._node.at("PickableGrowingTime"))
    @PickableGrowingTime.setter
    def PickableGrowingTime(self, val): self.PickableGrowingTime.set(val)
    @property
    def PickablePickedUpCooldownTime(self):  # type: ()->Float
        return Float(self._node.at("PickablePickedUpCooldownTime"))
    @PickablePickedUpCooldownTime.setter
    def PickablePickedUpCooldownTime(self, val): self.PickablePickedUpCooldownTime.set(val)
    @property
    def PickablesList(self):  # type: ()->Array[PickableDistributorComponentData]
        return (lambda n: Array(PickableDistributorComponentData, n))(self._node.at("PickablesList"))
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class PickableComponentGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/PickableComponentGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PickableComponentGD
        return PickableComponentGD(entlib.load_node_file(sourcefile, entlib.get_schema(PickableComponentGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PickableComponentGD
        return PickableComponentGD(entlib.make_node(PickableComponentGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def StatesForPicker(self):  # type: ()->Array[ResponsiblePointer_ActorState_]
        return (lambda n: Array(ResponsiblePointer_ActorState_, n))(self._node.at("StatesForPicker"))
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class PhysicsTriggerGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/PhysicsTriggerGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PhysicsTriggerGD
        return PhysicsTriggerGD(entlib.load_node_file(sourcefile, entlib.get_schema(PhysicsTriggerGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PhysicsTriggerGD
        return PhysicsTriggerGD(entlib.make_node(PhysicsTriggerGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def RequiredComponents(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("RequiredComponents"))
    @RequiredComponents.setter
    def RequiredComponents(self, val): self.RequiredComponents.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class PhysicsMeshProviderGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/PhysicsMeshProviderGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PhysicsMeshProviderGD
        return PhysicsMeshProviderGD(entlib.load_node_file(sourcefile, entlib.get_schema(PhysicsMeshProviderGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PhysicsMeshProviderGD
        return PhysicsMeshProviderGD(entlib.make_node(PhysicsMeshProviderGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def EdgeTransitionConstraintAllowed(self):  # type: ()->Bool
        return Bool(self._node.at("EdgeTransitionConstraintAllowed"))
    @EdgeTransitionConstraintAllowed.setter
    def EdgeTransitionConstraintAllowed(self, val): self.EdgeTransitionConstraintAllowed.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class PhysicsMeshDeformerGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/PhysicsMeshDeformerGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PhysicsMeshDeformerGD
        return PhysicsMeshDeformerGD(entlib.load_node_file(sourcefile, entlib.get_schema(PhysicsMeshDeformerGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PhysicsMeshDeformerGD
        return PhysicsMeshDeformerGD(entlib.make_node(PhysicsMeshDeformerGD.schema_name))
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
    pass


from EntityLibPy import Node

class PhysicsGD(HelperObject):
    schema_name = "./MergedComponents.json#/definitions/PhysicsGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PhysicsGD
        return PhysicsGD(entlib.load_node_file(sourcefile, entlib.get_schema(PhysicsGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PhysicsGD
        return PhysicsGD(entlib.make_node(PhysicsGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AffectByHit(self):  # type: ()->Bool
        return Bool(self._node.at("AffectByHit"))
    @AffectByHit.setter
    def AffectByHit(self, val): self.AffectByHit.set(val)
    @property
    def AngularDamping(self):  # type: ()->Float
        return Float(self._node.at("AngularDamping"))
    @AngularDamping.setter
    def AngularDamping(self, val): self.AngularDamping.set(val)
    @property
    def AxisRestriction(self):  # type: ()->Vector3
        return Vector3(self._node.at("AxisRestriction"))
    @AxisRestriction.setter
    def AxisRestriction(self, val): self.AxisRestriction.set(val)
    @property
    def CameraIgnored(self):  # type: ()->Bool
        return Bool(self._node.at("CameraIgnored"))
    @CameraIgnored.setter
    def CameraIgnored(self, val): self.CameraIgnored.set(val)
    @property
    def Ccd(self):  # type: ()->Bool
        return Bool(self._node.at("Ccd"))
    @Ccd.setter
    def Ccd(self, val): self.Ccd.set(val)
    @property
    def EDITOR_MeshColliders(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("EDITOR_MeshColliders"))
    @EDITOR_MeshColliders.setter
    def EDITOR_MeshColliders(self, val): self.EDITOR_MeshColliders.set(val)
    @property
    def EDITOR_MeshEdges(self):  # type: ()->String
        return String(self._node.at("EDITOR_MeshEdges"))
    @EDITOR_MeshEdges.setter
    def EDITOR_MeshEdges(self, val): self.EDITOR_MeshEdges.set(val)
    @property
    def EDITOR_NavMeshStamper(self):  # type: ()->String
        return String(self._node.at("EDITOR_NavMeshStamper"))
    @EDITOR_NavMeshStamper.setter
    def EDITOR_NavMeshStamper(self, val): self.EDITOR_NavMeshStamper.set(val)
    @property
    def EnergyLoss(self):  # type: ()->Float
        return Float(self._node.at("EnergyLoss"))
    @EnergyLoss.setter
    def EnergyLoss(self, val): self.EnergyLoss.set(val)
    @property
    def Friction(self):  # type: ()->Float
        return Float(self._node.at("Friction"))
    @Friction.setter
    def Friction(self, val): self.Friction.set(val)
    @property
    def HasGravity(self):  # type: ()->Bool
        return Bool(self._node.at("HasGravity"))
    @HasGravity.setter
    def HasGravity(self, val): self.HasGravity.set(val)
    @property
    def LinearDamping(self):  # type: ()->Float
        return Float(self._node.at("LinearDamping"))
    @LinearDamping.setter
    def LinearDamping(self, val): self.LinearDamping.set(val)
    @property
    def Mass(self):  # type: ()->Float
        return Float(self._node.at("Mass"))
    @Mass.setter
    def Mass(self, val): self.Mass.set(val)
    @property
    def MeshColliders(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("MeshColliders"))
    @MeshColliders.setter
    def MeshColliders(self, val): self.MeshColliders.set(val)
    @property
    def MeshEdges(self):  # type: ()->String
        return String(self._node.at("MeshEdges"))
    @MeshEdges.setter
    def MeshEdges(self, val): self.MeshEdges.set(val)
    @property
    def MotionType(self):  # type: ()->String
        return String(self._node.at("MotionType"))
    @MotionType.setter
    def MotionType(self, val): self.MotionType.set(val)
    @property
    def NavMeshStamper(self):  # type: ()->String
        return String(self._node.at("NavMeshStamper"))
    @NavMeshStamper.setter
    def NavMeshStamper(self, val): self.NavMeshStamper.set(val)
    @property
    def Offset(self):  # type: ()->Vector3
        return Vector3(self._node.at("Offset"))
    @Offset.setter
    def Offset(self, val): self.Offset.set(val)
    @property
    def OffsetRotation(self):  # type: ()->Vector3
        return Vector3(self._node.at("OffsetRotation"))
    @OffsetRotation.setter
    def OffsetRotation(self, val): self.OffsetRotation.set(val)
    @property
    def PhysicsMaterial(self):  # type: ()->String
        return String(self._node.at("PhysicsMaterial"))
    @PhysicsMaterial.setter
    def PhysicsMaterial(self, val): self.PhysicsMaterial.set(val)
    @property
    def PrimitiveCollider(self):  # type: ()->PrimitiveColliderType
        return PrimitiveColliderType(self._node.at("PrimitiveCollider"))
    @PrimitiveCollider.setter
    def PrimitiveCollider(self, val): self.PrimitiveCollider.set(val)
    @property
    def PrimitiveColliderSizeLayerMask(self):  # type: ()->PrimArray[Size]
        return (lambda n: PrimArray(Size, n))(self._node.at("PrimitiveColliderSizeLayerMask"))
    @PrimitiveColliderSizeLayerMask.setter
    def PrimitiveColliderSizeLayerMask(self, val): self.PrimitiveColliderSizeLayerMask.set(val)
    @property
    def Radius(self):  # type: ()->Float
        return Float(self._node.at("Radius"))
    @Radius.setter
    def Radius(self, val): self.Radius.set(val)
    @property
    def Restitution(self):  # type: ()->Float
        return Float(self._node.at("Restitution"))
    @Restitution.setter
    def Restitution(self, val): self.Restitution.set(val)
    @property
    def SelfFilter(self):  # type: ()->PrimArray[PhysicsLayer]
        return (lambda n: PrimArray(PhysicsLayer, n))(self._node.at("SelfFilter"))
    @SelfFilter.setter
    def SelfFilter(self, val): self.SelfFilter.set(val)
    @property
    def Size(self):  # type: ()->Vector3
        return Vector3(self._node.at("Size"))
    @Size.setter
    def Size(self, val): self.Size.set(val)
    @property
    def Sleep(self):  # type: ()->Bool
        return Bool(self._node.at("Sleep"))
    @Sleep.setter
    def Sleep(self, val): self.Sleep.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def TargetFilter(self):  # type: ()->PrimArray[PhysicsLayer]
        return (lambda n: PrimArray(PhysicsLayer, n))(self._node.at("TargetFilter"))
    @TargetFilter.setter
    def TargetFilter(self, val): self.TargetFilter.set(val)
    @property
    def Walkable(self):  # type: ()->Bool
        return Bool(self._node.at("Walkable"))
    @Walkable.setter
    def Walkable(self, val): self.Walkable.set(val)
    @property
    def WalkableSoundSwitch(self):  # type: ()->String
        return String(self._node.at("WalkableSoundSwitch"))
    @WalkableSoundSwitch.setter
    def WalkableSoundSwitch(self, val): self.WalkableSoundSwitch.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class PhysicsDataGD(HelperObject):
    schema_name = "./MergedComponents.json#/definitions/PhysicsDataGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PhysicsDataGD
        return PhysicsDataGD(entlib.load_node_file(sourcefile, entlib.get_schema(PhysicsDataGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PhysicsDataGD
        return PhysicsDataGD(entlib.make_node(PhysicsDataGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def EDITOR_Shapes(self):  # type: ()->Array[EDITOR_Mesh]
        return (lambda n: Array(EDITOR_Mesh, n))(self._node.at("EDITOR_Shapes"))
    @property
    def EDITOR_isTrigger(self):  # type: ()->Bool
        return Bool(self._node.at("EDITOR_isTrigger"))
    @EDITOR_isTrigger.setter
    def EDITOR_isTrigger(self, val): self.EDITOR_isTrigger.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def joints(self):  # type: ()->Array[sPhysicsJointDesc]
        return (lambda n: Array(sPhysicsJointDesc, n))(self._node.at("joints"))
    @property
    def rigidBodies(self):  # type: ()->Array[sRigidBodyDesc]
        return (lambda n: Array(sRigidBodyDesc, n))(self._node.at("rigidBodies"))
    pass


from EntityLibPy import Node

class PerceiverGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/PerceiverGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PerceiverGD
        return PerceiverGD(entlib.load_node_file(sourcefile, entlib.get_schema(PerceiverGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PerceiverGD
        return PerceiverGD(entlib.make_node(PerceiverGD.schema_name))
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
    def m_coneAngle(self):  # type: ()->Float
        return Float(self._node.at("m_coneAngle"))
    @m_coneAngle.setter
    def m_coneAngle(self, val): self.m_coneAngle.set(val)
    @property
    def m_farSoundDistance(self):  # type: ()->Float
        return Float(self._node.at("m_farSoundDistance"))
    @m_farSoundDistance.setter
    def m_farSoundDistance(self, val): self.m_farSoundDistance.set(val)
    @property
    def m_longRangeDistance(self):  # type: ()->Float
        return Float(self._node.at("m_longRangeDistance"))
    @m_longRangeDistance.setter
    def m_longRangeDistance(self, val): self.m_longRangeDistance.set(val)
    @property
    def m_lowRangeDistance(self):  # type: ()->Float
        return Float(self._node.at("m_lowRangeDistance"))
    @m_lowRangeDistance.setter
    def m_lowRangeDistance(self, val): self.m_lowRangeDistance.set(val)
    @property
    def m_middleRangeDistance(self):  # type: ()->Float
        return Float(self._node.at("m_middleRangeDistance"))
    @m_middleRangeDistance.setter
    def m_middleRangeDistance(self, val): self.m_middleRangeDistance.set(val)
    @property
    def m_middleSoundDistance(self):  # type: ()->Float
        return Float(self._node.at("m_middleSoundDistance"))
    @m_middleSoundDistance.setter
    def m_middleSoundDistance(self, val): self.m_middleSoundDistance.set(val)
    @property
    def m_nearSoundDistance(self):  # type: ()->Float
        return Float(self._node.at("m_nearSoundDistance"))
    @m_nearSoundDistance.setter
    def m_nearSoundDistance(self, val): self.m_nearSoundDistance.set(val)
    @property
    def m_perceptionHeightMultiplier(self):  # type: ()->Float
        return Float(self._node.at("m_perceptionHeightMultiplier"))
    @m_perceptionHeightMultiplier.setter
    def m_perceptionHeightMultiplier(self, val): self.m_perceptionHeightMultiplier.set(val)
    @property
    def m_perceptionHeightMultiplierHeightMax(self):  # type: ()->Float
        return Float(self._node.at("m_perceptionHeightMultiplierHeightMax"))
    @m_perceptionHeightMultiplierHeightMax.setter
    def m_perceptionHeightMultiplierHeightMax(self, val): self.m_perceptionHeightMultiplierHeightMax.set(val)
    @property
    def m_rayCastCheck(self):  # type: ()->Bool
        return Bool(self._node.at("m_rayCastCheck"))
    @m_rayCastCheck.setter
    def m_rayCastCheck(self, val): self.m_rayCastCheck.set(val)
    pass


from EntityLibPy import Node

class PerceivableGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/PerceivableGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PerceivableGD
        return PerceivableGD(entlib.load_node_file(sourcefile, entlib.get_schema(PerceivableGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PerceivableGD
        return PerceivableGD(entlib.make_node(PerceivableGD.schema_name))
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
    def m_perceivedDistanceMultiplier(self):  # type: ()->Float
        return Float(self._node.at("m_perceivedDistanceMultiplier"))
    @m_perceivedDistanceMultiplier.setter
    def m_perceivedDistanceMultiplier(self, val): self.m_perceivedDistanceMultiplier.set(val)
    @property
    def m_soundCrouch(self):  # type: ()->SoundEmissionStrength
        return SoundEmissionStrength(self._node.at("m_soundCrouch"))
    @m_soundCrouch.setter
    def m_soundCrouch(self, val): self.m_soundCrouch.set(val)
    @property
    def m_soundImmobile(self):  # type: ()->SoundEmissionStrength
        return SoundEmissionStrength(self._node.at("m_soundImmobile"))
    @m_soundImmobile.setter
    def m_soundImmobile(self, val): self.m_soundImmobile.set(val)
    @property
    def m_soundRun(self):  # type: ()->SoundEmissionStrength
        return SoundEmissionStrength(self._node.at("m_soundRun"))
    @m_soundRun.setter
    def m_soundRun(self, val): self.m_soundRun.set(val)
    @property
    def m_soundWalk(self):  # type: ()->SoundEmissionStrength
        return SoundEmissionStrength(self._node.at("m_soundWalk"))
    @m_soundWalk.setter
    def m_soundWalk(self, val): self.m_soundWalk.set(val)
    @property
    def m_tags(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("m_tags"))
    @m_tags.setter
    def m_tags(self, val): self.m_tags.set(val)
    pass


from EntityLibPy import Node

class PathNodeGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/PathNodeGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PathNodeGD
        return PathNodeGD(entlib.load_node_file(sourcefile, entlib.get_schema(PathNodeGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PathNodeGD
        return PathNodeGD(entlib.make_node(PathNodeGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Radius(self):  # type: ()->Float
        return Float(self._node.at("Radius"))
    @Radius.setter
    def Radius(self, val): self.Radius.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def Tags(self):  # type: ()->TagsList
        return TagsList(self._node.at("Tags"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class PathMotionControllerGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/PathMotionControllerGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PathMotionControllerGD
        return PathMotionControllerGD(entlib.load_node_file(sourcefile, entlib.get_schema(PathMotionControllerGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PathMotionControllerGD
        return PathMotionControllerGD(entlib.make_node(PathMotionControllerGD.schema_name))
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
    pass


from EntityLibPy import Node

class PathGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/PathGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PathGD
        return PathGD(entlib.load_node_file(sourcefile, entlib.get_schema(PathGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PathGD
        return PathGD(entlib.make_node(PathGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def FilePath(self):  # type: ()->String
        return String(self._node.at("FilePath"))
    @FilePath.setter
    def FilePath(self, val): self.FilePath.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class PathBoneRigidBodyGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/PathBoneRigidBodyGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PathBoneRigidBodyGD
        return PathBoneRigidBodyGD(entlib.load_node_file(sourcefile, entlib.get_schema(PathBoneRigidBodyGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PathBoneRigidBodyGD
        return PathBoneRigidBodyGD(entlib.make_node(PathBoneRigidBodyGD.schema_name))
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
    pass


from EntityLibPy import Node

class PathBoneInfluenceGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/PathBoneInfluenceGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PathBoneInfluenceGD
        return PathBoneInfluenceGD(entlib.load_node_file(sourcefile, entlib.get_schema(PathBoneInfluenceGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PathBoneInfluenceGD
        return PathBoneInfluenceGD(entlib.make_node(PathBoneInfluenceGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Data(self):  # type: ()->Array[sNodeBoneInfluenceDataTemplate]
        return (lambda n: Array(sNodeBoneInfluenceDataTemplate, n))(self._node.at("Data"))
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class PathBoneAnimGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/PathBoneAnimGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->PathBoneAnimGD
        return PathBoneAnimGD(entlib.load_node_file(sourcefile, entlib.get_schema(PathBoneAnimGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->PathBoneAnimGD
        return PathBoneAnimGD(entlib.make_node(PathBoneAnimGD.schema_name))
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
    pass


from EntityLibPy import Node

class OutfitWearerGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/OutfitWearerGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->OutfitWearerGD
        return OutfitWearerGD(entlib.load_node_file(sourcefile, entlib.get_schema(OutfitWearerGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->OutfitWearerGD
        return OutfitWearerGD(entlib.make_node(OutfitWearerGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def InventoryEntityRef(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("InventoryEntityRef"))
    @InventoryEntityRef.setter
    def InventoryEntityRef(self, val): self.InventoryEntityRef.set(val)
    @property
    def OutfitFadeDelay(self):  # type: ()->Float
        return Float(self._node.at("OutfitFadeDelay"))
    @OutfitFadeDelay.setter
    def OutfitFadeDelay(self, val): self.OutfitFadeDelay.set(val)
    @property
    def OutfitFadeDuration(self):  # type: ()->Float
        return Float(self._node.at("OutfitFadeDuration"))
    @OutfitFadeDuration.setter
    def OutfitFadeDuration(self, val): self.OutfitFadeDuration.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class OutfitGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/OutfitGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->OutfitGD
        return OutfitGD(entlib.load_node_file(sourcefile, entlib.get_schema(OutfitGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->OutfitGD
        return OutfitGD(entlib.make_node(OutfitGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def SnapLine(self):  # type: ()->Array[MountableSnapLine_ControlPoint]
        return (lambda n: Array(MountableSnapLine_ControlPoint, n))(self._node.at("SnapLine"))
    @property
    def SoundEventMappingRules(self):  # type: ()->SoundEventMapping
        return SoundEventMapping(self._node.at("SoundEventMappingRules"))
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def clothes(self):  # type: ()->Array[OutfitPiece]
        return (lambda n: Array(OutfitPiece, n))(self._node.at("clothes"))
    @property
    def faction(self):  # type: ()->String
        return String(self._node.at("faction"))
    @faction.setter
    def faction(self, val): self.faction.set(val)
    @property
    def overrideSpeciesAudioCategory(self):  # type: ()->String
        return String(self._node.at("overrideSpeciesAudioCategory"))
    @overrideSpeciesAudioCategory.setter
    def overrideSpeciesAudioCategory(self, val): self.overrideSpeciesAudioCategory.set(val)
    @property
    def soundBank(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("soundBank"))
    @soundBank.setter
    def soundBank(self, val): self.soundBank.set(val)
    @property
    def soundTag(self):  # type: ()->String
        return String(self._node.at("soundTag"))
    @soundTag.setter
    def soundTag(self, val): self.soundTag.set(val)
    @property
    def specialOutfitStyle(self):  # type: ()->StyleMode
        return StyleMode(self._node.at("specialOutfitStyle"))
    @specialOutfitStyle.setter
    def specialOutfitStyle(self, val): self.specialOutfitStyle.set(val)
    @property
    def spirit(self):  # type: ()->Bool
        return Bool(self._node.at("spirit"))
    @spirit.setter
    def spirit(self, val): self.spirit.set(val)
    pass


from EntityLibPy import Node

class NotVisibleInSubscene(HelperObject):
    schema_name = "./EditionComponents.json#/definitions/NotVisibleInSubscene"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->NotVisibleInSubscene
        return NotVisibleInSubscene(entlib.load_node_file(sourcefile, entlib.get_schema(NotVisibleInSubscene.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->NotVisibleInSubscene
        return NotVisibleInSubscene(entlib.make_node(NotVisibleInSubscene.schema_name))
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
    pass


from EntityLibPy import Node

class NetworkNode(HelperObject):
    schema_name = "./EditionComponents.json#/definitions/NetworkNode"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->NetworkNode
        return NetworkNode(entlib.load_node_file(sourcefile, entlib.get_schema(NetworkNode.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->NetworkNode
        return NetworkNode(entlib.make_node(NetworkNode.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def Tag(self):  # type: ()->String
        return String(self._node.at("Tag"))
    @Tag.setter
    def Tag(self, val): self.Tag.set(val)
    @property
    def ThumbnailMesh(self):  # type: ()->String
        return String(self._node.at("ThumbnailMesh"))
    @ThumbnailMesh.setter
    def ThumbnailMesh(self, val): self.ThumbnailMesh.set(val)
    @property
    def Type_(self):  # type: ()->String
        return String(self._node.at("Type_"))
    @Type_.setter
    def Type_(self, val): self.Type_.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class NetworkLink(HelperObject):
    schema_name = "./EditionComponents.json#/definitions/NetworkLink"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->NetworkLink
        return NetworkLink(entlib.load_node_file(sourcefile, entlib.get_schema(NetworkLink.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->NetworkLink
        return NetworkLink(entlib.make_node(NetworkLink.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Source(self):  # type: ()->String
        return String(self._node.at("Source"))
    @Source.setter
    def Source(self, val): self.Source.set(val)
    @property
    def SourceEntityRef(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("SourceEntityRef"))
    @SourceEntityRef.setter
    def SourceEntityRef(self, val): self.SourceEntityRef.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def Target(self):  # type: ()->String
        return String(self._node.at("Target"))
    @Target.setter
    def Target(self, val): self.Target.set(val)
    @property
    def TargetEntityRef(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("TargetEntityRef"))
    @TargetEntityRef.setter
    def TargetEntityRef(self, val): self.TargetEntityRef.set(val)
    @property
    def ThumbnailMesh(self):  # type: ()->String
        return String(self._node.at("ThumbnailMesh"))
    @ThumbnailMesh.setter
    def ThumbnailMesh(self, val): self.ThumbnailMesh.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class NetGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/NetGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->NetGD
        return NetGD(entlib.load_node_file(sourcefile, entlib.get_schema(NetGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->NetGD
        return NetGD(entlib.make_node(NetGD.schema_name))
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
    pass


from EntityLibPy import Node

class MultiThumbnail(HelperObject):
    schema_name = "./EditionComponents.json#/definitions/MultiThumbnail"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->MultiThumbnail
        return MultiThumbnail(entlib.load_node_file(sourcefile, entlib.get_schema(MultiThumbnail.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->MultiThumbnail
        return MultiThumbnail(entlib.make_node(MultiThumbnail.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def List(self):  # type: ()->Array[ListItem]
        return (lambda n: Array(ListItem, n))(self._node.at("List"))
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class MounterGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/MounterGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->MounterGD
        return MounterGD(entlib.load_node_file(sourcefile, entlib.get_schema(MounterGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->MounterGD
        return MounterGD(entlib.make_node(MounterGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def HotspotName(self):  # type: ()->String
        return String(self._node.at("HotspotName"))
    @HotspotName.setter
    def HotspotName(self, val): self.HotspotName.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class MountableGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/MountableGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->MountableGD
        return MountableGD(entlib.load_node_file(sourcefile, entlib.get_schema(MountableGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->MountableGD
        return MountableGD(entlib.make_node(MountableGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def HotspotNames(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("HotspotNames"))
    @HotspotNames.setter
    def HotspotNames(self, val): self.HotspotNames.set(val)
    @property
    def SnapLine(self):  # type: ()->Array[MountableSnapLine_ControlPoint]
        return (lambda n: Array(MountableSnapLine_ControlPoint, n))(self._node.at("SnapLine"))
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


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


from EntityLibPy import Node

class MissionHolderGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/MissionHolderGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->MissionHolderGD
        return MissionHolderGD(entlib.load_node_file(sourcefile, entlib.get_schema(MissionHolderGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->MissionHolderGD
        return MissionHolderGD(entlib.make_node(MissionHolderGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Private(self):  # type: ()->Bool
        return Bool(self._node.at("Private"))
    @Private.setter
    def Private(self, val): self.Private.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class MeshNavigationInfosGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/MeshNavigationInfosGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->MeshNavigationInfosGD
        return MeshNavigationInfosGD(entlib.load_node_file(sourcefile, entlib.get_schema(MeshNavigationInfosGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->MeshNavigationInfosGD
        return MeshNavigationInfosGD(entlib.make_node(MeshNavigationInfosGD.schema_name))
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
    pass


from EntityLibPy import Node

class Mesh(HelperObject):
    schema_name = "./EditionComponents.json#/definitions/Mesh"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->Mesh
        return Mesh(entlib.load_node_file(sourcefile, entlib.get_schema(Mesh.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->Mesh
        return Mesh(entlib.make_node(Mesh.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def File(self):  # type: ()->String
        return String(self._node.at("File"))
    @File.setter
    def File(self, val): self.File.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class LDPrimitive(HelperObject):
    schema_name = "./EditionComponents.json#/definitions/LDPrimitive"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->LDPrimitive
        return LDPrimitive(entlib.load_node_file(sourcefile, entlib.get_schema(LDPrimitive.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->LDPrimitive
        return LDPrimitive(entlib.make_node(LDPrimitive.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def NonDisuptive(self):  # type: ()->Bool
        return Bool(self._node.at("NonDisuptive"))
    @NonDisuptive.setter
    def NonDisuptive(self, val): self.NonDisuptive.set(val)
    @property
    def PrimitiveData(self):  # type: ()->PrimitiveData
        return PrimitiveData(self._node.at("PrimitiveData"))
    @property
    def PrimitiveType(self):  # type: ()->String
        return String(self._node.at("PrimitiveType"))
    @PrimitiveType.setter
    def PrimitiveType(self, val): self.PrimitiveType.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class ItemHolderGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ItemHolderGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ItemHolderGD
        return ItemHolderGD(entlib.load_node_file(sourcefile, entlib.get_schema(ItemHolderGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ItemHolderGD
        return ItemHolderGD(entlib.make_node(ItemHolderGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def HotspotDefault(self):  # type: ()->String
        return String(self._node.at("HotspotDefault"))
    @HotspotDefault.setter
    def HotspotDefault(self, val): self.HotspotDefault.set(val)
    @property
    def HotspotHandLeft(self):  # type: ()->String
        return String(self._node.at("HotspotHandLeft"))
    @HotspotHandLeft.setter
    def HotspotHandLeft(self, val): self.HotspotHandLeft.set(val)
    @property
    def HotspotHandRight(self):  # type: ()->String
        return String(self._node.at("HotspotHandRight"))
    @HotspotHandRight.setter
    def HotspotHandRight(self, val): self.HotspotHandRight.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def Visible(self):  # type: ()->Bool
        return Bool(self._node.at("Visible"))
    @Visible.setter
    def Visible(self, val): self.Visible.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class InventoryGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/InventoryGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->InventoryGD
        return InventoryGD(entlib.load_node_file(sourcefile, entlib.get_schema(InventoryGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->InventoryGD
        return InventoryGD(entlib.make_node(InventoryGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def TaggedEntityRefs(self):  # type: ()->Array[TaggedEntityRef]
        return (lambda n: Array(TaggedEntityRef, n))(self._node.at("TaggedEntityRefs"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class InfoboardRegistererGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/InfoboardRegistererGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->InfoboardRegistererGD
        return InfoboardRegistererGD(entlib.load_node_file(sourcefile, entlib.get_schema(InfoboardRegistererGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->InfoboardRegistererGD
        return InfoboardRegistererGD(entlib.make_node(InfoboardRegistererGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def InfoboardName(self):  # type: ()->String
        return String(self._node.at("InfoboardName"))
    @InfoboardName.setter
    def InfoboardName(self, val): self.InfoboardName.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class HotspotsGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/HotspotsGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->HotspotsGD
        return HotspotsGD(entlib.load_node_file(sourcefile, entlib.get_schema(HotspotsGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->HotspotsGD
        return HotspotsGD(entlib.make_node(HotspotsGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def HotspotsMap(self):  # type: ()->Map[str, HotspotData]
        return (lambda n: Map(str, HotspotData, n))(self._node.at("HotspotsMap"))
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class HitTriggerGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/HitTriggerGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->HitTriggerGD
        return HitTriggerGD(entlib.load_node_file(sourcefile, entlib.get_schema(HitTriggerGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->HitTriggerGD
        return HitTriggerGD(entlib.make_node(HitTriggerGD.schema_name))
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
    pass


from EntityLibPy import Node

class HeightObj(HelperObject):
    schema_name = "./EditionComponents.json#/definitions/HeightObj"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->HeightObj
        return HeightObj(entlib.load_node_file(sourcefile, entlib.get_schema(HeightObj.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->HeightObj
        return HeightObj(entlib.make_node(HeightObj.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def DisplaceNoiseList(self):  # type: ()->Array[DisplaceNoiseListItem]
        return (lambda n: Array(DisplaceNoiseListItem, n))(self._node.at("DisplaceNoiseList"))
    @property
    def EditorSubdivision(self):  # type: ()->Int
        return Int(self._node.at("EditorSubdivision"))
    @EditorSubdivision.setter
    def EditorSubdivision(self, val): self.EditorSubdivision.set(val)
    @property
    def LocalMatrix(self):  # type: ()->Matrix33
        return Matrix33(self._node.at("LocalMatrix"))
    @LocalMatrix.setter
    def LocalMatrix(self, val): self.LocalMatrix.set(val)
    @property
    def MeshFile(self):  # type: ()->String
        return String(self._node.at("MeshFile"))
    @MeshFile.setter
    def MeshFile(self, val): self.MeshFile.set(val)
    @property
    def MeshName(self):  # type: ()->String
        return String(self._node.at("MeshName"))
    @MeshName.setter
    def MeshName(self, val): self.MeshName.set(val)
    @property
    def Priority(self):  # type: ()->Int
        return Int(self._node.at("Priority"))
    @Priority.setter
    def Priority(self, val): self.Priority.set(val)
    @property
    def Subdivision(self):  # type: ()->Int
        return Int(self._node.at("Subdivision"))
    @Subdivision.setter
    def Subdivision(self, val): self.Subdivision.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class HeightMapComponentGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/HeightMapComponentGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->HeightMapComponentGD
        return HeightMapComponentGD(entlib.load_node_file(sourcefile, entlib.get_schema(HeightMapComponentGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->HeightMapComponentGD
        return HeightMapComponentGD(entlib.make_node(HeightMapComponentGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def HeightMapArchivePath(self):  # type: ()->String
        return String(self._node.at("HeightMapArchivePath"))
    @HeightMapArchivePath.setter
    def HeightMapArchivePath(self, val): self.HeightMapArchivePath.set(val)
    @property
    def HeightMapPaths(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("HeightMapPaths"))
    @HeightMapPaths.setter
    def HeightMapPaths(self, val): self.HeightMapPaths.set(val)
    @property
    def HeightScale(self):  # type: ()->Float
        return Float(self._node.at("HeightScale"))
    @HeightScale.setter
    def HeightScale(self, val): self.HeightScale.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def SwapX(self):  # type: ()->Bool
        return Bool(self._node.at("SwapX"))
    @SwapX.setter
    def SwapX(self, val): self.SwapX.set(val)
    @property
    def SwapY(self):  # type: ()->Bool
        return Bool(self._node.at("SwapY"))
    @SwapY.setter
    def SwapY(self, val): self.SwapY.set(val)
    @property
    def WorldSize(self):  # type: ()->Vector2
        return Vector2(self._node.at("WorldSize"))
    @WorldSize.setter
    def WorldSize(self, val): self.WorldSize.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class HealthAreaGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/HealthAreaGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->HealthAreaGD
        return HealthAreaGD(entlib.load_node_file(sourcefile, entlib.get_schema(HealthAreaGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->HealthAreaGD
        return HealthAreaGD(entlib.make_node(HealthAreaGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def EnergyRestorationRate(self):  # type: ()->Float
        return Float(self._node.at("EnergyRestorationRate"))
    @EnergyRestorationRate.setter
    def EnergyRestorationRate(self, val): self.EnergyRestorationRate.set(val)
    @property
    def FactionSide(self):  # type: ()->ReviveSide
        return ReviveSide(self._node.at("FactionSide"))
    @FactionSide.setter
    def FactionSide(self, val): self.FactionSide.set(val)
    @property
    def LifeRestorationRate(self):  # type: ()->Float
        return Float(self._node.at("LifeRestorationRate"))
    @LifeRestorationRate.setter
    def LifeRestorationRate(self, val): self.LifeRestorationRate.set(val)
    @property
    def Radius(self):  # type: ()->Float
        return Float(self._node.at("Radius"))
    @Radius.setter
    def Radius(self, val): self.Radius.set(val)
    @property
    def ReviveRestorationRate(self):  # type: ()->Float
        return Float(self._node.at("ReviveRestorationRate"))
    @ReviveRestorationRate.setter
    def ReviveRestorationRate(self, val): self.ReviveRestorationRate.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class HealerGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/HealerGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->HealerGD
        return HealerGD(entlib.load_node_file(sourcefile, entlib.get_schema(HealerGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->HealerGD
        return HealerGD(entlib.make_node(HealerGD.schema_name))
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
    pass


from EntityLibPy import Node

class HealTriggerGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/HealTriggerGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->HealTriggerGD
        return HealTriggerGD(entlib.load_node_file(sourcefile, entlib.get_schema(HealTriggerGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->HealTriggerGD
        return HealTriggerGD(entlib.make_node(HealTriggerGD.schema_name))
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
    pass


from EntityLibPy import Node

class HealPumpGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/HealPumpGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->HealPumpGD
        return HealPumpGD(entlib.load_node_file(sourcefile, entlib.get_schema(HealPumpGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->HealPumpGD
        return HealPumpGD(entlib.make_node(HealPumpGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AlliesLifeAgentPerSecond(self):  # type: ()->Float
        return Float(self._node.at("AlliesLifeAgentPerSecond"))
    @AlliesLifeAgentPerSecond.setter
    def AlliesLifeAgentPerSecond(self, val): self.AlliesLifeAgentPerSecond.set(val)
    @property
    def EnemiesLifeAgentPerSecond(self):  # type: ()->Float
        return Float(self._node.at("EnemiesLifeAgentPerSecond"))
    @EnemiesLifeAgentPerSecond.setter
    def EnemiesLifeAgentPerSecond(self, val): self.EnemiesLifeAgentPerSecond.set(val)
    @property
    def LifeAmountRatio(self):  # type: ()->Float
        return Float(self._node.at("LifeAmountRatio"))
    @LifeAmountRatio.setter
    def LifeAmountRatio(self, val): self.LifeAmountRatio.set(val)
    @property
    def Range(self):  # type: ()->Float
        return Float(self._node.at("Range"))
    @Range.setter
    def Range(self, val): self.Range.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class GroundTypeSamplerGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/GroundTypeSamplerGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->GroundTypeSamplerGD
        return GroundTypeSamplerGD(entlib.load_node_file(sourcefile, entlib.get_schema(GroundTypeSamplerGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->GroundTypeSamplerGD
        return GroundTypeSamplerGD(entlib.make_node(GroundTypeSamplerGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def GroundTypeMapPath(self):  # type: ()->String
        return String(self._node.at("GroundTypeMapPath"))
    @GroundTypeMapPath.setter
    def GroundTypeMapPath(self, val): self.GroundTypeMapPath.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class GameEffectSpawnerGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/GameEffectSpawnerGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->GameEffectSpawnerGD
        return GameEffectSpawnerGD(entlib.load_node_file(sourcefile, entlib.get_schema(GameEffectSpawnerGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->GameEffectSpawnerGD
        return GameEffectSpawnerGD(entlib.make_node(GameEffectSpawnerGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def GameEffectOffset(self):  # type: ()->Vector3
        return Vector3(self._node.at("GameEffectOffset"))
    @GameEffectOffset.setter
    def GameEffectOffset(self, val): self.GameEffectOffset.set(val)
    @property
    def StartGameEffects(self):  # type: ()->Array[sGameEffectTemplate]
        return (lambda n: Array(sGameEffectTemplate, n))(self._node.at("StartGameEffects"))
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class FluidVolumeComponentGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/FluidVolumeComponentGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->FluidVolumeComponentGD
        return FluidVolumeComponentGD(entlib.load_node_file(sourcefile, entlib.get_schema(FluidVolumeComponentGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->FluidVolumeComponentGD
        return FluidVolumeComponentGD(entlib.make_node(FluidVolumeComponentGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def FluidVolume(self):  # type: ()->FluidVolumeComponentGD_FluidVolumeData
        return FluidVolumeComponentGD_FluidVolumeData(self._node.at("FluidVolume"))
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class FluidViewGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/FluidViewGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->FluidViewGD
        return FluidViewGD(entlib.load_node_file(sourcefile, entlib.get_schema(FluidViewGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->FluidViewGD
        return FluidViewGD(entlib.make_node(FluidViewGD.schema_name))
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
    pass


from EntityLibPy import Node

class FluidToRegenInjectorGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/FluidToRegenInjectorGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->FluidToRegenInjectorGD
        return FluidToRegenInjectorGD(entlib.load_node_file(sourcefile, entlib.get_schema(FluidToRegenInjectorGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->FluidToRegenInjectorGD
        return FluidToRegenInjectorGD(entlib.make_node(FluidToRegenInjectorGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def EnergyPerSecond(self):  # type: ()->Float
        return Float(self._node.at("EnergyPerSecond"))
    @EnergyPerSecond.setter
    def EnergyPerSecond(self, val): self.EnergyPerSecond.set(val)
    @property
    def MinDepth(self):  # type: ()->Float
        return Float(self._node.at("MinDepth"))
    @MinDepth.setter
    def MinDepth(self, val): self.MinDepth.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def UpdatePeriod(self):  # type: ()->Float
        return Float(self._node.at("UpdatePeriod"))
    @UpdatePeriod.setter
    def UpdatePeriod(self, val): self.UpdatePeriod.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class FluidNavMeshTaggerGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/FluidNavMeshTaggerGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->FluidNavMeshTaggerGD
        return FluidNavMeshTaggerGD(entlib.load_node_file(sourcefile, entlib.get_schema(FluidNavMeshTaggerGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->FluidNavMeshTaggerGD
        return FluidNavMeshTaggerGD(entlib.make_node(FluidNavMeshTaggerGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def MinDepth(self):  # type: ()->Float
        return Float(self._node.at("MinDepth"))
    @MinDepth.setter
    def MinDepth(self, val): self.MinDepth.set(val)
    @property
    def SamplingPrecision(self):  # type: ()->Precision
        return Precision(self._node.at("SamplingPrecision"))
    @SamplingPrecision.setter
    def SamplingPrecision(self, val): self.SamplingPrecision.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def UpdatePeriod(self):  # type: ()->Float
        return Float(self._node.at("UpdatePeriod"))
    @UpdatePeriod.setter
    def UpdatePeriod(self, val): self.UpdatePeriod.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class FluidGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/FluidGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->FluidGD
        return FluidGD(entlib.load_node_file(sourcefile, entlib.get_schema(FluidGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->FluidGD
        return FluidGD(entlib.make_node(FluidGD.schema_name))
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
    def type(self):  # type: ()->FluidType
        return FluidType(self._node.at("type"))
    @type.setter
    def type(self, val): self.type.set(val)
    @property
    def useHalfShape(self):  # type: ()->Bool
        return Bool(self._node.at("useHalfShape"))
    @useHalfShape.setter
    def useHalfShape(self, val): self.useHalfShape.set(val)
    pass


from EntityLibPy import Node

class FluidFXEntitySpawnerGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/FluidFXEntitySpawnerGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->FluidFXEntitySpawnerGD
        return FluidFXEntitySpawnerGD(entlib.load_node_file(sourcefile, entlib.get_schema(FluidFXEntitySpawnerGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->FluidFXEntitySpawnerGD
        return FluidFXEntitySpawnerGD(entlib.make_node(FluidFXEntitySpawnerGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def SamplingPrecision(self):  # type: ()->Precision
        return Precision(self._node.at("SamplingPrecision"))
    @SamplingPrecision.setter
    def SamplingPrecision(self, val): self.SamplingPrecision.set(val)
    @property
    def SpawningParameters(self):  # type: ()->Array[SpawningParameter]
        return (lambda n: Array(SpawningParameter, n))(self._node.at("SpawningParameters"))
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def UpdatePeriod(self):  # type: ()->Float
        return Float(self._node.at("UpdatePeriod"))
    @UpdatePeriod.setter
    def UpdatePeriod(self, val): self.UpdatePeriod.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class FireSensorGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/FireSensorGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->FireSensorGD
        return FireSensorGD(entlib.load_node_file(sourcefile, entlib.get_schema(FireSensorGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->FireSensorGD
        return FireSensorGD(entlib.make_node(FireSensorGD.schema_name))
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
    pass


from EntityLibPy import Node

class EventTriggerGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/EventTriggerGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EventTriggerGD
        return EventTriggerGD(entlib.load_node_file(sourcefile, entlib.get_schema(EventTriggerGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EventTriggerGD
        return EventTriggerGD(entlib.make_node(EventTriggerGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Events(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("Events"))
    @Events.setter
    def Events(self, val): self.Events.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class EventHandlerGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/EventHandlerGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EventHandlerGD
        return EventHandlerGD(entlib.load_node_file(sourcefile, entlib.get_schema(EventHandlerGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EventHandlerGD
        return EventHandlerGD(entlib.make_node(EventHandlerGD.schema_name))
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
    pass


from EntityLibPy import Node

class EnvStampGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/EnvStampGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EnvStampGD
        return EnvStampGD(entlib.load_node_file(sourcefile, entlib.get_schema(EnvStampGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EnvStampGD
        return EnvStampGD(entlib.make_node(EnvStampGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def RegenStateChangeDuration(self):  # type: ()->Float
        return Float(self._node.at("RegenStateChangeDuration"))
    @RegenStateChangeDuration.setter
    def RegenStateChangeDuration(self, val): self.RegenStateChangeDuration.set(val)
    @property
    def Stamps(self):  # type: ()->Map[RegenerationStateEnum, Array[sEnvStamp]]
        return (lambda n: Map(RegenerationStateEnum, (lambda n: Array(sEnvStamp, n)), n))(self._node.at("Stamps"))
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class EnergySpoutGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/EnergySpoutGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EnergySpoutGD
        return EnergySpoutGD(entlib.load_node_file(sourcefile, entlib.get_schema(EnergySpoutGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EnergySpoutGD
        return EnergySpoutGD(entlib.make_node(EnergySpoutGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def EnergySpeed(self):  # type: ()->Float
        return Float(self._node.at("EnergySpeed"))
    @EnergySpeed.setter
    def EnergySpeed(self, val): self.EnergySpeed.set(val)
    @property
    def ListenerEntityRef(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("ListenerEntityRef"))
    @ListenerEntityRef.setter
    def ListenerEntityRef(self, val): self.ListenerEntityRef.set(val)
    @property
    def MinDistanceBetweenRegen(self):  # type: ()->Float
        return Float(self._node.at("MinDistanceBetweenRegen"))
    @MinDistanceBetweenRegen.setter
    def MinDistanceBetweenRegen(self, val): self.MinDistanceBetweenRegen.set(val)
    @property
    def MinTimeBetweenRegen(self):  # type: ()->Float
        return Float(self._node.at("MinTimeBetweenRegen"))
    @MinTimeBetweenRegen.setter
    def MinTimeBetweenRegen(self, val): self.MinTimeBetweenRegen.set(val)
    @property
    def Radius(self):  # type: ()->Float
        return Float(self._node.at("Radius"))
    @Radius.setter
    def Radius(self, val): self.Radius.set(val)
    @property
    def SplineRegenEffectName(self):  # type: ()->String
        return String(self._node.at("SplineRegenEffectName"))
    @SplineRegenEffectName.setter
    def SplineRegenEffectName(self, val): self.SplineRegenEffectName.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class EnergySourceGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/EnergySourceGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EnergySourceGD
        return EnergySourceGD(entlib.load_node_file(sourcefile, entlib.get_schema(EnergySourceGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EnergySourceGD
        return EnergySourceGD(entlib.make_node(EnergySourceGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def MaxBuffDuration(self):  # type: ()->Float
        return Float(self._node.at("MaxBuffDuration"))
    @MaxBuffDuration.setter
    def MaxBuffDuration(self, val): self.MaxBuffDuration.set(val)
    @property
    def NearbyReactionRadius(self):  # type: ()->Float
        return Float(self._node.at("NearbyReactionRadius"))
    @NearbyReactionRadius.setter
    def NearbyReactionRadius(self, val): self.NearbyReactionRadius.set(val)
    @property
    def Radius(self):  # type: ()->Float
        return Float(self._node.at("Radius"))
    @Radius.setter
    def Radius(self, val): self.Radius.set(val)
    @property
    def RefreshFrequency(self):  # type: ()->Float
        return Float(self._node.at("RefreshFrequency"))
    @RefreshFrequency.setter
    def RefreshFrequency(self, val): self.RefreshFrequency.set(val)
    @property
    def ReviveSide(self):  # type: ()->ReviveSide
        return ReviveSide(self._node.at("ReviveSide"))
    @ReviveSide.setter
    def ReviveSide(self, val): self.ReviveSide.set(val)
    @property
    def SourceRegenEffectName(self):  # type: ()->String
        return String(self._node.at("SourceRegenEffectName"))
    @SourceRegenEffectName.setter
    def SourceRegenEffectName(self, val): self.SourceRegenEffectName.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class EnergyProbeGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/EnergyProbeGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EnergyProbeGD
        return EnergyProbeGD(entlib.load_node_file(sourcefile, entlib.get_schema(EnergyProbeGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EnergyProbeGD
        return EnergyProbeGD(entlib.make_node(EnergyProbeGD.schema_name))
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
    pass


from EntityLibPy import Node

class EnergyPoolGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/EnergyPoolGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EnergyPoolGD
        return EnergyPoolGD(entlib.load_node_file(sourcefile, entlib.get_schema(EnergyPoolGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EnergyPoolGD
        return EnergyPoolGD(entlib.make_node(EnergyPoolGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def DrainConnectionRadius(self):  # type: ()->Float
        return Float(self._node.at("DrainConnectionRadius"))
    @DrainConnectionRadius.setter
    def DrainConnectionRadius(self, val): self.DrainConnectionRadius.set(val)
    @property
    def FactionOverride(self):  # type: ()->Bool
        return Bool(self._node.at("FactionOverride"))
    @FactionOverride.setter
    def FactionOverride(self, val): self.FactionOverride.set(val)
    @property
    def ProbeDetectionRadius(self):  # type: ()->Float
        return Float(self._node.at("ProbeDetectionRadius"))
    @ProbeDetectionRadius.setter
    def ProbeDetectionRadius(self, val): self.ProbeDetectionRadius.set(val)
    @property
    def RegenEffectsOnConversion(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("RegenEffectsOnConversion"))
    @RegenEffectsOnConversion.setter
    def RegenEffectsOnConversion(self, val): self.RegenEffectsOnConversion.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class EnergyNetworkListenerGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/EnergyNetworkListenerGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EnergyNetworkListenerGD
        return EnergyNetworkListenerGD(entlib.load_node_file(sourcefile, entlib.get_schema(EnergyNetworkListenerGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EnergyNetworkListenerGD
        return EnergyNetworkListenerGD(entlib.make_node(EnergyNetworkListenerGD.schema_name))
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
    pass


from EntityLibPy import Node

class EnergyDrainGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/EnergyDrainGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EnergyDrainGD
        return EnergyDrainGD(entlib.load_node_file(sourcefile, entlib.get_schema(EnergyDrainGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EnergyDrainGD
        return EnergyDrainGD(entlib.make_node(EnergyDrainGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def PoolEntityRef(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("PoolEntityRef"))
    @PoolEntityRef.setter
    def PoolEntityRef(self, val): self.PoolEntityRef.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class EnergyCrookGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/EnergyCrookGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EnergyCrookGD
        return EnergyCrookGD(entlib.load_node_file(sourcefile, entlib.get_schema(EnergyCrookGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EnergyCrookGD
        return EnergyCrookGD(entlib.make_node(EnergyCrookGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def FatherEntityRef(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("FatherEntityRef"))
    @FatherEntityRef.setter
    def FatherEntityRef(self, val): self.FatherEntityRef.set(val)
    @property
    def Radius(self):  # type: ()->Float
        return Float(self._node.at("Radius"))
    @Radius.setter
    def Radius(self, val): self.Radius.set(val)
    @property
    def RegenScale(self):  # type: ()->Float
        return Float(self._node.at("RegenScale"))
    @RegenScale.setter
    def RegenScale(self, val): self.RegenScale.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class DummyComponentGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/DummyComponentGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->DummyComponentGD
        return DummyComponentGD(entlib.load_node_file(sourcefile, entlib.get_schema(DummyComponentGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->DummyComponentGD
        return DummyComponentGD(entlib.make_node(DummyComponentGD.schema_name))
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
    pass


from EntityLibPy import Node

class DistanceTriggerGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/DistanceTriggerGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->DistanceTriggerGD
        return DistanceTriggerGD(entlib.load_node_file(sourcefile, entlib.get_schema(DistanceTriggerGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->DistanceTriggerGD
        return DistanceTriggerGD(entlib.make_node(DistanceTriggerGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Distances(self):  # type: ()->PrimArray[Float]
        return (lambda n: PrimArray(Float, n))(self._node.at("Distances"))
    @Distances.setter
    def Distances(self, val): self.Distances.set(val)
    @property
    def Hystereses(self):  # type: ()->PrimArray[Float]
        return (lambda n: PrimArray(Float, n))(self._node.at("Hystereses"))
    @Hystereses.setter
    def Hystereses(self, val): self.Hystereses.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class FightDistanceTriggerGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/FightDistanceTriggerGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->FightDistanceTriggerGD
        return FightDistanceTriggerGD(entlib.load_node_file(sourcefile, entlib.get_schema(FightDistanceTriggerGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->FightDistanceTriggerGD
        return FightDistanceTriggerGD(entlib.make_node(FightDistanceTriggerGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->DistanceTriggerGD
        return DistanceTriggerGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class DebugGridGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/DebugGridGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->DebugGridGD
        return DebugGridGD(entlib.load_node_file(sourcefile, entlib.get_schema(DebugGridGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->DebugGridGD
        return DebugGridGD(entlib.make_node(DebugGridGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Height(self):  # type: ()->Int
        return Int(self._node.at("Height"))
    @Height.setter
    def Height(self, val): self.Height.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def Width(self):  # type: ()->Int
        return Int(self._node.at("Width"))
    @Width.setter
    def Width(self, val): self.Width.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class CustomThumbnail(HelperObject):
    schema_name = "./EditionComponents.json#/definitions/CustomThumbnail"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CustomThumbnail
        return CustomThumbnail(entlib.load_node_file(sourcefile, entlib.get_schema(CustomThumbnail.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CustomThumbnail
        return CustomThumbnail(entlib.make_node(CustomThumbnail.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def Thumbnail(self):  # type: ()->ThumbPath
        return ThumbPath(self._node.at("Thumbnail"))
    @Thumbnail.setter
    def Thumbnail(self, val): self.Thumbnail.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class CreatureUIGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/CreatureUIGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CreatureUIGD
        return CreatureUIGD(entlib.load_node_file(sourcefile, entlib.get_schema(CreatureUIGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CreatureUIGD
        return CreatureUIGD(entlib.make_node(CreatureUIGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def LifeBarLength(self):  # type: ()->Float
        return Float(self._node.at("LifeBarLength"))
    @LifeBarLength.setter
    def LifeBarLength(self, val): self.LifeBarLength.set(val)
    @property
    def LifeBarWidth(self):  # type: ()->Float
        return Float(self._node.at("LifeBarWidth"))
    @LifeBarWidth.setter
    def LifeBarWidth(self, val): self.LifeBarWidth.set(val)
    @property
    def LifeBarZOffset(self):  # type: ()->Float
        return Float(self._node.at("LifeBarZOffset"))
    @LifeBarZOffset.setter
    def LifeBarZOffset(self, val): self.LifeBarZOffset.set(val)
    @property
    def ShowLifeBar(self):  # type: ()->Bool
        return Bool(self._node.at("ShowLifeBar"))
    @ShowLifeBar.setter
    def ShowLifeBar(self, val): self.ShowLifeBar.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class ConnectorGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ConnectorGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ConnectorGD
        return ConnectorGD(entlib.load_node_file(sourcefile, entlib.get_schema(ConnectorGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ConnectorGD
        return ConnectorGD(entlib.make_node(ConnectorGD.schema_name))
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
    pass


from EntityLibPy import Node

class ComponentWithProtoCodeGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ComponentWithProtoCodeGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ComponentWithProtoCodeGD
        return ComponentWithProtoCodeGD(entlib.load_node_file(sourcefile, entlib.get_schema(ComponentWithProtoCodeGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ComponentWithProtoCodeGD
        return ComponentWithProtoCodeGD(entlib.make_node(ComponentWithProtoCodeGD.schema_name))
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
    pass


from EntityLibPy import Node

class ClothAnimationGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ClothAnimationGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ClothAnimationGD
        return ClothAnimationGD(entlib.load_node_file(sourcefile, entlib.get_schema(ClothAnimationGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ClothAnimationGD
        return ClothAnimationGD(entlib.make_node(ClothAnimationGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def ClothSkeletonPath(self):  # type: ()->String
        return String(self._node.at("ClothSkeletonPath"))
    @ClothSkeletonPath.setter
    def ClothSkeletonPath(self, val): self.ClothSkeletonPath.set(val)
    @property
    def PhysicsDamping(self):  # type: ()->Float
        return Float(self._node.at("PhysicsDamping"))
    @PhysicsDamping.setter
    def PhysicsDamping(self, val): self.PhysicsDamping.set(val)
    @property
    def PhysicsFixedDt(self):  # type: ()->Bool
        return Bool(self._node.at("PhysicsFixedDt"))
    @PhysicsFixedDt.setter
    def PhysicsFixedDt(self, val): self.PhysicsFixedDt.set(val)
    @property
    def PhysicsGravity(self):  # type: ()->Vector3
        return Vector3(self._node.at("PhysicsGravity"))
    @PhysicsGravity.setter
    def PhysicsGravity(self, val): self.PhysicsGravity.set(val)
    @property
    def PhysicsMass(self):  # type: ()->Float
        return Float(self._node.at("PhysicsMass"))
    @PhysicsMass.setter
    def PhysicsMass(self, val): self.PhysicsMass.set(val)
    @property
    def PhysicsSpeedInfluence(self):  # type: ()->Float
        return Float(self._node.at("PhysicsSpeedInfluence"))
    @PhysicsSpeedInfluence.setter
    def PhysicsSpeedInfluence(self, val): self.PhysicsSpeedInfluence.set(val)
    @property
    def PhysicsUseDefaultProperties(self):  # type: ()->Bool
        return Bool(self._node.at("PhysicsUseDefaultProperties"))
    @PhysicsUseDefaultProperties.setter
    def PhysicsUseDefaultProperties(self, val): self.PhysicsUseDefaultProperties.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class ChildEntityPoolComponentGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ChildEntityPoolComponentGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ChildEntityPoolComponentGD
        return ChildEntityPoolComponentGD(entlib.load_node_file(sourcefile, entlib.get_schema(ChildEntityPoolComponentGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ChildEntityPoolComponentGD
        return ChildEntityPoolComponentGD(entlib.make_node(ChildEntityPoolComponentGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def EntityRefs(self):  # type: ()->PrimArray[EntityRef]
        return (lambda n: PrimArray(EntityRef, n))(self._node.at("EntityRefs"))
    @EntityRefs.setter
    def EntityRefs(self, val): self.EntityRefs.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class CharacterPlatformGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/CharacterPlatformGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CharacterPlatformGD
        return CharacterPlatformGD(entlib.load_node_file(sourcefile, entlib.get_schema(CharacterPlatformGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CharacterPlatformGD
        return CharacterPlatformGD(entlib.make_node(CharacterPlatformGD.schema_name))
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
    pass


from EntityLibPy import Node

class CameraDataGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/CameraDataGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CameraDataGD
        return CameraDataGD(entlib.load_node_file(sourcefile, entlib.get_schema(CameraDataGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CameraDataGD
        return CameraDataGD(entlib.make_node(CameraDataGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def CameraDataResourcePath(self):  # type: ()->String
        return String(self._node.at("CameraDataResourcePath"))
    @CameraDataResourcePath.setter
    def CameraDataResourcePath(self, val): self.CameraDataResourcePath.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class BreakableGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/BreakableGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->BreakableGD
        return BreakableGD(entlib.load_node_file(sourcefile, entlib.get_schema(BreakableGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->BreakableGD
        return BreakableGD(entlib.make_node(BreakableGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def BreakSoundBank(self):  # type: ()->String
        return String(self._node.at("BreakSoundBank"))
    @BreakSoundBank.setter
    def BreakSoundBank(self, val): self.BreakSoundBank.set(val)
    @property
    def BreakSoundEvent(self):  # type: ()->String
        return String(self._node.at("BreakSoundEvent"))
    @BreakSoundEvent.setter
    def BreakSoundEvent(self, val): self.BreakSoundEvent.set(val)
    @property
    def GameEffectOnBroken(self):  # type: ()->String
        return String(self._node.at("GameEffectOnBroken"))
    @GameEffectOnBroken.setter
    def GameEffectOnBroken(self, val): self.GameEffectOnBroken.set(val)
    @property
    def GameEffectOnDestruction(self):  # type: ()->String
        return String(self._node.at("GameEffectOnDestruction"))
    @GameEffectOnDestruction.setter
    def GameEffectOnDestruction(self, val): self.GameEffectOnDestruction.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def isBreakableWithAttack(self):  # type: ()->Bool
        return Bool(self._node.at("isBreakableWithAttack"))
    @isBreakableWithAttack.setter
    def isBreakableWithAttack(self, val): self.isBreakableWithAttack.set(val)
    pass


from EntityLibPy import Node

class BittenGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/BittenGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->BittenGD
        return BittenGD(entlib.load_node_file(sourcefile, entlib.get_schema(BittenGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->BittenGD
        return BittenGD(entlib.make_node(BittenGD.schema_name))
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
    pass


from EntityLibPy import Node

class BeamGeneratorGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/BeamGeneratorGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->BeamGeneratorGD
        return BeamGeneratorGD(entlib.load_node_file(sourcefile, entlib.get_schema(BeamGeneratorGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->BeamGeneratorGD
        return BeamGeneratorGD(entlib.make_node(BeamGeneratorGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def BonesStartPoints(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("BonesStartPoints"))
    @BonesStartPoints.setter
    def BonesStartPoints(self, val): self.BonesStartPoints.set(val)
    @property
    def ExtraDistanceBeyondTarget(self):  # type: ()->Float
        return Float(self._node.at("ExtraDistanceBeyondTarget"))
    @ExtraDistanceBeyondTarget.setter
    def ExtraDistanceBeyondTarget(self, val): self.ExtraDistanceBeyondTarget.set(val)
    @property
    def LengthDuration(self):  # type: ()->Float
        return Float(self._node.at("LengthDuration"))
    @LengthDuration.setter
    def LengthDuration(self, val): self.LengthDuration.set(val)
    @property
    def PathBeamEffect(self):  # type: ()->String
        return String(self._node.at("PathBeamEffect"))
    @PathBeamEffect.setter
    def PathBeamEffect(self, val): self.PathBeamEffect.set(val)
    @property
    def PointsPerBeam(self):  # type: ()->Int
        return Int(self._node.at("PointsPerBeam"))
    @PointsPerBeam.setter
    def PointsPerBeam(self, val): self.PointsPerBeam.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class AttackTriggerGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/AttackTriggerGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AttackTriggerGD
        return AttackTriggerGD(entlib.load_node_file(sourcefile, entlib.get_schema(AttackTriggerGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AttackTriggerGD
        return AttackTriggerGD(entlib.make_node(AttackTriggerGD.schema_name))
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
    pass


from EntityLibPy import Node

class AssemblyGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/AssemblyGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AssemblyGD
        return AssemblyGD(entlib.load_node_file(sourcefile, entlib.get_schema(AssemblyGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AssemblyGD
        return AssemblyGD(entlib.make_node(AssemblyGD.schema_name))
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
    pass


from EntityLibPy import Node

class AnimationRegenConstraintsGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/AnimationRegenConstraintsGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AnimationRegenConstraintsGD
        return AnimationRegenConstraintsGD(entlib.load_node_file(sourcefile, entlib.get_schema(AnimationRegenConstraintsGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AnimationRegenConstraintsGD
        return AnimationRegenConstraintsGD(entlib.make_node(AnimationRegenConstraintsGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def MaxDisplace(self):  # type: ()->Float
        return Float(self._node.at("MaxDisplace"))
    @MaxDisplace.setter
    def MaxDisplace(self, val): self.MaxDisplace.set(val)
    @property
    def MaxRegenSpeed(self):  # type: ()->Float
        return Float(self._node.at("MaxRegenSpeed"))
    @MaxRegenSpeed.setter
    def MaxRegenSpeed(self, val): self.MaxRegenSpeed.set(val)
    @property
    def MinDisplace(self):  # type: ()->Float
        return Float(self._node.at("MinDisplace"))
    @MinDisplace.setter
    def MinDisplace(self, val): self.MinDisplace.set(val)
    @property
    def RegenMultiplier(self):  # type: ()->Float
        return Float(self._node.at("RegenMultiplier"))
    @RegenMultiplier.setter
    def RegenMultiplier(self, val): self.RegenMultiplier.set(val)
    @property
    def RegenToDisplaceCurve(self):  # type: ()->String
        return String(self._node.at("RegenToDisplaceCurve"))
    @RegenToDisplaceCurve.setter
    def RegenToDisplaceCurve(self, val): self.RegenToDisplaceCurve.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class AnimationPlaylistGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/AnimationPlaylistGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AnimationPlaylistGD
        return AnimationPlaylistGD(entlib.load_node_file(sourcefile, entlib.get_schema(AnimationPlaylistGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AnimationPlaylistGD
        return AnimationPlaylistGD(entlib.make_node(AnimationPlaylistGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def PlayAnim(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("PlayAnim"))
    @PlayAnim.setter
    def PlayAnim(self, val): self.PlayAnim.set(val)
    @property
    def PlayAnimInputID(self):  # type: ()->Int
        return Int(self._node.at("PlayAnimInputID"))
    @PlayAnimInputID.setter
    def PlayAnimInputID(self, val): self.PlayAnimInputID.set(val)
    @property
    def RandomizeStartTime(self):  # type: ()->Bool
        return Bool(self._node.at("RandomizeStartTime"))
    @RandomizeStartTime.setter
    def RandomizeStartTime(self, val): self.RandomizeStartTime.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class AnimationPhysicsChainConstraintsGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/AnimationPhysicsChainConstraintsGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AnimationPhysicsChainConstraintsGD
        return AnimationPhysicsChainConstraintsGD(entlib.load_node_file(sourcefile, entlib.get_schema(AnimationPhysicsChainConstraintsGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AnimationPhysicsChainConstraintsGD
        return AnimationPhysicsChainConstraintsGD(entlib.make_node(AnimationPhysicsChainConstraintsGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def BoneNamePrefix(self):  # type: ()->String
        return String(self._node.at("BoneNamePrefix"))
    @BoneNamePrefix.setter
    def BoneNamePrefix(self, val): self.BoneNamePrefix.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class AnimationModelGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/AnimationModelGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AnimationModelGD
        return AnimationModelGD(entlib.load_node_file(sourcefile, entlib.get_schema(AnimationModelGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AnimationModelGD
        return AnimationModelGD(entlib.make_node(AnimationModelGD.schema_name))
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
    def isLandAnimDriven(self):  # type: ()->Bool
        return Bool(self._node.at("isLandAnimDriven"))
    @isLandAnimDriven.setter
    def isLandAnimDriven(self, val): self.isLandAnimDriven.set(val)
    @property
    def isTurnAllowed(self):  # type: ()->Bool
        return Bool(self._node.at("isTurnAllowed"))
    @isTurnAllowed.setter
    def isTurnAllowed(self, val): self.isTurnAllowed.set(val)
    @property
    def playRatioFactor(self):  # type: ()->Float
        return Float(self._node.at("playRatioFactor"))
    @playRatioFactor.setter
    def playRatioFactor(self, val): self.playRatioFactor.set(val)
    @property
    def scalePlayRatioCoeffInfluence(self):  # type: ()->Float
        return Float(self._node.at("scalePlayRatioCoeffInfluence"))
    @scalePlayRatioCoeffInfluence.setter
    def scalePlayRatioCoeffInfluence(self, val): self.scalePlayRatioCoeffInfluence.set(val)
    @property
    def startRunPlayRatioFactor(self):  # type: ()->Float
        return Float(self._node.at("startRunPlayRatioFactor"))
    @startRunPlayRatioFactor.setter
    def startRunPlayRatioFactor(self, val): self.startRunPlayRatioFactor.set(val)
    @property
    def turnPlayRatioFactor(self):  # type: ()->Float
        return Float(self._node.at("turnPlayRatioFactor"))
    @turnPlayRatioFactor.setter
    def turnPlayRatioFactor(self, val): self.turnPlayRatioFactor.set(val)
    pass


from EntityLibPy import Node

class AnimationHitsConstraintsGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/AnimationHitsConstraintsGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AnimationHitsConstraintsGD
        return AnimationHitsConstraintsGD(entlib.load_node_file(sourcefile, entlib.get_schema(AnimationHitsConstraintsGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AnimationHitsConstraintsGD
        return AnimationHitsConstraintsGD(entlib.make_node(AnimationHitsConstraintsGD.schema_name))
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
    pass


from EntityLibPy import Node
class Component(Union):
    pass


from EntityLibPy import Node
Object_Components = (lambda n: UnionSet(Component, n))
from EntityLibPy import Node
Components = (lambda n: UnionSet(Component, n))
from EntityLibPy import Node
Color = (lambda n: PrimArray(Float, n))
from EntityLibPy import Node

class LightComponentGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/LightComponentGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->LightComponentGD
        return LightComponentGD(entlib.load_node_file(sourcefile, entlib.get_schema(LightComponentGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->LightComponentGD
        return LightComponentGD(entlib.make_node(LightComponentGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AngleOffset(self):  # type: ()->Vector3
        return Vector3(self._node.at("AngleOffset"))
    @AngleOffset.setter
    def AngleOffset(self, val): self.AngleOffset.set(val)
    @property
    def Brightness(self):  # type: ()->Float
        return Float(self._node.at("Brightness"))
    @Brightness.setter
    def Brightness(self, val): self.Brightness.set(val)
    @property
    def CastShadow(self):  # type: ()->Bool
        return Bool(self._node.at("CastShadow"))
    @CastShadow.setter
    def CastShadow(self, val): self.CastShadow.set(val)
    @property
    def Color(self):  # type: ()->Color
        return Color(self._node.at("Color"))
    @Color.setter
    def Color(self, val): self.Color.set(val)
    @property
    def Direction(self):  # type: ()->Vector3
        return Vector3(self._node.at("Direction"))
    @Direction.setter
    def Direction(self, val): self.Direction.set(val)
    @property
    def Enabled(self):  # type: ()->Bool
        return Bool(self._node.at("Enabled"))
    @Enabled.setter
    def Enabled(self, val): self.Enabled.set(val)
    @property
    def LinearAttenuationStart(self):  # type: ()->Float
        return Float(self._node.at("LinearAttenuationStart"))
    @LinearAttenuationStart.setter
    def LinearAttenuationStart(self, val): self.LinearAttenuationStart.set(val)
    @property
    def LinearAttenuationStop(self):  # type: ()->Float
        return Float(self._node.at("LinearAttenuationStop"))
    @LinearAttenuationStop.setter
    def LinearAttenuationStop(self, val): self.LinearAttenuationStop.set(val)
    @property
    def Offset(self):  # type: ()->Vector3
        return Vector3(self._node.at("Offset"))
    @Offset.setter
    def Offset(self, val): self.Offset.set(val)
    @property
    def RadialAttenuationStart(self):  # type: ()->Float
        return Float(self._node.at("RadialAttenuationStart"))
    @RadialAttenuationStart.setter
    def RadialAttenuationStart(self, val): self.RadialAttenuationStart.set(val)
    @property
    def RadialAttenuationStop(self):  # type: ()->Float
        return Float(self._node.at("RadialAttenuationStop"))
    @RadialAttenuationStop.setter
    def RadialAttenuationStop(self, val): self.RadialAttenuationStop.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def Type_(self):  # type: ()->LightType
        return LightType(self._node.at("Type_"))
    @Type_.setter
    def Type_(self, val): self.Type_.set(val)
    @property
    def VolumetricFog(self):  # type: ()->Bool
        return Bool(self._node.at("VolumetricFog"))
    @VolumetricFog.setter
    def VolumetricFog(self, val): self.VolumetricFog.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class BoidsGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/BoidsGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->BoidsGD
        return BoidsGD(entlib.load_node_file(sourcefile, entlib.get_schema(BoidsGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->BoidsGD
        return BoidsGD(entlib.make_node(BoidsGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AffectedByFluid(self):  # type: ()->Bool
        return Bool(self._node.at("AffectedByFluid"))
    @AffectedByFluid.setter
    def AffectedByFluid(self, val): self.AffectedByFluid.set(val)
    @property
    def AllowMerge(self):  # type: ()->Bool
        return Bool(self._node.at("AllowMerge"))
    @AllowMerge.setter
    def AllowMerge(self, val): self.AllowMerge.set(val)
    @property
    def AutoMoveRoot(self):  # type: ()->Bool
        return Bool(self._node.at("AutoMoveRoot"))
    @AutoMoveRoot.setter
    def AutoMoveRoot(self, val): self.AutoMoveRoot.set(val)
    @property
    def BudEntityRef(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("BudEntityRef"))
    @BudEntityRef.setter
    def BudEntityRef(self, val): self.BudEntityRef.set(val)
    @property
    def BudVisualScaleMax(self):  # type: ()->Float
        return Float(self._node.at("BudVisualScaleMax"))
    @BudVisualScaleMax.setter
    def BudVisualScaleMax(self, val): self.BudVisualScaleMax.set(val)
    @property
    def BudVisualScaleMin(self):  # type: ()->Float
        return Float(self._node.at("BudVisualScaleMin"))
    @BudVisualScaleMin.setter
    def BudVisualScaleMin(self, val): self.BudVisualScaleMin.set(val)
    @property
    def DisplayMaster(self):  # type: ()->Bool
        return Bool(self._node.at("DisplayMaster"))
    @DisplayMaster.setter
    def DisplayMaster(self, val): self.DisplayMaster.set(val)
    @property
    def FlockingAttackDamages(self):  # type: ()->Float
        return Float(self._node.at("FlockingAttackDamages"))
    @FlockingAttackDamages.setter
    def FlockingAttackDamages(self, val): self.FlockingAttackDamages.set(val)
    @property
    def FluidSurfaceHeightOffset(self):  # type: ()->Float
        return Float(self._node.at("FluidSurfaceHeightOffset"))
    @FluidSurfaceHeightOffset.setter
    def FluidSurfaceHeightOffset(self, val): self.FluidSurfaceHeightOffset.set(val)
    @property
    def ForceOutsideWater(self):  # type: ()->Bool
        return Bool(self._node.at("ForceOutsideWater"))
    @ForceOutsideWater.setter
    def ForceOutsideWater(self, val): self.ForceOutsideWater.set(val)
    @property
    def FullEntityPoolRef(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("FullEntityPoolRef"))
    @FullEntityPoolRef.setter
    def FullEntityPoolRef(self, val): self.FullEntityPoolRef.set(val)
    @property
    def GetBackToFlockingDuration(self):  # type: ()->Float
        return Float(self._node.at("GetBackToFlockingDuration"))
    @GetBackToFlockingDuration.setter
    def GetBackToFlockingDuration(self, val): self.GetBackToFlockingDuration.set(val)
    @property
    def GhostDuration(self):  # type: ()->Float
        return Float(self._node.at("GhostDuration"))
    @GhostDuration.setter
    def GhostDuration(self, val): self.GhostDuration.set(val)
    @property
    def HierarchyDistanceMultiplier(self):  # type: ()->Float
        return Float(self._node.at("HierarchyDistanceMultiplier"))
    @HierarchyDistanceMultiplier.setter
    def HierarchyDistanceMultiplier(self, val): self.HierarchyDistanceMultiplier.set(val)
    @property
    def InitialRadius(self):  # type: ()->Float
        return Float(self._node.at("InitialRadius"))
    @InitialRadius.setter
    def InitialRadius(self, val): self.InitialRadius.set(val)
    @property
    def LightBrightness(self):  # type: ()->Float
        return Float(self._node.at("LightBrightness"))
    @LightBrightness.setter
    def LightBrightness(self, val): self.LightBrightness.set(val)
    @property
    def LightColor(self):  # type: ()->Color
        return Color(self._node.at("LightColor"))
    @LightColor.setter
    def LightColor(self, val): self.LightColor.set(val)
    @property
    def MainTargetHeight(self):  # type: ()->Float
        return Float(self._node.at("MainTargetHeight"))
    @MainTargetHeight.setter
    def MainTargetHeight(self, val): self.MainTargetHeight.set(val)
    @property
    def MainTargetRotateDistance(self):  # type: ()->Float
        return Float(self._node.at("MainTargetRotateDistance"))
    @MainTargetRotateDistance.setter
    def MainTargetRotateDistance(self, val): self.MainTargetRotateDistance.set(val)
    @property
    def MainTargetSpeedMultiplier(self):  # type: ()->Float
        return Float(self._node.at("MainTargetSpeedMultiplier"))
    @MainTargetSpeedMultiplier.setter
    def MainTargetSpeedMultiplier(self, val): self.MainTargetSpeedMultiplier.set(val)
    @property
    def MinRegenToWakeUp(self):  # type: ()->Float
        return Float(self._node.at("MinRegenToWakeUp"))
    @MinRegenToWakeUp.setter
    def MinRegenToWakeUp(self, val): self.MinRegenToWakeUp.set(val)
    @property
    def NbAgents(self):  # type: ()->Int
        return Int(self._node.at("NbAgents"))
    @NbAgents.setter
    def NbAgents(self, val): self.NbAgents.set(val)
    @property
    def NbAgentsPerZone(self):  # type: ()->Int
        return Int(self._node.at("NbAgentsPerZone"))
    @NbAgentsPerZone.setter
    def NbAgentsPerZone(self, val): self.NbAgentsPerZone.set(val)
    @property
    def ParamBlock(self):  # type: ()->String
        return String(self._node.at("ParamBlock"))
    @ParamBlock.setter
    def ParamBlock(self, val): self.ParamBlock.set(val)
    @property
    def ParamBudAppear(self):  # type: ()->String
        return String(self._node.at("ParamBudAppear"))
    @ParamBudAppear.setter
    def ParamBudAppear(self, val): self.ParamBudAppear.set(val)
    @property
    def ParamBudOpen(self):  # type: ()->String
        return String(self._node.at("ParamBudOpen"))
    @ParamBudOpen.setter
    def ParamBudOpen(self, val): self.ParamBudOpen.set(val)
    @property
    def ParamHome(self):  # type: ()->String
        return String(self._node.at("ParamHome"))
    @ParamHome.setter
    def ParamHome(self, val): self.ParamHome.set(val)
    @property
    def ParamMove(self):  # type: ()->String
        return String(self._node.at("ParamMove"))
    @ParamMove.setter
    def ParamMove(self, val): self.ParamMove.set(val)
    @property
    def ParamSwim(self):  # type: ()->String
        return String(self._node.at("ParamSwim"))
    @ParamSwim.setter
    def ParamSwim(self, val): self.ParamSwim.set(val)
    @property
    def ParamWakeUp(self):  # type: ()->String
        return String(self._node.at("ParamWakeUp"))
    @ParamWakeUp.setter
    def ParamWakeUp(self, val): self.ParamWakeUp.set(val)
    @property
    def PointCloudSearchRadius(self):  # type: ()->Float
        return Float(self._node.at("PointCloudSearchRadius"))
    @PointCloudSearchRadius.setter
    def PointCloudSearchRadius(self, val): self.PointCloudSearchRadius.set(val)
    @property
    def PointCloudTag(self):  # type: ()->String
        return String(self._node.at("PointCloudTag"))
    @PointCloudTag.setter
    def PointCloudTag(self, val): self.PointCloudTag.set(val)
    @property
    def PresetName(self):  # type: ()->String
        return String(self._node.at("PresetName"))
    @PresetName.setter
    def PresetName(self, val): self.PresetName.set(val)
    @property
    def PresetNameBud(self):  # type: ()->String
        return String(self._node.at("PresetNameBud"))
    @PresetNameBud.setter
    def PresetNameBud(self, val): self.PresetNameBud.set(val)
    @property
    def RegenMaxThreshold(self):  # type: ()->Float
        return Float(self._node.at("RegenMaxThreshold"))
    @RegenMaxThreshold.setter
    def RegenMaxThreshold(self, val): self.RegenMaxThreshold.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def VisualScaleMax(self):  # type: ()->Float
        return Float(self._node.at("VisualScaleMax"))
    @VisualScaleMax.setter
    def VisualScaleMax(self, val): self.VisualScaleMax.set(val)
    @property
    def VisualScaleMin(self):  # type: ()->Float
        return Float(self._node.at("VisualScaleMin"))
    @VisualScaleMin.setter
    def VisualScaleMin(self, val): self.VisualScaleMin.set(val)
    @property
    def WakeUpDuration(self):  # type: ()->Float
        return Float(self._node.at("WakeUpDuration"))
    @WakeUpDuration.setter
    def WakeUpDuration(self, val): self.WakeUpDuration.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class Collider(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/Collider"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->Collider
        return Collider(entlib.load_node_file(sourcefile, entlib.get_schema(Collider.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->Collider
        return Collider(entlib.make_node(Collider.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def BoneName(self):  # type: ()->String
        return String(self._node.at("BoneName"))
    @BoneName.setter
    def BoneName(self, val): self.BoneName.set(val)
    @property
    def RadiusFactor(self):  # type: ()->Float
        return Float(self._node.at("RadiusFactor"))
    @RadiusFactor.setter
    def RadiusFactor(self, val): self.RadiusFactor.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class AnimationTailConstraintsGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/AnimationTailConstraintsGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AnimationTailConstraintsGD
        return AnimationTailConstraintsGD(entlib.load_node_file(sourcefile, entlib.get_schema(AnimationTailConstraintsGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AnimationTailConstraintsGD
        return AnimationTailConstraintsGD(entlib.make_node(AnimationTailConstraintsGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AngularSpeedMaxForSpeedModeFurious(self):  # type: ()->Float
        return Float(self._node.at("AngularSpeedMaxForSpeedModeFurious"))
    @AngularSpeedMaxForSpeedModeFurious.setter
    def AngularSpeedMaxForSpeedModeFurious(self, val): self.AngularSpeedMaxForSpeedModeFurious.set(val)
    @property
    def AngularSpeedMaxForSpeedModeNone(self):  # type: ()->Float
        return Float(self._node.at("AngularSpeedMaxForSpeedModeNone"))
    @AngularSpeedMaxForSpeedModeNone.setter
    def AngularSpeedMaxForSpeedModeNone(self, val): self.AngularSpeedMaxForSpeedModeNone.set(val)
    @property
    def BoneInjectDirectionFromUseAmplitudeFactor(self):  # type: ()->Bool
        return Bool(self._node.at("BoneInjectDirectionFromUseAmplitudeFactor"))
    @BoneInjectDirectionFromUseAmplitudeFactor.setter
    def BoneInjectDirectionFromUseAmplitudeFactor(self, val): self.BoneInjectDirectionFromUseAmplitudeFactor.set(val)
    @property
    def BoneNameEnd(self):  # type: ()->String
        return String(self._node.at("BoneNameEnd"))
    @BoneNameEnd.setter
    def BoneNameEnd(self, val): self.BoneNameEnd.set(val)
    @property
    def BoneNameInjectDirectionFrom(self):  # type: ()->String
        return String(self._node.at("BoneNameInjectDirectionFrom"))
    @BoneNameInjectDirectionFrom.setter
    def BoneNameInjectDirectionFrom(self, val): self.BoneNameInjectDirectionFrom.set(val)
    @property
    def BoneNameStart(self):  # type: ()->String
        return String(self._node.at("BoneNameStart"))
    @BoneNameStart.setter
    def BoneNameStart(self, val): self.BoneNameStart.set(val)
    @property
    def Colliders(self):  # type: ()->Array[Collider]
        return (lambda n: Array(Collider, n))(self._node.at("Colliders"))
    @property
    def CollidersRadiusFactorGrounded(self):  # type: ()->Float
        return Float(self._node.at("CollidersRadiusFactorGrounded"))
    @CollidersRadiusFactorGrounded.setter
    def CollidersRadiusFactorGrounded(self, val): self.CollidersRadiusFactorGrounded.set(val)
    @property
    def CompensateSegmentStretchFactor(self):  # type: ()->Float
        return Float(self._node.at("CompensateSegmentStretchFactor"))
    @CompensateSegmentStretchFactor.setter
    def CompensateSegmentStretchFactor(self, val): self.CompensateSegmentStretchFactor.set(val)
    @property
    def ConditionalRigidityAttributes(self):  # type: ()->Array[ConditionalRigidityAttribute]
        return (lambda n: Array(ConditionalRigidityAttribute, n))(self._node.at("ConditionalRigidityAttributes"))
    @property
    def StickToGrounds(self):  # type: ()->Array[StickToGround]
        return (lambda n: Array(StickToGround, n))(self._node.at("StickToGrounds"))
    @property
    def StickToGroundsGravity(self):  # type: ()->Float
        return Float(self._node.at("StickToGroundsGravity"))
    @StickToGroundsGravity.setter
    def StickToGroundsGravity(self, val): self.StickToGroundsGravity.set(val)
    @property
    def StickToGroundsGravityUnderwater(self):  # type: ()->Float
        return Float(self._node.at("StickToGroundsGravityUnderwater"))
    @StickToGroundsGravityUnderwater.setter
    def StickToGroundsGravityUnderwater(self, val): self.StickToGroundsGravityUnderwater.set(val)
    @property
    def StickToGroundsRadiusFactorDead(self):  # type: ()->Float
        return Float(self._node.at("StickToGroundsRadiusFactorDead"))
    @StickToGroundsRadiusFactorDead.setter
    def StickToGroundsRadiusFactorDead(self, val): self.StickToGroundsRadiusFactorDead.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node
class CinematicUpdateTypeEnum(Enum):
    none = "none"
    Internal = "Internal"
    Pesto = "Pesto"
    CinematicUpdateType_COUNT = "CinematicUpdateType_COUNT"


class CinematicUpdateType(Primitive[CinematicUpdateTypeEnum]):  # Enum
    def __init__(self, node):
        super().__init__(CinematicUpdateTypeEnum, node)
    schema_name = "CinematicUpdateType"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> CinematicUpdateType
        return CinematicUpdateType(node)
    def set(self, val):  # type: (CinematicUpdateTypeEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)


from EntityLibPy import Node

class CinematicSlot(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/CinematicSlot"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CinematicSlot
        return CinematicSlot(entlib.load_node_file(sourcefile, entlib.get_schema(CinematicSlot.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CinematicSlot
        return CinematicSlot(entlib.make_node(CinematicSlot.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def ActorBone(self):  # type: ()->String
        return String(self._node.at("ActorBone"))
    @ActorBone.setter
    def ActorBone(self, val): self.ActorBone.set(val)
    @property
    def Anim(self):  # type: ()->String
        return String(self._node.at("Anim"))
    @Anim.setter
    def Anim(self, val): self.Anim.set(val)
    @property
    def CameraHolder(self):  # type: ()->Bool
        return Bool(self._node.at("CameraHolder"))
    @CameraHolder.setter
    def CameraHolder(self, val): self.CameraHolder.set(val)
    @property
    def CanBeInstanciated(self):  # type: ()->Bool
        return Bool(self._node.at("CanBeInstanciated"))
    @CanBeInstanciated.setter
    def CanBeInstanciated(self, val): self.CanBeInstanciated.set(val)
    @property
    def DestroyAfter(self):  # type: ()->Bool
        return Bool(self._node.at("DestroyAfter"))
    @DestroyAfter.setter
    def DestroyAfter(self, val): self.DestroyAfter.set(val)
    @property
    def EntityRef(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("EntityRef"))
    @EntityRef.setter
    def EntityRef(self, val): self.EntityRef.set(val)
    @property
    def EventCameraHolder(self):  # type: ()->Bool
        return Bool(self._node.at("EventCameraHolder"))
    @EventCameraHolder.setter
    def EventCameraHolder(self, val): self.EventCameraHolder.set(val)
    @property
    def FOV(self):  # type: ()->Float
        return Float(self._node.at("FOV"))
    @FOV.setter
    def FOV(self, val): self.FOV.set(val)
    @property
    def FadeInDelay(self):  # type: ()->Float
        return Float(self._node.at("FadeInDelay"))
    @FadeInDelay.setter
    def FadeInDelay(self, val): self.FadeInDelay.set(val)
    @property
    def FadeOutDelay(self):  # type: ()->Float
        return Float(self._node.at("FadeOutDelay"))
    @FadeOutDelay.setter
    def FadeOutDelay(self, val): self.FadeOutDelay.set(val)
    @property
    def InitTransform(self):  # type: ()->Transform3D
        return Transform3D(self._node.at("InitTransform"))
    @property
    def MainRole(self):  # type: ()->Bool
        return Bool(self._node.at("MainRole"))
    @MainRole.setter
    def MainRole(self, val): self.MainRole.set(val)
    @property
    def Mandatory(self):  # type: ()->Bool
        return Bool(self._node.at("Mandatory"))
    @Mandatory.setter
    def Mandatory(self, val): self.Mandatory.set(val)
    @property
    def Role(self):  # type: ()->String
        return String(self._node.at("Role"))
    @Role.setter
    def Role(self, val): self.Role.set(val)
    @property
    def RoleInNextSequence(self):  # type: ()->String
        return String(self._node.at("RoleInNextSequence"))
    @RoleInNextSequence.setter
    def RoleInNextSequence(self, val): self.RoleInNextSequence.set(val)
    @property
    def Visible(self):  # type: ()->Bool
        return Bool(self._node.at("Visible"))
    @Visible.setter
    def Visible(self, val): self.Visible.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class Sequence(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/Sequence"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->Sequence
        return Sequence(entlib.load_node_file(sourcefile, entlib.get_schema(Sequence.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->Sequence
        return Sequence(entlib.make_node(Sequence.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def ActivationDelay(self):  # type: ()->Float
        return Float(self._node.at("ActivationDelay"))
    @ActivationDelay.setter
    def ActivationDelay(self, val): self.ActivationDelay.set(val)
    @property
    def AutoSwitchToNextSequence(self):  # type: ()->Bool
        return Bool(self._node.at("AutoSwitchToNextSequence"))
    @AutoSwitchToNextSequence.setter
    def AutoSwitchToNextSequence(self, val): self.AutoSwitchToNextSequence.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def actors(self):  # type: ()->Array[CinematicSlot]
        return (lambda n: Array(CinematicSlot, n))(self._node.at("actors"))
    @property
    def loop(self):  # type: ()->Bool
        return Bool(self._node.at("loop"))
    @loop.setter
    def loop(self, val): self.loop.set(val)
    @property
    def name(self):  # type: ()->String
        return String(self._node.at("name"))
    @name.setter
    def name(self, val): self.name.set(val)
    pass


from EntityLibPy import Node

class CinematicGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/CinematicGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CinematicGD
        return CinematicGD(entlib.load_node_file(sourcefile, entlib.get_schema(CinematicGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CinematicGD
        return CinematicGD(entlib.make_node(CinematicGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def ActivationDistance(self):  # type: ()->Float
        return Float(self._node.at("ActivationDistance"))
    @ActivationDistance.setter
    def ActivationDistance(self, val): self.ActivationDistance.set(val)
    @property
    def ScriptEvents(self):  # type: ()->Array[ResponsiblePointer_CineEvent_]
        return (lambda n: Array(ResponsiblePointer_CineEvent_, n))(self._node.at("ScriptEvents"))
    @property
    def Sequences(self):  # type: ()->Array[Sequence]
        return (lambda n: Array(Sequence, n))(self._node.at("Sequences"))
    @property
    def Skippable(self):  # type: ()->Bool
        return Bool(self._node.at("Skippable"))
    @Skippable.setter
    def Skippable(self, val): self.Skippable.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def UpdateType(self):  # type: ()->CinematicUpdateType
        return CinematicUpdateType(self._node.at("UpdateType"))
    @UpdateType.setter
    def UpdateType(self, val): self.UpdateType.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class CineEvent(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/CineEvent"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CineEvent
        return CineEvent(entlib.load_node_file(sourcefile, entlib.get_schema(CineEvent.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CineEvent
        return CineEvent(entlib.make_node(CineEvent.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Active(self):  # type: ()->Bool
        return Bool(self._node.at("Active"))
    @Active.setter
    def Active(self, val): self.Active.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class CineEventTrigger(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/CineEventTrigger"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CineEventTrigger
        return CineEventTrigger(entlib.load_node_file(sourcefile, entlib.get_schema(CineEventTrigger.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CineEventTrigger
        return CineEventTrigger(entlib.make_node(CineEventTrigger.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->CineEvent
        return CineEvent(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class CineEventTriggerPlaySound(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/CineEventTriggerPlaySound"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CineEventTriggerPlaySound
        return CineEventTriggerPlaySound(entlib.load_node_file(sourcefile, entlib.get_schema(CineEventTriggerPlaySound.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CineEventTriggerPlaySound
        return CineEventTriggerPlaySound(entlib.make_node(CineEventTriggerPlaySound.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def SoundEventName(self):  # type: ()->String
        return String(self._node.at("SoundEventName"))
    @SoundEventName.setter
    def SoundEventName(self, val): self.SoundEventName.set(val)
    @property
    def Super(self):  # type: ()->CineEventTrigger
        return CineEventTrigger(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class CineEventTriggerPlaySequence(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/CineEventTriggerPlaySequence"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CineEventTriggerPlaySequence
        return CineEventTriggerPlaySequence(entlib.load_node_file(sourcefile, entlib.get_schema(CineEventTriggerPlaySequence.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CineEventTriggerPlaySequence
        return CineEventTriggerPlaySequence(entlib.make_node(CineEventTriggerPlaySequence.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def SequenceID(self):  # type: ()->Int
        return Int(self._node.at("SequenceID"))
    @SequenceID.setter
    def SequenceID(self, val): self.SequenceID.set(val)
    @property
    def Super(self):  # type: ()->CineEventTrigger
        return CineEventTrigger(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class CineEventTriggerGameStateChange(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/CineEventTriggerGameStateChange"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CineEventTriggerGameStateChange
        return CineEventTriggerGameStateChange(entlib.load_node_file(sourcefile, entlib.get_schema(CineEventTriggerGameStateChange.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CineEventTriggerGameStateChange
        return CineEventTriggerGameStateChange(entlib.make_node(CineEventTriggerGameStateChange.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def GameStateName(self):  # type: ()->String
        return String(self._node.at("GameStateName"))
    @GameStateName.setter
    def GameStateName(self, val): self.GameStateName.set(val)
    @property
    def Super(self):  # type: ()->CineEventTrigger
        return CineEventTrigger(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class CineEventTriggerEventHandlerPost(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/CineEventTriggerEventHandlerPost"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CineEventTriggerEventHandlerPost
        return CineEventTriggerEventHandlerPost(entlib.load_node_file(sourcefile, entlib.get_schema(CineEventTriggerEventHandlerPost.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CineEventTriggerEventHandlerPost
        return CineEventTriggerEventHandlerPost(entlib.make_node(CineEventTriggerEventHandlerPost.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def EventCategory(self):  # type: ()->String
        return String(self._node.at("EventCategory"))
    @EventCategory.setter
    def EventCategory(self, val): self.EventCategory.set(val)
    @property
    def EventName(self):  # type: ()->String
        return String(self._node.at("EventName"))
    @EventName.setter
    def EventName(self, val): self.EventName.set(val)
    @property
    def Super(self):  # type: ()->CineEventTrigger
        return CineEventTrigger(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class CineEventTest(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/CineEventTest"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CineEventTest
        return CineEventTest(entlib.load_node_file(sourcefile, entlib.get_schema(CineEventTest.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CineEventTest
        return CineEventTest(entlib.make_node(CineEventTest.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def InvertTest(self):  # type: ()->Bool
        return Bool(self._node.at("InvertTest"))
    @InvertTest.setter
    def InvertTest(self, val): self.InvertTest.set(val)
    @property
    def Super(self):  # type: ()->CineEvent
        return CineEvent(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class CineEventTestWait(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/CineEventTestWait"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CineEventTestWait
        return CineEventTestWait(entlib.load_node_file(sourcefile, entlib.get_schema(CineEventTestWait.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CineEventTestWait
        return CineEventTestWait(entlib.make_node(CineEventTestWait.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Duration(self):  # type: ()->Float
        return Float(self._node.at("Duration"))
    @Duration.setter
    def Duration(self, val): self.Duration.set(val)
    @property
    def Super(self):  # type: ()->CineEventTest
        return CineEventTest(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class CineEventTestIsCanceled(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/CineEventTestIsCanceled"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CineEventTestIsCanceled
        return CineEventTestIsCanceled(entlib.load_node_file(sourcefile, entlib.get_schema(CineEventTestIsCanceled.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CineEventTestIsCanceled
        return CineEventTestIsCanceled(entlib.make_node(CineEventTestIsCanceled.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->CineEventTest
        return CineEventTest(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class CineEventTestInput(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/CineEventTestInput"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CineEventTestInput
        return CineEventTestInput(entlib.load_node_file(sourcefile, entlib.get_schema(CineEventTestInput.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CineEventTestInput
        return CineEventTestInput(entlib.make_node(CineEventTestInput.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AnyButtonInput(self):  # type: ()->Bool
        return Bool(self._node.at("AnyButtonInput"))
    @AnyButtonInput.setter
    def AnyButtonInput(self, val): self.AnyButtonInput.set(val)
    @property
    def AnyJoyInput(self):  # type: ()->Bool
        return Bool(self._node.at("AnyJoyInput"))
    @AnyJoyInput.setter
    def AnyJoyInput(self, val): self.AnyJoyInput.set(val)
    @property
    def Super(self):  # type: ()->CineEventTest
        return CineEventTest(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class CineEventTestEndCurrentSequence(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/CineEventTestEndCurrentSequence"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CineEventTestEndCurrentSequence
        return CineEventTestEndCurrentSequence(entlib.load_node_file(sourcefile, entlib.get_schema(CineEventTestEndCurrentSequence.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CineEventTestEndCurrentSequence
        return CineEventTestEndCurrentSequence(entlib.make_node(CineEventTestEndCurrentSequence.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->CineEventTest
        return CineEventTest(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class CineEventTestCurrentGameState(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/CineEventTestCurrentGameState"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CineEventTestCurrentGameState
        return CineEventTestCurrentGameState(entlib.load_node_file(sourcefile, entlib.get_schema(CineEventTestCurrentGameState.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CineEventTestCurrentGameState
        return CineEventTestCurrentGameState(entlib.make_node(CineEventTestCurrentGameState.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def GameStateName(self):  # type: ()->String
        return String(self._node.at("GameStateName"))
    @GameStateName.setter
    def GameStateName(self, val): self.GameStateName.set(val)
    @property
    def Super(self):  # type: ()->CineEventTest
        return CineEventTest(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class CharacterControllerSlideData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/CharacterControllerSlideData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CharacterControllerSlideData
        return CharacterControllerSlideData(entlib.load_node_file(sourcefile, entlib.get_schema(CharacterControllerSlideData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CharacterControllerSlideData
        return CharacterControllerSlideData(entlib.make_node(CharacterControllerSlideData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def adherenceRecoverSpeedDependingOnTheSlope(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("adherenceRecoverSpeedDependingOnTheSlope"))
    @property
    def adherenceThresholdHysteresis(self):  # type: ()->Float
        return Float(self._node.at("adherenceThresholdHysteresis"))
    @adherenceThresholdHysteresis.setter
    def adherenceThresholdHysteresis(self, val): self.adherenceThresholdHysteresis.set(val)
    @property
    def adherenceThresholdRequiredToKeepControl(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("adherenceThresholdRequiredToKeepControl"))
    @property
    def adherenceUsingDownwardSlopeDirection(self):  # type: ()->Float
        return Float(self._node.at("adherenceUsingDownwardSlopeDirection"))
    @adherenceUsingDownwardSlopeDirection.setter
    def adherenceUsingDownwardSlopeDirection(self, val): self.adherenceUsingDownwardSlopeDirection.set(val)
    @property
    def adherenceUsingSideSlopeDirection(self):  # type: ()->Float
        return Float(self._node.at("adherenceUsingSideSlopeDirection"))
    @adherenceUsingSideSlopeDirection.setter
    def adherenceUsingSideSlopeDirection(self, val): self.adherenceUsingSideSlopeDirection.set(val)
    @property
    def adherenceUsingUpwardSlopeDirection(self):  # type: ()->Float
        return Float(self._node.at("adherenceUsingUpwardSlopeDirection"))
    @adherenceUsingUpwardSlopeDirection.setter
    def adherenceUsingUpwardSlopeDirection(self, val): self.adherenceUsingUpwardSlopeDirection.set(val)
    @property
    def animblendInTime(self):  # type: ()->Float
        return Float(self._node.at("animblendInTime"))
    @animblendInTime.setter
    def animblendInTime(self, val): self.animblendInTime.set(val)
    @property
    def friction(self):  # type: ()->Float
        return Float(self._node.at("friction"))
    @friction.setter
    def friction(self, val): self.friction.set(val)
    @property
    def maxSlopeAngle(self):  # type: ()->Float
        return Float(self._node.at("maxSlopeAngle"))
    @maxSlopeAngle.setter
    def maxSlopeAngle(self, val): self.maxSlopeAngle.set(val)
    @property
    def speedMediumCoeffHysteresis(self):  # type: ()->Float
        return Float(self._node.at("speedMediumCoeffHysteresis"))
    @speedMediumCoeffHysteresis.setter
    def speedMediumCoeffHysteresis(self, val): self.speedMediumCoeffHysteresis.set(val)
    @property
    def speedMediumCoeffIn(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("speedMediumCoeffIn"))
    @property
    def speedMediumCoeffMin(self):  # type: ()->Float
        return Float(self._node.at("speedMediumCoeffMin"))
    @speedMediumCoeffMin.setter
    def speedMediumCoeffMin(self, val): self.speedMediumCoeffMin.set(val)
    pass


from EntityLibPy import Node

class CharacterControllerGroundNormalData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/CharacterControllerGroundNormalData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CharacterControllerGroundNormalData
        return CharacterControllerGroundNormalData(entlib.load_node_file(sourcefile, entlib.get_schema(CharacterControllerGroundNormalData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CharacterControllerGroundNormalData
        return CharacterControllerGroundNormalData(entlib.make_node(CharacterControllerGroundNormalData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AllowOtherCreatureCast(self):  # type: ()->Bool
        return Bool(self._node.at("AllowOtherCreatureCast"))
    @AllowOtherCreatureCast.setter
    def AllowOtherCreatureCast(self, val): self.AllowOtherCreatureCast.set(val)
    @property
    def PercentageEdgeTolerance(self):  # type: ()->Float
        return Float(self._node.at("PercentageEdgeTolerance"))
    @PercentageEdgeTolerance.setter
    def PercentageEdgeTolerance(self, val): self.PercentageEdgeTolerance.set(val)
    @property
    def PercentageExtirpate(self):  # type: ()->Float
        return Float(self._node.at("PercentageExtirpate"))
    @PercentageExtirpate.setter
    def PercentageExtirpate(self, val): self.PercentageExtirpate.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class CharacterControllerFallData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/CharacterControllerFallData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CharacterControllerFallData
        return CharacterControllerFallData(entlib.load_node_file(sourcefile, entlib.get_schema(CharacterControllerFallData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CharacterControllerFallData
        return CharacterControllerFallData(entlib.make_node(CharacterControllerFallData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def DamagesPerHeightFall(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("DamagesPerHeightFall"))
    @property
    def MinHeightForDamageFall(self):  # type: ()->Float
        return Float(self._node.at("MinHeightForDamageFall"))
    @MinHeightForDamageFall.setter
    def MinHeightForDamageFall(self, val): self.MinHeightForDamageFall.set(val)
    @property
    def MinHeightForDeathFall(self):  # type: ()->Float
        return Float(self._node.at("MinHeightForDeathFall"))
    @MinHeightForDeathFall.setter
    def MinHeightForDeathFall(self, val): self.MinHeightForDeathFall.set(val)
    @property
    def MinHeightForRecoveryFall(self):  # type: ()->Float
        return Float(self._node.at("MinHeightForRecoveryFall"))
    @MinHeightForRecoveryFall.setter
    def MinHeightForRecoveryFall(self, val): self.MinHeightForRecoveryFall.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class CharacterControllerClamberData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/CharacterControllerClamberData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CharacterControllerClamberData
        return CharacterControllerClamberData(entlib.load_node_file(sourcefile, entlib.get_schema(CharacterControllerClamberData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CharacterControllerClamberData
        return CharacterControllerClamberData(entlib.make_node(CharacterControllerClamberData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def DropOffAngle(self):  # type: ()->Float
        return Float(self._node.at("DropOffAngle"))
    @DropOffAngle.setter
    def DropOffAngle(self, val): self.DropOffAngle.set(val)
    @property
    def EnterAngle(self):  # type: ()->Float
        return Float(self._node.at("EnterAngle"))
    @EnterAngle.setter
    def EnterAngle(self, val): self.EnterAngle.set(val)
    @property
    def ExitAngle(self):  # type: ()->Float
        return Float(self._node.at("ExitAngle"))
    @ExitAngle.setter
    def ExitAngle(self, val): self.ExitAngle.set(val)
    @property
    def IsAllowed(self):  # type: ()->Bool
        return Bool(self._node.at("IsAllowed"))
    @IsAllowed.setter
    def IsAllowed(self, val): self.IsAllowed.set(val)
    @property
    def VerticalOrientationRatio(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("VerticalOrientationRatio"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node
class CameraTypeEnum(Enum):
    NONE = "NONE"
    Death = "Death"
    Editor = "Editor"
    Event = "Event"
    Free = "Free"
    ThirdPerson = "ThirdPerson"
    ThirdPersonFollow = "ThirdPersonFollow"
    ThirdPersonAim = "ThirdPersonAim"
    ThirdPersonClamber = "ThirdPersonClamber"
    MotionConstraint = "MotionConstraint"
    OnSpline = "OnSpline"
    OnBones = "OnBones"
    TopView = "TopView"
    EntitySwap = "EntitySwap"
    Locked = "Locked"
    Pan = "Pan"
    CameraType_COUNT = "CameraType_COUNT"


class CameraType(Primitive[CameraTypeEnum]):  # Enum
    def __init__(self, node):
        super().__init__(CameraTypeEnum, node)
    schema_name = "CameraType"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> CameraType
        return CameraType(node)
    def set(self, val):  # type: (CameraTypeEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)


from EntityLibPy import Node

class CameraSetterGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/CameraSetterGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CameraSetterGD
        return CameraSetterGD(entlib.load_node_file(sourcefile, entlib.get_schema(CameraSetterGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CameraSetterGD
        return CameraSetterGD(entlib.make_node(CameraSetterGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def SetPositionToHotspot(self):  # type: ()->Bool
        return Bool(self._node.at("SetPositionToHotspot"))
    @SetPositionToHotspot.setter
    def SetPositionToHotspot(self, val): self.SetPositionToHotspot.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def SwitchToType(self):  # type: ()->Bool
        return Bool(self._node.at("SwitchToType"))
    @SwitchToType.setter
    def SwitchToType(self, val): self.SwitchToType.set(val)
    @property
    def Type_(self):  # type: ()->CameraType
        return CameraType(self._node.at("Type_"))
    @Type_.setter
    def Type_(self, val): self.Type_.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class CameraShakeData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/CameraShakeData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CameraShakeData
        return CameraShakeData(entlib.load_node_file(sourcefile, entlib.get_schema(CameraShakeData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CameraShakeData
        return CameraShakeData(entlib.make_node(CameraShakeData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def shakeDuration(self):  # type: ()->Float
        return Float(self._node.at("shakeDuration"))
    @shakeDuration.setter
    def shakeDuration(self, val): self.shakeDuration.set(val)
    @property
    def shakeFrequency(self):  # type: ()->Float
        return Float(self._node.at("shakeFrequency"))
    @shakeFrequency.setter
    def shakeFrequency(self, val): self.shakeFrequency.set(val)
    @property
    def shakeIntensity(self):  # type: ()->Float
        return Float(self._node.at("shakeIntensity"))
    @shakeIntensity.setter
    def shakeIntensity(self, val): self.shakeIntensity.set(val)
    @property
    def shakeRotation(self):  # type: ()->Vector3
        return Vector3(self._node.at("shakeRotation"))
    @shakeRotation.setter
    def shakeRotation(self, val): self.shakeRotation.set(val)
    pass


from EntityLibPy import Node

class BiteData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/BiteData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->BiteData
        return BiteData(entlib.load_node_file(sourcefile, entlib.get_schema(BiteData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->BiteData
        return BiteData(entlib.make_node(BiteData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def CanBiteBiped(self):  # type: ()->Bool
        return Bool(self._node.at("CanBiteBiped"))
    @CanBiteBiped.setter
    def CanBiteBiped(self, val): self.CanBiteBiped.set(val)
    @property
    def CanBiteFriends(self):  # type: ()->Bool
        return Bool(self._node.at("CanBiteFriends"))
    @CanBiteFriends.setter
    def CanBiteFriends(self, val): self.CanBiteFriends.set(val)
    @property
    def CheckHotspotOrientation(self):  # type: ()->Bool
        return Bool(self._node.at("CheckHotspotOrientation"))
    @CheckHotspotOrientation.setter
    def CheckHotspotOrientation(self, val): self.CheckHotspotOrientation.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def bezierMove(self):  # type: ()->Bool
        return Bool(self._node.at("bezierMove"))
    @bezierMove.setter
    def bezierMove(self, val): self.bezierMove.set(val)
    @property
    def biteDamagePerSec(self):  # type: ()->Float
        return Float(self._node.at("biteDamagePerSec"))
    @biteDamagePerSec.setter
    def biteDamagePerSec(self, val): self.biteDamagePerSec.set(val)
    @property
    def biteDefenseDamages(self):  # type: ()->Float
        return Float(self._node.at("biteDefenseDamages"))
    @biteDefenseDamages.setter
    def biteDefenseDamages(self, val): self.biteDefenseDamages.set(val)
    @property
    def biteDuration(self):  # type: ()->Float
        return Float(self._node.at("biteDuration"))
    @biteDuration.setter
    def biteDuration(self, val): self.biteDuration.set(val)
    @property
    def biteMaxRange(self):  # type: ()->Float
        return Float(self._node.at("biteMaxRange"))
    @biteMaxRange.setter
    def biteMaxRange(self, val): self.biteMaxRange.set(val)
    pass


from EntityLibPy import Node

class BehaviorScriptData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/BehaviorScriptData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->BehaviorScriptData
        return BehaviorScriptData(entlib.load_node_file(sourcefile, entlib.get_schema(BehaviorScriptData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->BehaviorScriptData
        return BehaviorScriptData(entlib.make_node(BehaviorScriptData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def additionalDangerousnessDiffToFlee(self):  # type: ()->Float
        return Float(self._node.at("additionalDangerousnessDiffToFlee"))
    @additionalDangerousnessDiffToFlee.setter
    def additionalDangerousnessDiffToFlee(self, val): self.additionalDangerousnessDiffToFlee.set(val)
    @property
    def aimingDuration(self):  # type: ()->Float
        return Float(self._node.at("aimingDuration"))
    @aimingDuration.setter
    def aimingDuration(self, val): self.aimingDuration.set(val)
    @property
    def answerAttackRunSpeed(self):  # type: ()->Int
        return Int(self._node.at("answerAttackRunSpeed"))
    @answerAttackRunSpeed.setter
    def answerAttackRunSpeed(self, val): self.answerAttackRunSpeed.set(val)
    @property
    def artificialArenaRadius(self):  # type: ()->Float
        return Float(self._node.at("artificialArenaRadius"))
    @artificialArenaRadius.setter
    def artificialArenaRadius(self, val): self.artificialArenaRadius.set(val)
    @property
    def attackAggressivityDecrease(self):  # type: ()->Int
        return Int(self._node.at("attackAggressivityDecrease"))
    @attackAggressivityDecrease.setter
    def attackAggressivityDecrease(self, val): self.attackAggressivityDecrease.set(val)
    @property
    def attackIfEnemyHasBeenSeenSince(self):  # type: ()->Float
        return Float(self._node.at("attackIfEnemyHasBeenSeenSince"))
    @attackIfEnemyHasBeenSeenSince.setter
    def attackIfEnemyHasBeenSeenSince(self, val): self.attackIfEnemyHasBeenSeenSince.set(val)
    @property
    def attackInPack(self):  # type: ()->Bool
        return Bool(self._node.at("attackInPack"))
    @attackInPack.setter
    def attackInPack(self, val): self.attackInPack.set(val)
    @property
    def attackOrderCanFlee(self):  # type: ()->Bool
        return Bool(self._node.at("attackOrderCanFlee"))
    @attackOrderCanFlee.setter
    def attackOrderCanFlee(self, val): self.attackOrderCanFlee.set(val)
    @property
    def attackRunSpeed(self):  # type: ()->Int
        return Int(self._node.at("attackRunSpeed"))
    @attackRunSpeed.setter
    def attackRunSpeed(self, val): self.attackRunSpeed.set(val)
    @property
    def attackWaitCircle_Offset_Z(self):  # type: ()->Float
        return Float(self._node.at("attackWaitCircle_Offset_Z"))
    @attackWaitCircle_Offset_Z.setter
    def attackWaitCircle_Offset_Z(self, val): self.attackWaitCircle_Offset_Z.set(val)
    @property
    def avoidGroundMovements(self):  # type: ()->Bool
        return Bool(self._node.at("avoidGroundMovements"))
    @avoidGroundMovements.setter
    def avoidGroundMovements(self, val): self.avoidGroundMovements.set(val)
    @property
    def avoidWaterMovements(self):  # type: ()->Bool
        return Bool(self._node.at("avoidWaterMovements"))
    @avoidWaterMovements.setter
    def avoidWaterMovements(self, val): self.avoidWaterMovements.set(val)
    @property
    def blockedByScaryWeather(self):  # type: ()->Bool
        return Bool(self._node.at("blockedByScaryWeather"))
    @blockedByScaryWeather.setter
    def blockedByScaryWeather(self, val): self.blockedByScaryWeather.set(val)
    @property
    def canBite(self):  # type: ()->Bool
        return Bool(self._node.at("canBite"))
    @canBite.setter
    def canBite(self, val): self.canBite.set(val)
    @property
    def canFlee(self):  # type: ()->Bool
        return Bool(self._node.at("canFlee"))
    @canFlee.setter
    def canFlee(self, val): self.canFlee.set(val)
    @property
    def closeAttack_Offset_Z(self):  # type: ()->Float
        return Float(self._node.at("closeAttack_Offset_Z"))
    @closeAttack_Offset_Z.setter
    def closeAttack_Offset_Z(self, val): self.closeAttack_Offset_Z.set(val)
    @property
    def closeCombatDistance(self):  # type: ()->Float
        return Float(self._node.at("closeCombatDistance"))
    @closeCombatDistance.setter
    def closeCombatDistance(self, val): self.closeCombatDistance.set(val)
    @property
    def combatFlyingHeightOffset(self):  # type: ()->Float
        return Float(self._node.at("combatFlyingHeightOffset"))
    @combatFlyingHeightOffset.setter
    def combatFlyingHeightOffset(self, val): self.combatFlyingHeightOffset.set(val)
    @property
    def combatSpeedModeOnNodes(self):  # type: ()->Int
        return Int(self._node.at("combatSpeedModeOnNodes"))
    @combatSpeedModeOnNodes.setter
    def combatSpeedModeOnNodes(self, val): self.combatSpeedModeOnNodes.set(val)
    @property
    def combatStopOnNodeCoolDown(self):  # type: ()->Float
        return Float(self._node.at("combatStopOnNodeCoolDown"))
    @combatStopOnNodeCoolDown.setter
    def combatStopOnNodeCoolDown(self, val): self.combatStopOnNodeCoolDown.set(val)
    @property
    def combatStopOnNodeMaxTime(self):  # type: ()->Float
        return Float(self._node.at("combatStopOnNodeMaxTime"))
    @combatStopOnNodeMaxTime.setter
    def combatStopOnNodeMaxTime(self, val): self.combatStopOnNodeMaxTime.set(val)
    @property
    def combatTooCloseDistance(self):  # type: ()->Float
        return Float(self._node.at("combatTooCloseDistance"))
    @combatTooCloseDistance.setter
    def combatTooCloseDistance(self, val): self.combatTooCloseDistance.set(val)
    @property
    def combatTriggerStopOnNodeTimerDistance(self):  # type: ()->Float
        return Float(self._node.at("combatTriggerStopOnNodeTimerDistance"))
    @combatTriggerStopOnNodeTimerDistance.setter
    def combatTriggerStopOnNodeTimerDistance(self, val): self.combatTriggerStopOnNodeTimerDistance.set(val)
    @property
    def considersRunnerAsAMenace(self):  # type: ()->Bool
        return Bool(self._node.at("considersRunnerAsAMenace"))
    @considersRunnerAsAMenace.setter
    def considersRunnerAsAMenace(self, val): self.considersRunnerAsAMenace.set(val)
    @property
    def coolDownBetweenProjectileDodge(self):  # type: ()->Float
        return Float(self._node.at("coolDownBetweenProjectileDodge"))
    @coolDownBetweenProjectileDodge.setter
    def coolDownBetweenProjectileDodge(self, val): self.coolDownBetweenProjectileDodge.set(val)
    @property
    def drivingAimAngle(self):  # type: ()->Float
        return Float(self._node.at("drivingAimAngle"))
    @drivingAimAngle.setter
    def drivingAimAngle(self, val): self.drivingAimAngle.set(val)
    @property
    def drivingAimSpeed(self):  # type: ()->Float
        return Float(self._node.at("drivingAimSpeed"))
    @drivingAimSpeed.setter
    def drivingAimSpeed(self, val): self.drivingAimSpeed.set(val)
    @property
    def enemyAggressivity(self):  # type: ()->Int
        return Int(self._node.at("enemyAggressivity"))
    @enemyAggressivity.setter
    def enemyAggressivity(self, val): self.enemyAggressivity.set(val)
    @property
    def energyAttackProbability(self):  # type: ()->Float
        return Float(self._node.at("energyAttackProbability"))
    @energyAttackProbability.setter
    def energyAttackProbability(self, val): self.energyAttackProbability.set(val)
    @property
    def engageInCombatDistance(self):  # type: ()->Float
        return Float(self._node.at("engageInCombatDistance"))
    @engageInCombatDistance.setter
    def engageInCombatDistance(self, val): self.engageInCombatDistance.set(val)
    @property
    def farCombatDistance(self):  # type: ()->Float
        return Float(self._node.at("farCombatDistance"))
    @farCombatDistance.setter
    def farCombatDistance(self, val): self.farCombatDistance.set(val)
    @property
    def feelsSafeWhenDangerIsThisFar(self):  # type: ()->Float
        return Float(self._node.at("feelsSafeWhenDangerIsThisFar"))
    @feelsSafeWhenDangerIsThisFar.setter
    def feelsSafeWhenDangerIsThisFar(self, val): self.feelsSafeWhenDangerIsThisFar.set(val)
    @property
    def fleeDistToEnemy(self):  # type: ()->Float
        return Float(self._node.at("fleeDistToEnemy"))
    @fleeDistToEnemy.setter
    def fleeDistToEnemy(self, val): self.fleeDistToEnemy.set(val)
    @property
    def fleeMaxDist(self):  # type: ()->Float
        return Float(self._node.at("fleeMaxDist"))
    @fleeMaxDist.setter
    def fleeMaxDist(self, val): self.fleeMaxDist.set(val)
    @property
    def fleeTime(self):  # type: ()->Float
        return Float(self._node.at("fleeTime"))
    @fleeTime.setter
    def fleeTime(self, val): self.fleeTime.set(val)
    @property
    def flockingArenaRadius(self):  # type: ()->Float
        return Float(self._node.at("flockingArenaRadius"))
    @flockingArenaRadius.setter
    def flockingArenaRadius(self, val): self.flockingArenaRadius.set(val)
    @property
    def friendAggressivity(self):  # type: ()->Int
        return Int(self._node.at("friendAggressivity"))
    @friendAggressivity.setter
    def friendAggressivity(self, val): self.friendAggressivity.set(val)
    @property
    def goToTargetCheckDistance(self):  # type: ()->Float
        return Float(self._node.at("goToTargetCheckDistance"))
    @goToTargetCheckDistance.setter
    def goToTargetCheckDistance(self, val): self.goToTargetCheckDistance.set(val)
    @property
    def guideFollowMalusScorePerSec(self):  # type: ()->Float
        return Float(self._node.at("guideFollowMalusScorePerSec"))
    @guideFollowMalusScorePerSec.setter
    def guideFollowMalusScorePerSec(self, val): self.guideFollowMalusScorePerSec.set(val)
    @property
    def guideFollowMaxBonusScorePerSec(self):  # type: ()->Float
        return Float(self._node.at("guideFollowMaxBonusScorePerSec"))
    @guideFollowMaxBonusScorePerSec.setter
    def guideFollowMaxBonusScorePerSec(self, val): self.guideFollowMaxBonusScorePerSec.set(val)
    @property
    def guideFollowMaxDistToScore(self):  # type: ()->Float
        return Float(self._node.at("guideFollowMaxDistToScore"))
    @guideFollowMaxDistToScore.setter
    def guideFollowMaxDistToScore(self, val): self.guideFollowMaxDistToScore.set(val)
    @property
    def guideFollowMaxDistanceToTrail(self):  # type: ()->Float
        return Float(self._node.at("guideFollowMaxDistanceToTrail"))
    @guideFollowMaxDistanceToTrail.setter
    def guideFollowMaxDistanceToTrail(self, val): self.guideFollowMaxDistanceToTrail.set(val)
    @property
    def guideFollowMinBonusScorePerSec(self):  # type: ()->Float
        return Float(self._node.at("guideFollowMinBonusScorePerSec"))
    @guideFollowMinBonusScorePerSec.setter
    def guideFollowMinBonusScorePerSec(self, val): self.guideFollowMinBonusScorePerSec.set(val)
    @property
    def guideFollowMinDistToScore(self):  # type: ()->Float
        return Float(self._node.at("guideFollowMinDistToScore"))
    @guideFollowMinDistToScore.setter
    def guideFollowMinDistToScore(self, val): self.guideFollowMinDistToScore.set(val)
    @property
    def guideFollowScoreThreshold(self):  # type: ()->Float
        return Float(self._node.at("guideFollowScoreThreshold"))
    @guideFollowScoreThreshold.setter
    def guideFollowScoreThreshold(self, val): self.guideFollowScoreThreshold.set(val)
    @property
    def guideFollowTimeBetweenTeleport(self):  # type: ()->Float
        return Float(self._node.at("guideFollowTimeBetweenTeleport"))
    @guideFollowTimeBetweenTeleport.setter
    def guideFollowTimeBetweenTeleport(self, val): self.guideFollowTimeBetweenTeleport.set(val)
    @property
    def guideMinSpeed(self):  # type: ()->Float
        return Float(self._node.at("guideMinSpeed"))
    @guideMinSpeed.setter
    def guideMinSpeed(self, val): self.guideMinSpeed.set(val)
    @property
    def guideRepulsiveDistIn(self):  # type: ()->Float
        return Float(self._node.at("guideRepulsiveDistIn"))
    @guideRepulsiveDistIn.setter
    def guideRepulsiveDistIn(self, val): self.guideRepulsiveDistIn.set(val)
    @property
    def guideRepulsiveDistOut(self):  # type: ()->Float
        return Float(self._node.at("guideRepulsiveDistOut"))
    @guideRepulsiveDistOut.setter
    def guideRepulsiveDistOut(self, val): self.guideRepulsiveDistOut.set(val)
    @property
    def hardFeelingsFriendlyHitCount(self):  # type: ()->Int
        return Int(self._node.at("hardFeelingsFriendlyHitCount"))
    @hardFeelingsFriendlyHitCount.setter
    def hardFeelingsFriendlyHitCount(self, val): self.hardFeelingsFriendlyHitCount.set(val)
    @property
    def hardFeelingsNotFriendlyHitCount(self):  # type: ()->Int
        return Int(self._node.at("hardFeelingsNotFriendlyHitCount"))
    @hardFeelingsNotFriendlyHitCount.setter
    def hardFeelingsNotFriendlyHitCount(self, val): self.hardFeelingsNotFriendlyHitCount.set(val)
    @property
    def helpOtherDoneIfLifeAboveThreshold(self):  # type: ()->Float
        return Float(self._node.at("helpOtherDoneIfLifeAboveThreshold"))
    @helpOtherDoneIfLifeAboveThreshold.setter
    def helpOtherDoneIfLifeAboveThreshold(self, val): self.helpOtherDoneIfLifeAboveThreshold.set(val)
    @property
    def helpOtherIfLifeBelowThreshold(self):  # type: ()->Float
        return Float(self._node.at("helpOtherIfLifeBelowThreshold"))
    @helpOtherIfLifeBelowThreshold.setter
    def helpOtherIfLifeBelowThreshold(self, val): self.helpOtherIfLifeBelowThreshold.set(val)
    @property
    def innerArenaRatio(self):  # type: ()->Float
        return Float(self._node.at("innerArenaRatio"))
    @innerArenaRatio.setter
    def innerArenaRatio(self, val): self.innerArenaRatio.set(val)
    @property
    def isAffectedByStench(self):  # type: ()->Bool
        return Bool(self._node.at("isAffectedByStench"))
    @isAffectedByStench.setter
    def isAffectedByStench(self, val): self.isAffectedByStench.set(val)
    @property
    def isCourageous(self):  # type: ()->Bool
        return Bool(self._node.at("isCourageous"))
    @isCourageous.setter
    def isCourageous(self, val): self.isCourageous.set(val)
    @property
    def isScaredBySoundEffect(self):  # type: ()->Bool
        return Bool(self._node.at("isScaredBySoundEffect"))
    @isScaredBySoundEffect.setter
    def isScaredBySoundEffect(self, val): self.isScaredBySoundEffect.set(val)
    @property
    def jumpAttackProbability(self):  # type: ()->Float
        return Float(self._node.at("jumpAttackProbability"))
    @jumpAttackProbability.setter
    def jumpAttackProbability(self, val): self.jumpAttackProbability.set(val)
    @property
    def lifeInDangerThreshold(self):  # type: ()->Float
        return Float(self._node.at("lifeInDangerThreshold"))
    @lifeInDangerThreshold.setter
    def lifeInDangerThreshold(self, val): self.lifeInDangerThreshold.set(val)
    @property
    def lifeInNoMoreDangerThreshold(self):  # type: ()->Float
        return Float(self._node.at("lifeInNoMoreDangerThreshold"))
    @lifeInNoMoreDangerThreshold.setter
    def lifeInNoMoreDangerThreshold(self, val): self.lifeInNoMoreDangerThreshold.set(val)
    @property
    def lockEnemyFollowMaxDistFromGuide(self):  # type: ()->Float
        return Float(self._node.at("lockEnemyFollowMaxDistFromGuide"))
    @lockEnemyFollowMaxDistFromGuide.setter
    def lockEnemyFollowMaxDistFromGuide(self, val): self.lockEnemyFollowMaxDistFromGuide.set(val)
    @property
    def maxDistanceToFollowBeam(self):  # type: ()->Float
        return Float(self._node.at("maxDistanceToFollowBeam"))
    @maxDistanceToFollowBeam.setter
    def maxDistanceToFollowBeam(self, val): self.maxDistanceToFollowBeam.set(val)
    @property
    def maxFollowerCount(self):  # type: ()->Int
        return Int(self._node.at("maxFollowerCount"))
    @maxFollowerCount.setter
    def maxFollowerCount(self, val): self.maxFollowerCount.set(val)
    @property
    def maxLookOutModeTimer(self):  # type: ()->Float
        return Float(self._node.at("maxLookOutModeTimer"))
    @maxLookOutModeTimer.setter
    def maxLookOutModeTimer(self, val): self.maxLookOutModeTimer.set(val)
    @property
    def maxTimeBeforeStoppingToWaitForBeam(self):  # type: ()->Float
        return Float(self._node.at("maxTimeBeforeStoppingToWaitForBeam"))
    @maxTimeBeforeStoppingToWaitForBeam.setter
    def maxTimeBeforeStoppingToWaitForBeam(self, val): self.maxTimeBeforeStoppingToWaitForBeam.set(val)
    @property
    def menaceSelection(self):  # type: ()->MenaceSelection
        return MenaceSelection(self._node.at("menaceSelection"))
    @menaceSelection.setter
    def menaceSelection(self, val): self.menaceSelection.set(val)
    @property
    def middleCombatDistance(self):  # type: ()->Float
        return Float(self._node.at("middleCombatDistance"))
    @middleCombatDistance.setter
    def middleCombatDistance(self, val): self.middleCombatDistance.set(val)
    @property
    def minAbsoluteDistanceToTeleportToMaster(self):  # type: ()->Float
        return Float(self._node.at("minAbsoluteDistanceToTeleportToMaster"))
    @minAbsoluteDistanceToTeleportToMaster.setter
    def minAbsoluteDistanceToTeleportToMaster(self, val): self.minAbsoluteDistanceToTeleportToMaster.set(val)
    @property
    def minDistanceToBeamPosition(self):  # type: ()->Float
        return Float(self._node.at("minDistanceToBeamPosition"))
    @minDistanceToBeamPosition.setter
    def minDistanceToBeamPosition(self, val): self.minDistanceToBeamPosition.set(val)
    @property
    def minDistanceToFollowBeam(self):  # type: ()->Float
        return Float(self._node.at("minDistanceToFollowBeam"))
    @minDistanceToFollowBeam.setter
    def minDistanceToFollowBeam(self, val): self.minDistanceToFollowBeam.set(val)
    @property
    def minNavmeshDistanceToTeleportToMaster(self):  # type: ()->Float
        return Float(self._node.at("minNavmeshDistanceToTeleportToMaster"))
    @minNavmeshDistanceToTeleportToMaster.setter
    def minNavmeshDistanceToTeleportToMaster(self, val): self.minNavmeshDistanceToTeleportToMaster.set(val)
    @property
    def minTimeBeforeStoppingToWaitForBeam(self):  # type: ()->Float
        return Float(self._node.at("minTimeBeforeStoppingToWaitForBeam"))
    @minTimeBeforeStoppingToWaitForBeam.setter
    def minTimeBeforeStoppingToWaitForBeam(self, val): self.minTimeBeforeStoppingToWaitForBeam.set(val)
    @property
    def noAttackTimeAfterAttack(self):  # type: ()->Float
        return Float(self._node.at("noAttackTimeAfterAttack"))
    @noAttackTimeAfterAttack.setter
    def noAttackTimeAfterAttack(self, val): self.noAttackTimeAfterAttack.set(val)
    @property
    def offerAGiftWhenChosen(self):  # type: ()->Bool
        return Bool(self._node.at("offerAGiftWhenChosen"))
    @offerAGiftWhenChosen.setter
    def offerAGiftWhenChosen(self, val): self.offerAGiftWhenChosen.set(val)
    @property
    def panicAggressivityDecrease(self):  # type: ()->Int
        return Int(self._node.at("panicAggressivityDecrease"))
    @panicAggressivityDecrease.setter
    def panicAggressivityDecrease(self, val): self.panicAggressivityDecrease.set(val)
    @property
    def panicsWhenGameEffect(self):  # type: ()->Int
        return Int(self._node.at("panicsWhenGameEffect"))
    @panicsWhenGameEffect.setter
    def panicsWhenGameEffect(self, val): self.panicsWhenGameEffect.set(val)
    @property
    def returnOnCircleAfterMaxAttacks(self):  # type: ()->Int
        return Int(self._node.at("returnOnCircleAfterMaxAttacks"))
    @returnOnCircleAfterMaxAttacks.setter
    def returnOnCircleAfterMaxAttacks(self, val): self.returnOnCircleAfterMaxAttacks.set(val)
    @property
    def roamSpeedModeOnNodes(self):  # type: ()->Int
        return Int(self._node.at("roamSpeedModeOnNodes"))
    @roamSpeedModeOnNodes.setter
    def roamSpeedModeOnNodes(self, val): self.roamSpeedModeOnNodes.set(val)
    @property
    def runsForDistancesSuperiorTo(self):  # type: ()->Float
        return Float(self._node.at("runsForDistancesSuperiorTo"))
    @runsForDistancesSuperiorTo.setter
    def runsForDistancesSuperiorTo(self, val): self.runsForDistancesSuperiorTo.set(val)
    @property
    def searchSoulOpportunity(self):  # type: ()->Bool
        return Bool(self._node.at("searchSoulOpportunity"))
    @searchSoulOpportunity.setter
    def searchSoulOpportunity(self, val): self.searchSoulOpportunity.set(val)
    @property
    def shootPreferedEnemyDistance(self):  # type: ()->Float
        return Float(self._node.at("shootPreferedEnemyDistance"))
    @shootPreferedEnemyDistance.setter
    def shootPreferedEnemyDistance(self, val): self.shootPreferedEnemyDistance.set(val)
    @property
    def shootSequence(self):  # type: ()->Array[ShootSequenceData]
        return (lambda n: Array(ShootSequenceData, n))(self._node.at("shootSequence"))
    @property
    def shootingMistakeMaxDelta(self):  # type: ()->Float
        return Float(self._node.at("shootingMistakeMaxDelta"))
    @shootingMistakeMaxDelta.setter
    def shootingMistakeMaxDelta(self, val): self.shootingMistakeMaxDelta.set(val)
    @property
    def shouldConquer(self):  # type: ()->Bool
        return Bool(self._node.at("shouldConquer"))
    @shouldConquer.setter
    def shouldConquer(self, val): self.shouldConquer.set(val)
    @property
    def shouldDodgeAfterAttack(self):  # type: ()->Bool
        return Bool(self._node.at("shouldDodgeAfterAttack"))
    @shouldDodgeAfterAttack.setter
    def shouldDodgeAfterAttack(self, val): self.shouldDodgeAfterAttack.set(val)
    @property
    def shouldHealPools(self):  # type: ()->Bool
        return Bool(self._node.at("shouldHealPools"))
    @shouldHealPools.setter
    def shouldHealPools(self, val): self.shouldHealPools.set(val)
    @property
    def shouldJumpInArena(self):  # type: ()->Bool
        return Bool(self._node.at("shouldJumpInArena"))
    @shouldJumpInArena.setter
    def shouldJumpInArena(self, val): self.shouldJumpInArena.set(val)
    @property
    def shouldStrafe(self):  # type: ()->Bool
        return Bool(self._node.at("shouldStrafe"))
    @shouldStrafe.setter
    def shouldStrafe(self, val): self.shouldStrafe.set(val)
    @property
    def shouldTranshumance(self):  # type: ()->Bool
        return Bool(self._node.at("shouldTranshumance"))
    @shouldTranshumance.setter
    def shouldTranshumance(self, val): self.shouldTranshumance.set(val)
    @property
    def staffAngleFullHint(self):  # type: ()->Float
        return Float(self._node.at("staffAngleFullHint"))
    @staffAngleFullHint.setter
    def staffAngleFullHint(self, val): self.staffAngleFullHint.set(val)
    @property
    def staffMaxTimeInAlert(self):  # type: ()->Float
        return Float(self._node.at("staffMaxTimeInAlert"))
    @staffMaxTimeInAlert.setter
    def staffMaxTimeInAlert(self, val): self.staffMaxTimeInAlert.set(val)
    @property
    def staffMinScoreToAlert(self):  # type: ()->Int
        return Int(self._node.at("staffMinScoreToAlert"))
    @staffMinScoreToAlert.setter
    def staffMinScoreToAlert(self, val): self.staffMinScoreToAlert.set(val)
    @property
    def staffTimeBeforeAlertAgain(self):  # type: ()->Float
        return Float(self._node.at("staffTimeBeforeAlertAgain"))
    @staffTimeBeforeAlertAgain.setter
    def staffTimeBeforeAlertAgain(self, val): self.staffTimeBeforeAlertAgain.set(val)
    @property
    def usesWarningShot(self):  # type: ()->Bool
        return Bool(self._node.at("usesWarningShot"))
    @usesWarningShot.setter
    def usesWarningShot(self, val): self.usesWarningShot.set(val)
    pass


from EntityLibPy import Node

class CreatureAIGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/CreatureAIGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CreatureAIGD
        return CreatureAIGD(entlib.load_node_file(sourcefile, entlib.get_schema(CreatureAIGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CreatureAIGD
        return CreatureAIGD(entlib.make_node(CreatureAIGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def BehaviorModifiersTags(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("BehaviorModifiersTags"))
    @BehaviorModifiersTags.setter
    def BehaviorModifiersTags(self, val): self.BehaviorModifiersTags.set(val)
    @property
    def BehaviorPath(self):  # type: ()->String
        return String(self._node.at("BehaviorPath"))
    @BehaviorPath.setter
    def BehaviorPath(self, val): self.BehaviorPath.set(val)
    @property
    def BehaviorState(self):  # type: ()->String
        return String(self._node.at("BehaviorState"))
    @BehaviorState.setter
    def BehaviorState(self, val): self.BehaviorState.set(val)
    @property
    def CanBeMaster(self):  # type: ()->Bool
        return Bool(self._node.at("CanBeMaster"))
    @CanBeMaster.setter
    def CanBeMaster(self, val): self.CanBeMaster.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def behaviorScriptData(self):  # type: ()->BehaviorScriptData
        return BehaviorScriptData(self._node.at("behaviorScriptData"))
    @property
    def m_oblivionTimerAfterSuspicious(self):  # type: ()->Float
        return Float(self._node.at("m_oblivionTimerAfterSuspicious"))
    @m_oblivionTimerAfterSuspicious.setter
    def m_oblivionTimerAfterSuspicious(self, val): self.m_oblivionTimerAfterSuspicious.set(val)
    @property
    def m_oblivionTimerBeforeSuspicious(self):  # type: ()->Float
        return Float(self._node.at("m_oblivionTimerBeforeSuspicious"))
    @m_oblivionTimerBeforeSuspicious.setter
    def m_oblivionTimerBeforeSuspicious(self, val): self.m_oblivionTimerBeforeSuspicious.set(val)
    @property
    def m_timerBeforeCertain(self):  # type: ()->Float
        return Float(self._node.at("m_timerBeforeCertain"))
    @m_timerBeforeCertain.setter
    def m_timerBeforeCertain(self, val): self.m_timerBeforeCertain.set(val)
    @property
    def m_timerBeforeSuspicious(self):  # type: ()->Float
        return Float(self._node.at("m_timerBeforeSuspicious"))
    @m_timerBeforeSuspicious.setter
    def m_timerBeforeSuspicious(self, val): self.m_timerBeforeSuspicious.set(val)
    pass


from EntityLibPy import Node
class BeamStaffModeEnum(Enum):
    Off = "Off"
    Searching = "Searching"
    Creature = "Creature"
    PossessingGPE = "PossessingGPE"
    Shapeshifting = "Shapeshifting"
    Item = "Item"
    UpgradeStaff = "UpgradeStaff"
    SideMap = "SideMap"
    PickUp = "PickUp"
    Hatching = "Hatching"
    Any = "Any"
    BeamStaffMode_COUNT = "BeamStaffMode_COUNT"


class BeamStaffMode(Primitive[BeamStaffModeEnum]):  # Enum
    def __init__(self, node):
        super().__init__(BeamStaffModeEnum, node)
    schema_name = "BeamStaffMode"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> BeamStaffMode
        return BeamStaffMode(node)
    def set(self, val):  # type: (BeamStaffModeEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)


from EntityLibPy import Node

class BeamTargetGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/BeamTargetGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->BeamTargetGD
        return BeamTargetGD(entlib.load_node_file(sourcefile, entlib.get_schema(BeamTargetGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->BeamTargetGD
        return BeamTargetGD(entlib.make_node(BeamTargetGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def CheckHotspotOrientation(self):  # type: ()->Bool
        return Bool(self._node.at("CheckHotspotOrientation"))
    @CheckHotspotOrientation.setter
    def CheckHotspotOrientation(self, val): self.CheckHotspotOrientation.set(val)
    @property
    def EventTriggered(self):  # type: ()->String
        return String(self._node.at("EventTriggered"))
    @EventTriggered.setter
    def EventTriggered(self, val): self.EventTriggered.set(val)
    @property
    def HotspotType(self):  # type: ()->HotSpotType
        return HotSpotType(self._node.at("HotspotType"))
    @HotspotType.setter
    def HotspotType(self, val): self.HotspotType.set(val)
    @property
    def IsCollectable(self):  # type: ()->Bool
        return Bool(self._node.at("IsCollectable"))
    @IsCollectable.setter
    def IsCollectable(self, val): self.IsCollectable.set(val)
    @property
    def Levitate(self):  # type: ()->Bool
        return Bool(self._node.at("Levitate"))
    @Levitate.setter
    def Levitate(self, val): self.Levitate.set(val)
    @property
    def MaxTargetableDistance(self):  # type: ()->Float
        return Float(self._node.at("MaxTargetableDistance"))
    @MaxTargetableDistance.setter
    def MaxTargetableDistance(self, val): self.MaxTargetableDistance.set(val)
    @property
    def Mode(self):  # type: ()->BeamStaffMode
        return BeamStaffMode(self._node.at("Mode"))
    @Mode.setter
    def Mode(self, val): self.Mode.set(val)
    @property
    def SpendEnergy(self):  # type: ()->Bool
        return Bool(self._node.at("SpendEnergy"))
    @SpendEnergy.setter
    def SpendEnergy(self, val): self.SpendEnergy.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node
class AttackTypeEnum(Enum):
    Short = "Short"
    Long = "Long"
    Backward = "Backward"
    Charged = "Charged"
    Distant = "Distant"
    Push = "Push"
    Unmount = "Unmount"
    Dodge = "Dodge"
    Uppercut = "Uppercut"
    Landing = "Landing"
    JumpOnto = "JumpOnto"
    Bite = "Bite"
    Stomp = "Stomp"
    AttackType_COUNT = "AttackType_COUNT"


class AttackType(Primitive[AttackTypeEnum]):  # Enum
    def __init__(self, node):
        super().__init__(AttackTypeEnum, node)
    schema_name = "AttackType"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> AttackType
        return AttackType(node)
    def set(self, val):  # type: (AttackTypeEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)


from EntityLibPy import Node

class AttackAbility(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/AttackAbility"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AttackAbility
        return AttackAbility(entlib.load_node_file(sourcefile, entlib.get_schema(AttackAbility.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AttackAbility
        return AttackAbility(entlib.make_node(AttackAbility.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Damage(self):  # type: ()->Float
        return Float(self._node.at("Damage"))
    @Damage.setter
    def Damage(self, val): self.Damage.set(val)
    @property
    def DistanceMax(self):  # type: ()->Float
        return Float(self._node.at("DistanceMax"))
    @DistanceMax.setter
    def DistanceMax(self, val): self.DistanceMax.set(val)
    @property
    def DistanceMin(self):  # type: ()->Float
        return Float(self._node.at("DistanceMin"))
    @DistanceMin.setter
    def DistanceMin(self, val): self.DistanceMin.set(val)
    @property
    def Duration(self):  # type: ()->Float
        return Float(self._node.at("Duration"))
    @Duration.setter
    def Duration(self, val): self.Duration.set(val)
    @property
    def EnergyCost(self):  # type: ()->Float
        return Float(self._node.at("EnergyCost"))
    @EnergyCost.setter
    def EnergyCost(self, val): self.EnergyCost.set(val)
    @property
    def FreezeData(self):  # type: ()->FreezeData
        return FreezeData(self._node.at("FreezeData"))
    @property
    def Impact(self):  # type: ()->Float
        return Float(self._node.at("Impact"))
    @Impact.setter
    def Impact(self, val): self.Impact.set(val)
    @property
    def ShakeData(self):  # type: ()->CameraShakeData
        return CameraShakeData(self._node.at("ShakeData"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class AttackWeaponAbility(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/AttackWeaponAbility"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AttackWeaponAbility
        return AttackWeaponAbility(entlib.load_node_file(sourcefile, entlib.get_schema(AttackWeaponAbility.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AttackWeaponAbility
        return AttackWeaponAbility(entlib.make_node(AttackWeaponAbility.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Backward(self):  # type: ()->AttackAbility
        return AttackAbility(self._node.at("Backward"))
    @property
    def Bite(self):  # type: ()->AttackAbility
        return AttackAbility(self._node.at("Bite"))
    @property
    def Charged(self):  # type: ()->AttackAbility
        return AttackAbility(self._node.at("Charged"))
    @property
    def Dash(self):  # type: ()->AttackAbility
        return AttackAbility(self._node.at("Dash"))
    @property
    def Distant(self):  # type: ()->AttackAbility
        return AttackAbility(self._node.at("Distant"))
    @property
    def Dodge(self):  # type: ()->AttackAbility
        return AttackAbility(self._node.at("Dodge"))
    @property
    def JumpOnto(self):  # type: ()->AttackAbility
        return AttackAbility(self._node.at("JumpOnto"))
    @property
    def Landing(self):  # type: ()->AttackAbility
        return AttackAbility(self._node.at("Landing"))
    @property
    def Long(self):  # type: ()->AttackAbility
        return AttackAbility(self._node.at("Long"))
    @property
    def Push(self):  # type: ()->AttackAbility
        return AttackAbility(self._node.at("Push"))
    @property
    def Short(self):  # type: ()->AttackAbility
        return AttackAbility(self._node.at("Short"))
    @property
    def Stomp(self):  # type: ()->AttackAbility
        return AttackAbility(self._node.at("Stomp"))
    @property
    def Unmount(self):  # type: ()->AttackAbility
        return AttackAbility(self._node.at("Unmount"))
    @property
    def Uppercut(self):  # type: ()->AttackAbility
        return AttackAbility(self._node.at("Uppercut"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class AttackData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/AttackData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AttackData
        return AttackData(entlib.load_node_file(sourcefile, entlib.get_schema(AttackData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AttackData
        return AttackData(entlib.make_node(AttackData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def DefaultAttackType(self):  # type: ()->AttackType
        return AttackType(self._node.at("DefaultAttackType"))
    @DefaultAttackType.setter
    def DefaultAttackType(self, val): self.DefaultAttackType.set(val)
    @property
    def Hammer(self):  # type: ()->AttackWeaponAbility
        return AttackWeaponAbility(self._node.at("Hammer"))
    @property
    def Knife(self):  # type: ()->AttackWeaponAbility
        return AttackWeaponAbility(self._node.at("Knife"))
    @property
    def None_(self):  # type: ()->AttackWeaponAbility
        return AttackWeaponAbility(self._node.at("None_"))
    @property
    def Stick(self):  # type: ()->AttackWeaponAbility
        return AttackWeaponAbility(self._node.at("Stick"))
    @property
    def Sword(self):  # type: ()->AttackWeaponAbility
        return AttackWeaponAbility(self._node.at("Sword"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node
class ArchetypeEnum(Enum):
    flying = "flying"
    swimming = "swimming"
    quadripede = "quadripede"
    bipede = "bipede"
    item = "item"
    structure = "structure"
    activator = "activator"
    Archetype_COUNT = "Archetype_COUNT"


class Archetype(Primitive[ArchetypeEnum]):  # Enum
    def __init__(self, node):
        super().__init__(ArchetypeEnum, node)
    schema_name = "Archetype"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> Archetype
        return Archetype(node)
    def set(self, val):  # type: (ArchetypeEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)


from EntityLibPy import Node

class AnimationTreeConstraintsGD_GrowData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/AnimationTreeConstraintsGD::GrowData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AnimationTreeConstraintsGD_GrowData
        return AnimationTreeConstraintsGD_GrowData(entlib.load_node_file(sourcefile, entlib.get_schema(AnimationTreeConstraintsGD_GrowData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AnimationTreeConstraintsGD_GrowData
        return AnimationTreeConstraintsGD_GrowData(entlib.make_node(AnimationTreeConstraintsGD_GrowData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def DegrowShakeForce(self):  # type: ()->Float
        return Float(self._node.at("DegrowShakeForce"))
    @DegrowShakeForce.setter
    def DegrowShakeForce(self, val): self.DegrowShakeForce.set(val)
    @property
    def GrowShakeForce(self):  # type: ()->Float
        return Float(self._node.at("GrowShakeForce"))
    @GrowShakeForce.setter
    def GrowShakeForce(self, val): self.GrowShakeForce.set(val)
    @property
    def GrowSpeed(self):  # type: ()->Float
        return Float(self._node.at("GrowSpeed"))
    @GrowSpeed.setter
    def GrowSpeed(self, val): self.GrowSpeed.set(val)
    @property
    def GrowingState(self):  # type: ()->GrowingState
        return GrowingState(self._node.at("GrowingState"))
    @GrowingState.setter
    def GrowingState(self, val): self.GrowingState.set(val)
    @property
    def ProgressSoundEventData(self):  # type: ()->ProgressSoundEventData
        return ProgressSoundEventData(self._node.at("ProgressSoundEventData"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class AnimationTreeConstraintsGD_ForceData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/AnimationTreeConstraintsGD::ForceData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AnimationTreeConstraintsGD_ForceData
        return AnimationTreeConstraintsGD_ForceData(entlib.load_node_file(sourcefile, entlib.get_schema(AnimationTreeConstraintsGD_ForceData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AnimationTreeConstraintsGD_ForceData
        return AnimationTreeConstraintsGD_ForceData(entlib.make_node(AnimationTreeConstraintsGD_ForceData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AutoSetupForceInfluence(self):  # type: ()->Bool
        return Bool(self._node.at("AutoSetupForceInfluence"))
    @AutoSetupForceInfluence.setter
    def AutoSetupForceInfluence(self, val): self.AutoSetupForceInfluence.set(val)
    @property
    def AutoSetupForceInfluenceLevelStart(self):  # type: ()->Int
        return Int(self._node.at("AutoSetupForceInfluenceLevelStart"))
    @AutoSetupForceInfluenceLevelStart.setter
    def AutoSetupForceInfluenceLevelStart(self, val): self.AutoSetupForceInfluenceLevelStart.set(val)
    @property
    def AutoSetupForceInfluenceLevelStop(self):  # type: ()->Int
        return Int(self._node.at("AutoSetupForceInfluenceLevelStop"))
    @AutoSetupForceInfluenceLevelStop.setter
    def AutoSetupForceInfluenceLevelStop(self, val): self.AutoSetupForceInfluenceLevelStop.set(val)
    @property
    def AutoSetupForceInfluenceValueAfterStop(self):  # type: ()->Float
        return Float(self._node.at("AutoSetupForceInfluenceValueAfterStop"))
    @AutoSetupForceInfluenceValueAfterStop.setter
    def AutoSetupForceInfluenceValueAfterStop(self, val): self.AutoSetupForceInfluenceValueAfterStop.set(val)
    @property
    def AutoSetupForceInfluenceValueBeforeStart(self):  # type: ()->Float
        return Float(self._node.at("AutoSetupForceInfluenceValueBeforeStart"))
    @AutoSetupForceInfluenceValueBeforeStart.setter
    def AutoSetupForceInfluenceValueBeforeStart(self, val): self.AutoSetupForceInfluenceValueBeforeStart.set(val)
    @property
    def AutoSetupForceInfluenceValueStart(self):  # type: ()->Float
        return Float(self._node.at("AutoSetupForceInfluenceValueStart"))
    @AutoSetupForceInfluenceValueStart.setter
    def AutoSetupForceInfluenceValueStart(self, val): self.AutoSetupForceInfluenceValueStart.set(val)
    @property
    def AutoSetupForceInfluenceValueStop(self):  # type: ()->Float
        return Float(self._node.at("AutoSetupForceInfluenceValueStop"))
    @AutoSetupForceInfluenceValueStop.setter
    def AutoSetupForceInfluenceValueStop(self, val): self.AutoSetupForceInfluenceValueStop.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


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


from EntityLibPy import Node

class AnimationTreeConstraintsGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/AnimationTreeConstraintsGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AnimationTreeConstraintsGD
        return AnimationTreeConstraintsGD(entlib.load_node_file(sourcefile, entlib.get_schema(AnimationTreeConstraintsGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AnimationTreeConstraintsGD
        return AnimationTreeConstraintsGD(entlib.make_node(AnimationTreeConstraintsGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def BendData(self):  # type: ()->AnimationTreeConstraintsGD_BendData
        return AnimationTreeConstraintsGD_BendData(self._node.at("BendData"))
    @property
    def ForceData(self):  # type: ()->AnimationTreeConstraintsGD_ForceData
        return AnimationTreeConstraintsGD_ForceData(self._node.at("ForceData"))
    @property
    def GrowData(self):  # type: ()->AnimationTreeConstraintsGD_GrowData
        return AnimationTreeConstraintsGD_GrowData(self._node.at("GrowData"))
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class AnimationLegsConstraints_SlopeOffsetInfo(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/AnimationLegsConstraints::SlopeOffsetInfo"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AnimationLegsConstraints_SlopeOffsetInfo
        return AnimationLegsConstraints_SlopeOffsetInfo(entlib.load_node_file(sourcefile, entlib.get_schema(AnimationLegsConstraints_SlopeOffsetInfo.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AnimationLegsConstraints_SlopeOffsetInfo
        return AnimationLegsConstraints_SlopeOffsetInfo(entlib.make_node(AnimationLegsConstraints_SlopeOffsetInfo.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def MaxSlopeAngle(self):  # type: ()->Float
        return Float(self._node.at("MaxSlopeAngle"))
    @MaxSlopeAngle.setter
    def MaxSlopeAngle(self, val): self.MaxSlopeAngle.set(val)
    @property
    def RotationOffset(self):  # type: ()->Vector3
        return Vector3(self._node.at("RotationOffset"))
    @RotationOffset.setter
    def RotationOffset(self, val): self.RotationOffset.set(val)
    @property
    def TranslationOffset(self):  # type: ()->Vector3
        return Vector3(self._node.at("TranslationOffset"))
    @TranslationOffset.setter
    def TranslationOffset(self, val): self.TranslationOffset.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class AnimationLegsConstraintsGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/AnimationLegsConstraintsGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AnimationLegsConstraintsGD
        return AnimationLegsConstraintsGD(entlib.load_node_file(sourcefile, entlib.get_schema(AnimationLegsConstraintsGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AnimationLegsConstraintsGD
        return AnimationLegsConstraintsGD(entlib.make_node(AnimationLegsConstraintsGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AllowHeightMapCastFallback(self):  # type: ()->Bool
        return Bool(self._node.at("AllowHeightMapCastFallback"))
    @AllowHeightMapCastFallback.setter
    def AllowHeightMapCastFallback(self, val): self.AllowHeightMapCastFallback.set(val)
    @property
    def AscendingSlopeOffsetInfo(self):  # type: ()->AnimationLegsConstraints_SlopeOffsetInfo
        return AnimationLegsConstraints_SlopeOffsetInfo(self._node.at("AscendingSlopeOffsetInfo"))
    @property
    def BackLegsCompensateExtensionThreshold(self):  # type: ()->Float
        return Float(self._node.at("BackLegsCompensateExtensionThreshold"))
    @BackLegsCompensateExtensionThreshold.setter
    def BackLegsCompensateExtensionThreshold(self, val): self.BackLegsCompensateExtensionThreshold.set(val)
    @property
    def BackLegsHeightRangeForIKInfluence(self):  # type: ()->Vector2
        return Vector2(self._node.at("BackLegsHeightRangeForIKInfluence"))
    @BackLegsHeightRangeForIKInfluence.setter
    def BackLegsHeightRangeForIKInfluence(self, val): self.BackLegsHeightRangeForIKInfluence.set(val)
    @property
    def BoneBending(self):  # type: ()->Bool
        return Bool(self._node.at("BoneBending"))
    @BoneBending.setter
    def BoneBending(self, val): self.BoneBending.set(val)
    @property
    def BoneBendingAnticipation(self):  # type: ()->Float
        return Float(self._node.at("BoneBendingAnticipation"))
    @BoneBendingAnticipation.setter
    def BoneBendingAnticipation(self, val): self.BoneBendingAnticipation.set(val)
    @property
    def BoneBendingAnticipationBackward(self):  # type: ()->Float
        return Float(self._node.at("BoneBendingAnticipationBackward"))
    @BoneBendingAnticipationBackward.setter
    def BoneBendingAnticipationBackward(self, val): self.BoneBendingAnticipationBackward.set(val)
    @property
    def BoneBendingLocomotionInfluenceSpeed(self):  # type: ()->Float
        return Float(self._node.at("BoneBendingLocomotionInfluenceSpeed"))
    @BoneBendingLocomotionInfluenceSpeed.setter
    def BoneBendingLocomotionInfluenceSpeed(self, val): self.BoneBendingLocomotionInfluenceSpeed.set(val)
    @property
    def CastDeltaDistToTriggerSmooth(self):  # type: ()->Float
        return Float(self._node.at("CastDeltaDistToTriggerSmooth"))
    @CastDeltaDistToTriggerSmooth.setter
    def CastDeltaDistToTriggerSmooth(self, val): self.CastDeltaDistToTriggerSmooth.set(val)
    @property
    def DescendingSlopeOffsetInfo(self):  # type: ()->AnimationLegsConstraints_SlopeOffsetInfo
        return AnimationLegsConstraints_SlopeOffsetInfo(self._node.at("DescendingSlopeOffsetInfo"))
    @property
    def FeetInfluence(self):  # type: ()->Float
        return Float(self._node.at("FeetInfluence"))
    @FeetInfluence.setter
    def FeetInfluence(self, val): self.FeetInfluence.set(val)
    @property
    def FrontLegsCompensateExtensionThreshold(self):  # type: ()->Float
        return Float(self._node.at("FrontLegsCompensateExtensionThreshold"))
    @FrontLegsCompensateExtensionThreshold.setter
    def FrontLegsCompensateExtensionThreshold(self, val): self.FrontLegsCompensateExtensionThreshold.set(val)
    @property
    def FrontLegsHeightRangeForIKInfluence(self):  # type: ()->Vector2
        return Vector2(self._node.at("FrontLegsHeightRangeForIKInfluence"))
    @FrontLegsHeightRangeForIKInfluence.setter
    def FrontLegsHeightRangeForIKInfluence(self, val): self.FrontLegsHeightRangeForIKInfluence.set(val)
    @property
    def GlobalInfluence(self):  # type: ()->Float
        return Float(self._node.at("GlobalInfluence"))
    @GlobalInfluence.setter
    def GlobalInfluence(self, val): self.GlobalInfluence.set(val)
    @property
    def LegInfluence(self):  # type: ()->Float
        return Float(self._node.at("LegInfluence"))
    @LegInfluence.setter
    def LegInfluence(self, val): self.LegInfluence.set(val)
    @property
    def LegLock(self):  # type: ()->Bool
        return Bool(self._node.at("LegLock"))
    @LegLock.setter
    def LegLock(self, val): self.LegLock.set(val)
    @property
    def MaxHeightForFootInfluence(self):  # type: ()->Float
        return Float(self._node.at("MaxHeightForFootInfluence"))
    @MaxHeightForFootInfluence.setter
    def MaxHeightForFootInfluence(self, val): self.MaxHeightForFootInfluence.set(val)
    @property
    def ObstructionCastHitPosMarginOffsetFactor(self):  # type: ()->Float
        return Float(self._node.at("ObstructionCastHitPosMarginOffsetFactor"))
    @ObstructionCastHitPosMarginOffsetFactor.setter
    def ObstructionCastHitPosMarginOffsetFactor(self, val): self.ObstructionCastHitPosMarginOffsetFactor.set(val)
    @property
    def ObstructionCastOffsetFactor(self):  # type: ()->Float
        return Float(self._node.at("ObstructionCastOffsetFactor"))
    @ObstructionCastOffsetFactor.setter
    def ObstructionCastOffsetFactor(self, val): self.ObstructionCastOffsetFactor.set(val)
    @property
    def ObstructionCastSafeRadiusFactor(self):  # type: ()->Float
        return Float(self._node.at("ObstructionCastSafeRadiusFactor"))
    @ObstructionCastSafeRadiusFactor.setter
    def ObstructionCastSafeRadiusFactor(self, val): self.ObstructionCastSafeRadiusFactor.set(val)
    @property
    def SpeedFactorFromLockedRootDistance(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("SpeedFactorFromLockedRootDistance"))
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def UseObstructionCast(self):  # type: ()->Bool
        return Bool(self._node.at("UseObstructionCast"))
    @UseObstructionCast.setter
    def UseObstructionCast(self, val): self.UseObstructionCast.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class AnimationEventsGeneratorGD_TrackedBone(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/AnimationEventsGeneratorGD::TrackedBone"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AnimationEventsGeneratorGD_TrackedBone
        return AnimationEventsGeneratorGD_TrackedBone(entlib.load_node_file(sourcefile, entlib.get_schema(AnimationEventsGeneratorGD_TrackedBone.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AnimationEventsGeneratorGD_TrackedBone
        return AnimationEventsGeneratorGD_TrackedBone(entlib.make_node(AnimationEventsGeneratorGD_TrackedBone.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Name(self):  # type: ()->String
        return String(self._node.at("Name"))
    @Name.setter
    def Name(self, val): self.Name.set(val)
    @property
    def OffsetFrameCountStart(self):  # type: ()->Int
        return Int(self._node.at("OffsetFrameCountStart"))
    @OffsetFrameCountStart.setter
    def OffsetFrameCountStart(self, val): self.OffsetFrameCountStart.set(val)
    @property
    def OffsetFrameCountStop(self):  # type: ()->Int
        return Int(self._node.at("OffsetFrameCountStop"))
    @OffsetFrameCountStop.setter
    def OffsetFrameCountStop(self, val): self.OffsetFrameCountStop.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class AnimationEventsGeneratorGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/AnimationEventsGeneratorGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AnimationEventsGeneratorGD
        return AnimationEventsGeneratorGD(entlib.load_node_file(sourcefile, entlib.get_schema(AnimationEventsGeneratorGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AnimationEventsGeneratorGD
        return AnimationEventsGeneratorGD(entlib.make_node(AnimationEventsGeneratorGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def TrackedBones(self):  # type: ()->Array[AnimationEventsGeneratorGD_TrackedBone]
        return (lambda n: Array(AnimationEventsGeneratorGD_TrackedBone, n))(self._node.at("TrackedBones"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node
class AnimTagTimelineTransitionEnum(Enum):
    beginning = "beginning"
    copy = "copy"
    reverse = "reverse"
    AnimTagTimelineTransition_COUNT = "AnimTagTimelineTransition_COUNT"


class AnimTagTimelineTransition(Primitive[AnimTagTimelineTransitionEnum]):  # Enum
    def __init__(self, node):
        super().__init__(AnimTagTimelineTransitionEnum, node)
    schema_name = "AnimTagTimelineTransition"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> AnimTagTimelineTransition
        return AnimTagTimelineTransition(node)
    def set(self, val):  # type: (AnimTagTimelineTransitionEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)


from EntityLibPy import Node
class AnimTagEnum(Enum):
    none = "none"
    apex = "apex"
    forward = "forward"
    forwardright = "forwardright"
    right = "right"
    backwardright = "backwardright"
    backward = "backward"
    backwardleft = "backwardleft"
    left = "left"
    forwardleft = "forwardleft"
    regular = "regular"
    alignedregular = "alignedregular"
    goofy = "goofy"
    alignedgoofy = "alignedgoofy"
    top = "top"
    bottom = "bottom"
    up = "up"
    upforward = "upforward"
    upward = "upward"
    down = "down"
    downforward = "downforward"
    downward = "downward"
    in_ = "in"
    out = "out"
    horizontal = "horizontal"
    vertical = "vertical"
    count = "count"


class AnimTag(Primitive[AnimTagEnum]):  # Enum
    def __init__(self, node):
        super().__init__(AnimTagEnum, node)
    schema_name = "AnimTag"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> AnimTag
        return AnimTag(node)
    def set(self, val):  # type: (AnimTagEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)


from EntityLibPy import Node

class MoveCapacityData_AnimTagTimelineTransitionItem(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/MoveCapacityData::AnimTagTimelineTransitionItem"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->MoveCapacityData_AnimTagTimelineTransitionItem
        return MoveCapacityData_AnimTagTimelineTransitionItem(entlib.load_node_file(sourcefile, entlib.get_schema(MoveCapacityData_AnimTagTimelineTransitionItem.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->MoveCapacityData_AnimTagTimelineTransitionItem
        return MoveCapacityData_AnimTagTimelineTransitionItem(entlib.make_node(MoveCapacityData_AnimTagTimelineTransitionItem.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def to(self):  # type: ()->AnimTag
        return AnimTag(self._node.at("to"))
    @to.setter
    def to(self, val): self.to.set(val)
    @property
    def type(self):  # type: ()->AnimTagTimelineTransition
        return AnimTagTimelineTransition(self._node.at("type"))
    @type.setter
    def type(self, val): self.type.set(val)
    pass


from EntityLibPy import Node

class MoveCapacityData_AnimTagTimelineTransitionTable(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/MoveCapacityData::AnimTagTimelineTransitionTable"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->MoveCapacityData_AnimTagTimelineTransitionTable
        return MoveCapacityData_AnimTagTimelineTransitionTable(entlib.load_node_file(sourcefile, entlib.get_schema(MoveCapacityData_AnimTagTimelineTransitionTable.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->MoveCapacityData_AnimTagTimelineTransitionTable
        return MoveCapacityData_AnimTagTimelineTransitionTable(entlib.make_node(MoveCapacityData_AnimTagTimelineTransitionTable.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def from_(self):  # type: ()->AnimTag
        return AnimTag(self._node.at("from_"))
    @from_.setter
    def from_(self, val): self.from_.set(val)
    @property
    def transitions(self):  # type: ()->Array[MoveCapacityData_AnimTagTimelineTransitionItem]
        return (lambda n: Array(MoveCapacityData_AnimTagTimelineTransitionItem, n))(self._node.at("transitions"))
    pass


from EntityLibPy import Node

class MoveCapacityData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/MoveCapacityData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->MoveCapacityData
        return MoveCapacityData(entlib.load_node_file(sourcefile, entlib.get_schema(MoveCapacityData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->MoveCapacityData
        return MoveCapacityData(entlib.make_node(MoveCapacityData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def airControlFactor(self):  # type: ()->Float
        return Float(self._node.at("airControlFactor"))
    @airControlFactor.setter
    def airControlFactor(self, val): self.airControlFactor.set(val)
    @property
    def allowClampSpeedBiggerThanLocomotionDuringBlend(self):  # type: ()->Bool
        return Bool(self._node.at("allowClampSpeedBiggerThanLocomotionDuringBlend"))
    @allowClampSpeedBiggerThanLocomotionDuringBlend.setter
    def allowClampSpeedBiggerThanLocomotionDuringBlend(self, val): self.allowClampSpeedBiggerThanLocomotionDuringBlend.set(val)
    @property
    def allowKeepAnimationPlayRatioUnclamped(self):  # type: ()->Bool
        return Bool(self._node.at("allowKeepAnimationPlayRatioUnclamped"))
    @allowKeepAnimationPlayRatioUnclamped.setter
    def allowKeepAnimationPlayRatioUnclamped(self, val): self.allowKeepAnimationPlayRatioUnclamped.set(val)
    @property
    def angularSpeedMaxFlyDumpFactor(self):  # type: ()->Float
        return Float(self._node.at("angularSpeedMaxFlyDumpFactor"))
    @angularSpeedMaxFlyDumpFactor.setter
    def angularSpeedMaxFlyDumpFactor(self, val): self.angularSpeedMaxFlyDumpFactor.set(val)
    @property
    def angularSpeedMaxGroundDumpFactor(self):  # type: ()->Float
        return Float(self._node.at("angularSpeedMaxGroundDumpFactor"))
    @angularSpeedMaxGroundDumpFactor.setter
    def angularSpeedMaxGroundDumpFactor(self, val): self.angularSpeedMaxGroundDumpFactor.set(val)
    @property
    def angularSpeedMaxRiderDumpFactor(self):  # type: ()->Float
        return Float(self._node.at("angularSpeedMaxRiderDumpFactor"))
    @angularSpeedMaxRiderDumpFactor.setter
    def angularSpeedMaxRiderDumpFactor(self, val): self.angularSpeedMaxRiderDumpFactor.set(val)
    @property
    def angularSpeedMaxWaterDumpFactor(self):  # type: ()->Float
        return Float(self._node.at("angularSpeedMaxWaterDumpFactor"))
    @angularSpeedMaxWaterDumpFactor.setter
    def angularSpeedMaxWaterDumpFactor(self, val): self.angularSpeedMaxWaterDumpFactor.set(val)
    @property
    def animTagTimelineTransitionTable(self):  # type: ()->MoveCapacityData_AnimTagTimelineTransitionTable
        return MoveCapacityData_AnimTagTimelineTransitionTable(self._node.at("animTagTimelineTransitionTable"))
    @property
    def brakeDeceleration(self):  # type: ()->Float
        return Float(self._node.at("brakeDeceleration"))
    @brakeDeceleration.setter
    def brakeDeceleration(self, val): self.brakeDeceleration.set(val)
    @property
    def capsuleBigRadius(self):  # type: ()->Float
        return Float(self._node.at("capsuleBigRadius"))
    @capsuleBigRadius.setter
    def capsuleBigRadius(self, val): self.capsuleBigRadius.set(val)
    @property
    def capsuleEnormousRadius(self):  # type: ()->Float
        return Float(self._node.at("capsuleEnormousRadius"))
    @capsuleEnormousRadius.setter
    def capsuleEnormousRadius(self, val): self.capsuleEnormousRadius.set(val)
    @property
    def capsuleMediumRadius(self):  # type: ()->Float
        return Float(self._node.at("capsuleMediumRadius"))
    @capsuleMediumRadius.setter
    def capsuleMediumRadius(self, val): self.capsuleMediumRadius.set(val)
    @property
    def capsuleSmallRadius(self):  # type: ()->Float
        return Float(self._node.at("capsuleSmallRadius"))
    @capsuleSmallRadius.setter
    def capsuleSmallRadius(self, val): self.capsuleSmallRadius.set(val)
    @property
    def capsuleTinyRadius(self):  # type: ()->Float
        return Float(self._node.at("capsuleTinyRadius"))
    @capsuleTinyRadius.setter
    def capsuleTinyRadius(self, val): self.capsuleTinyRadius.set(val)
    @property
    def constraintDetectionAnticipation(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("constraintDetectionAnticipation"))
    @property
    def constraintDetectionOffset(self):  # type: ()->Vector3
        return Vector3(self._node.at("constraintDetectionOffset"))
    @constraintDetectionOffset.setter
    def constraintDetectionOffset(self, val): self.constraintDetectionOffset.set(val)
    @property
    def constraintDetectionRadius(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("constraintDetectionRadius"))
    @property
    def coyoteJumpMaxTime(self):  # type: ()->Float
        return Float(self._node.at("coyoteJumpMaxTime"))
    @coyoteJumpMaxTime.setter
    def coyoteJumpMaxTime(self, val): self.coyoteJumpMaxTime.set(val)
    @property
    def crashPreventionSafeguardFactor(self):  # type: ()->Float
        return Float(self._node.at("crashPreventionSafeguardFactor"))
    @crashPreventionSafeguardFactor.setter
    def crashPreventionSafeguardFactor(self, val): self.crashPreventionSafeguardFactor.set(val)
    @property
    def doubleJump(self):  # type: ()->Bool
        return Bool(self._node.at("doubleJump"))
    @doubleJump.setter
    def doubleJump(self, val): self.doubleJump.set(val)
    @property
    def dropPlaneLegLenFactor(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("dropPlaneLegLenFactor"))
    @property
    def dropSyncTrajectoryAndVisual(self):  # type: ()->Bool
        return Bool(self._node.at("dropSyncTrajectoryAndVisual"))
    @dropSyncTrajectoryAndVisual.setter
    def dropSyncTrajectoryAndVisual(self, val): self.dropSyncTrajectoryAndVisual.set(val)
    @property
    def ellipseCoeff(self):  # type: ()->Float
        return Float(self._node.at("ellipseCoeff"))
    @ellipseCoeff.setter
    def ellipseCoeff(self, val): self.ellipseCoeff.set(val)
    @property
    def extirpateObstacleAcceleration(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("extirpateObstacleAcceleration"))
    @property
    def extirpateObstacleDuration(self):  # type: ()->Float
        return Float(self._node.at("extirpateObstacleDuration"))
    @extirpateObstacleDuration.setter
    def extirpateObstacleDuration(self, val): self.extirpateObstacleDuration.set(val)
    @property
    def flyCentrifugalCoeff(self):  # type: ()->ScaleConverter
        return ScaleConverter(self._node.at("flyCentrifugalCoeff"))
    @property
    def flyCentrifugalRate(self):  # type: ()->Float
        return Float(self._node.at("flyCentrifugalRate"))
    @flyCentrifugalRate.setter
    def flyCentrifugalRate(self, val): self.flyCentrifugalRate.set(val)
    @property
    def jumpAnalogScale(self):  # type: ()->Float
        return Float(self._node.at("jumpAnalogScale"))
    @jumpAnalogScale.setter
    def jumpAnalogScale(self, val): self.jumpAnalogScale.set(val)
    @property
    def jumpOntoPosition(self):  # type: ()->Bool
        return Bool(self._node.at("jumpOntoPosition"))
    @jumpOntoPosition.setter
    def jumpOntoPosition(self, val): self.jumpOntoPosition.set(val)
    @property
    def ledgeApproachSpeedMaxZ(self):  # type: ()->Float
        return Float(self._node.at("ledgeApproachSpeedMaxZ"))
    @ledgeApproachSpeedMaxZ.setter
    def ledgeApproachSpeedMaxZ(self, val): self.ledgeApproachSpeedMaxZ.set(val)
    @property
    def ledgeDepthRadiusCoeff(self):  # type: ()->Float
        return Float(self._node.at("ledgeDepthRadiusCoeff"))
    @ledgeDepthRadiusCoeff.setter
    def ledgeDepthRadiusCoeff(self, val): self.ledgeDepthRadiusCoeff.set(val)
    @property
    def ledgeMaxDistance(self):  # type: ()->Float
        return Float(self._node.at("ledgeMaxDistance"))
    @ledgeMaxDistance.setter
    def ledgeMaxDistance(self, val): self.ledgeMaxDistance.set(val)
    @property
    def ledgeMaxHeightEpsilon(self):  # type: ()->Float
        return Float(self._node.at("ledgeMaxHeightEpsilon"))
    @ledgeMaxHeightEpsilon.setter
    def ledgeMaxHeightEpsilon(self, val): self.ledgeMaxHeightEpsilon.set(val)
    @property
    def ledgeMinDepthEpsilon(self):  # type: ()->Float
        return Float(self._node.at("ledgeMinDepthEpsilon"))
    @ledgeMinDepthEpsilon.setter
    def ledgeMinDepthEpsilon(self, val): self.ledgeMinDepthEpsilon.set(val)
    @property
    def ledgeMinWidthEpsilon(self):  # type: ()->Float
        return Float(self._node.at("ledgeMinWidthEpsilon"))
    @ledgeMinWidthEpsilon.setter
    def ledgeMinWidthEpsilon(self, val): self.ledgeMinWidthEpsilon.set(val)
    @property
    def legLength(self):  # type: ()->Float
        return Float(self._node.at("legLength"))
    @legLength.setter
    def legLength(self, val): self.legLength.set(val)
    @property
    def mass(self):  # type: ()->Float
        return Float(self._node.at("mass"))
    @mass.setter
    def mass(self, val): self.mass.set(val)
    @property
    def maxAverageSpeedDuringJumpOnto(self):  # type: ()->Float
        return Float(self._node.at("maxAverageSpeedDuringJumpOnto"))
    @maxAverageSpeedDuringJumpOnto.setter
    def maxAverageSpeedDuringJumpOnto(self, val): self.maxAverageSpeedDuringJumpOnto.set(val)
    @property
    def maxFlapTime(self):  # type: ()->Float
        return Float(self._node.at("maxFlapTime"))
    @maxFlapTime.setter
    def maxFlapTime(self, val): self.maxFlapTime.set(val)
    @property
    def maxTimeBetweenFlaps(self):  # type: ()->Float
        return Float(self._node.at("maxTimeBetweenFlaps"))
    @maxTimeBetweenFlaps.setter
    def maxTimeBetweenFlaps(self, val): self.maxTimeBetweenFlaps.set(val)
    @property
    def minFlapTime(self):  # type: ()->Float
        return Float(self._node.at("minFlapTime"))
    @minFlapTime.setter
    def minFlapTime(self, val): self.minFlapTime.set(val)
    @property
    def minSpeedToSteerPitch(self):  # type: ()->Float
        return Float(self._node.at("minSpeedToSteerPitch"))
    @minSpeedToSteerPitch.setter
    def minSpeedToSteerPitch(self, val): self.minSpeedToSteerPitch.set(val)
    @property
    def minTimeBetweenFlaps(self):  # type: ()->Float
        return Float(self._node.at("minTimeBetweenFlaps"))
    @minTimeBetweenFlaps.setter
    def minTimeBetweenFlaps(self, val): self.minTimeBetweenFlaps.set(val)
    @property
    def orientationSpeedFly(self):  # type: ()->MoveCapacityData_OrientationSpeed
        return MoveCapacityData_OrientationSpeed(self._node.at("orientationSpeedFly"))
    @property
    def orientationSpeedGround(self):  # type: ()->MoveCapacityData_OrientationSpeed
        return MoveCapacityData_OrientationSpeed(self._node.at("orientationSpeedGround"))
    @property
    def orientationSpeedWater(self):  # type: ()->MoveCapacityData_OrientationSpeed
        return MoveCapacityData_OrientationSpeed(self._node.at("orientationSpeedWater"))
    @property
    def patinateSpeedMinEnter(self):  # type: ()->Float
        return Float(self._node.at("patinateSpeedMinEnter"))
    @patinateSpeedMinEnter.setter
    def patinateSpeedMinEnter(self, val): self.patinateSpeedMinEnter.set(val)
    @property
    def patinateSpeedMinExit(self):  # type: ()->Float
        return Float(self._node.at("patinateSpeedMinExit"))
    @patinateSpeedMinExit.setter
    def patinateSpeedMinExit(self, val): self.patinateSpeedMinExit.set(val)
    @property
    def reachSpeedAcceleration(self):  # type: ()->Float
        return Float(self._node.at("reachSpeedAcceleration"))
    @reachSpeedAcceleration.setter
    def reachSpeedAcceleration(self, val): self.reachSpeedAcceleration.set(val)
    @property
    def reachSpeedByLocomotion(self):  # type: ()->Array[MoveCapacityData_ReachSpeed]
        return (lambda n: Array(MoveCapacityData_ReachSpeed, n))(self._node.at("reachSpeedByLocomotion"))
    @property
    def reachSpeedDeceleration(self):  # type: ()->Float
        return Float(self._node.at("reachSpeedDeceleration"))
    @reachSpeedDeceleration.setter
    def reachSpeedDeceleration(self, val): self.reachSpeedDeceleration.set(val)
    @property
    def reactToOtherCharacterBodyCollision(self):  # type: ()->Bool
        return Bool(self._node.at("reactToOtherCharacterBodyCollision"))
    @reactToOtherCharacterBodyCollision.setter
    def reactToOtherCharacterBodyCollision(self, val): self.reactToOtherCharacterBodyCollision.set(val)
    @property
    def sphereCastRadiusRatio(self):  # type: ()->Float
        return Float(self._node.at("sphereCastRadiusRatio"))
    @sphereCastRadiusRatio.setter
    def sphereCastRadiusRatio(self, val): self.sphereCastRadiusRatio.set(val)
    @property
    def sphereOverrideRadius(self):  # type: ()->Float
        return Float(self._node.at("sphereOverrideRadius"))
    @sphereOverrideRadius.setter
    def sphereOverrideRadius(self, val): self.sphereOverrideRadius.set(val)
    @property
    def strafeBlendIn(self):  # type: ()->Float
        return Float(self._node.at("strafeBlendIn"))
    @strafeBlendIn.setter
    def strafeBlendIn(self, val): self.strafeBlendIn.set(val)
    @property
    def strafeBlendWeightMinToChangeAnim(self):  # type: ()->Float
        return Float(self._node.at("strafeBlendWeightMinToChangeAnim"))
    @strafeBlendWeightMinToChangeAnim.setter
    def strafeBlendWeightMinToChangeAnim(self, val): self.strafeBlendWeightMinToChangeAnim.set(val)
    @property
    def strafeOrientationRateFactor(self):  # type: ()->Float
        return Float(self._node.at("strafeOrientationRateFactor"))
    @strafeOrientationRateFactor.setter
    def strafeOrientationRateFactor(self, val): self.strafeOrientationRateFactor.set(val)
    @property
    def strafeSpeedModeMax(self):  # type: ()->SpeedMode
        return SpeedMode(self._node.at("strafeSpeedModeMax"))
    @strafeSpeedModeMax.setter
    def strafeSpeedModeMax(self, val): self.strafeSpeedModeMax.set(val)
    @property
    def strafeStopOrientationRateFactor(self):  # type: ()->Float
        return Float(self._node.at("strafeStopOrientationRateFactor"))
    @strafeStopOrientationRateFactor.setter
    def strafeStopOrientationRateFactor(self, val): self.strafeStopOrientationRateFactor.set(val)
    @property
    def strafeTurnAngleMin(self):  # type: ()->Float
        return Float(self._node.at("strafeTurnAngleMin"))
    @strafeTurnAngleMin.setter
    def strafeTurnAngleMin(self, val): self.strafeTurnAngleMin.set(val)
    @property
    def trajectoryRateFactorDuringLateralLand(self):  # type: ()->Float
        return Float(self._node.at("trajectoryRateFactorDuringLateralLand"))
    @trajectoryRateFactorDuringLateralLand.setter
    def trajectoryRateFactorDuringLateralLand(self, val): self.trajectoryRateFactorDuringLateralLand.set(val)
    @property
    def turnAroundInputDirectionAngleDeltaMin(self):  # type: ()->Float
        return Float(self._node.at("turnAroundInputDirectionAngleDeltaMin"))
    @turnAroundInputDirectionAngleDeltaMin.setter
    def turnAroundInputDirectionAngleDeltaMin(self, val): self.turnAroundInputDirectionAngleDeltaMin.set(val)
    pass


from EntityLibPy import Node

class CharacterControllerGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/CharacterControllerGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CharacterControllerGD
        return CharacterControllerGD(entlib.load_node_file(sourcefile, entlib.get_schema(CharacterControllerGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CharacterControllerGD
        return CharacterControllerGD(entlib.make_node(CharacterControllerGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def AllowHeightMapFallback(self):  # type: ()->Bool
        return Bool(self._node.at("AllowHeightMapFallback"))
    @AllowHeightMapFallback.setter
    def AllowHeightMapFallback(self, val): self.AllowHeightMapFallback.set(val)
    @property
    def ClamberData(self):  # type: ()->CharacterControllerClamberData
        return CharacterControllerClamberData(self._node.at("ClamberData"))
    @property
    def FallData(self):  # type: ()->CharacterControllerFallData
        return CharacterControllerFallData(self._node.at("FallData"))
    @property
    def GroundNormalData(self):  # type: ()->CharacterControllerGroundNormalData
        return CharacterControllerGroundNormalData(self._node.at("GroundNormalData"))
    @property
    def HeadCollisionData(self):  # type: ()->HeadCollisionBehaviorData
        return HeadCollisionBehaviorData(self._node.at("HeadCollisionData"))
    @property
    def ImmersedData(self):  # type: ()->ImmersedBehaviorData
        return ImmersedBehaviorData(self._node.at("ImmersedData"))
    @property
    def InputCollisionData(self):  # type: ()->InputCollisionBehaviorData
        return InputCollisionBehaviorData(self._node.at("InputCollisionData"))
    @property
    def MeshNavigationData(self):  # type: ()->MeshNavigationBehaviorData
        return MeshNavigationBehaviorData(self._node.at("MeshNavigationData"))
    @property
    def PredictionData(self):  # type: ()->PredictionBehaviorData
        return PredictionBehaviorData(self._node.at("PredictionData"))
    @property
    def RotationSmooth(self):  # type: ()->Vector3
        return Vector3(self._node.at("RotationSmooth"))
    @RotationSmooth.setter
    def RotationSmooth(self, val): self.RotationSmooth.set(val)
    @property
    def SlideData(self):  # type: ()->CharacterControllerSlideData
        return CharacterControllerSlideData(self._node.at("SlideData"))
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def moveCapacityData(self):  # type: ()->MoveCapacityData
        return MoveCapacityData(self._node.at("moveCapacityData"))
    pass


from EntityLibPy import Node

class AnimMirroringSpecData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/AnimMirroringSpecData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AnimMirroringSpecData
        return AnimMirroringSpecData(entlib.load_node_file(sourcefile, entlib.get_schema(AnimMirroringSpecData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AnimMirroringSpecData
        return AnimMirroringSpecData(entlib.make_node(AnimMirroringSpecData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def name(self):  # type: ()->String
        return String(self._node.at("name"))
    @name.setter
    def name(self, val): self.name.set(val)
    @property
    def name2(self):  # type: ()->String
        return String(self._node.at("name2"))
    @name2.setter
    def name2(self, val): self.name2.set(val)
    @property
    def spec(self):  # type: ()->String
        return String(self._node.at("spec"))
    @spec.setter
    def spec(self, val): self.spec.set(val)
    pass


from EntityLibPy import Node

class AnimMirroringData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/AnimMirroringData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AnimMirroringData
        return AnimMirroringData(entlib.load_node_file(sourcefile, entlib.get_schema(AnimMirroringData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AnimMirroringData
        return AnimMirroringData(entlib.make_node(AnimMirroringData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def specs(self):  # type: ()->Array[AnimMirroringSpecData]
        return (lambda n: Array(AnimMirroringSpecData, n))(self._node.at("specs"))
    pass


from EntityLibPy import Node

class AnimationControllerGD(HelperObject):
    schema_name = "./MergedComponents.json#/definitions/AnimationControllerGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AnimationControllerGD
        return AnimationControllerGD(entlib.load_node_file(sourcefile, entlib.get_schema(AnimationControllerGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AnimationControllerGD
        return AnimationControllerGD(entlib.make_node(AnimationControllerGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def EDITOR_skeleton(self):  # type: ()->String
        return String(self._node.at("EDITOR_skeleton"))
    @EDITOR_skeleton.setter
    def EDITOR_skeleton(self, val): self.EDITOR_skeleton.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def animDatabase(self):  # type: ()->String
        return String(self._node.at("animDatabase"))
    @animDatabase.setter
    def animDatabase(self, val): self.animDatabase.set(val)
    @property
    def mirroringData(self):  # type: ()->AnimMirroringData
        return AnimMirroringData(self._node.at("mirroringData"))
    @property
    def romLookAtInfluence(self):  # type: ()->Float
        return Float(self._node.at("romLookAtInfluence"))
    @romLookAtInfluence.setter
    def romLookAtInfluence(self, val): self.romLookAtInfluence.set(val)
    @property
    def skeleton(self):  # type: ()->String
        return String(self._node.at("skeleton"))
    @skeleton.setter
    def skeleton(self, val): self.skeleton.set(val)
    @property
    def syncDataName(self):  # type: ()->String
        return String(self._node.at("syncDataName"))
    @syncDataName.setter
    def syncDataName(self, val): self.syncDataName.set(val)
    pass


from EntityLibPy import Node
ActorStates = (lambda n: UnionSet(ResponsiblePointer_ActorState_, n))
from EntityLibPy import Node

class Object(HelperObject):
    schema_name = "./Scene-schema.json#/definitions/Object"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->Object
        return Object(entlib.load_node_file(sourcefile, entlib.get_schema(Object.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->Object
        return Object(entlib.make_node(Object.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def ActorStates(self):  # type: ()->ActorStates
        return ActorStates(self._node.at("ActorStates"))
    @property
    def Color(self):  # type: ()->Color
        return Color(self._node.at("Color"))
    @Color.setter
    def Color(self, val): self.Color.set(val)
    @property
    def Components(self):  # type: ()->Object_Components
        return Object_Components(self._node.at("Components"))
    @property
    def InstanceOf(self):  # type: ()->String
        return String(self._node.at("InstanceOf"))
    @InstanceOf.setter
    def InstanceOf(self, val): self.InstanceOf.set(val)
    @property
    def MaxActivationLevel(self):  # type: ()->Object_MaxActivationLevel
        return Object_MaxActivationLevel(self._node.at("MaxActivationLevel"))
    @MaxActivationLevel.setter
    def MaxActivationLevel(self, val): self.MaxActivationLevel.set(val)
    @property
    def Name(self):  # type: ()->String
        return String(self._node.at("Name"))
    @Name.setter
    def Name(self, val): self.Name.set(val)
    @property
    def Thumbnail(self):  # type: ()->String
        return String(self._node.at("Thumbnail"))
    @Thumbnail.setter
    def Thumbnail(self, val): self.Thumbnail.set(val)
    @property
    def __removed__(self):  # type: ()->Bool
        return Bool(self._node.at("__removed__"))
    @__removed__.setter
    def __removed__(self, val): self.__removed__.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class UnitTestComponent(HelperObject):
    schema_name = "./EditionComponents.json#/definitions/UnitTestComponent"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->UnitTestComponent
        return UnitTestComponent(entlib.load_node_file(sourcefile, entlib.get_schema(UnitTestComponent.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->UnitTestComponent
        return UnitTestComponent(entlib.make_node(UnitTestComponent.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Entity(self):  # type: ()->Object
        return Object(self._node.at("Entity"))
    @property
    def EnumSet(self):  # type: ()->PrimitiveSet[ReviveSideEnum]
        return (lambda n: PrimitiveSet(ReviveSideEnum, n))(self._node.at("EnumSet"))
    @property
    def Position(self):  # type: ()->Position
        return Position(self._node.at("Position"))
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class Entity(HelperObject):
    schema_name = "./Scene-schema.json#/definitions/Entity"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->Entity
        return Entity(entlib.load_node_file(sourcefile, entlib.get_schema(Entity.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->Entity
        return Entity(entlib.make_node(Entity.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def ActorStates(self):  # type: ()->ActorStates
        return ActorStates(self._node.at("ActorStates"))
    @property
    def Color(self):  # type: ()->Color
        return Color(self._node.at("Color"))
    @Color.setter
    def Color(self, val): self.Color.set(val)
    @property
    def Components(self):  # type: ()->Components
        return Components(self._node.at("Components"))
    @property
    def InstanceOf(self):  # type: ()->String
        return String(self._node.at("InstanceOf"))
    @InstanceOf.setter
    def InstanceOf(self, val): self.InstanceOf.set(val)
    @property
    def MaxActivationLevel(self):  # type: ()->MaxActivationLevel
        return MaxActivationLevel(self._node.at("MaxActivationLevel"))
    @MaxActivationLevel.setter
    def MaxActivationLevel(self, val): self.MaxActivationLevel.set(val)
    @property
    def Name(self):  # type: ()->String
        return String(self._node.at("Name"))
    @Name.setter
    def Name(self, val): self.Name.set(val)
    @property
    def Thumbnail(self):  # type: ()->String
        return String(self._node.at("Thumbnail"))
    @Thumbnail.setter
    def Thumbnail(self, val): self.Thumbnail.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class ActorStateTeleport_Inputs(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ActorStateTeleport::Inputs"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActorStateTeleport_Inputs
        return ActorStateTeleport_Inputs(entlib.load_node_file(sourcefile, entlib.get_schema(ActorStateTeleport_Inputs.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActorStateTeleport_Inputs
        return ActorStateTeleport_Inputs(entlib.make_node(ActorStateTeleport_Inputs.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Orientation(self):  # type: ()->Orientation
        return Orientation(self._node.at("Orientation"))
    @property
    def Position(self):  # type: ()->Position
        return Position(self._node.at("Position"))
    @property
    def ResetCamera(self):  # type: ()->Bool
        return Bool(self._node.at("ResetCamera"))
    @ResetCamera.setter
    def ResetCamera(self, val): self.ResetCamera.set(val)
    @property
    def TouchGround(self):  # type: ()->Bool
        return Bool(self._node.at("TouchGround"))
    @TouchGround.setter
    def TouchGround(self, val): self.TouchGround.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class ActorState(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ActorState"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActorState
        return ActorState(entlib.load_node_file(sourcefile, entlib.get_schema(ActorState.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActorState
        return ActorState(entlib.make_node(ActorState.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    pass


from EntityLibPy import Node

class EntityStateVoxelsVolume(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/EntityStateVoxelsVolume"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStateVoxelsVolume
        return EntityStateVoxelsVolume(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateVoxelsVolume.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStateVoxelsVolume
        return EntityStateVoxelsVolume(entlib.make_node(EntityStateVoxelsVolume.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def VoxelsState(self):  # type: ()->String
        return String(self._node.at("VoxelsState"))
    @VoxelsState.setter
    def VoxelsState(self, val): self.VoxelsState.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class EntityStatePlayer(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/EntityStatePlayer"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStatePlayer
        return EntityStatePlayer(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStatePlayer.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStatePlayer
        return EntityStatePlayer(entlib.make_node(EntityStatePlayer.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class EntityStateMask(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/EntityStateMask"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStateMask
        return EntityStateMask(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateMask.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStateMask
        return EntityStateMask(entlib.make_node(EntityStateMask.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def MaskMeshPath(self):  # type: ()->String
        return String(self._node.at("MaskMeshPath"))
    @MaskMeshPath.setter
    def MaskMeshPath(self, val): self.MaskMeshPath.set(val)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class EntityStateForceCanBeTargeted(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/EntityStateForceCanBeTargeted"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStateForceCanBeTargeted
        return EntityStateForceCanBeTargeted(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateForceCanBeTargeted.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStateForceCanBeTargeted
        return EntityStateForceCanBeTargeted(entlib.make_node(EntityStateForceCanBeTargeted.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def CanBeTargeted(self):  # type: ()->Bool
        return Bool(self._node.at("CanBeTargeted"))
    @CanBeTargeted.setter
    def CanBeTargeted(self, val): self.CanBeTargeted.set(val)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class EntityStateEnergySpoutState(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/EntityStateEnergySpoutState"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStateEnergySpoutState
        return EntityStateEnergySpoutState(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateEnergySpoutState.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStateEnergySpoutState
        return EntityStateEnergySpoutState(entlib.make_node(EntityStateEnergySpoutState.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def ReviveSide(self):  # type: ()->ReviveSide
        return ReviveSide(self._node.at("ReviveSide"))
    @ReviveSide.setter
    def ReviveSide(self, val): self.ReviveSide.set(val)
    @property
    def ReviveSideEvents(self):  # type: ()->Array[ReviveSideEvent]
        return (lambda n: Array(ReviveSideEvent, n))(self._node.at("ReviveSideEvents"))
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class EntityStateEnergyRootState(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/EntityStateEnergyRootState"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStateEnergyRootState
        return EntityStateEnergyRootState(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateEnergyRootState.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStateEnergyRootState
        return EntityStateEnergyRootState(entlib.make_node(EntityStateEnergyRootState.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Energy(self):  # type: ()->Float
        return Float(self._node.at("Energy"))
    @Energy.setter
    def Energy(self, val): self.Energy.set(val)
    @property
    def ReviveSide(self):  # type: ()->ReviveSide
        return ReviveSide(self._node.at("ReviveSide"))
    @ReviveSide.setter
    def ReviveSide(self, val): self.ReviveSide.set(val)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class EntityStateBoidsHomePos(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/EntityStateBoidsHomePos"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->EntityStateBoidsHomePos
        return EntityStateBoidsHomePos(entlib.load_node_file(sourcefile, entlib.get_schema(EntityStateBoidsHomePos.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->EntityStateBoidsHomePos
        return EntityStateBoidsHomePos(entlib.make_node(EntityStateBoidsHomePos.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def HomePosition(self):  # type: ()->Position
        return Position(self._node.at("HomePosition"))
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class ActorStateTeleport(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ActorStateTeleport"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActorStateTeleport
        return ActorStateTeleport(entlib.load_node_file(sourcefile, entlib.get_schema(ActorStateTeleport.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActorStateTeleport
        return ActorStateTeleport(entlib.make_node(ActorStateTeleport.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Inputs(self):  # type: ()->ActorStateTeleport_Inputs
        return ActorStateTeleport_Inputs(self._node.at("Inputs"))
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class ActorStateRegenerationLow(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ActorStateRegenerationLow"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActorStateRegenerationLow
        return ActorStateRegenerationLow(entlib.load_node_file(sourcefile, entlib.get_schema(ActorStateRegenerationLow.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActorStateRegenerationLow
        return ActorStateRegenerationLow(entlib.make_node(ActorStateRegenerationLow.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def NeedToBeFreed(self):  # type: ()->Bool
        return Bool(self._node.at("NeedToBeFreed"))
    @NeedToBeFreed.setter
    def NeedToBeFreed(self, val): self.NeedToBeFreed.set(val)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class ActorStateRegenerationFull(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ActorStateRegenerationFull"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActorStateRegenerationFull
        return ActorStateRegenerationFull(entlib.load_node_file(sourcefile, entlib.get_schema(ActorStateRegenerationFull.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActorStateRegenerationFull
        return ActorStateRegenerationFull(entlib.make_node(ActorStateRegenerationFull.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class ActorStateInvincible(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ActorStateInvincible"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActorStateInvincible
        return ActorStateInvincible(entlib.load_node_file(sourcefile, entlib.get_schema(ActorStateInvincible.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActorStateInvincible
        return ActorStateInvincible(entlib.make_node(ActorStateInvincible.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class ActorStateHoldingItem(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ActorStateHoldingItem"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActorStateHoldingItem
        return ActorStateHoldingItem(entlib.load_node_file(sourcefile, entlib.get_schema(ActorStateHoldingItem.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActorStateHoldingItem
        return ActorStateHoldingItem(entlib.make_node(ActorStateHoldingItem.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def InventoryEntityRef(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("InventoryEntityRef"))
    @InventoryEntityRef.setter
    def InventoryEntityRef(self, val): self.InventoryEntityRef.set(val)
    @property
    def ItemEntityRef(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("ItemEntityRef"))
    @ItemEntityRef.setter
    def ItemEntityRef(self, val): self.ItemEntityRef.set(val)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class ActorStateHasNoBody(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ActorStateHasNoBody"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActorStateHasNoBody
        return ActorStateHasNoBody(entlib.load_node_file(sourcefile, entlib.get_schema(ActorStateHasNoBody.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActorStateHasNoBody
        return ActorStateHasNoBody(entlib.make_node(ActorStateHasNoBody.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class ActorStateDead(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ActorStateDead"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActorStateDead
        return ActorStateDead(entlib.load_node_file(sourcefile, entlib.get_schema(ActorStateDead.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActorStateDead
        return ActorStateDead(entlib.make_node(ActorStateDead.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def LastAliveReviveSide(self):  # type: ()->LastAliveReviveSide
        return LastAliveReviveSide(self._node.at("LastAliveReviveSide"))
    @property
    def ReviveLifeSigned(self):  # type: ()->Float
        return Float(self._node.at("ReviveLifeSigned"))
    @ReviveLifeSigned.setter
    def ReviveLifeSigned(self, val): self.ReviveLifeSigned.set(val)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class ActorStateBuried(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ActorStateBuried"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActorStateBuried
        return ActorStateBuried(entlib.load_node_file(sourcefile, entlib.get_schema(ActorStateBuried.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActorStateBuried
        return ActorStateBuried(entlib.make_node(ActorStateBuried.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class ActorStateBeingOnGround(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ActorStateBeingOnGround"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActorStateBeingOnGround
        return ActorStateBeingOnGround(entlib.load_node_file(sourcefile, entlib.get_schema(ActorStateBeingOnGround.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActorStateBeingOnGround
        return ActorStateBeingOnGround(entlib.make_node(ActorStateBeingOnGround.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class ActorStateBeingInAir(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ActorStateBeingInAir"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActorStateBeingInAir
        return ActorStateBeingInAir(entlib.load_node_file(sourcefile, entlib.get_schema(ActorStateBeingInAir.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActorStateBeingInAir
        return ActorStateBeingInAir(entlib.make_node(ActorStateBeingInAir.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class ActorStateBeingImmersed(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ActorStateBeingImmersed"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActorStateBeingImmersed
        return ActorStateBeingImmersed(entlib.load_node_file(sourcefile, entlib.get_schema(ActorStateBeingImmersed.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActorStateBeingImmersed
        return ActorStateBeingImmersed(entlib.make_node(ActorStateBeingImmersed.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class ActorStateAlive(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ActorStateAlive"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActorStateAlive
        return ActorStateAlive(entlib.load_node_file(sourcefile, entlib.get_schema(ActorStateAlive.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActorStateAlive
        return ActorStateAlive(entlib.make_node(ActorStateAlive.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Life(self):  # type: ()->Float
        return Float(self._node.at("Life"))
    @Life.setter
    def Life(self, val): self.Life.set(val)
    @property
    def ReviveSide(self):  # type: ()->ReviveSide
        return ReviveSide(self._node.at("ReviveSide"))
    @ReviveSide.setter
    def ReviveSide(self, val): self.ReviveSide.set(val)
    @property
    def StunGauge(self):  # type: ()->StunGauge
        return StunGauge(self._node.at("StunGauge"))
    @property
    def Super(self):  # type: ()->ActorState
        return ActorState(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class AbilityData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/AbilityData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AbilityData
        return AbilityData(entlib.load_node_file(sourcefile, entlib.get_schema(AbilityData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AbilityData
        return AbilityData(entlib.make_node(AbilityData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def abilities(self):  # type: ()->PrimArray[ActorAbility]
        return (lambda n: PrimArray(ActorAbility, n))(self._node.at("abilities"))
    @abilities.setter
    def abilities(self, val): self.abilities.set(val)
    pass


from EntityLibPy import Node

class ActorGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ActorGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ActorGD
        return ActorGD(entlib.load_node_file(sourcefile, entlib.get_schema(ActorGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ActorGD
        return ActorGD(entlib.make_node(ActorGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Archetype(self):  # type: ()->Archetype
        return Archetype(self._node.at("Archetype"))
    @Archetype.setter
    def Archetype(self, val): self.Archetype.set(val)
    @property
    def ClassStyleTag(self):  # type: ()->StyleMode
        return StyleMode(self._node.at("ClassStyleTag"))
    @ClassStyleTag.setter
    def ClassStyleTag(self, val): self.ClassStyleTag.set(val)
    @property
    def FactionName(self):  # type: ()->String
        return String(self._node.at("FactionName"))
    @FactionName.setter
    def FactionName(self, val): self.FactionName.set(val)
    @property
    def Icon(self):  # type: ()->String
        return String(self._node.at("Icon"))
    @Icon.setter
    def Icon(self, val): self.Icon.set(val)
    @property
    def InSpiritWorld(self):  # type: ()->Bool
        return Bool(self._node.at("InSpiritWorld"))
    @InSpiritWorld.setter
    def InSpiritWorld(self, val): self.InSpiritWorld.set(val)
    @property
    def Specie(self):  # type: ()->Specie
        return Specie(self._node.at("Specie"))
    @Specie.setter
    def Specie(self, val): self.Specie.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def Weapon(self):  # type: ()->Bool
        return Bool(self._node.at("Weapon"))
    @Weapon.setter
    def Weapon(self, val): self.Weapon.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def abilityData(self):  # type: ()->AbilityData
        return AbilityData(self._node.at("abilityData"))
    @property
    def attackData(self):  # type: ()->AttackData
        return AttackData(self._node.at("attackData"))
    @property
    def lifeAndDamageData(self):  # type: ()->LifeAndDamageData
        return LifeAndDamageData(self._node.at("lifeAndDamageData"))
    @property
    def projectileData(self):  # type: ()->ProjectileData
        return ProjectileData(self._node.at("projectileData"))
    @property
    def radius(self):  # type: ()->Float
        return Float(self._node.at("radius"))
    @radius.setter
    def radius(self, val): self.radius.set(val)
    @property
    def shootData(self):  # type: ()->ShootData
        return ShootData(self._node.at("shootData"))
    @property
    def stunData(self):  # type: ()->StunData
        return StunData(self._node.at("stunData"))
    @property
    def volume(self):  # type: ()->Float
        return Float(self._node.at("volume"))
    @volume.setter
    def volume(self, val): self.volume.set(val)
    pass


from EntityLibPy import Node

class ProjectileGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ProjectileGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ProjectileGD
        return ProjectileGD(entlib.load_node_file(sourcefile, entlib.get_schema(ProjectileGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ProjectileGD
        return ProjectileGD(entlib.make_node(ProjectileGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Super(self):  # type: ()->ActorGD
        return ActorGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class CreatureGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/CreatureGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CreatureGD
        return CreatureGD(entlib.load_node_file(sourcefile, entlib.get_schema(CreatureGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CreatureGD
        return CreatureGD(entlib.make_node(CreatureGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def DisableLookAt(self):  # type: ()->Bool
        return Bool(self._node.at("DisableLookAt"))
    @DisableLookAt.setter
    def DisableLookAt(self, val): self.DisableLookAt.set(val)
    @property
    def DivePitchAngleMax(self):  # type: ()->Float
        return Float(self._node.at("DivePitchAngleMax"))
    @DivePitchAngleMax.setter
    def DivePitchAngleMax(self, val): self.DivePitchAngleMax.set(val)
    @property
    def DivePitchAngleMin(self):  # type: ()->Float
        return Float(self._node.at("DivePitchAngleMin"))
    @DivePitchAngleMin.setter
    def DivePitchAngleMin(self, val): self.DivePitchAngleMin.set(val)
    @property
    def FlyPitchAngleMax(self):  # type: ()->Float
        return Float(self._node.at("FlyPitchAngleMax"))
    @FlyPitchAngleMax.setter
    def FlyPitchAngleMax(self, val): self.FlyPitchAngleMax.set(val)
    @property
    def FlyPitchAngleMin(self):  # type: ()->Float
        return Float(self._node.at("FlyPitchAngleMin"))
    @FlyPitchAngleMin.setter
    def FlyPitchAngleMin(self, val): self.FlyPitchAngleMin.set(val)
    @property
    def IsBig(self):  # type: ()->Bool
        return Bool(self._node.at("IsBig"))
    @IsBig.setter
    def IsBig(self, val): self.IsBig.set(val)
    @property
    def IsDivinity(self):  # type: ()->Bool
        return Bool(self._node.at("IsDivinity"))
    @IsDivinity.setter
    def IsDivinity(self, val): self.IsDivinity.set(val)
    @property
    def IsGuardian(self):  # type: ()->Bool
        return Bool(self._node.at("IsGuardian"))
    @IsGuardian.setter
    def IsGuardian(self, val): self.IsGuardian.set(val)
    @property
    def IsStaff(self):  # type: ()->Bool
        return Bool(self._node.at("IsStaff"))
    @IsStaff.setter
    def IsStaff(self, val): self.IsStaff.set(val)
    @property
    def SpawnSoulIfNoEnemy(self):  # type: ()->Bool
        return Bool(self._node.at("SpawnSoulIfNoEnemy"))
    @SpawnSoulIfNoEnemy.setter
    def SpawnSoulIfNoEnemy(self, val): self.SpawnSoulIfNoEnemy.set(val)
    @property
    def SpeedFastMinDuration(self):  # type: ()->SpeedFastMinDuration
        return SpeedFastMinDuration(self._node.at("SpeedFastMinDuration"))
    @property
    def Super(self):  # type: ()->ActorGD
        return ActorGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def biteData(self):  # type: ()->BiteData
        return BiteData(self._node.at("biteData"))
    @property
    def dangerousnessData(self):  # type: ()->CreatureDangerousness
        return CreatureDangerousness(self._node.at("dangerousnessData"))
    @property
    def fusionData(self):  # type: ()->FusionData
        return FusionData(self._node.at("fusionData"))
    @property
    def interactData(self):  # type: ()->InteractData
        return InteractData(self._node.at("interactData"))
    @property
    def mountData(self):  # type: ()->MountData
        return MountData(self._node.at("mountData"))
    @property
    def revivedData(self):  # type: ()->RevivedData
        return RevivedData(self._node.at("revivedData"))
    pass


from EntityLibPy import Node

class ClothGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ClothGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ClothGD
        return ClothGD(entlib.load_node_file(sourcefile, entlib.get_schema(ClothGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ClothGD
        return ClothGD(entlib.make_node(ClothGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def BodyEventsPath(self):  # type: ()->String
        return String(self._node.at("BodyEventsPath"))
    @BodyEventsPath.setter
    def BodyEventsPath(self, val): self.BodyEventsPath.set(val)
    @property
    def BodyNamePath(self):  # type: ()->String
        return String(self._node.at("BodyNamePath"))
    @BodyNamePath.setter
    def BodyNamePath(self, val): self.BodyNamePath.set(val)
    @property
    def SoundBanks(self):  # type: ()->PrimArray[String]
        return (lambda n: PrimArray(String, n))(self._node.at("SoundBanks"))
    @SoundBanks.setter
    def SoundBanks(self, val): self.SoundBanks.set(val)
    @property
    def SoundEventMappingRules(self):  # type: ()->SoundEventMapping
        return SoundEventMapping(self._node.at("SoundEventMappingRules"))
    @property
    def Super(self):  # type: ()->ActorGD
        return ActorGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class AIContextSlot(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/AIContextSlot"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AIContextSlot
        return AIContextSlot(entlib.load_node_file(sourcefile, entlib.get_schema(AIContextSlot.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AIContextSlot
        return AIContextSlot(entlib.make_node(AIContextSlot.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Count(self):  # type: ()->Int
        return Int(self._node.at("Count"))
    @Count.setter
    def Count(self, val): self.Count.set(val)
    @property
    def Name(self):  # type: ()->String
        return String(self._node.at("Name"))
    @Name.setter
    def Name(self, val): self.Name.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class AIContextGD(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/AIContextGD"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->AIContextGD
        return AIContextGD(entlib.load_node_file(sourcefile, entlib.get_schema(AIContextGD.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->AIContextGD
        return AIContextGD(entlib.make_node(AIContextGD.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def FollowAccelerationCoeff(self):  # type: ()->Float
        return Float(self._node.at("FollowAccelerationCoeff"))
    @FollowAccelerationCoeff.setter
    def FollowAccelerationCoeff(self, val): self.FollowAccelerationCoeff.set(val)
    @property
    def FollowCanStopMaxStateDuration(self):  # type: ()->Float
        return Float(self._node.at("FollowCanStopMaxStateDuration"))
    @FollowCanStopMaxStateDuration.setter
    def FollowCanStopMaxStateDuration(self, val): self.FollowCanStopMaxStateDuration.set(val)
    @property
    def FollowCanStopMaxTimeInExpandedZone(self):  # type: ()->Float
        return Float(self._node.at("FollowCanStopMaxTimeInExpandedZone"))
    @FollowCanStopMaxTimeInExpandedZone.setter
    def FollowCanStopMaxTimeInExpandedZone(self, val): self.FollowCanStopMaxTimeInExpandedZone.set(val)
    @property
    def FollowDecelerationCoeff(self):  # type: ()->Float
        return Float(self._node.at("FollowDecelerationCoeff"))
    @FollowDecelerationCoeff.setter
    def FollowDecelerationCoeff(self, val): self.FollowDecelerationCoeff.set(val)
    @property
    def FollowDeltaAngleTarget(self):  # type: ()->Float
        return Float(self._node.at("FollowDeltaAngleTarget"))
    @FollowDeltaAngleTarget.setter
    def FollowDeltaAngleTarget(self, val): self.FollowDeltaAngleTarget.set(val)
    @property
    def FollowHotspotRadius(self):  # type: ()->Float
        return Float(self._node.at("FollowHotspotRadius"))
    @FollowHotspotRadius.setter
    def FollowHotspotRadius(self, val): self.FollowHotspotRadius.set(val)
    @property
    def FollowHotspotSpace(self):  # type: ()->Float
        return Float(self._node.at("FollowHotspotSpace"))
    @FollowHotspotSpace.setter
    def FollowHotspotSpace(self, val): self.FollowHotspotSpace.set(val)
    @property
    def FollowRandomSpeedZoneInBeginCoeffMax(self):  # type: ()->Float
        return Float(self._node.at("FollowRandomSpeedZoneInBeginCoeffMax"))
    @FollowRandomSpeedZoneInBeginCoeffMax.setter
    def FollowRandomSpeedZoneInBeginCoeffMax(self, val): self.FollowRandomSpeedZoneInBeginCoeffMax.set(val)
    @property
    def FollowRandomSpeedZoneInBeginCoeffMin(self):  # type: ()->Float
        return Float(self._node.at("FollowRandomSpeedZoneInBeginCoeffMin"))
    @FollowRandomSpeedZoneInBeginCoeffMin.setter
    def FollowRandomSpeedZoneInBeginCoeffMin(self, val): self.FollowRandomSpeedZoneInBeginCoeffMin.set(val)
    @property
    def FollowRandomSpeedZoneInEndCoeffMax(self):  # type: ()->Float
        return Float(self._node.at("FollowRandomSpeedZoneInEndCoeffMax"))
    @FollowRandomSpeedZoneInEndCoeffMax.setter
    def FollowRandomSpeedZoneInEndCoeffMax(self, val): self.FollowRandomSpeedZoneInEndCoeffMax.set(val)
    @property
    def FollowRandomSpeedZoneInEndCoeffMin(self):  # type: ()->Float
        return Float(self._node.at("FollowRandomSpeedZoneInEndCoeffMin"))
    @FollowRandomSpeedZoneInEndCoeffMin.setter
    def FollowRandomSpeedZoneInEndCoeffMin(self, val): self.FollowRandomSpeedZoneInEndCoeffMin.set(val)
    @property
    def FollowRandomSynchroDelayMax(self):  # type: ()->Float
        return Float(self._node.at("FollowRandomSynchroDelayMax"))
    @FollowRandomSynchroDelayMax.setter
    def FollowRandomSynchroDelayMax(self, val): self.FollowRandomSynchroDelayMax.set(val)
    @property
    def FollowRandomSynchroDelayMin(self):  # type: ()->Float
        return Float(self._node.at("FollowRandomSynchroDelayMin"))
    @FollowRandomSynchroDelayMin.setter
    def FollowRandomSynchroDelayMin(self, val): self.FollowRandomSynchroDelayMin.set(val)
    @property
    def FollowSpeedChangeThreshold(self):  # type: ()->Float
        return Float(self._node.at("FollowSpeedChangeThreshold"))
    @FollowSpeedChangeThreshold.setter
    def FollowSpeedChangeThreshold(self, val): self.FollowSpeedChangeThreshold.set(val)
    @property
    def FollowSpeedZoneInBegin(self):  # type: ()->Float
        return Float(self._node.at("FollowSpeedZoneInBegin"))
    @FollowSpeedZoneInBegin.setter
    def FollowSpeedZoneInBegin(self, val): self.FollowSpeedZoneInBegin.set(val)
    @property
    def FollowSpeedZoneInEnd(self):  # type: ()->Float
        return Float(self._node.at("FollowSpeedZoneInEnd"))
    @FollowSpeedZoneInEnd.setter
    def FollowSpeedZoneInEnd(self, val): self.FollowSpeedZoneInEnd.set(val)
    @property
    def FollowSpeedZoneOutEnd(self):  # type: ()->Float
        return Float(self._node.at("FollowSpeedZoneOutEnd"))
    @FollowSpeedZoneOutEnd.setter
    def FollowSpeedZoneOutEnd(self, val): self.FollowSpeedZoneOutEnd.set(val)
    @property
    def FollowTargetDistRadiusFactor(self):  # type: ()->Float
        return Float(self._node.at("FollowTargetDistRadiusFactor"))
    @FollowTargetDistRadiusFactor.setter
    def FollowTargetDistRadiusFactor(self, val): self.FollowTargetDistRadiusFactor.set(val)
    @property
    def Super(self):  # type: ()->ComponentGD
        return ComponentGD(self._node.at("Super"))
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def attackCircleRadius(self):  # type: ()->Float
        return Float(self._node.at("attackCircleRadius"))
    @attackCircleRadius.setter
    def attackCircleRadius(self, val): self.attackCircleRadius.set(val)
    @property
    def distanceBetweenCreatures(self):  # type: ()->Float
        return Float(self._node.at("distanceBetweenCreatures"))
    @distanceBetweenCreatures.setter
    def distanceBetweenCreatures(self, val): self.distanceBetweenCreatures.set(val)
    @property
    def distantReachCircleRadius(self):  # type: ()->Float
        return Float(self._node.at("distantReachCircleRadius"))
    @distantReachCircleRadius.setter
    def distantReachCircleRadius(self, val): self.distantReachCircleRadius.set(val)
    @property
    def followCircleRadius(self):  # type: ()->Float
        return Float(self._node.at("followCircleRadius"))
    @followCircleRadius.setter
    def followCircleRadius(self, val): self.followCircleRadius.set(val)
    @property
    def lockTargetCircleRadius(self):  # type: ()->Float
        return Float(self._node.at("lockTargetCircleRadius"))
    @lockTargetCircleRadius.setter
    def lockTargetCircleRadius(self, val): self.lockTargetCircleRadius.set(val)
    @property
    def slots(self):  # type: ()->Array[AIContextSlot]
        return (lambda n: Array(AIContextSlot, n))(self._node.at("slots"))
    pass


from EntityLibPy import Node
class ActorAbilityEnum(Enum):
    landing = "landing"
    crouch = "crouch"
    fly = "fly"
    ride = "ride"
    dive = "dive"
    stinky = "stinky"
    ActorAbility_COUNT = "ActorAbility_COUNT"


class ActorAbility(Primitive[ActorAbilityEnum]):  # Enum
    def __init__(self, node):
        super().__init__(ActorAbilityEnum, node)
    schema_name = "ActorAbility"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> ActorAbility
        return ActorAbility(node)
    def set(self, val):  # type: (ActorAbilityEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)


from EntityLibPy import Node
class ActorCategoryEnum(Enum):
    CATEGORY_All = "CATEGORY_All"
    CATEGORY_Action = "CATEGORY_Action"
    CATEGORY_AnimationLegConstraint = "CATEGORY_AnimationLegConstraint"
    CATEGORY_ActionAttack = "CATEGORY_ActionAttack"
    CATEGORY_Attitude = "CATEGORY_Attitude"
    CATEGORY_Context = "CATEGORY_Context"
    CATEGORY_ActionCosmetic = "CATEGORY_ActionCosmetic"
    CATEGORY_ActionDamage = "CATEGORY_ActionDamage"
    CATEGORY_ActionDefault = "CATEGORY_ActionDefault"
    CATEGORY_ActionDie = "CATEGORY_ActionDie"
    CATEGORY_Environment = "CATEGORY_Environment"
    CATEGORY_Fall = "CATEGORY_Fall"
    CATEGORY_Hint = "CATEGORY_Hint"
    CATEGORY_LookAt = "CATEGORY_LookAt"
    CATEGORY_ActionJump = "CATEGORY_ActionJump"
    CATEGORY_ActionLand = "CATEGORY_ActionLand"
    CATEGORY_Life = "CATEGORY_Life"
    CATEGORY_Locomotion = "CATEGORY_Locomotion"
    CATEGORY_ActionMove = "CATEGORY_ActionMove"
    CATEGORY_Persistent = "CATEGORY_Persistent"
    CATEGORY_Purgatory = "CATEGORY_Purgatory"
    CATEGORY_ActionSlide = "CATEGORY_ActionSlide"
    CATEGORY_ActionStop = "CATEGORY_ActionStop"
    CATEGORY_ActionStrafe = "CATEGORY_ActionStrafe"
    CATEGORY_Transition = "CATEGORY_Transition"
    CATEGORY_Trigger = "CATEGORY_Trigger"
    CATEGORY_ActionWingFlutter = "CATEGORY_ActionWingFlutter"
    CATEGORY_Health = "CATEGORY_Health"
    CATEGORY_HealthAlive = "CATEGORY_HealthAlive"
    CATEGORY_HealthDead = "CATEGORY_HealthDead"
    CATEGORY_Regeneration = "CATEGORY_Regeneration"
    CATEGORY_EntitySwitchTransition = "CATEGORY_EntitySwitchTransition"
    CATEGORY_EnergyRoot = "CATEGORY_EnergyRoot"
    CATEGORY_EnergySpout = "CATEGORY_EnergySpout"
    CATEGORY_GPE = "CATEGORY_GPE"
    ActorCategory_COUNT = "ActorCategory_COUNT"


class ActorCategory(Primitive[ActorCategoryEnum]):  # Enum
    def __init__(self, node):
        super().__init__(ActorCategoryEnum, node)
    schema_name = "ActorCategory"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> ActorCategory
        return ActorCategory(node)
    def set(self, val):  # type: (ActorCategoryEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)


from EntityLibPy import Node
class InventoryTagsEnum(Enum):
    outfit = "outfit"
    item = "item"
    default_ = "default"
    neutral = "neutral"
    sacred = "sacred"
    cursed = "cursed"
    skeleton = "skeleton"
    zombie = "zombie"
    full = "full"
    soul = "soul"
    disguise = "disguise"
    soulfreedflying = "soulfreedflying"
    soulfreednormal = "soulfreednormal"
    InventoryTags_COUNT = "InventoryTags_COUNT"


class InventoryTags(Primitive[InventoryTagsEnum]):  # Enum
    def __init__(self, node):
        super().__init__(InventoryTagsEnum, node)
    schema_name = "InventoryTags"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> InventoryTags
        return InventoryTags(node)
    def set(self, val):  # type: (InventoryTagsEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)


from EntityLibPy import Node

class MapOfObjectItem_A(HelperObject):

    @property
    def Value(self):  # type: ()->String
        return String(self._node.at("Value"))
    @Value.setter
    def Value(self, val): self.Value.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node
class Pasta_Easing_CurveEnum(Enum):
    Linear = "Linear"
    EaseInSin = "EaseInSin"
    EaseInQuad = "EaseInQuad"
    EaseInCubic = "EaseInCubic"
    EaseInQuart = "EaseInQuart"
    EaseInQuint = "EaseInQuint"
    EaseInExp = "EaseInExp"
    EaseOutSin = "EaseOutSin"
    EaseOutQuad = "EaseOutQuad"
    EaseOutCubic = "EaseOutCubic"
    EaseOutQuart = "EaseOutQuart"
    EaseOutQuint = "EaseOutQuint"
    EaseOutExp = "EaseOutExp"
    EaseInoutSin = "EaseInoutSin"
    EaseInoutQuad = "EaseInoutQuad"
    EaseInoutCubic = "EaseInoutCubic"
    EaseInoutQuart = "EaseInoutQuart"
    EaseInoutQuint = "EaseInoutQuint"
    EaseInoutExp = "EaseInoutExp"
    EaseInCirc = "EaseInCirc"
    EaseOutCirc = "EaseOutCirc"
    EaseInoutCirc = "EaseInoutCirc"
    EaseOutElastic = "EaseOutElastic"
    Count = "Count"


class Pasta_Easing_Curve(Primitive[Pasta_Easing_CurveEnum]):  # Enum
    def __init__(self, node):
        super().__init__(Pasta_Easing_CurveEnum, node)
    schema_name = "Pasta::Easing::Curve"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> Pasta_Easing_Curve
        return Pasta_Easing_Curve(node)
    def set(self, val):  # type: (Pasta_Easing_CurveEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)


from EntityLibPy import Node
class PhysicsLayerEnum(Enum):
    Default = "Default"
    Ground = "Ground"
    Static = "Static"
    Raycast = "Raycast"
    Trigger = "Trigger"
    Walkable = "Walkable"
    Camera = "Camera"
    ClimbEdge = "ClimbEdge"
    Kinematic = "Kinematic"
    Ragdoll = "Ragdoll"
    Projectile = "Projectile"
    Hit = "Hit"
    MotionConstraint = "MotionConstraint"
    Heal = "Heal"
    Body = "Body"
    Fluid = "Fluid"
    Hitable = "Hitable"
    None_ = "None"
    All = "All"
    PHYSICLAYER_COUNT = "PHYSICLAYER_COUNT"


class PhysicsLayer(Primitive[PhysicsLayerEnum]):  # Enum
    def __init__(self, node):
        super().__init__(PhysicsLayerEnum, node)
    schema_name = "PhysicsLayer"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> PhysicsLayer
        return PhysicsLayer(node)
    def set(self, val):  # type: (PhysicsLayerEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)


from EntityLibPy import Node

class ProjectileShooterData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ProjectileShooterData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ProjectileShooterData
        return ProjectileShooterData(entlib.load_node_file(sourcefile, entlib.get_schema(ProjectileShooterData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ProjectileShooterData
        return ProjectileShooterData(entlib.make_node(ProjectileShooterData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def SubEntity(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("SubEntity"))
    @SubEntity.setter
    def SubEntity(self, val): self.SubEntity.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node
class RegenerationStateEnum(Enum):
    None_ = "None"
    Sacred = "Sacred"
    Cursed = "Cursed"
    Lush = "Lush"
    Neutral = "Neutral"
    Dead = "Dead"
    RegenerationState_COUNT = "RegenerationState_COUNT"


class RegenerationState(Primitive[RegenerationStateEnum]):  # Enum
    def __init__(self, node):
        super().__init__(RegenerationStateEnum, node)
    schema_name = "RegenerationState"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> RegenerationState
        return RegenerationState(node)
    def set(self, val):  # type: (RegenerationStateEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)


from EntityLibPy import Node

class ReviveSideData(HelperObject):
    schema_name = "./RuntimeComponents.json#/definitions/ReviveSideData"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ReviveSideData
        return ReviveSideData(entlib.load_node_file(sourcefile, entlib.get_schema(ReviveSideData.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ReviveSideData
        return ReviveSideData(entlib.make_node(ReviveSideData.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def EntityRef(self):  # type: ()->EntityRef
        return EntityRef(self._node.at("EntityRef"))
    @EntityRef.setter
    def EntityRef(self, val): self.EntityRef.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class Scene(HelperObject):
    schema_name = "./Scene-schema.json#/definitions/Scene"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->Scene
        return Scene(entlib.load_node_file(sourcefile, entlib.get_schema(Scene.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->Scene
        return Scene(entlib.make_node(Scene.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def Objects(self):  # type: ()->ObjectSet[Entity]
        return (lambda n: ObjectSet(Entity, n))(self._node.at("Objects"))
    @property
    def Version(self):  # type: ()->Int
        return Int(self._node.at("Version"))
    @Version.setter
    def Version(self, val): self.Version.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node

class SetOfObjectItem(HelperObject):

    @property
    def Name(self):  # type: ()->String
        return String(self._node.at("Name"))
    @Name.setter
    def Name(self, val): self.Name.set(val)
    @property
    def Value(self):  # type: ()->String
        return String(self._node.at("Value"))
    @Value.setter
    def Value(self, val): self.Value.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass


from EntityLibPy import Node
class SizeEnum(Enum):
    tiny = "tiny"
    small = "small"
    medium = "medium"
    big = "big"
    enormous = "enormous"
    Size_COUNT = "Size_COUNT"


class Size(Primitive[SizeEnum]):  # Enum
    def __init__(self, node):
        super().__init__(SizeEnum, node)
    schema_name = "Size"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> Size
        return Size(node)
    def set(self, val):  # type: (SizeEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)



