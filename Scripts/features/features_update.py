import GCT
from time import sleep
import utils.math_utils as math_utils

global math_utils

global last_weapon_features_update, last_horse_features_update
last_weapon_features_update = 0
last_horse_features_update = 0


global get_player_weapon_last_impact_coords, rotation_to_direction, UpdateWeaponsFeatures

def get_player_weapon_last_impact_coords() -> list:
    import GCT
    import utils.GCT_utils as utils
    from threading import get_ident
    
    coords = [0.0, 0.0, 0.0]
    
    coords[0] = utils.Call(GCT.GetGlobalVariable("Features.dll"), "GetPlayerWeaponLastImpactCoordX", utils.ctypes.c_float, get_ident())
    coords[1] = utils.Call(GCT.GetGlobalVariable("Features.dll"), "GetPlayerWeaponLastImpactCoordY", utils.ctypes.c_float, get_ident())
    coords[2] = utils.Call(GCT.GetGlobalVariable("Features.dll"), "GetPlayerWeaponLastImpactCoordZ", utils.ctypes.c_float, get_ident())
    
    if not coords[0] and not coords[1] and not coords[2]:
        return None
    return coords

def rotation_to_direction(rot):
    import math
    
    radiansZ = math.radians(rot[2])
    radiansX = math.radians(rot[0])
    num = abs(math.cos(radiansX))
    
    direction = [0.0, 0.0, 0.0]
    direction[0] = -math.sin(radiansZ) * num
    direction[1] = math.cos(radiansZ) * num
    direction[2] = math.sin(radiansX)
    
    return direction

def UpdateWeaponsFeatures():
    from RDR2 import PLAYER, WEAPON, CAM, FIRE, MISC, PED, ENTITY
    
    if last_weapon_features_update >= 250:
        held_weapon = WEAPON._GET_PED_CURRENT_HELD_WEAPON(PLAYER.PLAYER_PED_ID())
        weapon_object = WEAPON._GET_PED_WEAPON_OBJECT(PLAYER.PLAYER_PED_ID(), True)
        
        if infinity_ammo_weapon:
            WEAPON.SET_PED_INFINITE_AMMO(PLAYER.PLAYER_PED_ID(), True, held_weapon)
        if infinity_ammo_clip_weapon:
            WEAPON._SET_PED_INFINITE_AMMO_CLIP(PLAYER.PLAYER_PED_ID(), True)
        if always_clean_weapon:
            if weapon_object:
                WEAPON._SET_WEAPON_DIRT(weapon_object, 0.0, True)
                WEAPON._SET_WEAPON_SOOT(weapon_object, 0.0, True)
                WEAPON._SET_WEAPON_DEGRADATION(weapon_object, 0.0)
    if last_horse_features_update >= 200:
        if always_clean_horse:
            horse = PED.GET_MOUNT(PLAYER.PLAYER_PED_ID())
            PED.CLEAR_PED_ENV_DIRT(horse)
        
    if GCT.GetGlobalVariable("feature_weapon_fire_ammo_enabled"):
        
        coords = get_player_weapon_last_impact_coords()
        if coords:
            FIRE.START_SCRIPT_FIRE(coords[0], coords[1], coords[2], 25, 1.0, True, "", 0.0, 0)
            FIRE.START_SCRIPT_FIRE(coords[0], coords[1], coords[2]-0.1, 25, 1.0, True, "", 0.0, 0)
            FIRE.START_SCRIPT_FIRE(coords[0], coords[1], coords[2]-0.5, 25, 1.0, True, "", 0.0, 0)
            FIRE.START_SCRIPT_FIRE(coords[0], coords[1], coords[2]-1.0, 25, 1.0, True, "", 0.0, 0)
    if GCT.GetGlobalVariable("feature_weapon_explosive_ammo_enabled"):
        coords = get_player_weapon_last_impact_coords()
        if coords:
            MISC.SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords[0]+0.2, coords[1], coords[2]+1.0, coords[0], coords[1], coords[2], 50, True, 0x7067E7A7, PLAYER.PLAYER_PED_ID(), True, False, 0xbf800000, False)
    if GCT.GetGlobalVariable("feature_weapon_rapid_fire_enabled"):
        if GCT.NativeCall(9555366875240188328, "bool", [PLAYER.PLAYER_PED_ID()]): # PED.IS_PED_SHOOTING(PLAYER.PLAYER_PED_ID())
            cam_coords = CAM.GET_GAMEPLAY_CAM_COORD()
            cam_rotation = CAM.GET_GAMEPLAY_CAM_ROT(2)
            cam_direction = rotation_to_direction(cam_rotation)
            
            startCoords = math_utils.SumVectors(cam_coords, math_utils.MultVector(cam_direction, 1.0))
            endCoords = math_utils.SumVectors(startCoords, math_utils.MultVector(cam_direction, 500.0))
            
            weapon_hash = WEAPON._GET_PED_CURRENT_HELD_WEAPON(PLAYER.PLAYER_PED_ID())
            
            while GCT.IsScriptsStillWorking():
                for _ in range(2):
                    GCT.NativeCall(1673108812380468058, "", [GCT.NativeCall(70382543660857, "long", []), True]) # DISABLE_PLAYER_FIRING(PLAYER.PLAYER_ID())
                    MISC.SHOOT_SINGLE_BULLET_BETWEEN_COORDS(startCoords[0], startCoords[1], startCoords[2], endCoords[0], endCoords[1], endCoords[2], 50, True, weapon_hash, PLAYER.PLAYER_PED_ID(), True, False, 0xbf800000, False)
                if not GCT.NativeCall(9555366875240188328, "bool", [PLAYER.PLAYER_PED_ID()]):
                    break
    if GCT.GetGlobalVariable("feature_godmode_godmode_enabled"):
        ENTITY.SET_ENTITY_INVINCIBLE(PLAYER.PLAYER_PED_ID(), True)
        
    if GCT.GetGlobalVariable("feature_godmode_autoheal_enabled"):
        if ENTITY.GET_ENTITY_HEALTH(PLAYER.PLAYER_PED_ID()) <= 100:
            ENTITY.SET_ENTITY_HEALTH(PLAYER.PLAYER_PED_ID(), 101, 0)
            
def update():
    import GCT
    import Game
    from RDR2 import PLAYER, WEAPON, CAM, FIRE, MISC, PED
    
    UpdateWeaponsFeatures()
        
def get_config_settings():
    import utils.config_utils as config_utils
    
    global infinity_ammo_weapon, infinity_ammo_clip_weapon, always_clean_weapon, always_clean_horse
    
    feature_settings = config_utils.get_feature_settings()
    
    infinity_ammo_weapon = feature_settings["WeaponOptions"]["InfinityAmmoWeapon"]
    infinity_ammo_clip_weapon = feature_settings["WeaponOptions"]["InfinityAmmoClipWeapon"]
    always_clean_weapon = feature_settings["WeaponOptions"]["AlwaysCleanWeapon"]
    always_clean_horse = feature_settings["HorseOptions"]["AlwaysCleanHorse"]

if __name__ == "__main__":
    get_config_settings()    

    while GCT.IsScriptsStillWorking():
        update()
        
        last_weapon_features_update += 1
        last_horse_features_update += 1
        if last_weapon_features_update > 250:
            last_weapon_features_update = 0
        if last_horse_features_update > 200:
            last_horse_features_update = 0
        time.sleep(0.01)