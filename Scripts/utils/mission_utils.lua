local networkUtils = require("network_utils")
local playerUtils = require("player_utils")
local blips = require("blips")

local missionUtils = { PlayerCoords = {x = 0.0, y = 0.0, z = 0.0 }, PlayerHeading = 0.0, time = {hours = 0, minutes = 0, seconds = 0}, weather = 0}

function missionUtils.CanStartMission()
    return playerUtils.IsPlayerPlaying() and PLAYER.CAN_PLAYER_START_MISSION(PLAYER.PLAYER_ID()) and not SCRIPTS.IS_LOADING_SCREEN_VISIBLE() and GetGlobalVariable("missions_mission_flag_state") == 1
end

function missionUtils.StartMission()
    missionUtils.PlayerCoords = ENTITY.GET_ENTITY_COORDS(PLAYER.PLAYER_PED_ID(), true, true)
    missionUtils.PlayerHeading = ENTITY.GET_ENTITY_HEADING(PLAYER.PLAYER_PED_ID())
    missionUtils.time = {hours = CLOCK.GET_CLOCK_HOURS(), minutes = CLOCK.GET_CLOCK_MINUTES(), seconds = CLOCK.GET_CLOCK_SECONDS()}
    local weatherp = New(4)
    local hashp = New(4)
    MISC._GET_FORCED_WEATHER(weatherp, hashp)
    missionUtils.weather = Game.ReadInt(weatherp)

    Delete(weatherp)
    Delete(hashp)

    NETWORK.NETWORK_SET_THIS_SCRIPT_IS_NETWORK_SCRIPT(1, true, 0)
    NETWORK.NETWORK_SET_SCRIPT_READY_FOR_EVENTS(false)

    SetGlobalVariableValue("missions_mission_flag_state", 2)
end

function missionUtils.StartLoadingMission(MissionName, MissionSubtitle, StartPoint, MissionTime, MissionWeather, GhostForPlayers, DisableWanted)
    PLAYER.SET_PLAYER_CONTROL(PLAYER.PLAYER_ID(), false, 4, false)
    
    MISC.SET_MISSION_FLAG(true)

    CAM.DO_SCREEN_FADE_OUT(700)
    Wait(750)

    SCRIPTS._DISPLAY_LOADING_SCREENS(0, 0, 0, MissionName, MissionSubtitle, "")

    if StartPoint then
        if PED.GET_MOUNT(PLAYER.PLAYER_PED_ID()) ~= 0.0 or PED.GET_VEHICLE_PED_IS_IN(PLAYER.PLAYER_PED_ID(), true) ~= 0.0 then
            TASK.CLEAR_PED_TASKS_IMMEDIATELY(PLAYER.PLAYER_PED_ID(), true, true)
        end

        ENTITY.SET_ENTITY_COORDS_NO_OFFSET(PLAYER.PLAYER_PED_ID(), StartPoint.x, StartPoint.y, StartPoint.z, false, false, false)
        ENTITY.SET_ENTITY_HEADING(PLAYER.PLAYER_PED_ID(), StartPoint.heading)
    end
    if MissionTime then
        NETWORK._NETWORK_CLOCK_TIME_OVERRIDE(MissionTime.hours, MissionTime.minutes, MissionTime.seconds, 1000, false)
    end
    if MissionWeather then
        MISC.SET_WEATHER_TYPE(MissionWeather, true, true, true, 10.0, true)
    end
    if GhostForPlayers then
        NETWORK.SET_LOCAL_PLAYER_AS_GHOST(true)
    end
    if DisableWanted then
        LAW.SET_WANTED_SCORE(PLAYER.PLAYER_ID(), 0)
        PLAYER.SET_WANTED_LEVEL_MULTIPLIER(0.0)
    end
end

function missionUtils.FailLoadingMission()
    if missionUtils.PlayerCoords.x ~= 0.0 and missionUtils.PlayerCoords.y ~= 0.0 and missionUtils.PlayerCoords.z ~= 0.0 then
        ENTITY.SET_ENTITY_COORDS_NO_OFFSET(PLAYER.PLAYER_PED_ID(), missionUtils.PlayerCoords.x, missionUtils.PlayerCoords.y, missionUtils.PlayerCoords.z, false, false, false)
        ENTITY.SET_ENTITY_HEADING(PLAYER.PLAYER_PED_ID(), missionUtils.PlayerHeading)
        NETWORK._NETWORK_CLOCK_TIME_OVERRIDE(missionUtils.time.hours, missionUtils.time.minutes, missionUtils.time.seconds, 100, false)
        MISC.SET_WEATHER_TYPE(missionUtils.weather, true, true, true, 0.1, true)
    end

    SCRIPTS.SHUTDOWN_LOADING_SCREEN()
    while SCRIPTS.IS_LOADING_SCREEN_VISIBLE() do
        Wait(50)
    end
    
    missionUtils.FinishMission()
end

function missionUtils.EndLoadingMission()
    SCRIPTS.SHUTDOWN_LOADING_SCREEN()
    while SCRIPTS.IS_LOADING_SCREEN_VISIBLE() do
        Wait(50)
    end

    --AUDIO.TRIGGER_MUSIC_EVENT("stop_title_screen_music")

    CAM.DO_SCREEN_FADE_IN(800)

    PLAYER.SET_PLAYER_CONTROL(PLAYER.PLAYER_ID(), true, 0, true)
end

function missionUtils.FinishMission()
    if CAM.IS_SCREEN_FADED_OUT() then
        CAM.DO_SCREEN_FADE_IN(200)
    end

    NETWORK.SET_LOCAL_PLAYER_AS_GHOST(false)
    MISC.SET_MISSION_FLAG(false)

    PLAYER.SET_WANTED_LEVEL_MULTIPLIER(1.0)

    NETWORK.NETWORK_SET_SCRIPT_READY_FOR_EVENTS(true)

    --AUDIO.PREPARE_MUSIC_EVENT("MP_BH_MISSION_COMPLETE_MUSIC")
    --AUDIO.TRIGGER_MUSIC_EVENT("MP_BH_MISSION_COMPLETE_MUSIC")

    SetGlobalVariableValue("missions_mission_flag_state", 0)
end

function missionUtils.FailMissionScreen()
    while ENTITY.IS_ENTITY_DEAD(PLAYER.PLAYER_PED_ID()) do
        Wait(10)
    end

    CAM.DO_SCREEN_FADE_OUT(200)
    Wait(200)

    local audioRef_s = "HUD_PENALTY_SOUNDSET"
    local audioName_s = "HUD_FAIL"
    local title_s = "Mission failed"
    local audioRef = MISC.CreateVarString(10, "LITERAL_STRING", audioRef_s)
    local audioName = MISC.CreateVarString(10, "LITERAL_STRING", audioName_s)
    local title = MISC.CreateVarString(10, "LITERAL_STRING", title_s)

    local struct1 = New(32)

    Game.WriteInt64(struct1, audioRef)
    Game.WriteInt64(struct1+8, audioName)
    Game.WriteInt(struct1+16, 4)

    local struct2 = New(64)
    Game.WriteInt64(struct2+8, title)

    local msgID = UISTICKYFEED._UI_STICKY_FEED_CREATE_DEATH_FAIL_MESSAGE(struct1, struct2, true)
    Wait(7000)

    if missionUtils.PlayerCoords.x ~= 0.0 and missionUtils.PlayerCoords.y ~= 0.0 and missionUtils.PlayerCoords.z ~= 0.0 then
        ENTITY.SET_ENTITY_COORDS_NO_OFFSET(PLAYER.PLAYER_PED_ID(), missionUtils.PlayerCoords.x, missionUtils.PlayerCoords.y, missionUtils.PlayerCoords.z, false, false, false)
        ENTITY.SET_ENTITY_HEADING(PLAYER.PLAYER_PED_ID(), missionUtils.PlayerHeading)
        NETWORK._NETWORK_CLOCK_TIME_OVERRIDE(missionUtils.time.hours, missionUtils.time.minutes, missionUtils.time.seconds, 100, false)
        MISC.SET_WEATHER_TYPE(missionUtils.weather, true, true, true, 0.1, true)
    end

    UISTICKYFEED._UI_STICKY_FEED_CLEAR_MESSAGE(msgID)

    Delete(struct1)
    Delete(struct2)
end

function missionUtils.MissionCompleteMessage(final_message)
    local title_s = "Mission complete"
    local shard_type_s = "FETCH_RESUPPLY_SHARD_NAME"
    local title = MISC.CreateVarString(10, "LITERAL_STRING", title_s)
    local subtitle = MISC.CreateVarString(10, "LITERAL_STRING", final_message)
    local shard_type = MISC.CreateVarString(10, "LITERAL_STRING", shard_type_s)

    local struct1 = New(32)

    local duration = 7500

    Game.WriteInt(struct1, duration)
    Game.WriteInt(struct1+4, 1397048415)
    Game.WriteInt64(struct1+8, title)
    Game.WriteInt64(struct1+16, subtitle)

    local struct2 = New(16)
    Game.WriteInt64(struct2, shard_type)

    local feedID = UIFEED._UI_FEED_POST_TWO_TEXT_SHARD(struct1, struct2, true, false)
    --AUDIO.PLAY_SOUND("supply_delivered", "HUD_MP_FREE_MODE", 0, 0, 0, 0) 
end

function missionUtils.MissionFailedMessage(final_message)
    local title_s = "Mission failed"
    local shard_type_s = "FETCH_RESUPPLY_SHARD_NAME"
    local title = MISC.CreateVarString(10, "LITERAL_STRING", title_s)
    local subtitle = MISC.CreateVarString(10, "LITERAL_STRING", final_message)
    local shard_type = MISC.CreateVarString(10, "LITERAL_STRING", shard_type_s)

    local struct1 = New(32)

    local duration = 7500

    Game.WriteInt(struct1, duration)
    Game.WriteInt(struct1+4, 1397048415)
    Game.WriteInt64(struct1+8, title)
    Game.WriteInt64(struct1+16, subtitle)

    local struct2 = New(16)
    Game.WriteInt64(struct2, shard_type)

    local feedID = UIFEED._UI_FEED_POST_TWO_TEXT_SHARD(struct1, struct2, true, false)
    --AUDIO.PLAY_SOUND("supply_delivered", "HUD_MP_FREE_MODE", 0, 0, 0, 0) 
end

function missionUtils.PlayMusic(music)
    if AUDIO.AUDIO_IS_MUSIC_PLAYING() then
        AUDIO.PREPARE_MUSIC_EVENT("MC_MUSIC_STOP")
        AUDIO.TRIGGER_MUSIC_EVENT("MC_MUSIC_STOP")
        Wait(1500)
    end
    AUDIO.PREPARE_MUSIC_EVENT(music)
    AUDIO.TRIGGER_MUSIC_EVENT(music)
end
function missionUtils.StopMusic()
    AUDIO.PREPARE_MUSIC_EVENT("MC_MUSIC_STOP")
    AUDIO.TRIGGER_MUSIC_EVENT("MC_MUSIC_STOP")
    --AUDIO.CANCEL_MUSIC_EVENT("ARM2_BANDITS")
end

function missionUtils.FocusPlayerCamOnEntity(entity, time)
    local coords = ENTITY.GET_ENTITY_COORDS(entity, true, true)

    local chars = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_'
    local name = ''
    for i = 1, 4 do
        local index = math.random(#chars)
        name = name .. chars:sub(index, index)
    end

    -- Устанавливаем фокус камеры на объект
    PLAYER._0x3946FC742AC305CD(PLAYER.PLAYER_ID(), entity, "SAD2_MAYOR_IF", coords.x, coords.y, coords.z, 0, name) --_ADD_AMBIENT_PLAYER_INTERACTIVE_FOCUS_PRESET
    Wait(time)

    -- Убираем фокус с объекта
    PLAYER._0xC67A4910425F11F1(PLAYER.PLAYER_ID(), name)
end


function missionUtils.CreateMissionObject(model, coords, heading, rotation, is_dynamic, place_on_ground, blip_info)
    if STREAMING.IS_MODEL_IN_CDIMAGE(model) and STREAMING.IS_MODEL_VALID(model) then
        STREAMING.REQUEST_MODEL(model, true)
        
        local iters = 0
        while not STREAMING.HAS_MODEL_LOADED(model) do
            if iters > 50 then
                DisplayError(true, "Failed to load model " .. model)
                return nil
            end

            Wait(100)
            iters = iters + 1
        end

        local obj = OBJECT.CREATE_OBJECT(model, coords.x, coords.y, coords.z, false, false, true, false, false)
        if obj ~= 0.0 and ENTITY.DOES_ENTITY_EXIST(obj) then
            networkUtils.RegisterAsNetwork(obj)

            ENTITY.SET_ENTITY_AS_MISSION_ENTITY(obj, true, true)

            ENTITY.SET_ENTITY_HEADING(obj, heading)
            ENTITY.SET_ENTITY_COLLISION(obj, true, true)

            if rotation then
                ENTITY.SET_ENTITY_ROTATION(obj, rotation.pitch, rotation.roll, rotation.yaw, 2, true)
            end

            if is_dynamic then
                ENTITY.SET_ENTITY_DYNAMIC(obj, true)
            end

            if place_on_ground then
                OBJECT.PLACE_OBJECT_ON_GROUND_PROPERLY(obj, true)
            end

            if blip_info ~= nil then
                local style = blips.blip_styles.BLIP_STYLE_CREATOR_DEFAULT
                if blip_info.style then
                    style = blip_info.style
                end

                local blip = 0.0
                local iters = 0
                while blip == 0.0 and iters < 25  do
                    blip = MAP.BLIP_ADD_FOR_ENTITY(style, obj)
                    iters = iters + 1
                end
            
                if blip_info.modifier then
                    MAP.BLIP_ADD_MODIFIER(blip, blip_info.modifier)
                end

                MAP.SET_BLIP_SPRITE(blip, MISC.GET_HASH_KEY(blip_info.sprite), true)
                MAP.SET_BLIP_SCALE(blip, blip_info.scale)
                MAP._SET_BLIP_NAME(blip, blip_info.name)
            end
        end
        
        return obj
    else
        DisplayError(true, "Not valid model " .. model)
    end

    return nil
end
function missionUtils.CreateMissionVehicle(model, coords, heading, place_on_ground, blip_info)
    if STREAMING.IS_MODEL_IN_CDIMAGE(model) and STREAMING.IS_MODEL_VALID(model) then
        STREAMING.REQUEST_MODEL(model, true)
        
        local iters = 0
        while not STREAMING.HAS_MODEL_LOADED(model) do
            if iters > 50 then
                DisplayError(true, "Failed to load model " .. model)
                return nil
            end
            
            Wait(10)
            iters = iters + 1
        end

        local veh = VEHICLE.CREATE_VEHICLE(model, coords.x, coords.y, coords.z, heading, false, false, false, true)
        if veh ~= 0.0 and ENTITY.DOES_ENTITY_EXIST(veh) then
            networkUtils.RegisterAsNetwork(veh)

            ENTITY.SET_ENTITY_AS_MISSION_ENTITY(veh, true, true)

            if place_on_ground then
                VEHICLE.SET_VEHICLE_ON_GROUND_PROPERLY(veh, true)
            end

            if blip_info ~= nil then
                local style = blips.blip_styles.BLIP_STYLE_CREATOR_DEFAULT
                if blip_info.style then
                    style = blip_info.style
                end

                local blip = 0.0
                local iters = 0
                while blip == 0.0 and iters < 25 do
                    blip = MAP.BLIP_ADD_FOR_ENTITY(style, veh)
                    iters = iters + 1
                end
            
                if blip_info.modifier then
                    MAP.BLIP_ADD_MODIFIER(blip, blip_info.modifier)
                end

                MAP.SET_BLIP_SPRITE(blip, MISC.GET_HASH_KEY(blip_info.sprite), true)
                MAP.SET_BLIP_SCALE(blip, blip_info.scale)
                MAP._SET_BLIP_NAME(blip, blip_info.name)
            end
        end
        
        return veh
    else
        DisplayError(true, "Not valid model " .. model)
    end

    return nil
end

function missionUtils.CreateMissionPed(model, coords, heading, outfit, place_on_ground, blip_info)
    if STREAMING.IS_MODEL_IN_CDIMAGE(model) and STREAMING.IS_MODEL_VALID(model) then
        STREAMING.REQUEST_MODEL(model, true)
        
        local iters = 0
        while not STREAMING.HAS_MODEL_LOADED(model) do
            if iters > 50 then
                DisplayError(true, "Failed to load model " .. model)
                return nil
            end

            Wait(100)
            iters = iters + 1
        end

        local ped = PED.CREATE_PED(model, coords.x, coords.y, coords.z, heading, false, false, true, true)
        if ped ~= 0.0 and ENTITY.DOES_ENTITY_EXIST(ped) then
            networkUtils.RegisterAsNetwork(ped)

            ENTITY.SET_ENTITY_AS_MISSION_ENTITY(ped, true, true)

            if outfit then
                PED._EQUIP_META_PED_OUTFIT_PRESET(ped, outfit, true) 
            else
                PED._SET_RANDOM_OUTFIT_VARIATION(ped, true)
            end
            
            ENTITY.SET_ENTITY_VISIBLE(ped, true)
            PED.CLEAR_PED_ENV_DIRT(ped)

            if place_on_ground then
                ENTITY.PLACE_ENTITY_ON_GROUND_PROPERLY(ped, true)
            end
            if blip_info ~= nil then
                local style = blips.blip_styles.BLIP_STYLE_CREATOR_DEFAULT
                if blip_info.style then
                    style = blip_info.style
                end
                
                local blip = 0.0
                local iters = 0
                while blip == 0.0 and iters < 25 do
                    blip = MAP.BLIP_ADD_FOR_ENTITY(style, ped)
                    iters = iters + 1
                end

                if blip_info.modifier then
                    MAP.BLIP_ADD_MODIFIER(blip, blip_info.modifier)
                end

                MAP.SET_BLIP_SPRITE(blip, MISC.GET_HASH_KEY(blip_info.sprite), true)
                MAP.SET_BLIP_SCALE(blip, blip_info.scale)
                MAP._SET_BLIP_NAME(blip, blip_info.name)
            end
        end
        
        return ped
    else
        DisplayError(true, "Not valid model " .. model)
    end

    return nil
end

function missionUtils.CreateMissionPedInVehicle(vehicle, seat, model, outfit, blip_info)
    local coords = ENTITY.GET_ENTITY_COORDS(vehicle, true, true)
    coords.x = coords.x+2.0

    local ped = missionUtils.CreateMissionPed(model, coords, 0.0, outfit, true, blip_info)

    if ped then
        PED.SET_PED_INTO_VEHICLE(ped, vehicle, seat)
    end

    return ped
end

function missionUtils.CreateMissionPedOnMount(mount, seat, model, outfit, blip_info)
    local coords = ENTITY.GET_ENTITY_COORDS(mount, true, true)
    coords.x = coords.x+1.0

    local ped = missionUtils.CreateMissionPed(model, coords, 0.0, outfit, true, blip_info)

    if ped then
        PED.SET_PED_ONTO_MOUNT(ped, mount, seat, true)
    end

    return ped
end

function missionUtils.CreatePropSet(propset, coords, heading)
    PROPSET._REQUEST_PROP_SET(propset)

    local iters = 0
    while not PROPSET._HAS_PROP_SET_LOADED(propset) do
        if iters > 50 then
            DisplayError(true, "Failed to load propset " .. propset)
            return nil
        end

        Wait(100)
        iters = iters + 1
    end

    local propset_id = PROPSET._CREATE_PROP_SET_2(propset, coords.x, coords.y, coords.z, 0, heading, 1200.0, false, true)
    PROPSET._RELEASE_PROP_SET(propset)

    return propset_id
end

function missionUtils.AddBlipForEntity(entity, style, modifier, sprite, scale, name)
    local blip_style = blips.blip_styles.BLIP_STYLE_CREATOR_DEFAULT
    if style then
        blip_style = style
    end

    local blip = 0
    local iters = 0
    while blip == 0.0 and iters < 25 do
        blip = MAP.BLIP_ADD_FOR_ENTITY(blip_style, entity) --style
        iters = iters + 1
    end

    if blip then
        if modifier then
            MAP.BLIP_ADD_MODIFIER(blip, modifier)
        end

        MAP.SET_BLIP_SPRITE(blip, MISC.GET_HASH_KEY(sprite), true) --sprite
        MAP.SET_BLIP_SCALE(blip, scale)
        MAP._SET_BLIP_NAME(blip, name)
    end

    return blip
end

function missionUtils.DeleteMissionObject(obj)  
    local iters = 0

    local objp = NewObject(obj)

    while ENTITY.DOES_ENTITY_EXIST(obj) and iters < 5 do
        OBJECT.DELETE_OBJECT(objp)

        iters = iters + 1
        Wait(1)
    end

    Delete(objp)

    if ENTITY.DOES_ENTITY_EXIST(obj) then
        local objp = NewObject(obj)
        ENTITY.SET_ENTITY_AS_NO_LONGER_NEEDED(objp)
        ENTITY.SET_ENTITY_COORDS_NO_OFFSET(obj, 4607.0, 813.0, 100.0, false, false, false)
        OBJECT.DELETE_OBJECT(objp)

        if Game.ReadInt(objp) == 0.0 and ENTITY.DOES_ENTITY_EXIST(obj) then
            local objp = NewObject(obj)

            ENTITY.DELETE_ENTITY(objp)

            Delete(objp)
        end

        Delete(objp)
    end
end

function missionUtils.DeleteMissionPed(ped) 
    local iters = 0

    local pedp = NewPed(ped)

    while ENTITY.DOES_ENTITY_EXIST(ped) and iters < 5 do
        PED.DELETE_PED(pedp)

        iters = iters + 1
        Wait(1)
    end

    Delete(pedp)

    if ENTITY.DOES_ENTITY_EXIST(ped) then
        --ENTITY.DELETE_ENTITY(ped)
        --ENTITY._DELETE_ENTITY_2(ped)
        local pedp = NewPed(ped)

        ENTITY.SET_ENTITY_INVINCIBLE(ped, false)
        ENTITY.SET_ENTITY_HEALTH(ped, 0, 0)
        ENTITY.SET_ENTITY_AS_NO_LONGER_NEEDED(pedp)
        ENTITY.SET_ENTITY_COORDS_NO_OFFSET(ped, 4607.0, 813.0, 100.0, false, false, false)
        PED.DELETE_PED(pedp)

        if Game.ReadInt(pedp) == 0.0 and ENTITY.DOES_ENTITY_EXIST(ped) then
            local pedp = NewPed(ped)

            ENTITY.DELETE_ENTITY(pedp)

            Delete(pedp)
        end

        Delete(pedp)
    end
end

function missionUtils.DeleteMissionVehicle(veh)
    local iters = 0

    local vehp = NewVehicle(veh)

    while ENTITY.DOES_ENTITY_EXIST(veh) and iters < 5 do
        VEHICLE.DELETE_VEHICLE(vehp)

        iters = iters + 1
        Wait(1)
    end

    Delete(vehp)

    if ENTITY.DOES_ENTITY_EXIST(veh) then
        local vehp = NewVehicle(veh)

        ENTITY.SET_ENTITY_AS_NO_LONGER_NEEDED(vehp)
        ENTITY.SET_ENTITY_COORDS_NO_OFFSET(veh, 4607.0, 813.0, 100.0, false, false, false)
        VEHICLE.DELETE_VEHICLE(vehp)

        if Game.ReadInt(vehp) == 0.0 and ENTITY.DOES_ENTITY_EXIST(veh) then
            local vehp = NewVehicle(veh)

            ENTITY.DELETE_ENTITY(vehp)

            Delete(vehp)
        end

        Delete(vehp)
    end
end

function missionUtils.DeleteMissionPropSet(propset_id)
    PROPSET._SET_PROP_SET_AS_NO_LONGER_NEEDED(propset_id)
    PROPSET._DELETE_PROP_SET(propset_id, true, true)
end

function missionUtils.RemoveBlipFromEntity(entity)
    local iters = 0

    local blip = MAP.GET_BLIP_FROM_ENTITY(entity)
    
    while MAP.DOES_BLIP_EXIST(blip) and iters < 5 do
        local blipp = NewPed(blip)
        MAP.REMOVE_BLIP(blipp)
        Delete(blipp)
        
        iters = iters + 1
        Wait(5)
    end
end

function missionUtils.CreateCamera(x, y, z, headingX, headingY, headingZ, transitionTime)
    local cam = CAM.CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", true)
    CAM.SET_CAM_COORD(cam, x, y, z)
    CAM.SET_CAM_ROT(cam, headingZ, headingY, headingX, 2)
    CAM.RENDER_SCRIPT_CAMS(true, true, transitionTime, true, true, 0)

    return cam
end


function missionUtils.DeleteCamera(camera, transitionTime)
    CAM.RENDER_SCRIPT_CAMS(false, true, transitionTime, true, true, 0)
    CAM.DESTROY_CAM(camera, false)
end

return missionUtils