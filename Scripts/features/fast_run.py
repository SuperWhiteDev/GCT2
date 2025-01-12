import GCT
import Gamepad
import time
from utils.player_utils import IsPlayerPlaying

global enable_fast_run, disable_fast_run

fast_run_active = False
delay = 0.1

def enable_fast_run():
    import GCT
    from RDR2 import PED, PLAYER, UITUTORIAL
    from time import sleep
    
    global fast_run_active, horse_speed_mult, player_speed_mult

    horse_speed_mult = 1.9854
    player_speed_mult = 2.8215
    
    PED.SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(PLAYER.PLAYER_PED_ID(), False)
    PED.SET_PED_CAN_RAGDOLL(PLAYER.PLAYER_PED_ID(), False)
    
    horse = PED.GET_MOUNT(PLAYER.PLAYER_PED_ID())
    PED.SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(horse, False)
    PED.SET_PED_CAN_RAGDOLL(horse, False)
    
    UITUTORIAL._UITUTORIAL_SET_RPG_ICON_VISIBILITY(1, 3)
    
    fast_run_gamepad.send_vibration(0.5, True, True)
    sleep(0.3)
    fast_run_gamepad.send_vibration(0.0, True, True)

    fast_run_active = True
    GCT.SetGlobalVariableValue("feature_fast_run_fast_run_enabled", 1)
    
def disable_fast_run():
    import GCT
    from RDR2 import PED, PLAYER, UITUTORIAL
    global fast_run_active
    
    PED.SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(PLAYER.PLAYER_PED_ID(), True)
    PED.SET_PED_CAN_RAGDOLL(PLAYER.PLAYER_PED_ID(), True)
    
    horse = PED.GET_MOUNT(PLAYER.PLAYER_PED_ID())
    PED.SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(horse, True)
    PED.SET_PED_CAN_RAGDOLL(horse, True)
    
    UITUTORIAL._UITUTORIAL_SET_RPG_ICON_VISIBILITY(1, 0)
    
    fast_run_active = False
    GCT.SetGlobalVariableValue("feature_fast_run_fast_run_enabled", 0)
def on_tick():
    import math
    import GCT
    from RDR2 import PED, PLAYER, ENTITY
    import utils.math_utils as math_utils
    from enums.bone import HorseBoneIndex
    
    horse = PED.GET_MOUNT(PLAYER.PLAYER_PED_ID())
    if horse:
        entity = horse
        speed_mult = horse_speed_mult
    else:
        entity = PLAYER.PLAYER_PED_ID()
        speed_mult = player_speed_mult
    
    speed = ENTITY.GET_ENTITY_SPEED(entity)
    if (GCT.IsPressedKey(fast_run_move_forward_key) or fast_run_gamepad_key == gamepad_fast_run_move_forward_key) and speed > 3.0:
        if not ENTITY.IS_ENTITY_IN_AIR(entity, 1):
            if horse:
                ENTITY.APPLY_FORCE_TO_ENTITY(entity, 0, 0.0, speed_mult*(10**3), 0.0, 0.0, 0.0, 0.0, HorseBoneIndex["MH_L_FrontHoof"], True, True, True, True, True)
                ENTITY.APPLY_FORCE_TO_ENTITY(entity, 0, 0.0, speed_mult*(10**3), 0.0, 0.0, 0.0, 0.0, HorseBoneIndex["MH_R_FrontHoof"], True, True, True, True, True)
            else:    
                ENTITY.APPLY_FORCE_TO_ENTITY(entity, 0, 0.0, speed_mult*(10**3), 0.0, 0.0, 0.0, 0.0, HorseBoneIndex["IK_L_Foot"], True, True, True, True, True)
                ENTITY.APPLY_FORCE_TO_ENTITY(entity, 0, 0.0, speed_mult*(10**3), 0.0, 0.0, 0.0, 0.0, HorseBoneIndex["IK_R_Foot"], True, True, True, True, True)

def initialize_settings():
    import GCT
    import utils.config_utils as config_utils
    
    global fast_run_turn, fast_run_move_forward_key, gamepad_fast_run_turn, gamepad_fast_run_move_forward_key

    feature_settings = config_utils.get_feature_settings()

    fast_run_turn = GCT.ConvertStringToKeyCode(feature_settings["Hotkeys"]["FastRunKey"])
    fast_run_move_forward_key = GCT.ConvertStringToKeyCode(feature_settings["Hotkeys"]["FastRunMoveForwardKey"])
    gamepad_fast_run_turn = feature_settings["Hotkeys"]["GamepadFastRunKey"]
    gamepad_fast_run_move_forward_key = feature_settings["Hotkeys"]["GamepadFastRunMoveForwardKey"]
    
    GCT.RegisterGlobalVariable("feature_fast_run_fast_run_enabled", 0)

initialize_settings()

global fast_run_gamepad_key, fast_run_gamepad

fast_run_gamepad = Gamepad.Gamepad()

while GCT.IsScriptsStillWorking():
    fast_run_gamepad_key = fast_run_gamepad.get_pressed_key()

    if GCT.IsPressedKey(fast_run_turn) or fast_run_gamepad_key == gamepad_fast_run_turn:
        skip_input = False
        if fast_run_gamepad_key == gamepad_fast_run_turn:
            time.sleep(0.1)
            fast_run_gamepad_key = fast_run_gamepad.get_pressed_key()
            if fast_run_gamepad_key == gamepad_fast_run_turn:
                skip_input = True
            
        if not skip_input and not GCT.GetGlobalVariable("feature_noclip_noclip_enabled") and not GCT.GetGlobalVariable("feature_fast_free_cam_free_cam_enabled") and IsPlayerPlaying():
            if not fast_run_active:
                enable_fast_run()
                delay = 0.0
            else:
                disable_fast_run()
                delay = 0.07
    if fast_run_active:
        on_tick()

    time.sleep(delay)
