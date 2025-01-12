def RequestControlOf(entity : int):
    """Sends a request to other players to allow the transfer of control of an entity."""
    
    from RDR2 import NETWORK
    NETWORK.NETWORK_REQUEST_CONTROL_OF_ENTITY(entity)
    
    for i in range(50):
        if NETWORK.NETWORK_HAS_CONTROL_OF_ENTITY(entity):
            break

        NETWORK.NETWORK_REQUEST_CONTROL_OF_ENTITY(entity)


def RegisterAsNetwork(entity : int):
    """Registers the entity on the network and then the entity will be visible to all players."""
    
    from RDR2 import NETWORK
    from time import sleep
    NETWORK.NETWORK_REGISTER_ENTITY_AS_NETWORKED(entity)
    sleep(0.01)
    RequestControlOf(entity)
    netID = NETWORK.NETWORK_GET_NETWORK_ID_FROM_ENTITY(entity)
    NETWORK.SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(netID, True)
    
def CreateNetObject(model : int, coords : tuple, place_on_ground : bool = True) -> int:
    import GCT
    from time import sleep
    from RDR2 import OBJECT, STREAMING, ENTITY
    
    if STREAMING.IS_MODEL_IN_CDIMAGE(model) and STREAMING.IS_MODEL_VALID(model):
        STREAMING.REQUEST_MODEL(model, True)
        
        iters = 0
        while not STREAMING.HAS_MODEL_LOADED(model):
            if iters > 50:
                GCT.DisplayError(False, f"Failed to load model {model}")
                return None

            sleep(0.1)
            iters = iters + 1
        obj = OBJECT.CREATE_OBJECT(model, coords[0], coords[1], coords[2], False, False, True, False, False) #https://www.unknowncheats.me/forum/red-dead-redemption-2-a/364651-red-dead-redemption-2-scripting-20.html
        if obj != 0.0 and ENTITY.DOES_ENTITY_EXIST(obj):
            RegisterAsNetwork(obj)
            ENTITY.SET_ENTITY_COLLISION(obj, True, True)
            if place_on_ground:
                OBJECT.PLACE_OBJECT_ON_GROUND_PROPERLY(obj, True)
            
        STREAMING.SET_MODEL_AS_NO_LONGER_NEEDED(model)
        
        return obj
    else:
        GCT.DisplayError(False, f"Not valid model {model}")
        
    return None

"""

blip_info = (style : int, sprite : int, scale : float, blip_name : str)

"""
def CreateNetPed(model : int, coords : tuple, heading : float, blip_info : dict = False) -> int:
    import GCT
    from time import sleep
    from RDR2 import PED, STREAMING, ENTITY, MAP, MISC
    from enums.blips import blip_styles

    if STREAMING.IS_MODEL_IN_CDIMAGE(model) and STREAMING.IS_MODEL_VALID(model):
        STREAMING.REQUEST_MODEL(model, True)
        
        iters = 0
        while not STREAMING.HAS_MODEL_LOADED(model):
            if iters > 50:
                GCT.DisplayError(False, f"Failed to load model {model}")
                return None

            sleep(0.1)
            iters = iters + 1
        ped = PED.CREATE_PED(model, coords[0], coords[1], coords[2], heading, False, False, True, True)
        if ped != 0.0 and ENTITY.DOES_ENTITY_EXIST(ped):
            RegisterAsNetwork(ped)
            PED._SET_RANDOM_OUTFIT_VARIATION(ped, True)
            ENTITY.SET_ENTITY_VISIBLE(ped, True)
            ENTITY.PLACE_ENTITY_ON_GROUND_PROPERLY(ped, True)
            PED.CLEAR_PED_ENV_DIRT(ped)
            
            if blip_info != False:
                blip_style = blip_styles["BLIP_STYLE_CREATOR_DEFAULT"]
                if "style" in blip_info:
                    blip_style = blip_info["style"]
                    
                blip = MAP.BLIP_ADD_FOR_ENTITY(blip_style, ped)
                
                if "modifier" in blip_info:
                    MAP.BLIP_ADD_MODIFIER(blip, blip_info["modifier"])
                
                MAP.SET_BLIP_SPRITE(blip, MISC.GET_HASH_KEY(blip_info["sprite"]), True)
                MAP.SET_BLIP_SCALE(blip, blip_info["scale"])
                MAP._SET_BLIP_NAME(blip, blip_info["name"])
            
        STREAMING.SET_MODEL_AS_NO_LONGER_NEEDED(model)
        
        return ped
    else:
        GCT.DisplayError(False, f"Not valid model {model}")
        
    return None

def CreateNetVehicle(model : int, coords : tuple, heading : float, blip_info : dict = False) -> int:
    import GCT
    from time import sleep
    from RDR2 import VEHICLE, STREAMING, ENTITY, MAP, MISC
    from enums.blips import blip_styles

    if STREAMING.IS_MODEL_IN_CDIMAGE(model) and STREAMING.IS_MODEL_VALID(model):
        STREAMING.REQUEST_MODEL(model, True)
        
        iters = 0
        while not STREAMING.HAS_MODEL_LOADED(model):
            if iters > 50:
                GCT.DisplayError(False, f"Failed to load model {model}")
                return None

            sleep(0.1)
            iters = iters + 1
        
        veh = VEHICLE.CREATE_VEHICLE(model, coords[0], coords[1], coords[2], heading, False, False, False, True)
        if veh != 0.0 and ENTITY.DOES_ENTITY_EXIST(veh):
            RegisterAsNetwork(veh)
            VEHICLE.SET_VEHICLE_ON_GROUND_PROPERLY(veh, True)
            VEHICLE.SET_VEHICLE_ENGINE_ON(veh, True, True)
            
            if blip_info != False:
                blip_style = blip_styles["BLIP_STYLE_CREATOR_DEFAULT"]
                if "style" in blip_info:
                    blip_style = blip_info["style"]
                    
                blip = MAP.BLIP_ADD_FOR_ENTITY(blip_style, veh)
                
                if "modifier" in blip_info:
                    MAP.BLIP_ADD_MODIFIER(blip, blip_info["modifier"])
                    
                MAP.SET_BLIP_SPRITE(blip, MISC.GET_HASH_KEY(blip_info["sprite"]), True)
                MAP.SET_BLIP_SCALE(blip, blip_info["scale"])
                MAP._SET_BLIP_NAME(blip, blip_info["name"])
            
        STREAMING.SET_MODEL_AS_NO_LONGER_NEEDED(model)
        
        return veh
    else:
        GCT.DisplayError(False, f"Not valid model {model}")
        
    return None

def DeleteNetObject(obj : int) -> None:
    import GCT
    from RDR2 import OBJECT, ENTITY
    
    RequestControlOf(obj)
    ENTITY.SET_ENTITY_AS_MISSION_ENTITY(obj, True, True)
    
    objp = GCT.NewObject(obj)
    
    OBJECT.DELETE_OBJECT(objp)
    
    GCT.Delete(objp)
    
def DeleteNetPed(ped : int) -> None:
    import GCT
    from RDR2 import PED, ENTITY
    
    RequestControlOf(ped)
    ENTITY.SET_ENTITY_AS_MISSION_ENTITY(ped, True, True)
    
    pedp = GCT.NewPed(ped)
    
    PED.DELETE_PED(pedp)
    
    GCT.Delete(pedp)
    
def DeleteNetVehicle(veh : int) -> None:
    import GCT
    from RDR2 import VEHICLE, ENTITY
    
    RequestControlOf(veh)
    ENTITY.SET_ENTITY_AS_MISSION_ENTITY(veh, True, True)
    
    vehp = GCT.NewVehicle(veh)
    
    VEHICLE.DELETE_VEHICLE(vehp)
    
    GCT.Delete(vehp)