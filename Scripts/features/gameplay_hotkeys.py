import time

import GCT
import Gamepad
from RDR2 import PLAYER, PED

def HealEntity(entity, boost_cores = False):
    from RDR2 import ATTRIBUTE, ENTITY
    
    if boost_cores:
        ATTRIBUTE.ENABLE_ATTRIBUTE_OVERPOWER(entity, 0, 900.0, 1)
        ATTRIBUTE.ENABLE_ATTRIBUTE_OVERPOWER(entity, 1, 900.0, 1)
        ATTRIBUTE.ENABLE_ATTRIBUTE_OVERPOWER(entity, 2, 900.0, 1)

        ATTRIBUTE._ENABLE_ATTRIBUTE_CORE_OVERPOWER(entity, 0, 100.0, 1)
        ATTRIBUTE._ENABLE_ATTRIBUTE_CORE_OVERPOWER(entity, 1, 100.0, 1)
        ATTRIBUTE._ENABLE_ATTRIBUTE_CORE_OVERPOWER(entity, 2, 100.0, 1)
    ENTITY.SET_ENTITY_HEALTH(entity, ENTITY.GET_ENTITY_MAX_HEALTH(entity, True), 0)
    
    
    
def initialize_settings():
    import utils.config_utils as config_utils
    
    global fast_heal_player_key, gamepad_fast_heal_player_key
    
    feature_settings = config_utils.get_feature_settings()

    fast_heal_player_key = GCT.ConvertStringToKeyCode(feature_settings["Hotkeys"]["FastHealPlayerKey"])
    
    gamepad_fast_heal_player_key = feature_settings["Hotkeys"]["GamepadFastHealPlayerKey"]

initialize_settings()

global gameplay_hotkeys_gamepad
gameplay_hotkeys_gamepad = Gamepad.Gamepad()

while GCT.IsScriptsStillWorking():
    gamepad_key = gameplay_hotkeys_gamepad.get_pressed_key()
    
    action1 = GCT.IsDoubleClickedKey(fast_heal_player_key)
    if action1 == 2:
        HealEntity(PLAYER.PLAYER_PED_ID(), True)
        horse = PED.GET_MOUNT(PLAYER.PLAYER_PED_ID())
        if horse:
            HealEntity(horse, True)
    elif action1 == 1:
        HealEntity(PLAYER.PLAYER_PED_ID())
        horse = PED.GET_MOUNT(PLAYER.PLAYER_PED_ID())
        if horse:
            HealEntity(horse)
            
    if gamepad_key == gamepad_fast_heal_player_key:
        double_clicked = False
        for _ in range(50):
            gamepad_key = gameplay_hotkeys_gamepad.get_pressed_key()
            if gamepad_key == gamepad_fast_heal_player_key:
                double_clicked = True
                break
            time.sleep(0.01)
        if double_clicked:
            HealEntity(PLAYER.PLAYER_PED_ID(), True)
            horse = PED.GET_MOUNT(PLAYER.PLAYER_PED_ID())
            if horse:
                HealEntity(horse, True)
        else:
            HealEntity(PLAYER.PLAYER_PED_ID())
            horse = PED.GET_MOUNT(PLAYER.PLAYER_PED_ID())
            if horse:
                HealEntity(horse)
    time.sleep(0.06)