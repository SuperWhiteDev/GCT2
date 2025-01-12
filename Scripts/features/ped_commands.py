import GCT

global peds_list, control_ped, set_ped_as_bodyguard
peds_list = {  }

def set_ped_as_bodyguard(bodyguard, playerPed):
    from RDR2 import ENTITY, PED, PLAYER, TASK, WEAPON, MISC
    from enums.weapons import weapons
    from random import choice
    
    # Stops the current action of the ped
    TASK.CLEAR_PED_TASKS(bodyguard, True, True)
    TASK.CLEAR_PED_SECONDARY_TASK(bodyguard)
    
    # Sets a player as a leader in his own group
    player_ped_group = PED.GET_PED_GROUP_INDEX(playerPed)
    PED.SET_PED_AS_GROUP_LEADER(PLAYER.PLAYER_PED_ID(), player_ped_group, True)
    
    # Adds a ped to the player's group
    PED.SET_PED_RELATIONSHIP_GROUP_HASH(bodyguard, 0xB5A1D680)
    PED.SET_GROUP_SEPARATION_RANGE(player_ped_group, 400.0)
    PED.SET_GROUP_FORMATION_SPACING(player_ped_group, 1.5, -1.0, -1.0)
    PED.SET_PED_AS_GROUP_MEMBER(bodyguard, player_ped_group)
    # Sets a flag that the ped will never leave player group
    PED.SET_PED_CONFIG_FLAG(bodyguard, 279, True)
    PED.SET_PED_CONFIG_FLAG(bodyguard, 569, False)

    # Sets other settings for the bodyguard
    PED.SET_PED_CAN_RAGDOLL(bodyguard, False)
    PED.SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(bodyguard, False)
    PED.SET_PED_COMBAT_RANGE(bodyguard, 500)
    PED.SET_PED_COMBAT_ABILITY(bodyguard, 2)
    PED.SET_PED_COMBAT_MOVEMENT(bodyguard, 2)
    PED.SET_PED_COMBAT_ATTRIBUTES(bodyguard, 17, False)
    PED.SET_PED_COMBAT_ATTRIBUTES(bodyguard, 113, True)
    PED.SET_PED_COMBAT_ATTRIBUTES(bodyguard, 46, True)
    PED.SET_PED_COMBAT_ATTRIBUTES(bodyguard, 58, True)
    PED.SET_PED_ACCURACY(bodyguard, 100)
    PED.SET_PED_FIRING_PATTERN(bodyguard, 0xC6EE6B4C)
    PED.SET_PED_SHOOT_RATE(bodyguard, 200)
    PED.SET_PED_KEEP_TASK(bodyguard, True)
    
    bodyguard_invincible = GCT.Input("Make the bodyguard invincible? [Y/n]: ", True)
    if is_bodyguard_invincible == "y":
        ENTITY.SET_ENTITY_INVINCIBLE(bodyguard, True)
    
    give_bodyguard_weapon = GCT.Input("You want to give bodyguard the weapon? [Y/n]: ", True)
    if give_bodyguard_weapon == "y":
        options = [ "Random", "Custom" ]
        option = GCT.InputFromList("Enter the weapon you want to give to the bodyguard: ", options)

        if option == 0:
            first_weapons = [weapons["weapon_rifle_springfield"], weapons["weapon_sniperrifle_carcano"], weapons["weapon_sniperrifle_rollingblock"], weapons["weapon_shotgun_semiauto"], weapons["weapon_shotgun_pump"]]
            second_weapons = [weapons["weapon_pistol_m1899"], weapons["weapon_pistol_mauser"], weapons["weapon_pistol_semiauto"], weapons["weapon_repeater_winchester"]]
            grenades = [weapons["weapon_thrown_dynamite"], weapons["weapon_thrown_molotov"]]

            primary_weapon = choice(first_weapons)
            secondary_weapon = choice(second_weapons)

            WEAPON.GIVE_DELAYED_WEAPON_TO_PED(bodyguard, primary_weapon, 100, True, 0x2cd419dc)
            WEAPON.GIVE_DELAYED_WEAPON_TO_PED(bodyguard, secondary_weapon, 100, True, 0x2CD419DC)
            WEAPON.GIVE_DELAYED_WEAPON_TO_PED(bodyguard, choice(grenades), 100, True, 0x2CD419DC)

            WEAPON.SET_CURRENT_PED_WEAPON(bodyguard, primary_weapon, True, 0, False, False)
            WEAPON.SET_CURRENT_PED_WEAPON(bodyguard, secondary_weapon, True, 2, False, False)
        elif option == 1:
            first_weapon = MISC.GET_HASH_KEY(GCT.Input("Enter weapon(https://github.com/femga/rdr3_discoveries/blob/master/weapons/weapons.lua): ", False))

            WEAPON.GIVE_DELAYED_WEAPON_TO_PED(bodyguard, first_weapon, 100, True, 0x2CD419DC)
            WEAPON.SET_CURRENT_PED_WEAPON(bodyguard, first_weapon, True, 0, False, False)

    PED.SET_PED_KEEP_TASK(bodyguard, True)

def view_peds_list():
    from utils.network_utils import DeleteNetPed, RegisterAsNetwork
    from RDR2 import ENTITY, PED
    
    ped_ids = []
    models = []
    
    for ped_id, model in peds_list.items():
        ped_ids.append(ped_id)
        models.append(model)
        
    if len(ped_ids) != 0:
        ped_id = GCT.InputFromList("Choose the ped you want to interact with: ", models)
    
        if ped_id != -1:
            ped = ped_ids[ped_id]
        
            print(f"The ped ID of the selected ped is {ped}")

            options = [ "Control ped", "Clone ped", "Delete" ]
            option = GCT.InputFromList("Choose what you want to: ", options)

            if option == 0:
                control_ped(ped)
            elif option == 1:
                cloned_ped = PED.CLONE_PED(ped, False, False, True)
                RegisterAsNetwork(cloned_ped)
                
                peds_list[cloned_ped] = models[ped_id]
            elif option == 2:
                DeleteNetPed(ped)

                if not ENTITY.DOES_ENTITY_EXIST(ped):
                    peds_list.pop(ped)
    else:
        print("The list of created peds is empty")


def add_ped_to_ped_list():
    from RDR2 import ENTITY
    
    ped = int(GCT.Input("Enter ped handle: ", False))
    
    if not ped and not ENTITY.DOES_ENTITY_EXIST(ped):
        GCT.DisplayError(False, "Uncorrect input")
    else:
        peds_list[ped] = "UNKNOWN"
        
def control_ped(ped):
    from RDR2 import ENTITY, PLAYER, PED, VEHICLE, TASK, STREAMING, MAP, MISC, ATTRIBUTE
    from utils.network_utils import RequestControlOf
    from utils.map_utils import GetWaypointCoords
    from enums.task_flags import EnterExitVehicleFlags
    from enums.blips import blip_styles
    from time import sleep
    
    options = [ "Go to", "Drive to", "Stop driving", "Make angry", "Make friendly", "Make come to vehicle", "Make bodyguard", "Freeze ped", "Set action", "Play animation", "Change outfit", "Set invincible", "Seat to", "Heal", "Fill stats", "Kill", "Mark" ]
    option = GCT.InputFromList("Choose what you want to: ", options)

    RequestControlOf(ped)
    if option == 0:
        options = [ "Waypoint", "Local player", "Custom" ]
        option = GCT.InputFromList("Choose where you want the ped to go: ", options)

        if option == 0:
            coords = GetWaypointCoords()
            if not coords:
                print("Please choose a waypoint first")
                return
            TASK.TASK_GO_STRAIGHT_TO_COORD(ped, coords[0], coords[1], coords[2], 2.0, 0, 0.0, 0.0, 0)
        elif option == 1:
            TASK.TASK_GO_TO_ENTITY(ped, PLAYER.PLAYER_PED_ID(), -1, -1, 1.0, 0.0, 0)
        elif option == 2:
            x = float(GCT.Input("Enter X coord: ", False))
            y = float(GCT.Input("Enter Y coord: ", False))
            z = float(GCT.Input("Enter Z coord: ", False))
            
            TASK.TASK_SMART_FLEE_COORD(ped, x, y, z, -1, -1, 4, 1.0)
    elif option == 1:
        options = [ "Waypoint", "Local player", "Custom" ]
        option = GCT.InputFromList("Choose where you want the ped to go: ", options)

        if option == 0:
            coords = GetWaypointCoords()
            if not coords:
                print("Please choose a waypoint first")
                return
            
            veh = PED.GET_VEHICLE_PED_IS_IN(ped, True)
            veh_model = ENTITY.GET_ENTITY_MODEL(veh)
            
            speed = VEHICLE.GET_VEHICLE_ESTIMATED_MAX_SPEED(veh)
            if speed < 40.0:
                speed = 40.0
            
            TASK.TASK_VEHICLE_DRIVE_TO_COORD(ped, veh, coords[0], coords[1], coords[2], speed, 262204, veh_model, 0, 4.0, -1.0)
        elif option == 1:
            coords = ENTITY.GET_ENTITY_COORDS(PLAYER.PLAYER_PED_ID(), True, True)
            
            veh = PED.GET_VEHICLE_PED_IS_IN(ped, True)
            veh_model = ENTITY.GET_ENTITY_MODEL(veh)
            
            speed = VEHICLE.GET_VEHICLE_ESTIMATED_MAX_SPEED(veh)
            if speed < 40.0:
                speed = 40.0
            
            TASK.TASK_VEHICLE_DRIVE_TO_COORD(ped, veh, coords[0], coords[1], coords[2], speed, 262204, veh_model, 0, 4.0, -1.0)
        elif option == 2:
            x = float(GCT.Input("Enter X coord: ", False))
            y = float(GCT.Input("Enter Y coord: ", False))
            z = float(GCT.Input("Enter Z coord: ", False))
            
            veh = PED.GET_VEHICLE_PED_IS_IN(ped, True)
            veh_model = ENTITY.GET_ENTITY_MODEL(veh)
            
            speed = VEHICLE.GET_VEHICLE_ESTIMATED_MAX_SPEED(veh)
            if speed < 40.0:
                speed = 40.0
            
            TASK.TASK_VEHICLE_DRIVE_TO_COORD(ped, veh, x, y, z, speed, 262204, veh_model, 0, 4.0, -1.0)
    elif option == 2:
        veh = PED.GET_VEHICLE_PED_IS_IN(ped, True)
        
        TASK.CLEAR_PED_TASKS_IMMEDIATELY(ped, True, True)
        PED.SET_PED_INTO_VEHICLE(ped, veh, -1)
    elif option == 3:
        TASK.TASK_COMBAT_HATED_TARGETS_AROUND_PED(ped, 10000.0, 0, 0)
        PED.SET_PED_KEEP_TASK(ped, True)
    elif option == 4:
        player_ped_group = PED.GET_PED_GROUP_INDEX(PLAYER.PLAYER_PED_ID())
        PED.SET_PED_AS_GROUP_MEMBER(ped, player_ped_group)
    elif option == 5:
        veh = PED.GET_VEHICLE_PED_IS_IN(PLAYER.PLAYER_PED_ID(), True)
        if veh:
            TASK.TASK_ENTER_VEHICLE(ped, veh, 20000, -2, 1.0, EnterExitVehicleFlags["WILL_SHOOT_AT_TARGET_PEDS"] | EnterExitVehicleFlags["WARP_IF_DOOR_IS_BLOCKED"] | EnterExitVehicleFlags["RESUME_IF_INTERRUPTED"], 0) 
        mount = PED.GET_MOUNT(PLAYER.PLAYER_PED_ID())
        if mount:
            TASK.TASK_MOUNT_ANIMAL(ped, mount, 20000, -2, 1.0, EnterExitVehicleFlags["WILL_SHOOT_AT_TARGET_PEDS"] | EnterExitVehicleFlags["RESUME_IF_INTERRUPTED"], 0, 0)
        PED.SET_PED_KEEP_TASK(ped, True)
    elif option == 6:
        set_ped_as_bodyguard(ped, PLAYER.PLAYER_PED_ID())
    elif option == 7:
        freeze_ped = GCT.Input("You want to freeze the ped? [Y/n]: ", True)
        if freeze_ped == "y":
            TASK.CLEAR_PED_TASKS_IMMEDIATELY(ped, False, False)
            ENTITY.FREEZE_ENTITY_POSITION(ped, True)
        elif freeze_ped == "n":
            ENTITY.FREEZE_ENTITY_POSITION(ped, False)
    elif option == 8:
        actions = [ "Lean Back Wall", "Guard With Lantern", "Dancing(Female only)", "Drinking Coffee", "Sit Drinking Coffee", "Sleeping", "Stop Action" ]
        action_names = [ "WORLD_HUMAN_LEAN_BACK_WALL", "WORLD_HUMAN_GUARD_LANTERN_NERVOUS", "WORLD_HUMAN_DANCING", "WORLD_HUMAN_COFFEE_DRINK", "WORLD_HUMAN_SIT_GROUND_COFFEE_DRINK",
                         "WORLD_HUMAN_SLEEP_GROUND_ARM" ]
        action_condition = [ "WORLD_HUMAN_LEAN_BACK_WALL_MALE_D", "WORLD_HUMAN_GUARD_LANTERN_NERVOUS_MALE_B", "WORLD_HUMAN_DANCING_FEMALE_A", "WORLD_HUMAN_COFFEE_DRINK_MALE_A",
                             "WORLD_HUMAN_SIT_GROUND_COFFEE_DRINK_FEMALE_A", "WORLD_HUMAN_SLEEP_GROUND_ARM_FEMALE_A" ]
        action = GCT.InputFromList("Choose an action for the ped: ", actions)

        if action == 6:
            TASK.CLEAR_PED_TASKS_IMMEDIATELY(ped, True, False)
        else:
            TASK.TASK_START_SCENARIO_IN_PLACE_HASH(ped, MISC.GET_HASH_KEY(action_names[action]), -1, True, MISC.GET_HASH_KEY(action_condition[action]), ENTITY.GET_ENTITY_HEADING(ped), True)
    elif option == 9:
        iters = 0
        animations = [ "Drunk uncle", "Kill player", "Pick up an item", "Stop animation" ]
        animationNames = [ "action_uncle", "agitated_fast_kill_player", "base" ]
        animationDicts = [ "cnv_camp@rcbch@mus@ccabijck_sng1_never_get_drunk", "creatures_mammal@cow@agitated@dead", "script_common@town_secrets@razor_box_pickup" ]
        animation = GCT.InputFromList("Choose an animation for the ped: ", animations)

        if animation == 3:
            TASK.CLEAR_PED_TASKS_IMMEDIATELY(ped, True, False)
            TASK.CLEAR_PED_SECONDARY_TASK(ped)
        else:
            STREAMING.REQUEST_ANIM_DICT(animationDicts[animation])
            while not STREAMING.HAS_ANIM_DICT_LOADED(animationDicts[animation]) and iters < 50:
                iters = iters + 1
                sleep(0.001)
    
            TASK.TASK_PLAY_ANIM(ped, animationDicts[animation], animationNames[animation], 1.0, 1.0, -1, 127, 0.0, False, 0, False, "", 0)
    elif option == 10:
        num_outfits = PED.GET_NUM_META_PED_OUTFITS(ped)
    
        outfit = int(GCT.Input(f"Enter an outfit index in the range 0 to {num_outfits}: ", False))
    
        if outfit > -1 and outfit < num_outfits:
            PED._EQUIP_META_PED_OUTFIT_PRESET(ped, outfit, True) 
        else:
            GCT.DisplayError(False, "Uncorrect input")
    elif option == 11:
        ped_invincible = GCT.Input("Set the ped invincible? [Y/n]: ", True)
        if ped_invincible == "y":
            ENTITY.SET_ENTITY_INVINCIBLE(ped, True)
        elif ped_invincible == "n":
            ENTITY.SET_ENTITY_INVINCIBLE(ped, False)
    elif option == 12:
        
        seats = [ "Driver seat", "Available passenger seat", "Custom" ]
        seat = GCT.InputFromList("Choose where you want to seat the ped in the ped vehicle: ", seats)

        veh = PED.GET_VEHICLE_PED_IS_IN(ped, True)
        horse = PED.GET_MOUNT(PLAYER.PLAYER_PED_ID())
        if veh:
            if seat == 0:
                driver = VEHICLE.GET_PED_IN_VEHICLE_SEAT(veh, -1)
                PED.SET_PED_INTO_VEHICLE(driver, veh, -2)
                PED.SET_PED_INTO_VEHICLE(ped, veh, -1)
                PED.SET_PED_INTO_VEHICLE(driver, veh, -2)
            elif seat == 1:
                PED.SET_PED_INTO_VEHICLE(ped, veh, -2)
            elif seat == 2:
                seat_index = int(GCT.Input("Enter the seat index: ", False))
                
                if seat_index:
                    passenger = VEHICLE.GET_PED_IN_VEHICLE_SEAT(veh, seat_index)
                    PED.SET_PED_INTO_VEHICLE(passenger, veh, -2)
                    PED.SET_PED_INTO_VEHICLE(ped, veh, seat_index)
                    PED.SET_PED_INTO_VEHICLE(passenger, veh, -2)
        elif horse:
            mount_instantly = GCT.Input("You want choosen ped to sit on your horse instantly? [Y/n]: ", True)
            if mount_instantly == "y":
                mount_instantly = True
            else:
                mount_instantly = False
                
            if seat == 0:
                if mount_instantly:
                    PED.SET_PED_ONTO_MOUNT(ped, horse, -1, True)
                else:
                    TASK.TASK_MOUNT_ANIMAL(ped, horse, -1, -1, 2.0, EnterExitVehicleFlags["None"], 0, 0)
            elif seat == 1:
                if mount_instantly:
                    PED.SET_PED_ONTO_MOUNT(ped, horse, -2, True)
                else:
                    TASK.TASK_MOUNT_ANIMAL(ped, horse, -1, -2, 2.0, EnterExitVehicleFlags["None"], 0, 0)
            elif seat == 2:
                seat_index = int(GCT.Input("Enter the seat index: ", False))
                
                if seat_index:
                    if mount_instantly:
                        PED.SET_PED_ONTO_MOUNT(driver, horse, seat_index, True)
                    else:
                        TASK.TASK_MOUNT_ANIMAL(ped, horse, -1, seat_index, 2.0, EnterExitVehicleFlags["None"], 0, 0)
        
    elif option == 13:
        ENTITY.SET_ENTITY_HEALTH(ped, PED.GET_PED_MAX_HEALTH(ped), 0)
    elif option == 14:
        ATTRIBUTE.ENABLE_ATTRIBUTE_OVERPOWER(ped, 0, 900.0, 1)
        ATTRIBUTE.ENABLE_ATTRIBUTE_OVERPOWER(ped, 1, 900.0, 1)
        ATTRIBUTE.ENABLE_ATTRIBUTE_OVERPOWER(ped, 2, 900.0, 1)

        ATTRIBUTE._ENABLE_ATTRIBUTE_CORE_OVERPOWER(ped, 0, 100.0, 1)
        ATTRIBUTE._ENABLE_ATTRIBUTE_CORE_OVERPOWER(ped, 1, 100.0, 1)
        ATTRIBUTE._ENABLE_ATTRIBUTE_CORE_OVERPOWER(ped, 2, 100.0, 1)
    elif option == 15:
        ENTITY.SET_ENTITY_HEALTH(ped, 0, PLAYER.PLAYER_PED_ID())
    elif option == 16:
        blip = MAP.BLIP_ADD_FOR_ENTITY(blip_styles["BLIP_STYLE_FRIENDLY"], ped)
        MAP.SET_BLIP_SPRITE(blip, MISC.GET_HASH_KEY("blip_ambient_companion"), True)
        MAP.SET_BLIP_SCALE(blip, 0.1)
        MAP._SET_BLIP_NAME(blip, GCT.Input("Enter a name for the blip on the map: ", False))
def create_ped():
    import GCT
    import Game
    from RDR2 import ENTITY, PLAYER, MISC, PATHFIND
    import utils.network_utils as network_utils
    from utils.math_utils import SumVectors, MultVector
    
    model = GCT.Input("Enter ped model(https://www.rdr2mods.com/wiki/peds/): ", False)
    model_hash = MISC.GET_HASH_KEY(model)
    
    # Calculate the spawn coordinates for ped by moving forward from the player's position
    coords = ENTITY.GET_ENTITY_COORDS(PLAYER.PLAYER_PED_ID(), True, True)
    forward = ENTITY.GET_ENTITY_FORWARD_VECTOR(PLAYER.PLAYER_PED_ID())
    
    coords = SumVectors(coords, MultVector(forward, 2.0))
    
    safe_coords = GCT.NewVector3({"x" : 0.0, "y" : 0.0, "z" : 0.0})
    if PATHFIND.GET_SAFE_COORD_FOR_PED(coords[0], coords[1], coords[2], True, safe_coords, 0):
        coords = [Game.ReadFloat(safe_coords), Game.ReadFloat(safe_coords+0x8), Game.ReadFloat(safe_coords+0x10)]
    
    ped = network_utils.CreateNetPed(model_hash, coords, ENTITY.GET_ENTITY_HEADING(PLAYER.PLAYER_PED_ID()))
    if ped:
        peds_list[ped] = model
        
        GCT.printColoured("green", f"Succesfully created new ped. Ped ID is {ped}")
    else:
        GCT.DisplayError(False, "Failed to create ped")

def create_horse():
    import GCT
    import Game
    import json
    from RDR2 import ENTITY, PLAYER, PED, MISC, MAP, PATHFIND
    import utils.network_utils as network_utils
    from utils.math_utils import SumVectors, MultVector
    from enums.blips import blip_modifiers
    
    
    horse_types = []
    try:
        with open(GCT.GetGCTFolder()+"\\"+"Lists"+"\\"+"horses.json", "r") as f:
            horses_list = json.load(f)
    except FileNotFoundError:
        GCT.DisplayError(False, "The file with the list of horses was not found")
        return None
    
    for horse_type, horse_type_list in horses_list.items():
        horse_types.append(horse_type)
        
    horse_type_id = GCT.InputFromList("Choose a breed of horse: ", horse_types)
    
    if horse_type_id == -1:
        return None
    
    horses = horses_list[horse_types[horse_type_id]]
    
    horse_id = GCT.InputFromList("Choose the horse you want to create: ", horses)
    
    if horse_id == -1:
        return None
    
    model = horses[horse_id]
    model_hash = MISC.GET_HASH_KEY(model)
    
    # Calculate the spawn coordinates for horse by moving forward from the player's position
    coords = ENTITY.GET_ENTITY_COORDS(PLAYER.PLAYER_PED_ID(), True, True)
    forward = ENTITY.GET_ENTITY_FORWARD_VECTOR(PLAYER.PLAYER_PED_ID())
    
    coords = SumVectors(coords, MultVector(forward, 2.0))
    
    safe_coords = GCT.NewVector3({"x" : 0.0, "y" : 0.0, "z" : 0.0})
    if PATHFIND.GET_SAFE_COORD_FOR_PED(coords[0], coords[1], coords[2], True, safe_coords, 0):
        coords = [Game.ReadFloat(safe_coords), Game.ReadFloat(safe_coords+0x8), Game.ReadFloat(safe_coords+0x10)]
    
    horse = network_utils.CreateNetPed(model_hash, coords, ENTITY.GET_ENTITY_HEADING(PLAYER.PLAYER_PED_ID()), {"modifier": blip_modifiers["BLIP_MODIFIER_MP_COLOR_5"], "sprite": "blip_horse_temp", "scale": 0.1, "name": "Horse"})
    if horse:
        peds_list[horse] = model
        
        PED._EQUIP_META_PED_OUTFIT(horse, 0x4B96E611)
        PED._UPDATE_PED_VARIATION(horse, True, True, True, True, True)
        
        GCT.printColoured("green", f"Succesfully created new horse. Ped ID is {horse}")
        
        mount_horse = GCT.Input("Do you want to get in? [Y/n]: ", True)
        if mount_horse == "y":
            PED.SET_PED_ONTO_MOUNT(PLAYER.PLAYER_PED_ID(), horse, -1, True)
    else:
        GCT.DisplayError(False, "Failed to create horse")

# Define a dictionary with commands and their functions
commands = {
    "peds": view_peds_list,
    "add ped to list" : add_ped_to_ped_list,
    "create ped": create_ped,
    "create horse": create_horse
}

for command, function in commands.items():
    if not GCT.BindCommand(command, function):
       GCT.DisplayError(True, f"Failed to register the command: {command}")