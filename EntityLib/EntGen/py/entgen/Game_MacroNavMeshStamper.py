
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy

from entgen.String import *
from entgen.Bool import *
from entgen.Float import *
from entgen.Matrix44 import *
from entgen.Vector3 import *

from EntityLibPy import Node

class Game_MacroNavMeshStamper(HelperObject):
    schema_name = "Game::MacroNavMeshStamper"
    @staticmethod
    def load(entlib, sourcefile):  # type: (EntityLib, str)->Game_MacroNavMeshStamper
        return Game_MacroNavMeshStamper(entlib.load_node_file(sourcefile, entlib.get_schema(Game_MacroNavMeshStamper.schema_name)))
    @staticmethod
    def create(entlib):  # type: (EntityLib)->Game_MacroNavMeshStamper
        return Game_MacroNavMeshStamper(entlib.make_node(Game_MacroNavMeshStamper.schema_name))
    def save(self, destfile):
        self.node.save_node(destfile)
    @property
    def BoundingBox(self):  # type: ()->Vector3
        return Vector3(self._node.at("BoundingBox"))
    @BoundingBox.setter
    def BoundingBox(self, val): self.BoundingBox.set(val)
    @property
    def Matrix(self):  # type: ()->Matrix44
        return Matrix44(self._node.at("Matrix"))
    @Matrix.setter
    def Matrix(self, val): self.Matrix.set(val)
    @property
    def NavmeshPath(self):  # type: ()->String
        return String(self._node.at("NavmeshPath"))
    @NavmeshPath.setter
    def NavmeshPath(self, val): self.NavmeshPath.set(val)
    @property
    def Position(self):  # type: ()->Vector3
        return Vector3(self._node.at("Position"))
    @Position.setter
    def Position(self, val): self.Position.set(val)
    @property
    def RotationZ(self):  # type: ()->Float
        return Float(self._node.at("RotationZ"))
    @RotationZ.setter
    def RotationZ(self, val): self.RotationZ.set(val)
    @property
    def StickToGround(self):  # type: ()->Bool
        return Bool(self._node.at("StickToGround"))
    @StickToGround.setter
    def StickToGround(self, val): self.StickToGround.set(val)
    @property
    def _comment(self):  # type: ()->String
        return String(self._node.at("_comment"))
    @_comment.setter
    def _comment(self, val): self._comment.set(val)
    pass




