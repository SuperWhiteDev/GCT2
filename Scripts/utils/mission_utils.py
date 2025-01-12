StartState = {"PlayerCoords" : (0.0, 0.0, 0.0), "PlayerHeading":  0.0, "time" : {"hours": 0, "minutes": 0, "seconds": 0}, "weather": 0}

def CanStartMission() -> bool:
    import GCT
    from RDR2 import PLAYER, SCRIPTS
    
    return PLAYER.CAN_PLAYER_START_MISSION(PLAYER.PLAYER_ID()) and not SCRIPTS.IS_LOADING_SCREEN_VISIBLE() and GCT.GetGlobalVariable("missions_mission_flag_state") == 1

def StartMission() -> None:
    import GCT
    import Game
    from RDR2 import ENTITY, PLAYER, CLOCK, MISC, NETWORK
    
    StartState["PlayerCoords"] = ENTITY.GET_ENTITY_COORDS(PLAYER.PLAYER_PED_ID(), True, True)
    StartState["PlayerHeading"] = ENTITY.GET_ENTITY_HEADING(PLAYER.PLAYER_PED_ID())
    StartState["time"] = { "hours": CLOCK.GET_CLOCK_HOURS(), "minutes": CLOCK.GET_CLOCK_MINUTES(), "seconds": CLOCK.GET_CLOCK_SECONDS() }
    
    weatherp = GCT.New(4)
    hashp = GCT.New(4)
    MISC._GET_FORCED_WEATHER(weatherp, hashp)
    StartState["weather"] = Game.ReadInt(weatherp)
    
    GCT.Delete(weatherp)
    GCT.Delete(hashp)

    NETWORK.NETWORK_SET_THIS_SCRIPT_IS_NETWORK_SCRIPT(1, True, 0)
    NETWORK.NETWORK_SET_SCRIPT_READY_FOR_EVENTS(False)

    GCT.SetGlobalVariableValue("missions_mission_flag_state", 2)
    
def StartLoadingMission(MissionName : str, MissionSubtitle : str, StartPoint : dict, MissionTime : dict, MissionWeather : int, GhostForPlayers : bool, DisableWanted : bool) -> None:
    from RDR2 import ENTITY, PLAYER, MISC, NETWORK, CAM, SCRIPTS, TASK, LAW
    from time import sleep
    
    PLAYER.SET_PLAYER_CONTROL(PLAYER.PLAYER_ID(), False, 4, True)
    
    MISC.SET_MISSION_FLAG(True)

    CAM.DO_SCREEN_FADE_OUT(700)
    sleep(0.75)

    SCRIPTS._DISPLAY_LOADING_SCREENS(0, 0, 0, MissionName, MissionSubtitle, "")

    if StartPoint:
        if PED.GET_MOUNT(PLAYER.PLAYER_PED_ID()) or PED.GET_VEHICLE_PED_IS_IN(PLAYER.PLAYER_PED_ID(), True):
            TASK.CLEAR_PED_TASKS_IMMEDIATELY(PLAYER.PLAYER_PED_ID(), True, True)

        ENTITY.SET_ENTITY_COORDS_NO_OFFSET(PLAYER.PLAYER_PED_ID(), StartPoint["x"], StartPoint["y"], StartPoint["z"], False, False, False)
        
        if "heading" in StartPoint:
            ENTITY.SET_ENTITY_HEADING(PLAYER.PLAYER_PED_ID(), StartPoint["heading"])

    if MissionTime:
        NETWORK._NETWORK_CLOCK_TIME_OVERRIDE(MissionTime["hours"], MissionTime["minutes"], MissionTime["seconds"], 1000, False)
    
    if MissionWeather:
        MISC.SET_WEATHER_TYPE(MissionWeather, True, True, True, 10.0, True)
    
    if GhostForPlayers:
        NETWORK.SET_LOCAL_PLAYER_AS_GHOST(True)
    
    if DisableWanted:
        LAW.SET_WANTED_SCORE(PLAYER.PLAYER_ID(), 0)
        PLAYER.SET_WANTED_LEVEL_MULTIPLIER(0.0)
    

def FailLoadingMission():
    from RDR2 import ENTITY, PLAYER, MISC, NETWORK, SCRIPTS
    from time import sleep
    
    if StartState["PlayerCoords"][0] and StartState["PlayerCoords"][1] and StartState["PlayerCoords"][2]:
        ENTITY.SET_ENTITY_COORDS_NO_OFFSET(PLAYER.PLAYER_PED_ID(), StartState["PlayerCoords"][0], StartState["PlayerCoords"][1], StartState["PlayerCoords"][2], False, False, False)
        ENTITY.SET_ENTITY_HEADING(PLAYER.PLAYER_PED_ID(), StartState["PlayerHeading"])
        NETWORK._NETWORK_CLOCK_TIME_OVERRIDE(StartState["time"]["hours"], StartState["time"]["minutes"], StartState["time"]["seconds"], 100, False)
        MISC.SET_WEATHER_TYPE(StartState["weather"], True, True, True, 0.1, True)

    SCRIPTS.SHUTDOWN_LOADING_SCREEN()
    while SCRIPTS.IS_LOADING_SCREEN_VISIBLE():
        sleep(0.05)
    
    FinishMission()

def EndLoadingMission():
    from RDR2 import CAM, PLAYER, SCRIPTS, AUDIO
    from time import sleep
    
    SCRIPTS.SHUTDOWN_LOADING_SCREEN()
    while SCRIPTS.IS_LOADING_SCREEN_VISIBLE():
        sleep(0.05)

    #AUDIO.TRIGGER_MUSIC_EVENT("stop_title_screen_music")

    CAM.DO_SCREEN_FADE_IN(800)

    PLAYER.SET_PLAYER_CONTROL(PLAYER.PLAYER_ID(), True, 0, True)

def FinishMission():
    import GCT
    from RDR2 import ENTITY, PLAYER, CLOCK, MISC, NETWORK, CAM, AUDIO
    
    if CAM.IS_SCREEN_FADED_OUT():
        CAM.DO_SCREEN_FADE_IN(200)

    NETWORK.SET_LOCAL_PLAYER_AS_GHOST(False)
    MISC.SET_MISSION_FLAG(False)

    PLAYER.SET_WANTED_LEVEL_MULTIPLIER(1.0)

    NETWORK.NETWORK_SET_SCRIPT_READY_FOR_EVENTS(True)

    #AUDIO.PREPARE_MUSIC_EVENT("MP_BH_MISSION_COMPLETE_MUSIC")
    #AUDIO.TRIGGER_MUSIC_EVENT("MP_BH_MISSION_COMPLETE_MUSIC")

    GCT.SetGlobalVariableValue("missions_mission_flag_state", 0)
    
def FailMissionScreen():
    import GCT
    import Game
    from RDR2 import ENTITY, PLAYER, CAM, MISC, NETWORK, UISTICKYFEED
    from time import sleep
    
    while ENTITY.IS_ENTITY_DEAD(PLAYER.PLAYER_PED_ID()):
        sleep(0.01)

    CAM.DO_SCREEN_FADE_OUT(200)
    sleep(0.2)

    audio_ref_s = "HUD_PENALTY_SOUNDSET"
    audio_name_s = "HUD_FAIL"
    title_s = "Mission failed"
    audio_ref = MISC.CreateVarString(10, "LITERAL_STRING", audio_ref_s)
    audio_name = MISC.CreateVarString(10, "LITERAL_STRING", audio_name_s)
    title = MISC.CreateVarString(10, "LITERAL_STRING", title_s)

    struct1 = GCT.New(32)

    Game.WriteInt64(struct1, audio_ref)
    Game.WriteInt64(struct1+8, audio_name)
    Game.WriteInt(struct1+16, 4)

    struct2 = GCT.New(64)
    Game.WriteInt64(struct2+8, title)

    msg_id = UISTICKYFEED._UI_STICKY_FEED_CREATE_DEATH_FAIL_MESSAGE(struct1, struct2, True)
    sleep(7.0)

    if StartState["PlayerCoords"][0] and StartState["PlayerCoords"][1] and StartState["PlayerCoords"][2]:
        ENTITY.SET_ENTITY_COORDS_NO_OFFSET(PLAYER.PLAYER_PED_ID(), StartState["PlayerCoords"][0], StartState["PlayerCoords"][1], StartState["PlayerCoords"][2], False, False, False)
        ENTITY.SET_ENTITY_HEADING(PLAYER.PLAYER_PED_ID(), StartState["PlayerHeading"])
        NETWORK._NETWORK_CLOCK_TIME_OVERRIDE(StartState["time"]["hours"], StartState["time"]["minutes"], StartState["time"]["seconds"], 100, False)
        MISC.SET_WEATHER_TYPE(StartState["weather"], True, True, True, 0.1, True)

    UISTICKYFEED._UI_STICKY_FEED_CLEAR_MESSAGE(msg_id)
    GCT.Delete(struct1)
    GCT.Delete(struct2)

def MissionCompleteMessage(final_message : str):
    import GCT
    import Game
    from RDR2 import MISC, UIFEED
    
    title = "Mission complete"
    shard_type = "FETCH_RESUPPLY_SHARD_NAME"
    struct1 = GCT.New(32)

    duration = 7500

    Game.WriteInt(struct1, duration)
    Game.WriteInt(struct1+4, 1397048415)
    Game.WriteInt64(struct1+8, MISC.CreateVarString(10, "LITERAL_STRING", title))
    Game.WriteInt64(struct1+16, MISC.CreateVarString(10, "LITERAL_STRING", final_message))

    struct2 = GCT.New(16)
    Game.WriteInt64(struct2, MISC.CreateVarString(10, "LITERAL_STRING", shard_type))

    UIFEED._UI_FEED_POST_TWO_TEXT_SHARD(struct1, struct2, True, False)
    #AUDIO.PLAY_SOUND("supply_delivered", "HUD_MP_FREE_MODE", 0, 0, 0, 0) 
    
    GCT.Delete(struct1)
    GCT.Delete(struct2)
    
    
def MissionFailedMessage(final_message : str):
    import GCT
    import Game
    from RDR2 import MISC, UIFEED
    
    title = "Mission complete"
    shard_type = "FETCH_RESUPPLY_SHARD_NAME"

    struct1 = GCT.New(32)

    duration = 7500

    Game.WriteInt(struct1, duration)
    Game.WriteInt(struct1+4, 1397048415)
    Game.WriteInt64(struct1+8, MISC.CreateVarString(10, "LITERAL_STRING", title))
    Game.WriteInt64(struct1+16, MISC.CreateVarString(10, "LITERAL_STRING", final_message))

    struct2 = GCT.New(16)
    Game.WriteInt64(struct2, MISC.CreateVarString(10, "LITERAL_STRING", shard_type))

    UIFEED._UI_FEED_POST_TWO_TEXT_SHARD(struct1, struct2, True, False)
    #AUDIO.PLAY_SOUND("supply_delivered", "HUD_MP_FREE_MODE", 0, 0, 0, 0) 
    
    GCT.Delete(struct1)
    GCT.Delete(struct2)
    

def PlayMusic(music : str):
    from RDR2 import AUDIO
    from time import sleep
    
    if AUDIO.AUDIO_IS_MUSIC_PLAYING():
        AUDIO.PREPARE_MUSIC_EVENT("MC_MUSIC_STOP")
        AUDIO.TRIGGER_MUSIC_EVENT("MC_MUSIC_STOP")
        sleep(1.5)
    AUDIO.PREPARE_MUSIC_EVENT(music)
    AUDIO.TRIGGER_MUSIC_EVENT(music)

def StopMusic():
    from RDR2 import AUDIO
    
    AUDIO.PREPARE_MUSIC_EVENT("MC_MUSIC_STOP")
    AUDIO.TRIGGER_MUSIC_EVENT("MC_MUSIC_STOP")

def FocusPlayerCamOnEntity(entity : int, duration : int):
    from RDR2 import ENTITY, PLAYER
    from time import sleep
    
    coords = ENTITY.GET_ENTITY_COORDS(entity, True, True)
    
    chars = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_'
    name = ''.join(random.choice(chars) for _ in range(4))

    # Устанавливаем фокус камеры на объект
    PLAYER._0x3946FC742AC305CD(PLAYER.PLAYER_ID(), entity, "SAD2_MAYOR_IF", coords[0], coords[1], coords[2], 0, name)  # _ADD_AMBIENT_PLAYER_INTERACTIVE_FOCUS_PRESET
    
    sleep(duration / 1000)  # Преобразуем миллисекунды в секунды

    # Убираем фокус с объекта
    PLAYER._0xC67A4910425F11F1(PLAYER.PLAYER_ID(), name)

def CreateMissionObject(model : int, coords : tuple | dict, heading : float, rotation : dict, is_dynamic : bool, place_on_ground : bool, blip_info : dict = None) -> int:
    import GCT
    from time import sleep
    from RDR2 import OBJECT, STREAMING, ENTITY
    from utils.network_utils import RegisterAsNetwork
    
    if STREAMING.IS_MODEL_IN_CDIMAGE(model) and STREAMING.IS_MODEL_VALID(model):
        STREAMING.REQUEST_MODEL(model, True)
        
        iters = 0
        while not STREAMING.HAS_MODEL_LOADED(model):
            if iters > 50:
                GCT.DisplayError(False, f"Failed to load model {model}")
                return None

            sleep(0.1)
            iters = iters + 1
            
        if isinstance(coords, dict):
            coords_new = (coords["x"], coords["y"], coords["z"])
            coords = coords_new

        obj = OBJECT.CREATE_OBJECT(model, coords[0], coords[1], coords[2], False, False, True, False, False)
        if obj and ENTITY.DOES_ENTITY_EXIST(obj):
            RegisterAsNetwork(obj)

            ENTITY.SET_ENTITY_AS_MISSION_ENTITY(obj, True, True)

            ENTITY.SET_ENTITY_HEADING(obj, heading)
            ENTITY.SET_ENTITY_COLLISION(obj, True, True)

            if rotation:
                ENTITY.SET_ENTITY_ROTATION(obj, rotation["pitch"], rotation["roll"], rotation["yaw"], 2, True)

            if is_dynamic:
                ENTITY.SET_ENTITY_DYNAMIC(obj, True)

            if place_on_ground:
                OBJECT.PLACE_OBJECT_ON_GROUND_PROPERLY(obj, True)

            if blip_info:
                if "style" in blip_info:
                    style = blip_info["style"]
                else:
                    style = None
                    
                if "modifier" in blip_info:
                    modifier = blip_info["modifier"]
                else:
                    modifier = None
                    
                AddBlipForEntity(obj, style, modifier, blip_info["sprite"], blip_info["scale"], blip_info["name"])
        
        return obj
    else:
        GCT.DisplayError(False, f"Not valid model {model}")

    return None
    
def CreateMissionVehicle(model : int, coords : tuple | dict, heading : float, place_on_ground : bool, blip_info = None) -> int:
    import GCT
    from time import sleep
    from RDR2 import VEHICLE, STREAMING, ENTITY
    from utils.network_utils import RegisterAsNetwork
    
    if STREAMING.IS_MODEL_IN_CDIMAGE(model) and STREAMING.IS_MODEL_VALID(model):
        STREAMING.REQUEST_MODEL(model, True)
        
        iters = 0
        while not STREAMING.HAS_MODEL_LOADED(model):
            if iters > 50:
                GCT.DisplayError(False, f"Failed to load model {model}")
                return None

            sleep(0.1)
            iters = iters + 1
            
        if isinstance(coords, dict):
            coords_new = (coords["x"], coords["y"], coords["z"])
            coords = coords_new
            
        veh = VEHICLE.CREATE_VEHICLE(model, coords[0], coords[1], coords[2], heading, False, False, False, True)
        if veh and ENTITY.DOES_ENTITY_EXIST(veh):
            RegisterAsNetwork(veh)

            ENTITY.SET_ENTITY_AS_MISSION_ENTITY(veh, True, True)

            if place_on_ground:
                VEHICLE.SET_VEHICLE_ON_GROUND_PROPERLY(veh, True)

            if blip_info:
                if "style" in blip_info:
                    style = blip_info["style"]
                else:
                    style = None
                    
                if "modifier" in blip_info:
                    modifier = blip_info["modifier"]
                else:
                    modifier = None
                    
                AddBlipForEntity(veh, style, modifier, blip_info["sprite"], blip_info["scale"], blip_info["name"])
        
        return veh
    else:
        GCT.DisplayError(False, f"Not valid model {model}")

    return None

def CreateMissionPed(model : int, coords : tuple | dict, heading : float, outfit : int, place_on_ground : int, blip_info = None) -> int:
    import GCT
    from time import sleep
    from RDR2 import PED, STREAMING, ENTITY
    from utils.network_utils import RegisterAsNetwork
    
    if STREAMING.IS_MODEL_IN_CDIMAGE(model) and STREAMING.IS_MODEL_VALID(model):
        STREAMING.REQUEST_MODEL(model, True)
        
        iters = 0
        while not STREAMING.HAS_MODEL_LOADED(model):
            if iters > 50:
                GCT.DisplayError(False, f"Failed to load model {model}")
                return None

            sleep(0.1)
            iters = iters + 1
            
        if isinstance(coords, dict):
            coords_new = [coords["x"], coords["y"], coords["z"]]
            coords = coords_new
            
        ped = PED.CREATE_PED(model, coords[0], coords[1], coords[2], heading, False, False, True, True)
        if ped and ENTITY.DOES_ENTITY_EXIST(ped):
            RegisterAsNetwork(ped)

            ENTITY.SET_ENTITY_AS_MISSION_ENTITY(ped, True, True)

            if outfit:
                PED._EQUIP_META_PED_OUTFIT_PRESET(ped, outfit, True) 
            else:
                PED._SET_RANDOM_OUTFIT_VARIATION(ped, True)
            
            ENTITY.SET_ENTITY_VISIBLE(ped, True)
            PED.CLEAR_PED_ENV_DIRT(ped)

            if place_on_ground:
                ENTITY.PLACE_ENTITY_ON_GROUND_PROPERLY(ped, True)
                
            if blip_info:
                if "style" in blip_info:
                    style = blip_info["style"]
                else:
                    style = None
                    
                if "modifier" in blip_info:
                    modifier = blip_info["modifier"]
                else:
                    modifier = None
                    
                AddBlipForEntity(ped, style, modifier, blip_info["sprite"], blip_info["scale"], blip_info["name"])
        
        return ped
    else:
        GCT.DisplayError(False, f"Not valid model {model}")

    return None

def CreateMissionPedInVehicle(vehicle : int, seat : int, model : int, outfit : int, blip_info : dict = None) -> int:
    from RDR2 import PED, ENTITY
    
    coords = ENTITY.GET_ENTITY_COORDS(vehicle, True, True)
    coords = (coords[0] + 2.0, coords[1], coords[2])

    ped = CreateMissionPed(model, coords, 0.0, outfit, True, blip_info)

    if ped:
        PED.SET_PED_INTO_VEHICLE(ped, vehicle, seat)

    return ped

def CreateMissionPedOnMount(mount : int, seat : int, model : int, outfit : int, blip_info : dict = None) -> int:
    from RDR2 import PED, ENTITY
    
    coords = ENTITY.GET_ENTITY_COORDS(mount, True, True)
    coords = (coords[0] + 1.0, coords[1], coords[2])

    ped = CreateMissionPed(model, coords, 0.0, outfit, True, blip_info)

    if ped:
        PED.SET_PED_ONTO_MOUNT(ped, mount, seat, True)

    return ped

def CreatePropSet(propset : int, coords : tuple | dict, heading : float) -> int:
    import GCT
    from RDR2 import PROPSET
    from time import sleep
    
    PROPSET._REQUEST_PROP_SET(propset)

    iters = 0
    while not PROPSET._HAS_PROP_SET_LOADED(propset):
        if iters > 50:
            GCT.DisplayError(False, f"Failed to load propset {propset}")
            return None

        sleep(0.1)
        iters = iters + 1
        
    if isinstance(coords, dict):
        coords_new = [coords["x"], coords["y"], coords["z"]]
        coords = coords_new

    propset_id = PROPSET._CREATE_PROP_SET_2(propset, coords[0], coords[1], coords[2], 0, heading, 1200.0, False, True)
    PROPSET._RELEASE_PROP_SET(propset)

    return propset_id

def AddBlipForEntity(entity : int, style : int, modifier : int, sprite : str, scale : float, name : str) -> int:
    from RDR2 import MAP, MISC
    from enums.blips import blip_styles
    
    blip_style = blip_styles["BLIP_STYLE_CREATOR_DEFAULT"]
    if style:
        blip_style = style

    blip = 0
    iters = 0
    while not blip and iters < 25:
        blip = MAP.BLIP_ADD_FOR_ENTITY(blip_style, entity)
        iters = iters + 1

    if blip:
        if modifier:
            MAP.BLIP_ADD_MODIFIER(blip, modifier)

        MAP.SET_BLIP_SPRITE(blip, MISC.GET_HASH_KEY(sprite), True)
        MAP.SET_BLIP_SCALE(blip, scale)
        MAP._SET_BLIP_NAME(blip, name)

    return blip

def RemoveBlipFromEntity(entity : int) -> None:
    import GCT
    from RDR2 import MAP
    from time import sleep
    
    blip = MAP.GET_BLIP_FROM_ENTITY(entity)
    
    iters = 0
    while MAP.DOES_BLIP_EXIST(blip) and iters < 5:
        blipp = GCT.NewPed(blip)
        MAP.REMOVE_BLIP(blipp)
        GCT.Delete(blipp)
        
        iters = iters + 1
        sleep(0.005)

def CreateCamera(x, y, z, heading_x, heading_y, heading_z, transition_time : int) -> int:
    from RDR2 import CAM
    
    cam = CAM.CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", True)
    CAM.SET_CAM_COORD(cam, x, y, z)
    CAM.SET_CAM_ROT(cam, heading_z, heading_y, heading_x, 2)
    CAM.RENDER_SCRIPT_CAMS(True, True, transition_time, True, True, 0)

    return cam

def DeleteMissionObject(obj : int) -> None:
    import GCT
    import Game
    from RDR2 import OBJECT, ENTITY
    from time import sleep
    
    objp = GCT.NewObject(obj)
    
    iters = 0
    while ENTITY.DOES_ENTITY_EXIST(obj) and iters < 5:
        OBJECT.DELETE_OBJECT(objp)

        iters = iters + 1
        sleep(0.001)

    GCT.Delete(objp)

    if ENTITY.DOES_ENTITY_EXIST(obj):
        objp = GCT.NewObject(obj)
        ENTITY.SET_ENTITY_AS_NO_LONGER_NEEDED(objp)
        ENTITY.SET_ENTITY_COORDS_NO_OFFSET(obj, 4607.0, 813.0, 100.0, False, False, False)
        OBJECT.DELETE_OBJECT(objp)

        if Game.ReadInt(objp) == 0.0 and ENTITY.DOES_ENTITY_EXIST(obj):
            objp = GCT.NewObject(obj)

            ENTITY.DELETE_ENTITY(objp)

            GCT.Delete(objp)

        GCT.Delete(objp)

def DeleteMissionPed(ped : int) -> None:
    import GCT
    import Game
    from RDR2 import PED, ENTITY
    from time import sleep
    
    pedp = GCT.NewPed(ped)
    
    iters = 0
    while ENTITY.DOES_ENTITY_EXIST(ped) and iters < 5:
        PED.DELETE_PED(pedp)

        iters = iters + 1
        sleep(0.001)

    GCT.Delete(pedp)

    if ENTITY.DOES_ENTITY_EXIST(ped):
        pedp = GCT.NewPed(ped)

        ENTITY.SET_ENTITY_INVINCIBLE(ped, False)
        ENTITY.SET_ENTITY_HEALTH(ped, 0, 0)
        ENTITY.SET_ENTITY_AS_NO_LONGER_NEEDED(pedp)
        ENTITY.SET_ENTITY_COORDS_NO_OFFSET(ped, 4607.0, 813.0, 100.0, False, False, False)
        PED.DELETE_PED(pedp)

        if Game.ReadInt(pedp) == 0.0 and ENTITY.DOES_ENTITY_EXIST(ped):
            pedp = GCT.NewPed(ped)

            ENTITY.DELETE_ENTITY(pedp)

            GCT.Delete(pedp)
        GCT.Delete(pedp)

def DeleteMissionVehicle(veh : int) -> None:
    import GCT
    import Game
    from RDR2 import VEHICLE, ENTITY
    from time import sleep
    
    vehp = GCT.NewVehicle(veh)

    while ENTITY.DOES_ENTITY_EXIST(veh) and iters < 5:
        VEHICLE.DELETE_VEHICLE(vehp)

        iters = iters + 1
        sleep(0.001)

    GCT.Delete(vehp)

    if ENTITY.DOES_ENTITY_EXIST(veh):
        vehp = GCT.NewVehicle(veh)

        ENTITY.SET_ENTITY_AS_NO_LONGER_NEEDED(vehp)
        ENTITY.SET_ENTITY_COORDS_NO_OFFSET(veh, 4607.0, 813.0, 100.0, False, False, False)
        VEHICLE.DELETE_VEHICLE(vehp)

        if Game.ReadInt(vehp) == 0.0 and ENTITY.DOES_ENTITY_EXIST(veh):
            vehp = GCT.NewVehicle(veh)

            ENTITY.DELETE_ENTITY(vehp)

            GCT.Delete(vehp)

        GCT.Delete(vehp)

def DeleteMissionPropSet(propset_id : int) -> None:
    from RDR2 import PROPSET
    
    PROPSET._SET_PROP_SET_AS_NO_LONGER_NEEDED(propset_id)
    PROPSET._DELETE_PROP_SET(propset_id, True, True)

def DeleteCamera(camera : int, transition_time : int) -> None:
    from RDR2 import CAM
    
    CAM.RENDER_SCRIPT_CAMS(False, True, transition_time, True, True, 0)
    CAM.DESTROY_CAM(camera, False)