import time

import GCT
import Gamepad
from RDR2 import PLAYER, PED
from utils.player_utils import IsPlayerPlaying

global enable_noclip, enable_vehicle_noclip, disable_noclip, disable_vehicle_noclip

player_horse = 0
player_alpha = 0
player_proofs = None
noclip_active = False
noclip_in_vehicle = False
noclip_in_horse = False
speed = 1.0
speed_mult = 1.0
delay = 0.1

def enable_noclip():
    import GCT
    from RDR2 import PLAYER, ENTITY
    from enums.proofs import EntityProofs
    
    global noclip_active, speed
    
    player_ped = PLAYER.PLAYER_PED_ID()
        
    player_alpha = ENTITY.GET_ENTITY_ALPHA(player_ped)

    ENTITY.SET_ENTITY_VISIBLE(player_ped, False)
    ENTITY.SET_ENTITY_ALPHA(player_ped, 0, False)
    ENTITY.FREEZE_ENTITY_POSITION(player_ped, True)

    #proofs = EntityProofs(ENTITY._GET_ENTITY_PROOFS(player_ped))
    #player_proofs = proofs
    #proofs.bullet_proof = True
    #proofs.explosion_proof = True
    #proofs.collision_proof = True
    
    #ENTITY.SET_ENTITY_PROOFS(player_ped, proofs.get_proofs_bitset(), False)
    speed = 1.0

    noclip_active = True
    GCT.SetGlobalVariableValue("feature_noclip_noclip_enabled", 1)
    
def enable_horse_noclip(horse):
    import GCT
    from RDR2 import ENTITY
    global noclip_active, noclip_in_horse, player_horse, speed
    
    player_horse = horse
    
    ENTITY.FREEZE_ENTITY_POSITION(player_horse, True)
    
    speed = 1.0
    noclip_in_horse = True
    noclip_active = True
    GCT.SetGlobalVariableValue("feature_noclip_noclip_enabled", 1)
    
def enable_vehicle_noclip():
    from RDR2 import PED, ENTITY, PLAYER
    
    global GCT
    global noclip_active, noclip_in_vehicle
    
    vehicle = PED.GET_VEHICLE_PED_IS_IN(PLAYER.PLAYER_PED_ID(), True)

    ENTITY.SET_ENTITY_COLLISION(vehicle, False, False)
    ENTITY.FREEZE_ENTITY_POSITION(vehicle, True)

    speed = 2.0

    noclip_in_vehicle = True
    noclip_active = True
    GCT.SetGlobalVariableValue("feature_noclip_noclip_enabled", 1)

def disable_noclip():
    import GCT
    from RDR2 import PLAYER, ENTITY
    global noclip_active
    player_ped = PLAYER.PLAYER_PED_ID()

    ENTITY.SET_ENTITY_VISIBLE(player_ped, True)
    ENTITY.SET_ENTITY_ALPHA(player_ped, 255, True)
    ENTITY.RESET_ENTITY_ALPHA(player_ped)
    ENTITY.FREEZE_ENTITY_POSITION(player_ped, False)
    
    noclip_active = False
    GCT.SetGlobalVariableValue("feature_noclip_noclip_enabled", 0)
    player_horse = 0
    
def disable_horse_noclip():
    import GCT
    from RDR2 import ENTITY
    global noclip_active, noclip_in_horse
    
    ENTITY.FREEZE_ENTITY_POSITION(player_horse, False)
    ENTITY.SET_ENTITY_COLLISION(player_horse, True, True)
       
    noclip_in_horse = False
    noclip_active = False
    GCT.SetGlobalVariableValue("feature_noclip_noclip_enabled", 0)
    
def disable_vehicle_noclip():
    import GCT
    from RDR2 import PED, PLAYER, ENTITY
    global noclip_active, noclip_in_vehicle
    
    vehicle = PED.GET_VEHICLE_PED_IS_IN(PLAYER.PLAYER_PED_ID(), True)

    ENTITY.SET_ENTITY_COLLISION(vehicle, True, True)
    ENTITY.FREEZE_ENTITY_POSITION(vehicle, False)
    
    noclip_in_vehicle = False
    noclip_active = False
    GCT.SetGlobalVariableValue("feature_noclip_noclip_enabled", 0)

def on_tick():
    import math
    import GCT
    from RDR2 import PLAYER, ENTITY, PED, CAM, TASK
    import utils.math_utils as math_utils
    
    if noclip_in_horse:
        entity = player_horse
    else:
        entity = PLAYER.PLAYER_PED_ID()
    
    if ENTITY.IS_ENTITY_DEAD(entity):
        disable_noclip()
    else:
        left_stick_state = noclip_gamepad.get_left_stick_state()
        if left_stick_state:
            stick_x = left_stick_state['ThumbLX']
            stick_y = left_stick_state['ThumbLY']
        else:
            stick_x = 0.0
            stick_y = 0.0
        
        if noclip_in_vehicle:
            if PED.IS_PED_IN_ANY_VEHICLE(entity, False):
                vehicle = PED.GET_VEHICLE_PED_IS_IN(entity, True)
            else:
                disable_vehicle_noclip()
                return

            cam_rotation = CAM.GET_GAMEPLAY_CAM_ROT(2)
            coord = ENTITY.GET_ENTITY_COORDS(vehicle, True, True)
        
            # convert angles of rotation to radians.
            heading = math.radians(cam_rotation[2])
            pitch = math.radians(cam_rotation[0]) 

            forward = [ -math.sin(heading), math.cos(heading), math.sin(pitch) ]

            # Normalise the direction vector
            forward_magnitude = math.sqrt(math.pow(forward[0], 2) + math.pow(forward[1], 2) + math.pow(forward[2], 2))
            forward[0] /= forward_magnitude
            forward[1] /= forward_magnitude
            forward[2] /= forward_magnitude
            
            # Set the direction of movement
            move_vector = [0.0, 0.0, 0.0]

            if GCT.IsPressedKey(noclip_sprint_key) or gamepad_key == gamepad_noclip_sprint_key:
                speed_mult = 3.0
            else:
                speed_mult = 1.0
                
            
            if GCT.IsPressedKey(noclip_move_forward_key) or stick_y > 0:
                move_vector = math_utils.SumVectors(move_vector, math_utils.MultVector(forward, speed*speed_mult))
                
            if GCT.IsPressedKey(noclip_move_left_key) or stick_x < 0:
                left = [ -forward[1], forward[0], 0.0 ]
                move_vector = math_utils.SumVectors(move_vector, math_utils.MultVector(left, speed*speed_mult))
                
            if GCT.IsPressedKey(noclip_move_backward_key) or stick_y < 0:
                move_vector = math_utils.SumVectors(move_vector, math_utils.MultVector(forward, (speed * 1.5) * speed_mult))
                move_vector = math_utils.SubtractVectors(move_vector, math_utils.MultVector(move_vector, (speed * 1.5) * speed_mult))
                
            if GCT.IsPressedKey(noclip_move_right_key) or stick_x > 0:
                right = [ forward[1], -forward[0], 0.0 ]
                move_vector = math_utils.SumVectors(move_vector, math_utils.MultVector(right, speed*speed_mult))
                
            if GCT.IsPressedKey(noclip_move_up_key) or gamepad_key == gamepad_noclip_move_up_key:
                move_vector[2] = move_vector[2] + (speed*speed_mult / 2.0)
                
            if GCT.IsPressedKey(noclip_move_down_key) or gamepad_key == gamepad_noclip_move_down_key:
                move_vector[2] = move_vector[2] - (speed*speed_mult / 2.0)

            if GCT.IsPressedKey(noclip_enter_exit_vehicle_key) or gamepad_key == gamepad_noclip_enter_exit_vehicle_key:
                disable_vehicle_noclip()

                TASK.CLEAR_PED_TASKS(PLAYER.PLAYER_PED_ID(), True, True)

                enable_noclip()
            
            # Updating vehicle coordinates
            coord = math_utils.SumVectors(coord, move_vector)

            ENTITY.SET_ENTITY_COORDS_NO_OFFSET(vehicle, coord[0], coord[1], coord[2], True, True, True)
            ENTITY.SET_ENTITY_ROTATION(vehicle, cam_rotation[0], cam_rotation[1], cam_rotation[2], 2, True)
        else:
            cam_rotation = CAM.GET_GAMEPLAY_CAM_ROT(2)
            coord = ENTITY.GET_ENTITY_COORDS(entity, True, True)
            
            # convert angles of rotation to radians.
            heading = math.radians(cam_rotation[2])
            pitch = math.radians(cam_rotation[0])
            
            forward = [ -math.sin(heading), math.cos(heading), math.sin(pitch) ]
            
            # Normalise the direction vector
            forward_magnitude = math.sqrt(math.pow(forward[0], 2) + math.pow(forward[1], 2) + math.pow(forward[2], 2))
            forward[0] /= forward_magnitude
            forward[1] /= forward_magnitude
            forward[2] /= forward_magnitude
            
            # Set the direction of movement
            move_vector = [0.0, 0.0, 0.0]
            
            if GCT.IsPressedKey(noclip_sprint_key) or gamepad_key == gamepad_noclip_sprint_key:
                speed_mult = 3.0
            else:
                speed_mult = 1.0
            
            if GCT.IsPressedKey(noclip_move_forward_key) or stick_y > 0:
                move_vector = math_utils.SumVectors(move_vector, math_utils.MultVector(forward, speed*speed_mult))
            
            if GCT.IsPressedKey(noclip_move_left_key) or stick_x < 0:
                left = [ -forward[1], forward[0], 0.0 ] # вектор влево
                move_vector = math_utils.SumVectors(move_vector, math_utils.MultVector(left, speed*speed_mult))
            
            if GCT.IsPressedKey(noclip_move_backward_key) or stick_y < 0:
                move_vector = math_utils.SumVectors(move_vector, math_utils.MultVector(forward, (speed * 1.5) * speed_mult))
                move_vector = math_utils.SubtractVectors(move_vector, math_utils.MultVector(move_vector, (speed * 1.5) * speed_mult))
            
            if GCT.IsPressedKey(noclip_move_right_key) or stick_x > 0:
                right = [ forward[1], -forward[0], 0.0 ] # вектор вправо
                move_vector = math_utils.SumVectors(move_vector, math_utils.MultVector(right, speed*speed_mult))
                
            if GCT.IsPressedKey(noclip_move_up_key) or gamepad_key == gamepad_noclip_move_up_key:
                move_vector[2] = move_vector[2] + (speed*speed_mult / 2.0)
            
            if GCT.IsPressedKey(noclip_move_down_key) or gamepad_key == gamepad_noclip_move_down_key:
                move_vector[2] = move_vector[2] - (speed*speed_mult / 2.0)
            
            if GCT.IsPressedKey(noclip_enter_exit_vehicle_key) or gamepad_key == gamepad_noclip_enter_exit_vehicle_key:
                pass
            
            # Updating player coordinates
            coord = math_utils.SumVectors(coord, move_vector)

            ENTITY.SET_ENTITY_COORDS_NO_OFFSET(entity, coord[0], coord[1], coord[2], True, True, True)
            if not noclip_in_horse:
                TASK.CLEAR_PED_TASKS_IMMEDIATELY(entity, True, True)
            if noclip_in_horse:
                ENTITY.SET_ENTITY_ROTATION(entity, cam_rotation[0], cam_rotation[1], cam_rotation[2], 2, True)
                #ENTITY.SET_ENTITY_HEADING(entity, math.degrees(heading))
            #ENTITY.SET_ENTITY_VISIBLE(entity, False)
    speed_mult = 1.0

def initialize_settings():
    import GCT
    import utils.config_utils as config_utils
    
    global noclip_turn, noclip_move_forward_key, noclip_move_backward_key, noclip_move_left_key, noclip_move_right_key, noclip_move_up_key, noclip_move_down_key, noclip_sprint_key, noclip_enter_exit_vehicle_key, gamepad_noclip_turn, gamepad_noclip_move_up_key, gamepad_noclip_move_down_key, gamepad_noclip_sprint_key, gamepad_noclip_enter_exit_vehicle_key

    feature_settings = config_utils.get_feature_settings()

    noclip_turn = GCT.ConvertStringToKeyCode(feature_settings["Hotkeys"]["NoclipKey"])
    noclip_move_forward_key = GCT.ConvertStringToKeyCode(feature_settings["Hotkeys"]["NoclipMoveForwardKey"])
    noclip_move_backward_key = GCT.ConvertStringToKeyCode(feature_settings["Hotkeys"]["NoclipMoveBackwardKey"])
    noclip_move_left_key = GCT.ConvertStringToKeyCode(feature_settings["Hotkeys"]["NoclipMoveLeftKey"])
    noclip_move_right_key = GCT.ConvertStringToKeyCode(feature_settings["Hotkeys"]["NoclipMoveRightKey"])
    noclip_move_up_key = GCT.ConvertStringToKeyCode(feature_settings["Hotkeys"]["NoclipMoveUpKey"])
    noclip_move_down_key = GCT.ConvertStringToKeyCode(feature_settings["Hotkeys"]["NoclipMoveDownKey"])
    noclip_sprint_key = GCT.ConvertStringToKeyCode(feature_settings["Hotkeys"]["NoclipSprintKey"])
    noclip_enter_exit_vehicle_key = GCT.ConvertStringToKeyCode(feature_settings["Hotkeys"]["NoclipEnterExitVehicleKey"])
    
    gamepad_noclip_turn = feature_settings["Hotkeys"]["GamepadNoclipKey"]
    gamepad_noclip_move_up_key = feature_settings["Hotkeys"]["GamepadNoclipMoveUpKey"]
    gamepad_noclip_move_down_key = feature_settings["Hotkeys"]["GamepadNoclipMoveDownKey"]
    gamepad_noclip_sprint_key = feature_settings["Hotkeys"]["GamepadNoclipSprintKey"]
    gamepad_noclip_enter_exit_vehicle_key = feature_settings["Hotkeys"]["GamepadNoclipEnterExitVehicleKey"]
    
    GCT.RegisterGlobalVariable("feature_noclip_noclip_enabled", 0)

initialize_settings()

global gamepad_key, noclip_gamepad

noclip_gamepad = Gamepad.Gamepad()

while GCT.IsScriptsStillWorking():
    gamepad_key = noclip_gamepad.get_pressed_key()
    
    if gamepad_key == gamepad_noclip_turn:
        for _ in range(50):
            gamepad_key = noclip_gamepad.get_pressed_key()
            if gamepad_key == gamepad_noclip_turn:
                break
            time.sleep(0.01)
    if GCT.IsPressedKey(noclip_turn) or gamepad_key == gamepad_noclip_turn:
        if not GCT.GetGlobalVariable("feature_fast_run_fast_run_enabled") and not GCT.GetGlobalVariable("feature_fast_free_cam_free_cam_enabled") and IsPlayerPlaying():
            if not noclip_active:
                if PED.IS_PED_IN_ANY_VEHICLE(PLAYER.PLAYER_PED_ID(), False):
                    enable_vehicle_noclip()
                else:
                    horse = PED.GET_MOUNT(PLAYER.PLAYER_PED_ID())
                    if horse:
                        enable_horse_noclip(horse)
                    else:
                        enable_noclip()
                delay = 0.0
            else:
                if noclip_in_vehicle:
                    disable_vehicle_noclip()
                elif noclip_in_horse:
                    disable_horse_noclip()
                else:
                    disable_noclip()
                delay = 0.07
    if noclip_active:
        on_tick()

    time.sleep(delay)