
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


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
        super(Specie, self).__init__(SpecieEnum, node)
    schema_name = "Specie"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> Specie
        return Specie(node)
    def set(self, val):  # type: (SpecieEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




