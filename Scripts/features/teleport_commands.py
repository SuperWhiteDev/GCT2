import GCT

def teleport():
    import GCT
    from RDR2 import PLAYER, PED, CAM
    import utils.map_utils as map_utils
    import utils.teleport_utils as teleport_utils
    from utils.input_utils import input_coords
    from enums.locations import locations
    from time import sleep
    
    places = ["Waypoint", "Valentine", "Strawberry", "Rhodes", "Emerald Ranch", "Saint Denis", "Saint Denis Bank", "Blackwater", "Armadillo", "Sisika Island",
                     "Mexico", "Guarma", "Beecher's Hope", "All Available locations", "Saved location", "Custom"]
    place = GCT.InputFromList("Enter where you want to teleport to: ", places)

    if place == -1:
        return None
    
    coords = None
    
    if place == 0:
        coords = map_utils.GetWaypointCoords()
        if not coords:
            GCT.DisplayError(False, "Please choose a waypoint first")
            return None            
    elif place == 1:
        coords = locations["Valentine"]
    elif place == 2:
        coords = locations["Strawberry"]
    elif place == 3:
        coords = locations["Rhodes"]
    elif place == 4:
        coords = locations["Emerald Ranch"]
    elif place == 5:
        coords = locations["Saint Denis"]
    elif place == 6:
        coords = locations["Saint Denis Bank"]
    elif place == 7:
        coords = locations["Blackwater"]
    elif place == 8:
        coords = locations["Armadillo"]
    elif place == 9:
        coords = locations["Sisika Island"]
    elif place == 10:
        coords = locations["Mexico"]
    elif place == 11:
        coords = locations["Guarma"]
    elif place == 12:
        coords = locations["Beecher's Hope"]
    elif place == 13:
        location_names = list(locations.keys())
        
        location_nameID = GCT.InputFromList("Enter where you want to teleport to: ", location_names)
        
        if location_nameID != -1:
            coords = locations[location_names[location_nameID]]
        else:
            return None
    elif place == 14:
        import json
        import GCT
        
        places = []
        
        try:
            with open(GCT.GetGCTFolder()+"\\"+"Lists"+"\\"+"teleports.json", "r") as f:
                teleports = json.load(f)
            
            for place, _ in teleports.items():
                places.append(place)
            
            placeID = GCT.InputFromList("Enter where you want to teleport to: ", places)
        
            if placeID != -1:
                coords = teleports[places[placeID]]
            else:
                return None
        except FileNotFoundError:
            return None
    elif place == 15:
        coords = input_coords()
        
    entity = PLAYER.PLAYER_PED_ID()
    if PED.GET_MOUNT(PLAYER.PLAYER_PED_ID()):
        entity = PED.GET_MOUNT(PLAYER.PLAYER_PED_ID())
    elif PED.IS_PED_IN_ANY_VEHICLE(PLAYER.PLAYER_PED_ID(), False):
        entity = PED.GET_VEHICLE_PED_IS_IN(PLAYER.PLAYER_PED_ID(), True)
    
    CAM.DO_SCREEN_FADE_OUT(500)
    sleep(0.5)
    teleport_utils.TeleportEntity(entity, coords)
    sleep(2.5)
    CAM.DO_SCREEN_FADE_IN(600)

def save_current_place():
    import json
    import GCT
    from RDR2 import ENTITY, PLAYER
    
    name = GCT.Input("Enter a name for the current location: ", False)
    coords = ENTITY.GET_ENTITY_COORDS(PLAYER.PLAYER_PED_ID(), True, True)
    
    try:
        with open(GCT.GetGCTFolder()+"\\"+"Lists"+"\\"+"teleports.json", "r") as f:
            teleports = json.load(f)
    except FileNotFoundError:
        teleports = {}
        
    teleports[name] = { "x" : coords[0], "y" : coords[1], "z" : coords[2] }
    
    with open(GCT.GetGCTFolder()+"\\"+"Lists"+"\\"+"teleports.json", "w") as f:
        json.dump(teleports, f, indent=4)

# Define a dictionary with commands and their functions
commands = {
    "teleport": teleport,
    "save current place": save_current_place
}

for command, function in commands.items():
    if not GCT.BindCommand(command, function):
        GCT.DisplayError(True, f"Failed to register the command: {command}")