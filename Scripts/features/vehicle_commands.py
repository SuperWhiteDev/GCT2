import GCT

global vehicles_list, control_vehicle
vehicles_list = {  }

def view_vehicles_list():
    from utils.network_utils import DeleteNetVehicle, RegisterAsNetwork
    from RDR2 import ENTITY, VEHICLE
    
    vehicle_ids = []
    models = []
    
    for vehicle_id, model in vehicles_list.items():
        vehicle_ids.append(vehicle_id)
        models.append(model)
        
    if len(vehicle_ids) != 0:
        vehicle_id = GCT.InputFromList("Choose the vehicle you want to interact with: ", models)
    
        if vehicle_id != -1:
            vehicle = vehicle_ids[vehicle_id]
        
            print(f"The vehicle ID of the selected vehicle is {vehicle}")

            options = [ "Control vehicle", "Delete" ]
            option = GCT.InputFromList("Choose what you want to: ", options)

            if option == 0:
                control_vehicle(vehicle)
            elif option == 1:
                DeleteNetVehicle(vehicle)

                if not ENTITY.DOES_ENTITY_EXIST(vehicle):
                    vehicles_list.pop(vehicle)
    else:
        print("The list of created vehicles is empty")
        
def control_vehicle(veh):
    from utils.network_utils import RequestControlOf
    from RDR2 import ENTITY, PLAYER, VEHICLE

    options = [ "Fix vehicle", "Explode vehicle", "Make strong", "Doors control", "Clean vehicle", "Lights" ]
    option = GCT.InputFromList("Choose what you want to: ", options)

    RequestControlOf(veh)
    if option == 0:
        VEHICLE.SET_VEHICLE_FIXED(veh)
        VEHICLE.SET_VEHICLE_ENGINE_HEALTH(veh, 1000)
        VEHICLE.SET_VEHICLE_PETROL_TANK_HEALTH(veh, 1000)
    elif option == 1:
        VEHICLE.EXPLODE_VEHICLE(veh, True, False, 0, 0)
    elif option == 2:
        VEHICLE.SET_VEHICLE_STRONG(veh, True)
        VEHICLE.SET_VEHICLE_HAS_STRONG_AXLES(veh, True)
        VEHICLE.SET_VEHICLE_TYRES_CAN_BURST(veh, False)
        VEHICLE.SET_VEHICLE_WHEELS_CAN_BREAK(veh, False)
    elif option == 3:
        options = [ "Open doors", "Close doors", "Open door", "Close door", "Lock door", "Unlock door" ]
        option = GCT.InputFromList("Choose what you want to: ", options)
        
        if option == 0:
            for i in range(0, 11):
                VEHICLE.SET_VEHICLE_DOOR_OPEN(veh, i, False, False)
        elif option == 1:
            VEHICLE.SET_VEHICLE_DOORS_SHUT(veh, False)
        elif option == 2:    
            VEHICLE.SET_VEHICLE_DOOR_OPEN(veh, int(GCT.Input("Enter door ID(from 0 to 11): ", False)), False, False)
        elif option == 3:
            VEHICLE.SET_VEHICLE_DOOR_SHUT(veh, int(GCT.Input("Enter door ID(from 0 to 11): ", False)), False)
        elif option == 4:
            VEHICLE.SET_VEHICLE_DOORS_LOCKED_FOR_PLAYER(veh, PLAYER.PLAYER_ID(), True)
        elif option == 5:
            VEHICLE.SET_VEHICLE_DOORS_LOCKED_FOR_PLAYER(veh, PLAYER.PLAYER_ID(), False)
    elif option == 4:
        VEHICLE._SET_VEHICLE_DIRT_LEVEL_2(veh, 0.0)
        VEHICLE._SET_VEHICLE_MUD_LEVEL(veh, 0.0)
    elif option == 5:
        turn_lights = GCT.Input("Do you want to turn on the lights? [Y/n]: ", True)
        if turn_lights == "y":
            VEHICLE.SET_VEHICLE_LIGHTS(veh, 2)
        elif turn_lights == "n":
            VEHICLE.SET_VEHICLE_LIGHTS(veh, 1)

def add_vehicle_to_vehicle_list():
    from utils.input_utils import input_vehicle
    
    vehicles_list[input_vehicle()] = "UNKNOWN"

def create_vehicle():
    import GCT
    import Game
    import json
    from random import randrange
    from RDR2 import ENTITY, MISC, PLAYER, PED, PATHFIND, VEHICLE
    import utils.network_utils as network_utils
    from utils.math_utils import SumVectors, MultVector
    from time import sleep
    from enums.blips import blip_modifiers
    
    vehicle_types = []
    try:
        # Open the JSON file containing the list of vehicles
        with open(GCT.GetGCTFolder()+"\\"+"Lists"+"\\"+"vehicles.json", "r") as f:
            vehicle_lists = json.load(f)
    except FileNotFoundError:
        GCT.DisplayError(False, "The file with the list of vehicles was not found")
        return None
    
    for vehicle_type, vehicle_type_list in vehicle_lists.items():
        vehicle_types.append(vehicle_type)
        
    vehicle_typeID = GCT.InputFromList("Choose a type of vehicle: ", vehicle_types)
    
    if vehicle_typeID == -1:
        return None
    
    vehicles = vehicle_lists[vehicle_types[vehicle_typeID]]
    
    vehicleID = GCT.InputFromList("Choose the vehicle you want to create: ", vehicles)
    
    if vehicleID == -1:
        return None
    
    model = vehicles[vehicleID]
    model_hash = MISC.GET_HASH_KEY(model)
    
    coords = ENTITY.GET_ENTITY_COORDS(PLAYER.PLAYER_PED_ID(), True, True)  
    forward = ENTITY.GET_ENTITY_FORWARD_VECTOR(PLAYER.PLAYER_PED_ID())
    
    # Calculate the spawn coordinates for vehicle by moving forward from the player's position
    coords = SumVectors(coords, MultVector(forward, 3.5))
    heading = ENTITY.GET_ENTITY_HEADING(PLAYER.PLAYER_PED_ID())
    
    # Determine the blip (map marker) settings based on the vehicle type
    if vehicle_types[vehicle_typeID] in ("Cart", "Coach", "Wagons"):
        blip = {"modifier": blip_modifiers["BLIP_MODIFIER_MP_COLOR_5"], "name" : "Vehicle", "sprite" : "blip_mp_player_wagon", "scale" : 0.2}
    elif vehicle_types[vehicle_typeID] in ("Boats", "Ships"):
        blip = {"modifier": blip_modifiers["BLIP_MODIFIER_MP_COLOR_5"], "name" : "Vehicle", "sprite" : "blip_canoe", "scale" : 0.2}
    else:
        blip = False
        
    # If the transport corresponds to land and wheeled, then calculate the spawn of vehicle relative to the nearest road
    if vehicle_types[vehicle_typeID] in ("Cart", "Coach", "Wagons"):
        vec1 = GCT.NewVector3({"x" : 0.0, "y" : 0.0, "z" : 0.0})
        vec2 = GCT.NewVector3({"x" : 0.0, "y" : 0.0, "z" : 0.0})
        any1 = GCT.New(4)
        any2 = GCT.New(4)
        any3 = GCT.New(4)
        
        if PATHFIND.GET_CLOSEST_ROAD(coords[0], coords[1], coords[2], 2.0, 1, vec1, vec2, any1, any2, any3, True):
            if VEHICLE.IS_ANY_VEHICLE_NEAR_POINT(Game.ReadFloat(vec1), Game.ReadFloat(vec1+0x8), Game.ReadFloat(vec1+0x10), 7.0):
                if Game.ReadFloat(vec2) or Game.ReadFloat(vec2+0x8) or Game.ReadFloat(vec2+0x10):
                    coords = [Game.ReadFloat(vec2), Game.ReadFloat(vec2+0x8), Game.ReadFloat(vec2+0x10)]
            else:
                if Game.ReadFloat(vec1) or Game.ReadFloat(vec1+0x8) or Game.ReadFloat(vec1+0x10):
                    coords = [Game.ReadFloat(vec1), Game.ReadFloat(vec1+0x8), Game.ReadFloat(vec1+0x10)]
    veh = network_utils.CreateNetVehicle(model_hash, coords, heading, blip)
    if veh:
        vehicles_list[veh] = model
        
        GCT.printColoured("green", f"Succesfully created new veh. Veh ID is {veh}")
        
        get_in_vehicle = GCT.Input("Do you want to get in? [Y/n]: ", True)
        if get_in_vehicle == "y":
            PED.SET_PED_INTO_VEHICLE(PLAYER.PLAYER_PED_ID(), veh, -1)
        
    else:
        GCT.DisplayError(False, "Failed to create veh")
    

def fix_vehicle():
    from RDR2 import VEHICLE
    from utils.input_utils import input_vehicle
    
    veh = input_vehicle()

    VEHICLE.SET_VEHICLE_FIXED(veh)
    VEHICLE.SET_VEHICLE_ENGINE_HEALTH(veh, 1000)
    VEHICLE.SET_VEHICLE_PETROL_TANK_HEALTH(veh, 1000)

# Define a dictionary with commands and their functions
commands = {
    "vehicles": view_vehicles_list,
    "add vehicle to list": add_vehicle_to_vehicle_list,
    "create vehicle": create_vehicle,
    "fix vehicle" : fix_vehicle,
}

for command, function in commands.items():
    if not GCT.BindCommand(command, function):
        GCT.DisplayError(True, f"Failed to register the command: {command}")