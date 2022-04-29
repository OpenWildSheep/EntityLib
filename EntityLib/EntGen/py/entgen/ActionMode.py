
### /!\ This code is GENERATED! Do not modify it.

from entgen_helpers import *
import EntityLibPy


from EntityLibPy import Node
class ActionModeEnum(Enum):
    noaction = "noaction"
    attack = "attack"
    attackjump = "attackjump"
    attackcharged = "attackcharged"
    attackpush = "attackpush"
    attackjumponto = "attackjumponto"
    bite = "bite"
    stun = "stun"
    collapse = "collapse"
    throw_ = "throw"
    respawn = "respawn"
    incarnate = "incarnate"
    incarnated = "incarnated"
    hit = "hit"
    hitwall = "hitwall"
    hitjump = "hitjump"
    landing = "landing"
    landingfail = "landingfail"
    landingcatapult = "landingcatapult"
    landingrecover = "landingrecover"
    landingdamage = "landingdamage"
    landingdying = "landingdying"
    landinggrip = "landinggrip"
    landingtree = "landingtree"
    jumpmount = "jumpmount"
    fallin = "fallin"
    landingmount = "landingmount"
    soul = "soul"
    mountreception = "mountreception"
    changeridingspot = "changeridingspot"
    goingtomountstate = "goingtomountstate"
    mount = "mount"
    unmount = "unmount"
    flap = "flap"
    flystop = "flystop"
    flapfast = "flapfast"
    turn = "turn"
    turnfromspeed0 = "turnfromspeed0"
    turnfromspeed1 = "turnfromspeed1"
    turnfromspeed2 = "turnfromspeed2"
    turnfromspeed3 = "turnfromspeed3"
    jump = "jump"
    jumpoff = "jumpoff"
    doublejump = "doublejump"
    jumpcharging = "jumpcharging"
    jumpcharged = "jumpcharged"
    longjump = "longjump"
    bounce = "bounce"
    regenerate = "regenerate"
    drift = "drift"
    wait = "wait"
    chosen = "chosen"
    revive = "revive"
    revivemaskeffect = "revivemaskeffect"
    shakeoff = "shakeoff"
    convert = "convert"
    drop = "drop"
    landingdrop = "landingdrop"
    dropoff = "dropoff"
    start = "start"
    reachspeed3 = "reachspeed3"
    strafe = "strafe"
    strafeturn = "strafeturn"
    slide = "slide"
    slope = "slope"
    forceagainstslope = "forceagainstslope"
    patinate = "patinate"
    climb = "climb"
    call = "call"
    callanswer = "callanswer"
    scream = "scream"
    grab = "grab"
    grabbed = "grabbed"
    grabbedin = "grabbedin"
    grabbedout = "grabbedout"
    taunt = "taunt"
    sink = "sink"
    shoot = "shoot"
    reload = "reload"
    stop = "stop"
    rise = "rise"
    centrifugal = "centrifugal"
    climbedgehead = "climbedgehead"
    climbedgehips = "climbedgehips"
    climbedgefoot = "climbedgefoot"
    jumpedge = "jumpedge"
    catapult = "catapult"
    sleep = "sleep"
    head = "head"
    chest = "chest"
    ascendpurgatory = "ascendpurgatory"
    purgatory = "purgatory"
    stung = "stung"
    riderstance = "riderstance"
    drawweapon = "drawweapon"
    levitate = "levitate"
    levitatemove = "levitatemove"
    aim = "aim"
    wallrun = "wallrun"
    wallrunjump = "wallrunjump"
    wallrundrop = "wallrundrop"
    strongattackcharging = "strongattackcharging"
    strongattackcharged = "strongattackcharged"
    strongattack = "strongattack"
    aimcharge = "aimcharge"
    aimcharged = "aimcharged"
    aimflow = "aimflow"
    shootcharged = "shootcharged"
    shootchargedlight = "shootchargedlight"
    shootchargedmedium = "shootchargedmedium"
    shootchargedbig = "shootchargedbig"
    emptyshoot = "emptyshoot"
    attackstomp = "attackstomp"
    requestwait = "requestwait"
    requestheal = "requestheal"
    quadstandupin = "quadstandupin"
    standupin = "standupin"
    diguptreasure = "diguptreasure"
    swimin = "swimin"
    swimlanding = "swimlanding"
    duck = "duck"
    recover = "recover"
    happy = "happy"
    underground = "underground"
    spawn = "spawn"
    unspawn = "unspawn"
    dance = "dance"
    askstaffguide = "askstaffguide"
    hintfull = "hintfull"
    hintlight = "hintlight"
    hintnone = "hintnone"
    hatching = "hatching"
    dying = "dying"
    followerorder = "followerorder"
    ultimateattack = "ultimateattack"
    ultimateattacked = "ultimateattacked"
    parry = "parry"
    failingorder = "failingorder"
    settingrespawnplace = "settingrespawnplace"
    romlookat = "romlookat"
    emoteshame = "emoteshame"
    emotecrazy = "emotecrazy"
    emotetaunt = "emotetaunt"
    emoteproud = "emoteproud"
    emotemenace = "emotemenace"
    emotehello = "emotehello"
    emoteimpatience = "emoteimpatience"
    ActionMode_COUNT = "ActionMode_COUNT"


class ActionMode(Primitive[ActionModeEnum]):  # Enum
    def __init__(self, node):
        super(ActionMode, self).__init__(ActionModeEnum, node)
    schema_name = "ActionMode"
    def __call__(self, node):  # type: (EntityLibPy.Node) -> ActionMode
        return ActionMode(node)
    def set(self, val):  # type: (ActionModeEnum) -> None
        return self._node.set_string(val.value)
    def get(self):  # type: () -> T
        return self._item_type(self._node.value)




