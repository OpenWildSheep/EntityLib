
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.PrimitiveColliderType import *
from entgen.String import *
from entgen.Bool import *
from entgen.ComponentGD import *
from entgen.Float import *
from entgen.Vector3 import *
from entgen.PhysicsLayer import *
from entgen.Size import *
from entgen.String import *


class PhysicsGD(HelperObject):
    schema_name = "./MergedComponents.json#/definitions/PhysicsGD"
    @staticmethod
    def load(entlib, sourcefile):
        return entlib.load_node_file(sourcefile, entlib.get_schema(PhysicsGD.schema_name))
    @property
    def AffectByHit(self): return Bool(self._node.at("AffectByHit"))
    @AffectByHit.setter
    def AffectByHit(self, val): self.AffectByHit.set(val)
    @property
    def AngularDamping(self): return Float(self._node.at("AngularDamping"))
    @AngularDamping.setter
    def AngularDamping(self, val): self.AngularDamping.set(val)
    @property
    def AxisRestriction(self): return Vector3(self._node.at("AxisRestriction"))
    @AxisRestriction.setter
    def AxisRestriction(self, val): self.AxisRestriction.set(val)
    @property
    def CameraIgnored(self): return Bool(self._node.at("CameraIgnored"))
    @CameraIgnored.setter
    def CameraIgnored(self, val): self.CameraIgnored.set(val)
    @property
    def Ccd(self): return Bool(self._node.at("Ccd"))
    @Ccd.setter
    def Ccd(self, val): self.Ccd.set(val)
    @property
    def EDITOR_MeshColliders(self): return (lambda n: PrimArray(String, n))(self._node.at("EDITOR_MeshColliders"))
    @EDITOR_MeshColliders.setter
    def EDITOR_MeshColliders(self, val): self.EDITOR_MeshColliders.set(val)
    @property
    def EDITOR_MeshEdges(self): return String(self._node.at("EDITOR_MeshEdges"))
    @EDITOR_MeshEdges.setter
    def EDITOR_MeshEdges(self, val): self.EDITOR_MeshEdges.set(val)
    @property
    def EDITOR_NavMeshStamper(self): return String(self._node.at("EDITOR_NavMeshStamper"))
    @EDITOR_NavMeshStamper.setter
    def EDITOR_NavMeshStamper(self, val): self.EDITOR_NavMeshStamper.set(val)
    @property
    def EnergyLoss(self): return Float(self._node.at("EnergyLoss"))
    @EnergyLoss.setter
    def EnergyLoss(self, val): self.EnergyLoss.set(val)
    @property
    def Friction(self): return Float(self._node.at("Friction"))
    @Friction.setter
    def Friction(self, val): self.Friction.set(val)
    @property
    def HasGravity(self): return Bool(self._node.at("HasGravity"))
    @HasGravity.setter
    def HasGravity(self, val): self.HasGravity.set(val)
    @property
    def LinearDamping(self): return Float(self._node.at("LinearDamping"))
    @LinearDamping.setter
    def LinearDamping(self, val): self.LinearDamping.set(val)
    @property
    def Mass(self): return Float(self._node.at("Mass"))
    @Mass.setter
    def Mass(self, val): self.Mass.set(val)
    @property
    def MeshColliders(self): return (lambda n: PrimArray(String, n))(self._node.at("MeshColliders"))
    @MeshColliders.setter
    def MeshColliders(self, val): self.MeshColliders.set(val)
    @property
    def MeshEdges(self): return String(self._node.at("MeshEdges"))
    @MeshEdges.setter
    def MeshEdges(self, val): self.MeshEdges.set(val)
    @property
    def MotionType(self): return String(self._node.at("MotionType"))
    @MotionType.setter
    def MotionType(self, val): self.MotionType.set(val)
    @property
    def NavMeshStamper(self): return String(self._node.at("NavMeshStamper"))
    @NavMeshStamper.setter
    def NavMeshStamper(self, val): self.NavMeshStamper.set(val)
    @property
    def Offset(self): return Vector3(self._node.at("Offset"))
    @Offset.setter
    def Offset(self, val): self.Offset.set(val)
    @property
    def OffsetRotation(self): return Vector3(self._node.at("OffsetRotation"))
    @OffsetRotation.setter
    def OffsetRotation(self, val): self.OffsetRotation.set(val)
    @property
    def PhysicsMaterial(self): return String(self._node.at("PhysicsMaterial"))
    @PhysicsMaterial.setter
    def PhysicsMaterial(self, val): self.PhysicsMaterial.set(val)
    @property
    def PrimitiveCollider(self): return PrimitiveColliderType(self._node.at("PrimitiveCollider"))
    @PrimitiveCollider.setter
    def PrimitiveCollider(self, val): self.PrimitiveCollider.set(val)
    @property
    def PrimitiveColliderSizeLayerMask(self): return (lambda n: PrimArray(Size, n))(self._node.at("PrimitiveColliderSizeLayerMask"))
    @PrimitiveColliderSizeLayerMask.setter
    def PrimitiveColliderSizeLayerMask(self, val): self.PrimitiveColliderSizeLayerMask.set(val)
    @property
    def Radius(self): return Float(self._node.at("Radius"))
    @Radius.setter
    def Radius(self, val): self.Radius.set(val)
    @property
    def Restitution(self): return Float(self._node.at("Restitution"))
    @Restitution.setter
    def Restitution(self, val): self.Restitution.set(val)
    @property
    def SelfFilter(self): return (lambda n: PrimArray(PhysicsLayer, n))(self._node.at("SelfFilter"))
    @SelfFilter.setter
    def SelfFilter(self, val): self.SelfFilter.set(val)
    @property
    def Size(self): return Vector3(self._node.at("Size"))
    @Size.setter
    def Size(self, val): self.Size.set(val)
    @property
    def Sleep(self): return Bool(self._node.at("Sleep"))
    @Sleep.setter
    def Sleep(self, val): self.Sleep.set(val)
    @property
    def Super(self): return ComponentGD(self._node.at("Super"))
    @property
    def TargetFilter(self): return (lambda n: PrimArray(PhysicsLayer, n))(self._node.at("TargetFilter"))
    @TargetFilter.setter
    def TargetFilter(self, val): self.TargetFilter.set(val)
    @property
    def Walkable(self): return Bool(self._node.at("Walkable"))
    @Walkable.setter
    def Walkable(self, val): self.Walkable.set(val)
    @property
    def WalkableSoundSwitch(self): return String(self._node.at("WalkableSoundSwitch"))
    @WalkableSoundSwitch.setter
    def WalkableSoundSwitch(self, val): self.WalkableSoundSwitch.set(val)
    @property
    def _comment(self): return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




