local blips = require("blips")

local networkUtils = { }

--- Sends a request to other players to allow the transfer of control of an entity.
-- @param entity number: The ID of the entity.
-- @return nil: This function does not return a value.
function networkUtils.RequestControlOf(entity)
    NETWORK.NETWORK_REQUEST_CONTROL_OF_ENTITY(entity)
    
    for i = 1, 51 do
        if NETWORK.NETWORK_HAS_CONTROL_OF_ENTITY(entity) then
            break
        end

        NETWORK.NETWORK_REQUEST_CONTROL_OF_ENTITY(entity)
    end
end

--- Registers the entity on the network and then the entity will be visible to all players
-- @param entity number: The ID of the entity.
-- @return nil: This function does not return a value.
function networkUtils.RegisterAsNetwork(entity)
    NETWORK.NETWORK_REGISTER_ENTITY_AS_NETWORKED(entity)
    Wait(1)
    networkUtils.RequestControlOf(entity)
    local netid = NETWORK.NETWORK_GET_NETWORK_ID_FROM_ENTITY(entity)
    NETWORK.SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(netid, 1)
end


function networkUtils.CreateNetObject(model, coords)
    if STREAMING.IS_MODEL_IN_CDIMAGE(model) and STREAMING.IS_MODEL_VALID(model) then
        STREAMING.REQUEST_MODEL(model, true)
        
        local iters = 0
        while not STREAMING.HAS_MODEL_LOADED(model) do
            if iters > 50 then
                GCT.DisplayError(false, "Failed to load model " .. model)
                return nil
            end

            Wait(100)
            iters = iters + 1
        end

        local obj = OBJECT.CREATE_OBJECT(model, coords.x, coords.y, coords.z, false, false, true, false, false) --https://www.unknowncheats.me/forum/red-dead-redemption-2-a/364651-red-dead-redemption-2-scripting-20.html
        if obj ~= 0.0 and ENTITY.DOES_ENTITY_EXIST(obj) then
            networkUtils.RegisterAsNetwork(obj)
            ENTITY.SET_ENTITY_COLLISION(obj, true, true)
            OBJECT.PLACE_OBJECT_ON_GROUND_PROPERLY(obj, true)
        end

        STREAMING.SET_MODEL_AS_NO_LONGER_NEEDED(model)
        
        return obj
    else
        DisplayError(false, "Not valid model " .. model)
    end

    return nil
end

function networkUtils.CreateNetPed(model, coords, heading, blip_info)
    if STREAMING.IS_MODEL_IN_CDIMAGE(model) and STREAMING.IS_MODEL_VALID(model) then
        STREAMING.REQUEST_MODEL(model, true)
        
        local iters = 0
        while not STREAMING.HAS_MODEL_LOADED(model) do
            if iters > 50 then
                GCT.DisplayError(false, "Failed to load model " .. model)
                return nil
            end

            Wait(100)
            iters = iters + 1
        end

        local ped = PED.CREATE_PED(model, coords.x, coords.y, coords.z, heading, false, false, true, true)
        if ped ~= 0.0 and ENTITY.DOES_ENTITY_EXIST(ped) then
            networkUtils.RegisterAsNetwork(ped)
            PED._SET_RANDOM_OUTFIT_VARIATION(ped, true)
            ENTITY.SET_ENTITY_VISIBLE(ped, true)
            ENTITY.PLACE_ENTITY_ON_GROUND_PROPERLY(ped, true)
            PED.CLEAR_PED_ENV_DIRT(ped)
            
            if blip_info ~= nil then
                local blip_style = blips.blip_styles.BLIP_STYLE_CREATOR_DEFAULT
                if blip_info["style"] then
                    blip_style = blip_info["style"]
                end

                local blip = MAP.BLIP_ADD_FOR_ENTITY(blip_style, ped)

                if blip_info["modifier"] then
                    MAP.BLIP_ADD_MODIFIER(blip, blip_info["modifier"])
                end

                MAP.SET_BLIP_SPRITE(blip, MISC.GET_HASH_KEY(blip_info["sprite"]), true)
                MAP.SET_BLIP_SCALE(blip, blip_info["scale"])
                MAP._SET_BLIP_NAME(blip, blip_info["name"])
            end
        end
        STREAMING.SET_MODEL_AS_NO_LONGER_NEEDED(model)
        
        return ped
    else
        DisplayError(false, "Not valid model " .. model)
    end

    return nil
end

function networkUtils.CreateNetVehicle(model, coords, heading, blip_info)
    if STREAMING.IS_MODEL_IN_CDIMAGE(model) and STREAMING.IS_MODEL_VALID(model) then
        STREAMING.REQUEST_MODEL(model, true)
        
        local iters = 0
        while not STREAMING.HAS_MODEL_LOADED(model) do
            if iters > 50 then
                GCT.DisplayError(false, "Failed to load model " .. model)
                return nil
            end
            
            Wait(100)
            iters = iters + 1
        end

        local veh = VEHICLE.CREATE_VEHICLE(model, coords.x, coords.y, coords.z, heading, false, false, false, true)
        if veh ~= 0.0 and ENTITY.DOES_ENTITY_EXIST(veh) then
            networkUtils.RegisterAsNetwork(veh)
            VEHICLE.SET_VEHICLE_ON_GROUND_PROPERLY(veh, true)
            VEHICLE.SET_VEHICLE_ENGINE_ON(veh, true, true)
            
            if blip_info ~= nil then
                local blip_style = blips.blip_styles.BLIP_STYLE_CREATOR_DEFAULT
                if blip_info["style"] then
                    blip_style = blip_info["style"]
                end
                
                local blip = MAP.BLIP_ADD_FOR_ENTITY(blip_style, veh)

                if blip_info["modifier"] then
                    MAP.BLIP_ADD_MODIFIER(blip, blip_info["modifier"])
                end

                MAP.SET_BLIP_SPRITE(blip, MISC.GET_HASH_KEY(blip_info["sprite"]), true)
                MAP.SET_BLIP_SCALE(blip, blip_info["scale"])
                MAP._SET_BLIP_NAME(blip, blip_info["name"])
            end
        end

        STREAMING.SET_MODEL_AS_NO_LONGER_NEEDED(model)
        
        return veh
    else
        DisplayError(false, "Not valid model " .. model)
    end

    return nil
end

function networkUtils.DeleteNetObject(obj)  
    networkUtils.RequestControlOf(obj)
    ENTITY.SET_ENTITY_AS_MISSION_ENTITY(obj, true, true)
    
    local objp = NewObject(obj)
    
    OBJECT.DELETE_OBJECT(objp)
    
    Delete(objp)
end

function networkUtils.DeleteNetPed(ped) 
    networkUtils.RequestControlOf(ped)
    ENTITY.SET_ENTITY_AS_MISSION_ENTITY(ped, true, true)
    
    local pedp = NewPed(ped)
    
    PED.DELETE_PED(pedp)
    
    Delete(pedp)
end

function networkUtils.DeleteNetVehicle(veh)
    networkUtils.RequestControlOf(veh)
    ENTITY.SET_ENTITY_AS_MISSION_ENTITY(veh, true, true)
    
    local vehp = NewVehicle(veh)
    
    VEHICLE.DELETE_VEHICLE(vehp)
    
    Delete(vehp)
end

return networkUtils