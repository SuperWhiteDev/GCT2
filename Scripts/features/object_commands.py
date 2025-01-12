import GCT
import Gamepad

global objects_list, move_object, rotation_to_direction, control_object
objects_list = {  }

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

def move_object(obj):
    import GCT
    import Game
    from utils.network_utils import CreateNetObject, DeleteNetObject
    from RDR2 import CAM, ENTITY, SHAPETEST, OBJECT, PAD
    from time import sleep
    
    gamepad_key = move_object_gamepad.get_pressed_key()
    
    coords = [0.0, 0.0, 0.0]
    distance = 12.0
    
    while GCT.IsScriptsStillWorking() and not GCT.IsPressedKey(object_editor_place_object_key) and gamepad_key != gamepad_object_editor_place_object_key:
        gamepad_key = move_object_gamepad.get_pressed_key()
        
        if GCT.IsPressedKey(object_editor_turn_left_key):
            ENTITY.SET_ENTITY_HEADING(obj, ENTITY.GET_ENTITY_HEADING(obj)+10.0)
        elif GCT.IsPressedKey(object_editor_turn_right_key):
            ENTITY.SET_ENTITY_HEADING(obj, ENTITY.GET_ENTITY_HEADING(obj)-10.0)
            
        if gamepad_key == gamepad_object_editor_turn_left_key:
            ENTITY.SET_ENTITY_HEADING(obj, ENTITY.GET_ENTITY_HEADING(obj)+10.0)
        elif gamepad_key == gamepad_object_editor_turn_right_key:
            ENTITY.SET_ENTITY_HEADING(obj, ENTITY.GET_ENTITY_HEADING(obj)-10.0)
        elif gamepad_key == gamepad_object_editor_zoom_in_key:
            if distance > 1.0:
                distance -= 1.0
        elif gamepad_key == gamepad_object_editor_zoom_out_key:
            if distance < 100.0:
                distance += 1.0
        
        cam_coords = CAM.GET_GAMEPLAY_CAM_COORD()
        cam_rotation = CAM.GET_GAMEPLAY_CAM_ROT(2)
        cam_direction = rotation_to_direction(cam_rotation)
            
        start_coords = math_utils.SumVectors(cam_coords, math_utils.MultVector(cam_direction, 1.0))
        end_coords = math_utils.SumVectors(start_coords, math_utils.MultVector(cam_direction, distance))
        
        if not obj:
            obj = CreateNetObject(model, coords)
        else:
            ENTITY.SET_ENTITY_COORDS_NO_OFFSET(obj, end_coords[0], end_coords[1], end_coords[2], True, True, True)
            
        coords = end_coords

        #rayHandle = SHAPETEST.START_EXPENSIVE_SYNCHRONOUS_SHAPE_TEST_LOS_PROBE(start_coords[0], start_coords[1], start_coords[2], end_coords[0], end_coords[1], end_coords[2], -1, 0, 7)
    
        #hitP = GCT.New(4)
        #endCoordsP = GCT.NewVector3({"x" : 0.0, "y" : 0.0, "z" : 0.0})
        #surfaceNormalP = GCT.NewVector3({"x" : 0.0, "y" : 0.0, "z" : 0.0})
        #entityHitP = GCT.New(4)
    
        #if SHAPETEST.GET_SHAPE_TEST_RESULT(rayHandle, hitP, endCoordsP, surfaceNormalP, entityHitP) == 2:
        #    coords = GCT.Vector3ToList(endCoordsP)
        #    if not coords[0] and not coords[1] and not coords[2]:
        #        coords = end_coords
        #    if not obj:
        #        obj = CreateNetObject(model, coords)
        #    else:
        #        ENTITY.SET_ENTITY_COORDS_NO_OFFSET(obj, coords[0], coords[1], coords[2], True, True, True)
        #        
        #GCT.Delete(hitP)
        #GCT.DeleteVector3(endCoordsP)
        #GCT.DeleteVector3(surfaceNormalP)
        #GCT.Delete(entityHitP)
        
        sleep(0.01)
    
    OBJECT.PLACE_OBJECT_ON_GROUND_PROPERLY(obj, True)
        
    return coords
        

def view_objects_list():
    from utils.network_utils import DeleteNetObject
    from RDR2 import ENTITY
    
    objectIDs = []
    models = []
    
    for objID, model in objects_list.items():
        objectIDs.append(objID)
        models.append(model)
        
    if len(objectIDs) != 0:
        objectID = GCT.InputFromList("Choose the object you want to interact with: ", models)
    
        if objectID != -1:
            obj = objectIDs[objectID]
        
            print(f"The object ID of the selected object is {obj}")

            options = [ "Control object", "Delete" ]
            option = GCT.InputFromList("Choose what you want to: ", options)

            if option == 0:
                control_object(obj)
            elif option == 1:
                DeleteNetObject(obj)

                if not ENTITY.DOES_ENTITY_EXIST(obj):
                    objects_list.pop(obj)
    else:
        print("The list of created objects is empty")
        
def control_object(obj):
    from utils.network_utils import RequestControlOf
    from RDR2 import OBJECT, FIRE
    from time import sleep

    options = [ "Fix object", "Break object", "Burn object", "Move object" ]
    option = GCT.InputFromList("Choose what you want to: ", options)

    RequestControlOf(obj)
    if option == 0:
        OBJECT.FIX_OBJECT_FRAGMENT(obj)
    elif option == 1:
        OBJECT.BREAK_ALL_OBJECT_FRAGMENT_BONES(obj)
        OBJECT.BREAK_OBJECT_FRAGMENT_CHILD(obj, 1, True)
    elif option == 2:
        OBJECT._SET_OBJECT_BURN_OPACITY(obj, 1.0)
        OBJECT._SET_OBJECT_BURN_INTENSITY(obj, 1)
        OBJECT._SET_OBJECT_BURN_LEVEL(obj, 1.0, True)
        
        FIRE.START_ENTITY_FIRE(obj, 1, 1, 1)
    elif option == 3:
        sleep(0.5)
        move_object(obj)

def add_object_to_object_list():
    import GCT
    from RDR2 import ENTITY
    
    obj = int(GCT.Input("Enter object handle: ", False))
    
    if not obj and not ENTITY.DOES_ENTITY_EXIST(obj):
        GCT.DisplayError(False, "Uncorrect input")
    else:
        objects_list[obj] = "UNKNOWN"

def create_object():
    import GCT
    from RDR2 import MISC
    import utils.network_utils as network_utils
    from time import sleep
    
    model = GCT.Input("Enter object model(https://rdr2.mooshe.tv/): ", False)
    model_hash = MISC.GET_HASH_KEY(model)
    
    sleep(0.5)
    
    obj = network_utils.CreateNetObject(model_hash, (0.0, 0.0, 0.0))
    move_object(obj)
    if obj:
        objects_list[obj] = model
        
        GCT.printColoured("green", f"Succesfully created new object. Object ID is {obj}")
    else:
        GCT.DisplayError(False, "Failed to create object")
        
def initialize_settings():
    import utils.config_utils as config_utils
    
    global object_editor_place_object_key, object_editor_turn_left_key, object_editor_turn_right_key, gamepad_object_editor_place_object_key, gamepad_object_editor_turn_left_key, gamepad_object_editor_turn_right_key, gamepad_object_editor_zoom_in_key, gamepad_object_editor_zoom_out_key
    
    feature_settings = config_utils.get_feature_settings()
    
    object_editor_place_object_key = GCT.ConvertStringToKeyCode(feature_settings["Hotkeys"]["ObjectEditorPlaceObject"])
    object_editor_turn_left_key = GCT.ConvertStringToKeyCode(feature_settings["Hotkeys"]["ObjectEditorTurnLeft"])
    object_editor_turn_right_key = GCT.ConvertStringToKeyCode(feature_settings["Hotkeys"]["ObjectEditorTurnRight"])

    gamepad_object_editor_place_object_key = feature_settings["Hotkeys"]["GamepadObjectEditorPlaceObject"]
    gamepad_object_editor_turn_left_key = feature_settings["Hotkeys"]["GamepadObjectEditorTurnLeft"]
    gamepad_object_editor_turn_right_key = feature_settings["Hotkeys"]["GamepadObjectEditorTurnRight"]
    gamepad_object_editor_zoom_in_key = feature_settings["Hotkeys"]["GamepadObjectEditorZoomIn"]
    gamepad_object_editor_zoom_out_key = feature_settings["Hotkeys"]["GamepadObjectEditorZoomOut"]
    
initialize_settings()

global move_object_gamepad
move_object_gamepad = Gamepad.Gamepad()

# Define a dictionary with commands and their functions
commands = {
    "objects": view_objects_list,
    "add object to list": add_object_to_object_list,
    "create object": create_object,
}

for command, function in commands.items():
    if not GCT.BindCommand(command, function):
        GCT.DisplayError(True, f"Failed to register the command: {command}")