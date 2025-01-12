local configUtils = require("config_utils")
local mathUtils = require("math_utils")
local missionUtils = require("mission_utils")
local playerUtils = require("player_utils")
local Entity = require("entity")
local graphics = require("graphics++")
local graphics_base = require("graphics_base")

local IS_PED_A_PLAYER = HashString("IS_PED_A_PLAYER")
local GET_ENTITY_TYPE = HashString("GET_ENTITY_TYPE")
local GET_ENTITY_MODEL = HashString("GET_ENTITY_MODEL")
local GET_ENTITY_MAX_HEALTH = HashString("GET_ENTITY_MAX_HEALTH")
local GET_ENTITY_HEALTH = HashString("GET_ENTITY_HEALTH")
local GET_PED_MONEY = HashString("GET_PED_MONEY")
local _GET_PED_STAMINA = HashString("_GET_PED_STAMINA")
local _GET_PED_MAX_STAMINA = HashString("_GET_PED_MAX_STAMINA")
local NETWORK_GET_PLAYER_INDEX_FROM_PED = HashString("NETWORK_GET_PLAYER_INDEX_FROM_PED")
local GET_PLAYER_NAME = HashString("GET_PLAYER_NAME")
local GET_PLAYER_WANTED_LEVEL = HashString("GET_PLAYER_WANTED_LEVEL")
local GET_PLAYER_INVINCIBLE = HashString("GET_PLAYER_INVINCIBLE")
local NETWORK_GET_AVERAGE_LATENCY = HashString("NETWORK_GET_AVERAGE_LATENCY")

local freeCamActive = false
local speed = nil
local speedmult = 1.0
local sensitivity = 0.1
local waitTime = 100

local object = nil
local objectCoords = nil
local freeCamCamera = nil
local lastMousePos = { x = 0, y = 0 }

local cameraPitch = 0.0
local cameraYaw = 0.0
local cameraHeading = 0.0

local sightShape = nil
local prompt = { background = nil, text_entity_type = nil, text_entity_id = nil, text_entity_model = nil, text_entity_health = nil, text_ped_stamina = nil, text_ped_money = nil,
                 text_player_name = nil, text_player_wanted = nil, text_player_god_mode = nil, text_player_ping = nil, text_vehicle_passangers = nil,
                 text_vehicle_doors_locked = nil, text_vehicle_max_speed = nil, text_object_broken = nil }

local FreeCamKey = nil
local FreeCamMoveForwardKey = nil
local FreeCamMoveBackwardKey = nil
local FreeCamMoveLeftKey = nil
local FreeCamMoveRightKey = nil
local FreeCamMoveUpKey = nil
local FreeCamMoveDownKey = nil
local FreeCamSprintKey = nil
local FreeCamTeleportToCamKey = nil
local GamepadFreeCamKey = nil
local GamepadFreeCamMoveUpKey = nil
local GamepadFreeCamMoveDownKey = nil
local GamepadFreeCamSprintKey = nil
local GamepadFreeCamTeleportToCamKey = nil

local FreeCamGamepad = Gamepad.Gamepad()
local GamepadPressedKey = nil

function EnableFreeCam()
    objectCoords = ENTITY.GET_ENTITY_COORDS(PLAYER.PLAYER_PED_ID(), true, true)
    objectCoords.x = objectCoords.x + ENTITY.GET_ENTITY_FORWARD_X(PLAYER.PLAYER_PED_ID())
    objectCoords.y = objectCoords.y + ENTITY.GET_ENTITY_FORWARD_Y(PLAYER.PLAYER_PED_ID())

    object = OBJECT.CREATE_OBJECT_NO_OFFSET(MISC.GET_HASH_KEY("p_decapitated_head01x_2"), objectCoords.x, objectCoords.y, objectCoords.z, false, false, false, false)
    ENTITY.SET_ENTITY_AS_MISSION_ENTITY(object, false, false)
    ENTITY.FREEZE_ENTITY_POSITION(object, true)
    STREAMING.SET_FOCUS_ENTITY(object)

    local camRot = CAM.GET_GAMEPLAY_CAM_ROT(2)
    
    ENTITY.SET_ENTITY_HEADING(object, CAM.GET_GAMEPLAY_CAM_RELATIVE_HEADING())
    
    ENTITY.SET_ENTITY_VISIBLE(object, false)
    ENTITY.SET_ENTITY_ALPHA(object, 0, true)

    local objectP = NewObject(object)
    ENTITY.SET_OBJECT_AS_NO_LONGER_NEEDED(objectP)
    Delete(objectP)

    freeCamCamera = missionUtils.CreateCamera(objectCoords.x, objectCoords.y, objectCoords.z, camRot.x, camRot.y, 0.0, 500)

    CAM.ATTACH_CAM_TO_ENTITY(freeCamCamera, object, 0.0, 0.0, 0.0, false)

    local camRot = CAM.GET_CAM_ROT(freeCamCamera, 2)

    cameraPitch = camRot.x
    cameraYaw = camRot.y
    cameraHeading = camRot.z

    CAM.SET_CAM_ROT(freeCamCamera, cameraPitch, cameraYaw, cameraHeading, 2)

    local mousePos = GetMousePos()
    lastMousePos.x = mousePos.x
    lastMousePos.y = mousePos.y
    
    PLAYER.SET_PLAYER_CONTROL(PLAYER.PLAYER_ID(), false, 4, false)

    local DisplaX, DisplaY = graphics_base.GetDisplaySize()

    SetMousePos(DisplaX/2, DisplaY/2)

    freeCamActive = true
    SetGlobalVariableValue("feature_fast_free_cam_free_cam_enabled", 1)
    speed = 1.0
end


function DisableFreeCam()
    if freeCamActive then
        missionUtils.DeleteCamera(freeCamCamera, 500)
        
        DeleteSightShape()
        DeletePrompt()

        PLAYER.SET_PLAYER_CONTROL(PLAYER.PLAYER_ID(), true, 0, true)

        STREAMING.SET_FOCUS_ENTITY(PLAYER.PLAYER_PED_ID())
        ENTITY.SET_ENTITY_COORDS_NO_OFFSET(object, 100.0, -242.5, 0.0, true, true, true)

        local objectP = NewObject(object)

        local iters = 0
        while ScriptStillWorking and ENTITY.DOES_ENTITY_EXIST(object) and iters < 50 do
            OBJECT.DELETE_OBJECT(objectP)

            iters = iters + 1

            Wait(10)
        end

        Delete(objectP)

        freeCamActive = false
        SetGlobalVariableValue("feature_fast_free_cam_free_cam_enabled", 0)

        Wait(500)
    end
end

function RotationToDirection(rot)
    local radiansZ =  math.rad(rot.z)
    local radiansX = math.rad(rot.x)
    local num = math.abs(math.cos(radiansX))
    
    local dir = {}
    dir.x = -math.sin(radiansZ) * num
    dir.y = math.cos(radiansZ) * num
    dir.z = math.sin(radiansX)
    
    return dir
end

function CreateSightShape()
    local DisplaX, DisplaY = graphics_base.GetDisplaySize()
    sightShape = graphics.Ellipse.DrawEllipse(DisplaX/2, DisplaY/2, 2, 2, 255, 0, 0, 255)
end

function DeleteSightShape()
    if sightShape then
        sightShape:Delete()
        sightShape = nil
    end
end

function DeletePrompt()
    if prompt.background then
        prompt.background:Delete()
        prompt.text_entity_type:Delete()
        prompt.text_entity_id:Delete()
        prompt.text_entity_model:Delete()
        prompt.text_entity_health:Delete()

        if prompt.text_ped_stamina then
            prompt.text_ped_stamina:Delete()
        end
        if prompt.text_ped_money then
            prompt.text_ped_money:Delete()
        end

        if prompt.text_player_name then
            prompt.text_player_name:Delete()
        end
        if prompt.text_player_wanted then
            prompt.text_player_wanted:Delete()
        end
        if prompt.text_player_god_mode then
            prompt.text_player_god_mode:Delete()
        end
        if prompt.text_player_ping then
            prompt.text_player_ping:Delete()
        end
        if prompt.text_vehicle_passangers then
            prompt.text_vehicle_passangers:Delete()
        end
        if prompt.text_vehicle_doors_locked then
            prompt.text_vehicle_doors_locked:Delete()
        end
        if prompt.text_vehicle_max_speed then
            prompt.text_vehicle_max_speed:Delete()
        end
        if prompt.text_object_broken then
            prompt.text_object_broken:Delete()
        end

        prompt = {  background = nil, text_entity_type = nil, text_entity_id = nil, text_entity_model = nil, text_entity_health = nil, text_ped_stamina = nil, text_ped_money = nil,
                    text_player_name = nil, text_player_wanted = nil, text_player_god_mode = nil, text_player_ping = nil, text_vehicle_passangers = nil,
                    text_vehicle_doors_locked = nil, text_vehicle_max_speed = nil, text_object_broken = nil }
    end
end

function GetInfoAboutObject()
    if not sightShape then
        CreateSightShape()
    end

    local startpoint = objectCoords
    local endpoint = mathUtils.SumVectors(objectCoords, mathUtils.MultVector(RotationToDirection({x = cameraPitch, y = cameraYaw, z = cameraHeading}), 35.0))

    local rayHandle = SHAPETEST.START_EXPENSIVE_SYNCHRONOUS_SHAPE_TEST_LOS_PROBE(startpoint.x, startpoint.y, startpoint.z, endpoint.x, endpoint.y, endpoint.z, -1, object, 7)
    
    local hitP = New(4)
    local endCoordsP = NewVector3({x = 0, y = 0, z = 0})
    local surfaceNormalP = NewVector3({x = 0, y = 0, z = 0})
    local entityHitP = New(4)

    if SHAPETEST.GET_SHAPE_TEST_RESULT(rayHandle, hitP, endCoordsP, surfaceNormalP, entityHitP) then
        local target = Game.ReadInt(entityHitP)
        if target ~= 0.0 then
            local entityType = NativeCall(GET_ENTITY_TYPE, "integer32", {target}) --ENTITY.GET_ENTITY_TYPE(target)
            local entityModel = NativeCall(GET_ENTITY_MODEL, "integer32", {target})--ENTITY.GET_ENTITY_MODEL(target)
            local entityMaxHealth = NativeCall(GET_ENTITY_MAX_HEALTH, "integer32", {target})--ENTITY.GET_ENTITY_MAX_HEALTH(target)
            local entityHealth = NativeCall(GET_ENTITY_HEALTH, "integer32", {target})--ENTITY.GET_ENTITY_HEALTH(target)
            
            local targetType = "**Invalid**"

            if entityType == Entity.EntityType.OBJECT then
                targetType = "Object"
            elseif entityType == Entity.EntityType.PED and NativeCall(IS_PED_A_PLAYER, "integer32", {target}) then --PED.IS_PED_A_PLAYER(target)
                targetType = "Player"
            elseif entityType == Entity.EntityType.PED then
                targetType = "Ped"
            elseif entityType == Entity.EntityType.VEHICLE then
                targetType = "Vehicle"
            end

            --Ped
            local pedMoney = nil
            local pedStamina = nil
            local pedMaxStamina = nil
            if entityType == Entity.EntityType.PED then
                pedMoney = NativeCall(GET_PED_MONEY, "integer32", {target}) -- PED.GET_PED_MONEY(target)
                pedStamina = NativeCall(_GET_PED_STAMINA, "number", {target}) -- PED._GET_PED_STAMINA(target)
                pedMaxStamina = NativeCall(_GET_PED_MAX_STAMINA, "number", {target}) -- PED._GET_PED_MAX_STAMINA(target)
            end

            --Player
            local playerName = nil
            local playerWantedLevel = nil
            local playerGodMode = nil
            local playerPing = nil
            if targetType == "Player" then
                local player = NativeCall(NETWORK_GET_PLAYER_INDEX_FROM_PED, "integer32", {target}) -- NETWORK.NETWORK_GET_PLAYER_INDEX_FROM_PED(target)
                playerName = NativeCall(GET_PLAYER_NAME, "string", {player}) -- PLAYER.GET_PLAYER_NAME(player)
                playerWantedLevel = NativeCall(GET_PLAYER_WANTED_LEVEL, "integer32", {player}) -- PLAYER.GET_PLAYER_WANTED_LEVEL(player) 
                playerGodMode = NativeCall(GET_PLAYER_INVINCIBLE, "boolean", {player}) -- PLAYER.GET_PLAYER_INVINCIBLE(player)
                playerPing = NativeCall(NETWORK_GET_AVERAGE_LATENCY, "number", {player}) -- NETWORK.NETWORK_GET_AVERAGE_LATENCY(player)
            end

            --Vehicle
            local vehiclePassangersCount = nil
            local vehicleMaxPassangersCount = nil
            local vehicleMaxSpeed = nil
            local vehicleIsDoordsLocked = nil
            if entityType == Entity.EntityType.VEHICLE then
                vehiclePassangersCount = VEHICLE.GET_VEHICLE_NUMBER_OF_PASSENGERS(target)
                vehicleMaxPassangersCount = VEHICLE.GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(target)
                vehicleMaxSpeed = VEHICLE.GET_VEHICLE_ESTIMATED_MAX_SPEED(target)
                vehicleIsDoordsLocked = VEHICLE.GET_VEHICLE_DOORS_LOCKED_FOR_PLAYER(target, PLAYER.PLAYER_ID())
            end

            --Object
            local objectIsBroken = nil
            if entityType == Entity.EntityType.OBJECT then
                objectIsBroken = OBJECT.HAS_OBJECT_BEEN_BROKEN(target)
            end

            if not prompt.background then
                local DisplaX, DisplaY = graphics_base.GetDisplaySize()

                local backgroundX = DisplaX/2+5
                local backgroundY = DisplaY/2 - 225

                prompt.background = graphics.Rect.DrawRect(backgroundX, backgroundY, 190, 220, 20, 20, 20, 200, 1)
                prompt.text_entity_type = graphics.Text.DrawText(targetType, backgroundX + 50, backgroundY + 5, 255, 255, 255, 255, "", 16)
                prompt.text_entity_id = graphics.Text.DrawText("ID: " .. target, backgroundX + 5, backgroundY + 30, 255, 255, 255, 255, "", 16)
                prompt.text_entity_model = graphics.Text.DrawText("Model: " .. string.format("0x%x", entityModel), backgroundX + 5, backgroundY + 50, 255, 255, 255, 255, "", 16)
                prompt.text_entity_health = graphics.Text.DrawText("Health: " .. entityHealth .. " / " .. entityMaxHealth, backgroundX + 5, backgroundY + 70, 255, 255, 255, 255, "", 16)

                if entityType == Entity.EntityType.PED then
                    if pedStamina and pedMaxStamina then
                        prompt.text_ped_stamina = graphics.Text.DrawText("Stamina: " .. pedStamina .. " / " .. pedMaxStamina, backgroundX + 5, backgroundY + 90, 255, 255, 255, 255, "", 16)
                    else
                        prompt.text_ped_stamina = graphics.Text.DrawText("Stamina: " .. 0, backgroundX + 5, backgroundY + 90, 255, 255, 255, 255, "", 16)
                    end
                    if pedMoney then
                        prompt.text_ped_money = graphics.Text.DrawText("Money: " .. pedMoney, backgroundX + 5, backgroundY + 110, 255, 255, 255, 255, "", 16)
                    else
                        prompt.text_ped_money = graphics.Text.DrawText("Money: " .. 0, backgroundX + 5, backgroundY + 110, 255, 255, 255, 255, "", 16)
                    end
                end
                if targetType == "Player" then
                    if playerName then
                        prompt.text_player_name = graphics.Text.DrawText("Name: " .. playerName, backgroundX + 5, backgroundY + 130, 255, 255, 255, 255, "", 16)
                    else
                        prompt.text_player_name = graphics.Text.DrawText("Name: " .. "**Invalid**", backgroundX + 5, backgroundY + 130, 255, 255, 255, 255, "", 16)
                    end
                    if playerWantedLevel then
                        prompt.text_player_wanted = graphics.Text.DrawText("Wanted: " .. playerWantedLevel, backgroundX + 5, backgroundY + 150, 255, 255, 255, 255, "", 16)
                    else
                        prompt.text_player_wanted = graphics.Text.DrawText("Wanted: " .. 0, backgroundX + 5, backgroundY + 150, 255, 255, 255, 255, "", 16)
                    end
                    if playerGodMode then
                        prompt.text_player_god_mode = graphics.Text.DrawText("God mode: " .. "Yes", backgroundX + 5, backgroundY + 170, 255, 255, 255, 255, "", 16)
                    else
                        prompt.text_player_god_mode = graphics.Text.DrawText("God mode: " .. "No", backgroundX + 5, backgroundY + 170, 255, 255, 255, 255, "", 16)
                    end
                    if playerPing then
                        prompt.text_player_ping = graphics.Text.DrawText("Ping: " .. playerPing, backgroundX + 5, backgroundY + 190, 255, 255, 255, 255, "", 16)
                    else
                        prompt.text_player_ping = graphics.Text.DrawText("Ping: " .. "**Invalid**", backgroundX + 5, backgroundY + 190, 255, 255, 255, 255, "", 16)
                    end
                end

                if entityType == Entity.EntityType.VEHICLE then
                    if vehiclePassangersCount and vehicleMaxPassangersCount then
                        prompt.text_vehicle_passangers = graphics.Text.DrawText("Passangers: " .. vehiclePassangersCount .. " / " .. vehicleMaxPassangersCount, backgroundX + 5, backgroundY + 90, 255, 255, 255, 255, "", 16)
                    else
                        prompt.text_vehicle_passangers = graphics.Text.DrawText("Passangers: " .. "**Invalid**", backgroundX + 5, backgroundY + 90, 255, 255, 255, 255, "", 16)
                    end

                    if vehicleIsDoordsLocked then
                        prompt.text_vehicle_doors_locked = graphics.Text.DrawText("Doors locked: " .. "Yes", backgroundX + 5, backgroundY + 110, 255, 255, 255, 255, "", 16)
                    else
                        prompt.text_vehicle_doors_locked = graphics.Text.DrawText("Doors locked: " .. "No", backgroundX + 5, backgroundY + 110, 255, 255, 255, 255, "", 16)
                    end
                    if vehicleMaxSpeed then
                        prompt.text_vehicle_max_speed = graphics.Text.DrawText("Max speed: " .. vehicleMaxSpeed, backgroundX + 5, backgroundY + 130, 255, 255, 255, 255, "", 16)
                    else
                        prompt.text_vehicle_max_speed = graphics.Text.DrawText("Max speed: " .. "**Invalid**", backgroundX + 5, backgroundY + 130, 255, 255, 255, 255, "", 16)
                    end
                end

                if entityType == Entity.EntityType.OBJECT then
                    if objectIsBroken then
                        prompt.text_object_broken = graphics.Text.DrawText("Broken: " .. "Yes", backgroundX + 5, backgroundY + 90, 255, 255, 255, 255, "", 16)
                    else
                        prompt.text_object_broken = graphics.Text.DrawText("Broken: " .. "No", backgroundX + 5, backgroundY + 90, 255, 255, 255, 255, "", 16)
                    end
                end
            else    
                prompt.text_entity_type:SetLabel(targetType)
                prompt.text_entity_id:SetLabel("ID: " .. target)
                prompt.text_entity_model:SetLabel("Model: " .. string.format("0x%x", entityModel))
                prompt.text_entity_health:SetLabel("Health: " .. entityHealth .. " / " .. entityMaxHealth)

                if entityType == Entity.EntityType.PED then
                    if pedStamina and pedMaxStamina and prompt.text_ped_stamina then
                        prompt.text_ped_stamina:SetLabel("Stamina: " .. pedStamina .. " / " .. pedMaxStamina)
                    end
                    if pedMoney and prompt.text_ped_money then
                        prompt.text_ped_money:SetLabel("Money: " .. pedMoney)
                    end
                    
                end
                if targetType == "Player" then
                    if playerName and prompt.text_player_name then
                        prompt.text_player_name:SetLabel("Name: " .. playerName)
                    end
                    if playerWantedLevel and prompt.text_player_wanted then
                        prompt.text_player_wanted:SetLabel("Wanted: " .. playerWantedLevel)
                    end
                    if prompt.text_player_god_mode then
                        if playerGodMode then
                            prompt.text_player_god_mode:SetLabel("God mode: " .. "Yes")
                        else
                            prompt.text_player_god_mode:SetLabel("God mode: " .. "No")
                        end
                    end
                    if playerPing and prompt.text_player_ping then
                        prompt.text_player_ping:SetLabel("Ping: " .. playerPing)
                    end
                end
                if entityType == Entity.EntityType.VEHICLE then
                    if vehiclePassangersCount and vehicleMaxPassangersCount and prompt.text_vehicle_passangers then
                        prompt.text_vehicle_passangers:SetLabel("Passangers: " .. vehiclePassangersCount .. " / " .. vehicleMaxPassangersCount)
                    end
                    if prompt.text_vehicle_doors_locked then
                        if vehicleIsDoordsLocked then
                            prompt.text_vehicle_doors_locked:SetLabel("Doors locked: " .. "Yes")
                        else
                            prompt.text_vehicle_doors_locked:SetLabel("Doors locked: " .. "No")
                        end
                    end
                    if vehicleMaxSpeed and prompt.text_vehicle_max_speed then
                        prompt.text_vehicle_max_speed:SetLabel("Max speed: " .. vehicleMaxSpeed)
                    end
                end
                if entityType == Entity.EntityType.OBJECT then
                    if prompt.text_object_broken then
                        if objectIsBroken then
                            prompt.text_object_broken:SetLabel("Broken: " .. "Yes")
                        else
                            prompt.text_object_broken:SetLabel("Broken: " .. "No")
                        end
                    end
                end
            end
        else
            DeletePrompt()
        end
    end
end

function GetMouseMovement()
    local mousePos = { x = 0, y = 0 }

    if IsGlobalVariableExist("mouse_movement_mouse_x") then
        mousePos.x = GetGlobalVariable("mouse_movement_mouse_x")
    end
    if IsGlobalVariableExist("mouse_movement_mouse_y") then
        mousePos.y = GetGlobalVariable("mouse_movement_mouse_y")
    end
    return mousePos
end

function OnTick()
    if freeCamActive then
        GetInfoAboutObject()
        
        local mousePos = GetMousePos()

        local leftStickX = 0.0
        local leftStickY = 0.0

        local gamepadLeftStickMovement = FreeCamGamepad.GetLeftStickState()
        if gamepadLeftStickMovement then
            leftStickX = gamepadLeftStickMovement.ThumbLX
            leftStickY = gamepadLeftStickMovement.ThumbLY
        end

        local rightStickX = 0.0
        local rightStickY = 0.0

        local gamepadRightStickMovement = FreeCamGamepad.GetRightStickState()
        if gamepadRightStickMovement then
            rightStickX = gamepadRightStickMovement.ThumbRX
            rightStickY = gamepadRightStickMovement.ThumbRY
        end

        if mousePos.x ~= lastMousePos.x or mousePos.y ~= mousePos.y then
            -- Calculate changes in coordinates
            local deltaX = mousePos.x - lastMousePos.x
            local deltaY = mousePos.y - lastMousePos.y
       
            cameraHeading = cameraHeading - (deltaX * sensitivity) -- Y rotation (right-left)
            cameraPitch = cameraPitch - (deltaY * sensitivity) -- X rotation (up and down)

            --ENTITY.SET_ENTITY_ROTATION(object, camRot.x, camRot.y, camRot.z, 2, true)

            -- Updating previous mouse coordinates
            lastMousePos.x = mousePos.x
            lastMousePos.y = mousePos.y

            CAM.SET_CAM_ROT(freeCamCamera, cameraPitch, cameraYaw, cameraHeading, 2)
        end
        if rightStickX ~= 0.0 or rightStickY ~= 0.0 then
            cameraHeading = cameraHeading - (rightStickX * (sensitivity * 70.0)) -- Y rotation (right-left)
            cameraPitch = cameraPitch + (rightStickY * (sensitivity * 70.0)) -- X rotation (up and down)
       
            --ENTITY.SET_ENTITY_ROTATION(object, camRot.x, camRot.y, camRot.z, 2, true)

            CAM.SET_CAM_ROT(freeCamCamera, cameraPitch, cameraYaw, cameraHeading, 2)
        end

        -- convert angles of rotation to radians.
        local heading = math.rad(cameraHeading)
        local pitch = math.rad(cameraPitch)

        local forward = {
            x = -math.sin(heading),
            y = math.cos(heading),
            z = math.sin(pitch)
        }

        -- Normalise the direction vector
        local forwardMagnitude = math.sqrt(forward.x^2 + forward.y^2 + forward.z^2)
        forward.x = forward.x / forwardMagnitude
        forward.y = forward.y / forwardMagnitude
        forward.z = forward.z / forwardMagnitude
            
        -- Set the direction of movement
        local moveVector = { x = 0.0, y = 0.0, z = 0.0 }

        if IsPressedKey(FreeCamTeleportToCamKey) or GamepadPressedKey == GamepadFreeCamTeleportToCamKey then
            ENTITY.SET_ENTITY_COORDS_NO_OFFSET(PLAYER.PLAYER_PED_ID(), objectCoords.x, objectCoords.y, objectCoords.z, true, true, true)

            DisableFreeCam()
            waitTime = 100

            return
        end

        if IsPressedKey(FreeCamSprintKey) or GamepadPressedKey == GamepadFreeCamSprintKey then
            speedmult = 3.0
        end
        if IsPressedKey(FreeCamMoveForwardKey) or leftStickY > 0 then
            moveVector = mathUtils.SumVectors(moveVector, mathUtils.MultVector(forward, speed*speedmult))
        end
        if IsPressedKey(FreeCamMoveLeftKey) or leftStickX < 0 then
            local left = { x = -forward.y, y = forward.x, z = 0.0 }
            moveVector = mathUtils.SumVectors(moveVector, mathUtils.MultVector(left, speed*speedmult))
        end
        if IsPressedKey(FreeCamMoveBackwardKey) or leftStickY < 0 then
            moveVector = mathUtils.SumVectors(moveVector, mathUtils.MultVector(forward, (speed * 1.5) * speedmult))
            moveVector = mathUtils.SubtractVectors(moveVector, mathUtils.MultVector(moveVector, (speed * 1.5) * speedmult))
        end
        if IsPressedKey(FreeCamMoveRightKey) or leftStickX > 0 then
            local right = { x = forward.y, y = -forward.x, z = 0.0 }
            moveVector = mathUtils.SumVectors(moveVector, mathUtils.MultVector(right, speed*speedmult))
        end
        if IsPressedKey(FreeCamMoveUpKey) or GamepadPressedKey == GamepadFreeCamMoveUpKey then
            moveVector.z = moveVector.z + (speed*speedmult / 2.0)
        end
        if IsPressedKey(FreeCamMoveDownKey) or GamepadPressedKey == GamepadFreeCamMoveDownKey then
            moveVector.z = moveVector.z - (speed*speedmult / 2.0)
        end

        speedmult = 1.0
            
        -- Updating object coordinates
        objectCoords = mathUtils.SumVectors(objectCoords, moveVector)

        ENTITY.SET_ENTITY_COORDS_NO_OFFSET(object, objectCoords.x, objectCoords.y, objectCoords.z, true, true, true)
    end
end

function InitializeSettings()
    FreeCamKey = ConvertStringToKeyCode(configUtils.GetFeatureSetting("Hotkeys", "FreeCamKey"))
    FreeCamMoveForwardKey = ConvertStringToKeyCode(configUtils.GetFeatureSetting("Hotkeys", "FreeCamMoveForwardKey"))
    FreeCamMoveBackwardKey = ConvertStringToKeyCode(configUtils.GetFeatureSetting("Hotkeys", "FreeCamMoveBackwardKey"))
    FreeCamMoveLeftKey = ConvertStringToKeyCode(configUtils.GetFeatureSetting("Hotkeys", "FreeCamMoveLeftKey"))
    FreeCamMoveRightKey = ConvertStringToKeyCode(configUtils.GetFeatureSetting("Hotkeys", "FreeCamMoveRightKey"))
    FreeCamMoveUpKey = ConvertStringToKeyCode(configUtils.GetFeatureSetting("Hotkeys", "FreeCamMoveUpKey"))
    FreeCamMoveDownKey = ConvertStringToKeyCode(configUtils.GetFeatureSetting("Hotkeys", "FreeCamMoveDownKey"))
    FreeCamSprintKey = ConvertStringToKeyCode(configUtils.GetFeatureSetting("Hotkeys", "FreeCamSprintKey"))
    FreeCamTeleportToCamKey = ConvertStringToKeyCode(configUtils.GetFeatureSetting("Hotkeys", "FreeCamTeleportToCamKey"))

    GamepadFreeCamKey = configUtils.GetFeatureSetting("Hotkeys", "GamepadFreeCamKey")
    GamepadFreeCamMoveUpKey = configUtils.GetFeatureSetting("Hotkeys", "GamepadFreeCamMoveUpKey")
    GamepadFreeCamMoveDownKey = configUtils.GetFeatureSetting("Hotkeys", "GamepadFreeCamMoveDownKey")
    GamepadFreeCamSprintKey = configUtils.GetFeatureSetting("Hotkeys", "GamepadFreeCamSprintKey")
    GamepadFreeCamTeleportToCamKey = configUtils.GetFeatureSetting("Hotkeys", "GamepadFreeCamTeleportToCamKey")

    RegisterGlobalVariable("feature_fast_free_cam_free_cam_enabled", 0)
end

InitializeSettings()

while ScriptStillWorking do
    GamepadPressedKey = FreeCamGamepad.GetPressedKey(FreeCamGamepad)
    if not GamepadPressedKey then
        GamepadPressedKey = ""
    end

    if IsPressedKey(FreeCamKey) or GamepadPressedKey == GamepadFreeCamKey then
        local skip_input = false
        if GamepadPressedKey == GamepadFreeCamKey then
            skip_input = true

            Wait(100)
            GamepadPressedKey = FreeCamGamepad.GetPressedKey(FreeCamGamepad)
            if GamepadPressedKey == GamepadFreeCamKey then
                Wait(100)
                GamepadPressedKey = FreeCamGamepad.GetPressedKey(FreeCamGamepad)
                if GamepadPressedKey ~= GamepadFreeCamKey then
                    skip_input = false
                end
            end
        end
        if not skip_input and freeCamActive then
            DisableFreeCam()
            waitTime = 100
        elseif not skip_input and GetGlobalVariable("feature_noclip_noclip_enabled") == 0.0 and GetGlobalVariable("feature_fast_run_fast_run_enabled") == 0.0 and playerUtils.IsPlayerPlaying() then
            if not freeCamActive then
                EnableFreeCam()
                waitTime = 0
            end
        end
    end

    if freeCamActive then
        OnTick()
    end
    Wait(waitTime)
end

DisableFreeCam()