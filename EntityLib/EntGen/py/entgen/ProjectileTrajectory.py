
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Float import *
from entgen.Position import *
from entgen.Vector3 import *

from EntityLibPy import Node

class ProjectileTrajectory(HelperObject):
    schema_name = "ProjectileTrajectory"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->ProjectileTrajectory
        return ProjectileTrajectory(entlib.load_node_file(sourcefile, entlib.get_schema(ProjectileTrajectory.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->ProjectileTrajectory
        return ProjectileTrajectory(entlib.make_node(ProjectileTrajectory.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    @property
    def m_direction(self):  # type: ()->Vector3
        return Vector3(self._node.at("m_direction"))
    @m_direction.setter
    def m_direction(self, val): self.m_direction.set(val)
    @property
    def m_position(self):  # type: ()->Position
        return Position(self._node.at("m_position"))
    @property
    def m_speed(self):  # type: ()->Float
        return Float(self._node.at("m_speed"))
    @m_speed.setter
    def m_speed(self, val): self.m_speed.set(val)
    @property
    def m_straightDistance(self):  # type: ()->Float
        return Float(self._node.at("m_straightDistance"))
    @m_straightDistance.setter
    def m_straightDistance(self, val): self.m_straightDistance.set(val)
    pass




