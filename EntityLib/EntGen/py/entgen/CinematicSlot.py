
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.EntityRef import *
from entgen.String import *
from entgen.Bool import *
from entgen.Float import *
from entgen.Transform3D import *

from EntityLibPy import Node

class CinematicSlot(HelperObject):
    schema_name = "CinematicSlot"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->CinematicSlot
        return CinematicSlot(entlib.load_node_file(sourcefile, entlib.get_schema(CinematicSlot.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->CinematicSlot
        return CinematicSlot(entlib.make_node(CinematicSlot.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
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




