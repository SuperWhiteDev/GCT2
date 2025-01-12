local missionUtils = require("mission_utils")
local math_utils = require("math_utils")
local GraphicsBase = require("graphics_base")
local Graphics = require("graphics++")
local weather = require("weather_types")
local weapons = require("weapons")
local blips = require("blips")
local task_flags = require("task_flags")

local is_mission_active = false
local is_mission_initialized = false
local player_has_detected = false

local sadie_waypoint_1 = {x = 253.1189727783203, y = 1036.35107421875, z = 186.84506225585938}
local sadie_waypoint_2 = {x = 246.423583984375, y = 1035.1502685546875, z = 188.31309509277344}
local odriscolls_ranch = {x = 208.78811645507812, y = 992.4566650390625, z = 190.06785583496094}
local money_bag_1 = {x = 197.0285186767578, y = 986.9894409179688, z = 192.3063201904297, heading = 90.0, rotation = {pitch = 0.0, roll = 0.0, yaw = 1.5707963267948966}}

local mission_peds = {}
local mission_vehicles = {}
local mission_objects = {}
local mission_prop_sets = {}
local mission_enemies = {}
local mission_groups = {}


--missionUtils.PlayMusic("LBH_EDW_INTRO_START") Tense music

function isMissionStillActive()
    return is_mission_active and GetGlobalVariable("missions_mission_flag_state") == 2
end

function deleteAllMissionEntities()
    missionUtils.RemoveBlipFromEntity(mission_peds[1])

    for _, ped in pairs(mission_peds) do
        missionUtils.DeleteMissionPed(ped)
        local blip = MAP.GET_BLIP_FROM_ENTITY(ped)
        if blip then
            local blipp = NewPed(blip)
            MAP.REMOVE_BLIP(blipp)
            Delete(blipp)
        end
    end
    for _, veh in pairs(mission_vehicles) do
        missionUtils.DeleteMissionVehicle(veh)
        local blip = MAP.GET_BLIP_FROM_ENTITY(veh)
        if blip then
            local blipp = NewPed(blip)
            MAP.REMOVE_BLIP(blipp)
            Delete(blipp)
        end
    end
    for _, propset_id in pairs(mission_prop_sets) do
        missionUtils.DeleteMissionPropSet(propset_id)
    end
    for _, obj in pairs(mission_objects) do
        missionUtils.DeleteMissionObject(obj)
        local blip = MAP.GET_BLIP_FROM_ENTITY(obj)
        if blip then
            local blipp = NewPed(blip)
            MAP.REMOVE_BLIP(blipp)
            Delete(blipp)
        end
    end
end

function endMission(IsMissionFailed)
    if is_mission_initialized then
        if IsMissionFailed then
            missionUtils.FailMissionScreen()
        else
            missionUtils.MissionCompleteMessage("You successfully destroyed the O'Driscolls' dirty money")
        end

        deleteAllMissionEntities()

        --Closing barn doors
        OBJECT.DOOR_SYSTEM_SET_DOOR_STATE(160425541, 1)
        OBJECT.DOOR_SYSTEM_SET_DOOR_STATE(3167931616, 1)

        missionUtils.FinishMission()

        is_mission_active = false
        is_mission_initialized = false
    end
end

function initializeMission()
    local StartPoint = {x = -242.85110473632812, y = 771.0281982421875, z = 118.08615112304688, heading = 183.6}

    local Sadie = {x = -242.7650146484375, y = 769.2818603515625, z = 118.08499908447266, heading = 358.7}
    local SadieHorse = {x = -249.99217224121094, y = 766.489501953125, z = 117.4679946899414, heading = 287.2}
    local ODriscoll1 = {x = 218.62049865722656, y = 1011.5408203125, z = 188.7357177734375, heading = 10.2} -- near main enter
    local ODriscoll2 = {x = 202.44808959960938, y = 1016.3632202148438, z = 188.56411743164062, heading = 326.0} -- near supply wagon
    local ODriscoll3 = {x = 202.7650604248047, y = 1018.03271484375, z = 188.35340881347656, heading = 210.0} -- near supply wagon
    local ODriscoll4 = {x = 225.5601348876953, y = 1002.4893188476562, z = 189.61962890625, heading = 161.2, action_name = "WORLD_HUMAN_SLEEP_GROUND_ARM", action_condition = "WORLD_HUMAN_SLEEP_GROUND_ARM_FEMALE_A"} -- near tree
    local ODriscoll5 = {x = 235.36663818359375, y = 991.5486450195312, z = 189.55722045898438, heading = 275.1} -- toilet
    local ODriscoll6 = {x = 199.6907196044922, y = 987.9202880859375, z = 190.32508850097656, heading = 289.7} -- Near maxim
    local ODriscoll7 = {x = 205.24452209472656, y = 963.5758666992188, z = 190.57566833496094, heading = 193.5, action_name = "WORLD_HUMAN_GUARD_LANTERN_NERVOUS", action_condition = "WORLD_HUMAN_GUARD_LANTERN_NERVOUS_MALE_B"} -- Near back door
    local ODriscoll8 = {x = 191.11505126953125, y = 991.559814453125, z = 189.92886352539062, heading = 7.0, action_name = "WORLD_HUMAN_SIT_GROUND_COFFEE_DRINK", action_condition = "WORLD_HUMAN_SIT_GROUND_COFFEE_DRINK_FEMALE_A"} --Near campfire
    local ODriscoll9 = {x = 190.35916137695312, y = 992.5963134765625, z = 189.9114227294922, heading = 300.0, action_name = "WORLD_HUMAN_SIT_GROUND_COFFEE_DRINK", action_condition = "WORLD_HUMAN_SIT_GROUND_COFFEE_DRINK_FEMALE_A"} --Near campfire
    local ODriscoll10 = {x = 199.7984619140625, y = 1004.8833618164062, z = 189.64639282226562, heading = 270.7, action_name = "WORLD_HUMAN_SLEEP_GROUND_ARM", action_condition = "WORLD_HUMAN_SLEEP_GROUND_ARM_FEMALE_A" }  --In the tent
    local ODriscoll11 = {x = 194.4931182861328, y = 1004.786376953125, z = 189.5292205810547, heading = 206.4, action_name = "WORLD_HUMAN_SIT_GROUND_COFFEE_DRINK", action_condition = "WORLD_HUMAN_SIT_GROUND_COFFEE_DRINK_FEMALE_A"} --Near campfire
    local ODriscoll12 = {x = 196.10576171875, y = 1001.356337890625,  z = 189.71766662597656, heading = 30.0, action_name = "WORLD_HUMAN_SIT_GROUND_COFFEE_DRINK", action_condition = "WORLD_HUMAN_SIT_GROUND_COFFEE_DRINK_FEMALE_A"} --Near campfire
    local ODriscoll13 = {x = 224.13754272460938, y = 983.8928833007812, z = 190.88502502441406, heading = 230.0} --In house
    local ODriscoll14 = {x = 219.4154052734375, y = 985.704833984375, z = 190.90277099609375, heading = 276.0} --In house
    local ODriscoll15 = {x = 220.60813903808594, y = 985.8724975585938, z = 190.89608764648438, heading = 85.0} --In house
    local ODriscoll16 = {x = 215.82907104492188, y = 990.555419921875, z = 190.12110900878906, heading = 14.0, action_name = "WORLD_HUMAN_GUARD_LANTERN_NERVOUS", action_condition = "WORLD_HUMAN_GUARD_LANTERN_NERVOUS_MALE_B"} --Near house

    local SupplyWagon = { x = 205.50306701660156, y = 1017.6665283203125, z = 188.69065856933594, heading = 270.0}
    local OdoriscollCamp = {x = 195.67721557617188, y = 1002.8211669921875, z = 189.6764678955078, heading = 0.0}
    local Maximgun = {x = 201.55831909179688, y = 989.0, z = 189.0, heading = 285.0}
    local DynamiteBox = {x = 202.9192657470703, y = 984.7610473632812, z = 190.279052734375, heading = 270.0}
    local DynamiteBox2 = {x = 203.9192657470703, y = 984.7610473632812, z = 190.279052734375, heading = 270.0}
    local DynamiteBox3 = {x = 203.0192657470703, y = 985.1610473632812, z = 190.279052734375, heading = 270.0}
    local DynamiteBox4 = {x = 202.1192657470703, y = 984.7610473632812, z = 190.279052734375, heading = 270.0}
    local LanternStick1 = {x = 200.74032592773438, y = 1015.0382080078125, z = 187.7185516357422, heading = 270.0}
    local LanternStick2 = {x = 212.41311645507812, y = 1013.0830078125, z = 187.82083129882812, heading = 270.0}
    local LanternStick3 = {x = 218.79312133789062, y = 1011.3302001953125, z = 187.966552734375, heading = 270.0}
    local Lantern1 = { x = 196.26748657226562, y = 982.1720581054688, z = 193.13600158691406, heading = 270.0}
    local Lantern2 = { x = 198.21472778320312, y = 988.2286376953125, z = 193.87144470214844, heading = 0.0}
    local MoneyBag2 = {x = 196.75439453125, y = 988.8241577148438, 189.047216796875, heading = 90.0}
    local MoneyBag4 = {x = 196.75439453125, y = 988.8241577148438, 189.147216796875, heading = 90.0}
    local MoneyBag5 = {x = 196.15439453125, y = 988.1241577148438, z = 189.147216796875, heading = 90.0}

    missionUtils.StartMission()

    missionUtils.PlayMusic("MP_CLOUDS_TRANSITION_MUSIC")

    missionUtils.StartLoadingMission("The O'Driscoll raid", "This is example mission", StartPoint, {hours = 2, minutes = 15, seconds = 0}, weather.BLIZZARD, true, true)

    --Peds creating
    mission_peds[1] = missionUtils.CreateMissionPed(MISC.GET_HASH_KEY("CS_mrsadler"), Sadie, Sadie.heading, 20, true, {style = blips.blip_styles.BLIP_STYLE_OBJECTIVE, sprite = "blip_ambient_companion", scale = 0.2, name = "Sadie Adler"})
    WEAPON.GIVE_DELAYED_WEAPON_TO_PED(mission_peds[1], weapons.weapon_shotgun_semiauto, 100, true, 0x2cd419dc)
    WEAPON.GIVE_DELAYED_WEAPON_TO_PED(mission_peds[1], weapons.weapon_pistol_m1899, 100, true, 0x2cd419dc)
    WEAPON.GIVE_DELAYED_WEAPON_TO_PED(mission_peds[1], weapons.weapon_melee_knife_horror, 1, true, 0x2cd419dc)
    
    local playerPedGroup = PED.GET_PED_GROUP_INDEX(PLAYER.PLAYER_PED_ID())
    PED.SET_PED_AS_GROUP_LEADER(mission_peds[1], playerPedGroup, true)
    
    PED.SET_PED_RELATIONSHIP_GROUP_HASH(mission_peds[1], 0xB5A1D680)
    PED.SET_GROUP_SEPARATION_RANGE(playerPedGroup, 400.0)
    PED.SET_GROUP_FORMATION_SPACING(playerPedGroup, 1.5, -1.0, -1.0)

    PED.SET_PED_AS_GROUP_MEMBER(mission_peds[1], playerPedGroup)
    
    -- Sets a flag that the Sadie will never leave player group
    PED.SET_PED_CONFIG_FLAG(mission_peds[1], 279, true)
    PED.SET_PED_CONFIG_FLAG(mission_peds[1], 569, false)

    ENTITY.SET_ENTITY_CAN_BE_DAMAGED_BY_RELATIONSHIP_GROUP(mission_peds[1], false, 0xB5A1D680)

    PED.SET_PED_COMBAT_ABILITY(mission_peds[1], 2)
    PED.SET_PED_COMBAT_MOVEMENT(mission_peds[1], 2)
    PED.SET_PED_FIRING_PATTERN(mission_peds[1], 0xC6EE6B4C)
	PED.SET_PED_SHOOT_RATE(mission_peds[1], 200)

    -- Makin Sadie to contain her aggression.
    PED.SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(mission_peds[1], true)

    PED.SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(mission_peds[1], 1)
    PED.SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(mission_peds[1], false)
    PED.SET_PED_CAN_BE_TARGETTED_BY_PLAYER(mission_peds[1], PLAYER.PLAYER_ID(), false)

    mission_peds[2] = missionUtils.CreateMissionPed(MISC.GET_HASH_KEY("A_C_Horse_Gang_Sadie"), SadieHorse, SadieHorse.heading, nil, true, nil)

    -- Sets the saddle on the horse
    PED._EQUIP_META_PED_OUTFIT(mission_peds[2], 0x4B96E611) --https://github.com/femga/rdr3_discoveries/blob/master/peds_customization/ped_outfits.lua
    PED._UPDATE_PED_VARIATION(mission_peds[2], true, true, true, true, true)

    if mission_peds[1] == 0.0 or mission_peds[2] == 0.0 then
        missionUtils.FailLoadingMission()
        deleteAllMissionEntities()
        return false
    end

    mission_enemies[1] = missionUtils.CreateMissionPed(MISC.GET_HASH_KEY("U_M_M_BHT_ODRISCOLLDRUNK"), ODriscoll1, ODriscoll1.heading, nil, true, nil)
    mission_enemies[2] = missionUtils.CreateMissionPed(MISC.GET_HASH_KEY("U_M_M_BHT_ODRISCOLLDRUNK"), ODriscoll2, ODriscoll2.heading, nil, true, nil)
    mission_enemies[3] = missionUtils.CreateMissionPed(MISC.GET_HASH_KEY("U_M_M_BHT_ODRISCOLLMAULED"), ODriscoll3, ODriscoll3.heading, nil, true, nil)
    mission_enemies[4] = missionUtils.CreateMissionPed(MISC.GET_HASH_KEY("U_M_M_BHT_ODRISCOLLSLEEPING"), ODriscoll4, ODriscoll4.heading, nil, true, nil)
    mission_enemies[5] = missionUtils.CreateMissionPed(MISC.GET_HASH_KEY("U_M_M_BHT_ODRISCOLLDRUNK"), ODriscoll5, ODriscoll5.heading, nil, true, nil)
    mission_enemies[6] = missionUtils.CreateMissionPed(MISC.GET_HASH_KEY("U_M_M_BHT_ODRISCOLLMAULED"), ODriscoll6, ODriscoll6.heading, nil, true, nil)
    mission_enemies[7] = missionUtils.CreateMissionPed(MISC.GET_HASH_KEY("U_M_M_BHT_ODRISCOLLDRUNK"), ODriscoll7, ODriscoll7.heading, nil, true, nil)
    mission_enemies[8] = missionUtils.CreateMissionPed(MISC.GET_HASH_KEY("U_M_M_BHT_ODRISCOLLMAULED"), ODriscoll8, ODriscoll8.heading, nil, true, nil)
    mission_enemies[9] = missionUtils.CreateMissionPed(MISC.GET_HASH_KEY("U_M_M_BHT_ODRISCOLLDRUNK"), ODriscoll9, ODriscoll9.heading, nil, true, nil)
    mission_enemies[10] = missionUtils.CreateMissionPed(MISC.GET_HASH_KEY("U_M_M_BHT_ODRISCOLLDRUNK"), ODriscoll10, ODriscoll10.heading, nil, true, nil)
    mission_enemies[11] = missionUtils.CreateMissionPed(MISC.GET_HASH_KEY("U_M_M_BHT_ODRISCOLLDRUNK"), ODriscoll11, ODriscoll11.heading, nil, true, nil)
    mission_enemies[12] = missionUtils.CreateMissionPed(MISC.GET_HASH_KEY("U_M_M_BHT_ODRISCOLLDRUNK"), ODriscoll12, ODriscoll12.heading, nil, true, nil)
    mission_enemies[13] = missionUtils.CreateMissionPed(MISC.GET_HASH_KEY("U_M_M_BHT_ODRISCOLLDRUNK"), ODriscoll13, ODriscoll13.heading, nil, true, nil)
    mission_enemies[14] = missionUtils.CreateMissionPed(MISC.GET_HASH_KEY("U_M_M_BHT_ODRISCOLLDRUNK"), ODriscoll14, ODriscoll14.heading, nil, true, nil)
    mission_enemies[15] = missionUtils.CreateMissionPed(MISC.GET_HASH_KEY("U_M_M_BHT_ODRISCOLLDRUNK"), ODriscoll15, ODriscoll15.heading, nil, true, nil)
    mission_enemies[16] = missionUtils.CreateMissionPed(MISC.GET_HASH_KEY("U_M_M_BHT_ODRISCOLLDRUNK"), ODriscoll16, ODriscoll16.heading, nil, true, nil)

    PED.SET_PED_COMBAT_MOVEMENT(mission_enemies[6], 1)
    PED.SET_PED_COMBAT_MOVEMENT(mission_enemies[3], 1)
    PED.SET_PED_COMBAT_MOVEMENT(mission_enemies[11], 1)
    PED.SET_PED_COMBAT_MOVEMENT(mission_enemies[12], 1)

    PED.SET_PED_ACCURACY(mission_enemies[6], 100)
	PED.SET_PED_SHOOT_RATE(mission_enemies[6], 200)
    PED.SET_PED_COMBAT_MOVEMENT(mission_enemies[6], 0)

    for _, ped in pairs(mission_enemies) do
        local FirstWeapons = { weapons.weapon_shotgun_semiauto, weapons.weapon_shotgun_pump, weapons.weapon_repeater_winchester,  weapons.weapon_rifle_boltaction }
        local SecondWeapons = { weapons.weapon_pistol_semiauto, weapons.weapon_revolver_schofield }
        local MeleeWeapons = { weapons.weapon_melee_knife_miner }

        local PrimaryWeapon = FirstWeapons[math.random(1, #FirstWeapons)]
        local PecondaryWeapon = SecondWeapons[math.random(1, #SecondWeapons)]

        WEAPON.GIVE_DELAYED_WEAPON_TO_PED(ped, PrimaryWeapon, 100, true, 0x2cd419dc)
        WEAPON.GIVE_DELAYED_WEAPON_TO_PED(ped, PecondaryWeapon, 100, true, 0x2CD419DC)
        WEAPON.GIVE_DELAYED_WEAPON_TO_PED(ped, MeleeWeapons[1], 100, true, 0x2CD419DC)

        WEAPON.SET_CURRENT_PED_WEAPON(ped, PrimaryWeapon, true, 0, false, false)
        WEAPON.SET_CURRENT_PED_WEAPON(ped, PecondaryWeapon, true, 2, false, false)

        mission_peds[#mission_peds+1] = ped
        PED.SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(ped, true)
    end

    mission_groups[1] = PED.CREATE_GROUP(0)
    mission_groups[2] = PED.CREATE_GROUP(0)

    if mission_groups[1] == 0.0 or mission_groups[2] == 0.0 then
        missionUtils.FailLoadingMission()
        deleteAllMissionEntities()
        return false
    end


    PED.SET_GROUP_SEPARATION_RANGE(mission_groups[1], 400.0)
    PED.SET_GROUP_FORMATION_SPACING(mission_groups[1], 1.5, -1.0, -1.0)
    PED.SET_GROUP_SEPARATION_RANGE(mission_groups[2], 400.0)
    PED.SET_GROUP_FORMATION_SPACING(mission_groups[2], 1.5, -1.0, -1.0)

    for i = 1, 8, 1 do
        PED.SET_PED_AS_GROUP_MEMBER(mission_enemies[i], mission_groups[1])
        PED.SET_PED_CONFIG_FLAG(mission_enemies[i], 279, true)
        PED.SET_PED_CONFIG_FLAG(mission_enemies[i], 569, false)
    end
    for i = 9, 16, 1 do
        PED.SET_PED_AS_GROUP_MEMBER(mission_enemies[i], mission_groups[2])
        PED.SET_PED_CONFIG_FLAG(mission_enemies[i], 279, true)
        PED.SET_PED_CONFIG_FLAG(mission_enemies[i], 569, false)
    end

    TASK.TASK_START_SCENARIO_IN_PLACE_HASH(mission_enemies[4], MISC.GET_HASH_KEY(ODriscoll4.action_name), -1, true, MISC.GET_HASH_KEY(ODriscoll4.action_condition), ODriscoll4.heading, true)
    TASK.TASK_START_SCENARIO_IN_PLACE_HASH(mission_enemies[7], MISC.GET_HASH_KEY(ODriscoll7.action_name), -1, true, MISC.GET_HASH_KEY(ODriscoll7.action_condition), ODriscoll7.heading, true)
    TASK.TASK_START_SCENARIO_IN_PLACE_HASH(mission_enemies[8], MISC.GET_HASH_KEY(ODriscoll8.action_name), -1, true, MISC.GET_HASH_KEY(ODriscoll8.action_condition), ODriscoll8.heading, true)
    TASK.TASK_START_SCENARIO_IN_PLACE_HASH(mission_enemies[9], MISC.GET_HASH_KEY(ODriscoll9.action_name), -1, true, MISC.GET_HASH_KEY(ODriscoll9.action_condition), ODriscoll9.heading, true)
    TASK.TASK_START_SCENARIO_IN_PLACE_HASH(mission_enemies[10], MISC.GET_HASH_KEY(ODriscoll10.action_name), -1, true, MISC.GET_HASH_KEY(ODriscoll10.action_condition), ODriscoll10.heading, true)
    TASK.TASK_START_SCENARIO_IN_PLACE_HASH(mission_enemies[11], MISC.GET_HASH_KEY(ODriscoll11.action_name), -1, true, MISC.GET_HASH_KEY(ODriscoll11.action_condition), ODriscoll11.heading, true)
    TASK.TASK_START_SCENARIO_IN_PLACE_HASH(mission_enemies[12], MISC.GET_HASH_KEY(ODriscoll12.action_name), -1, true, MISC.GET_HASH_KEY(ODriscoll12.action_condition), ODriscoll12.heading, true)
    TASK.TASK_START_SCENARIO_IN_PLACE_HASH(mission_enemies[16], MISC.GET_HASH_KEY(ODriscoll16.action_name), -1, true, MISC.GET_HASH_KEY(ODriscoll16.action_condition), ODriscoll16.heading, true)
    

    --Vehciles creating
    mission_vehicles[1] = missionUtils.CreateMissionVehicle(MISC.GET_HASH_KEY("supplywagon"), SupplyWagon, SupplyWagon.heading, true, nil)
    mission_vehicles[2] = missionUtils.CreateMissionVehicle(MISC.GET_HASH_KEY("gatlingMaxim02"), Maximgun, Maximgun.heading, true, nil)
 
    --Propsets creating
    mission_prop_sets[1] = missionUtils.CreatePropSet(MISC.GET_HASH_KEY("pg_re_odoriscollboysgang03x"), OdoriscollCamp, OdoriscollCamp.heading)

    --Objects creating
    mission_objects[1] = missionUtils.CreateMissionObject(MISC.GET_HASH_KEY("p_dynamitecrate01x"), DynamiteBox, DynamiteBox.heading, nil, true, true, nil)
    mission_objects[2] = missionUtils.CreateMissionObject(MISC.GET_HASH_KEY("p_dynamitecrate01x"), DynamiteBox2, DynamiteBox2.heading, nil, true, true, nil)
    mission_objects[3] = missionUtils.CreateMissionObject(MISC.GET_HASH_KEY("p_dynamitecrate01x"), DynamiteBox3, DynamiteBox3.heading, nil, true, true, nil)
    mission_objects[4] = missionUtils.CreateMissionObject(MISC.GET_HASH_KEY("p_dynamitecrate01x"), DynamiteBox4, DynamiteBox4.heading, nil, true, true, nil)
    mission_objects[5] = missionUtils.CreateMissionObject(MISC.GET_HASH_KEY("p_lanternstick09x"), LanternStick1, LanternStick1.heading, nil, false, true, nil)
    mission_objects[6] = missionUtils.CreateMissionObject(MISC.GET_HASH_KEY("p_lanternstick09x"), LanternStick2, LanternStick2.heading, nil, false, true, nil)
    mission_objects[7] = missionUtils.CreateMissionObject(MISC.GET_HASH_KEY("p_lanternstick09x"), LanternStick3, LanternStick3.heading, nil, false, true, nil)
    mission_objects[8] = missionUtils.CreateMissionObject(MISC.GET_HASH_KEY("p_lantern05x"), Lantern1, Lantern1.heading, nil, false, true, nil)
    mission_objects[9] = missionUtils.CreateMissionObject(MISC.GET_HASH_KEY("p_lantern05x"), Lantern2, Lantern2.heading, nil, false, false, nil)
    
    for x_offset = 0.0, 0.8, 0.2 do
        for y_offset = 0.0, 1.0, 0.2 do
            local MoneyBagNew = { x = money_bag_1.x + x_offset, y = money_bag_1.y + y_offset, z = money_bag_1.z, heading = money_bag_1.heading, rotation = money_bag_1.rotation }
            mission_objects[#mission_objects+1] = missionUtils.CreateMissionObject(MISC.GET_HASH_KEY("p_moneybag02x"), MoneyBagNew, MoneyBagNew.heading, MoneyBagNew.rotation,  true, false, nil)
        end
    end

    if mission_objects[10] == 0.0 or mission_objects[11] == 0.0 then
        missionUtils.FailLoadingMission()
        return false
    end

    mission_objects[#mission_objects+1] = missionUtils.CreateMissionObject(MISC.GET_HASH_KEY("p_moneystack02x"), MoneyBag2, MoneyBag2.heading, nil,  true, true, nil)
    mission_objects[#mission_objects+1] = missionUtils.CreateMissionObject(MISC.GET_HASH_KEY("p_moneybag05x"), MoneyBag4, MoneyBag4.heading, nil,  true, true, nil)
    mission_objects[#mission_objects+1] = missionUtils.CreateMissionObject(MISC.GET_HASH_KEY("p_moneybag05x"), MoneyBag5, MoneyBag5.heading, nil,  true, true, nil)
    
    
    --local BarnDoor1 = ENTITY._GET_ENTITY_BY_DOORHASH(160425541, 0) --Barn door entity ID. Model = "p_eme_barn_door3"
    --local BarnDoor2 = ENTITY._GET_ENTITY_BY_DOORHASH(3167931616, 0) --Barn door entity ID. Model = "p_eme_barn_door3"

    --Opening barn doors
    OBJECT.DOOR_SYSTEM_SET_DOOR_STATE(160425541, 0)
    OBJECT.DOOR_SYSTEM_SET_DOOR_STATE(3167931616, 0)

    missionUtils.EndLoadingMission()
    missionUtils.FocusPlayerCamOnEntity(mission_peds[1], 1000)

    Wait(800)

    missionUtils.StopMusic()

    is_mission_active = true
    is_mission_initialized = true

    return true
end

function missionUpdate()
    if ENTITY.IS_ENTITY_DEAD(mission_peds[1]) or ENTITY.IS_ENTITY_DEAD(mission_peds[2]) or ENTITY.IS_ENTITY_DEAD(PLAYER.PLAYER_PED_ID()) then
        is_mission_active = false
        return nil
    end
    if not player_has_detected then
        for _, ped in pairs(mission_enemies) do
            local ped_coords = ENTITY.GET_ENTITY_COORDS(ped, true, true)

            -- Checking if the enemy can see the player
            if (not PED.GET_PED_CROUCH_MOVEMENT(PLAYER.PLAYER_PED_ID()) and math_utils.GetDistanceBetweenCoords(ped_coords, ENTITY.GET_ENTITY_COORDS(PLAYER.PLAYER_PED_ID(), true, true)) <= 17.0)
               or
               (PED.GET_PED_CROUCH_MOVEMENT(PLAYER.PLAYER_PED_ID()) and math_utils.GetDistanceBetweenCoords(ped_coords, ENTITY.GET_ENTITY_COORDS(PLAYER.PLAYER_PED_ID(), true, true)) <= 10.0) then
                
                player_has_detected = true

                missionUtils.PlayMusic("MP_NAT_MISSION_ANIMAL_SPOTTED")
                
                TASK.CLEAR_PED_TASKS(mission_peds[1], true, true)
                TASK.TASK_COMBAT_HATED_TARGETS_AROUND_PED(mission_peds[1], 20.0, 0, 0)
                TASK.TASK_COMBAT_HATED_TARGETS(mission_peds[1], 20.0)
                TASK.TASK_COMBAT_PED(mission_peds[1], mission_enemies[4], 0, 0)

                for _, ped in pairs(mission_enemies) do
                    missionUtils.AddBlipForEntity(ped, blips.blip_styles.BLIP_STYLE_ENEMY, nil, "blip_ambient_ped_small", 0.2, "Enemy")
                    PED.SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(ped, false)
                    TASK.TASK_COMBAT_PED(ped, PLAYER.PLAYER_PED_ID(), 0, 0)
                    --TASK.TASK_COMBAT_PED(mission_peds[1], ped, 0, 0)
                end

                

                ENTITY.SET_ENTITY_INVINCIBLE(mission_peds[1], true)
                TASK.TASK_ENTER_VEHICLE(mission_enemies[6], mission_vehicles[2], 5000, -1, 2.0, task_flags.None, 0)
                PED.SET_PED_KEEP_TASK(mission_enemies[6], true)
            end
        end
    end
end

function missionMain()
    if NETWORK.NETWORK_GET_NUM_CONNECTED_PLAYERS() > 1.0 then
        printColoured("dark yellow", "It is not recommended to start this missions in public sessions in which there are other players present besides you")
    end

    if not missionUtils.CanStartMission() or not initializeMission() then
        DisplayError(false, "Unable to start mission at this time try again later")
    end

    local DisplayX, DisplayY = GraphicsBase.GetDisplaySize()

    local prompt = Graphics.Text.DrawText("Follow Sadie Adler", DisplayX/2-100, DisplayY - 45, 255, 255, 255, 255, "Arial", 24)

    AUDIO.PLAY_SOUND_FRONTEND("Idle_Kick_Message", "RDRO_Idle_Kick_Sounds", true, 0)

    TASK.TASK_MOUNT_ANIMAL(mission_peds[1], mission_peds[2], 25000, -1, 1.0, task_flags.None, 0, 0)
    PED.SET_PED_KEEP_TASK(mission_peds[1], true)

    while ScriptStillWorking and isMissionStillActive() and PED.GET_MOUNT(mission_peds[1]) == 0.0 do
        missionUpdate()
        Wait(500)
    end
    if not ScriptStillWorking or not isMissionStillActive() then
        prompt:Delete()

        missionUtils.StopMusic()
        endMission(true)

        return nil
    end

    PED.SET_PED_KEEP_TASK(mission_peds[1], false)

    TASK.TASK_GO_TO_COORD_ANY_MEANS(mission_peds[1], sadie_waypoint_1.x, sadie_waypoint_1.y, sadie_waypoint_1.z, 10.0, 0, false, 0, 0.0)

    missionUtils.PlayMusic("DOPN_HIGH_HON_ANIMAL_MUSIC")

    while ScriptStillWorking and isMissionStillActive() and math_utils.GetDistanceBetweenCoords(sadie_waypoint_1, ENTITY.GET_ENTITY_COORDS(mission_peds[1], true, true)) > 5.0 do
        missionUpdate()

        if PED.GET_VEHICLE_PED_IS_IN(PLAYER.PLAYER_PED_ID(), true) ~= 0.0 or math_utils.GetDistanceBetweenCoords(ENTITY.GET_ENTITY_COORDS(PLAYER.PLAYER_PED_ID(), true, true), ENTITY.GET_ENTITY_COORDS(mission_peds[1], true, true)) > 135.0 then
            prompt:Delete()

            missionUtils.StopMusic()
            endMission(true)

            return nil
        end

        TASK.TASK_GO_TO_COORD_ANY_MEANS(mission_peds[1], sadie_waypoint_1.x, sadie_waypoint_1.y, sadie_waypoint_1.z, 10.0, 0, false, 0, 0.0)
        --TASK.TASK_GO_TO_COORD_ANY_MEANS_EXTRA_PARAMS_WITH_CRUISE_SPEED(mission_peds[1], sadie_waypoint_1.x, sadie_waypoint_1.y, sadie_waypoint_1.z, 15.0, 0, false, 0, 0.0, 0.0, 0.0, 0, 15.0, 0.0)
        
        Wait(500)
    end
    if not ScriptStillWorking or not isMissionStillActive() then
        prompt:Delete()

        missionUtils.StopMusic()
        endMission(true)

        return nil
    end

    TASK.TASK_DISMOUNT_ANIMAL(mission_peds[1], task_flags.None, 0, 0, 0, 0)
    Wait(1000)
    TASK.TASK_GO_TO_COORD_ANY_MEANS(mission_peds[1], sadie_waypoint_2.x, sadie_waypoint_2.y, sadie_waypoint_2.z, 1.0, 0, false, 0, 0.0)

    while ScriptStillWorking and isMissionStillActive() and math_utils.GetDistanceBetweenCoords(sadie_waypoint_2, ENTITY.GET_ENTITY_COORDS(mission_peds[1], true, true)) > 1.0 do
        missionUpdate()
        Wait(500)
    end
    if not ScriptStillWorking or not isMissionStillActive() then
        prompt:Delete()

        missionUtils.StopMusic()
        endMission(true)

        return nil
    end

    prompt:Delete()

    Wait(1000)
    
    WEAPON.SET_CURRENT_PED_WEAPON(mission_peds[1], weapons.weapon_shotgun_semiauto, true, 0, false, false)
    TASK.TASK_FOLLOW_TO_OFFSET_OF_ENTITY(mission_peds[1], PLAYER.PLAYER_PED_ID(), 0.0, -0.05, 0.0, 15.0, 100000, 1000.0, true, true, false, false, false, false)
    PED.SET_PED_KEEP_TASK(mission_peds[1], true)

    missionUtils.RemoveBlipFromEntity(mission_peds[1])

    missionUtils.AddBlipForEntity(mission_peds[1], blips.blip_styles.BLIP_STYLE_FRIENDLY, nil, "blip_ambient_companion", 0.05, "Sadie Adler")

    missionUtils.FocusPlayerCamOnEntity(mission_enemies[1], 2000)

    prompt = Graphics.Text.DrawText("Find where the O'Driscolls' dirty money is hidden", DisplayX/2-280, DisplayY - 45, 255, 255, 255, 255, "Arial", 24)

    AUDIO.PLAY_SOUND_FRONTEND("Idle_Kick_Message", "RDRO_Idle_Kick_Sounds", true, 0)

    -- Waiting until the player is close to the main target
    while ScriptStillWorking and isMissionStillActive() and math_utils.GetDistanceBetweenCoords(money_bag_1, ENTITY.GET_ENTITY_COORDS(PLAYER.PLAYER_PED_ID(), true, true)) > 8.0 do
        if math_utils.GetDistanceBetweenCoords(odriscolls_ranch, ENTITY.GET_ENTITY_COORDS(PLAYER.PLAYER_PED_ID(), true, true)) > 70.0 then
            prompt:Delete()

            missionUtils.StopMusic()
            endMission(true)

            return nil
        end
        
        missionUpdate()
        Wait(200)
    end
    if not ScriptStillWorking or not isMissionStillActive() then
        prompt:Delete()

        missionUtils.StopMusic()
        endMission(true)
        return nil
    end

    prompt:Delete()

    local blip_on_entity = 0
    local cash_blip = 0
    local iters = 0
    while iters < 30 do
        blip_on_entity = mission_objects[10+iters]

        cash_blip = missionUtils.AddBlipForEntity(blip_on_entity, blips.blip_styles.BLIP_STYLE_OBJECTIVE, nil, "blip_cash_bag", 0.2, "Dirty money")
        if cash_blip ~= 0.0 then
            break
        end
        
        iters = iters + 1
    end

    -- Again Opening barn doors
    OBJECT.DOOR_SYSTEM_SET_DOOR_STATE(160425541, 0)
    OBJECT.DOOR_SYSTEM_SET_DOOR_STATE(3167931616, 0)

    prompt = Graphics.Text.DrawText("Burn the barn with the O'Driscolls' dirty money", DisplayX/2-256, DisplayY - 45, 255, 255, 255, 255, "Arial", 24)

    AUDIO.PLAY_SOUND_FRONTEND("Idle_Kick_Message", "RDRO_Idle_Kick_Sounds", true, 0)
    
    while ScriptStillWorking and isMissionStillActive() and FIRE.GET_NUMBER_OF_FIRES_IN_RANGE(money_bag_1.x, money_bag_1.y, money_bag_1.z, 7.0) == 0.0 do
        missionUpdate()
        Wait(200)
    end
    if not ScriptStillWorking or not isMissionStillActive() then
        prompt:Delete()

        missionUtils.StopMusic()
        endMission(true)
        return nil
    end

    missionUtils.RemoveBlipFromEntity(blip_on_entity)
    missionUtils.DeleteMissionObject(blip_on_entity)

    prompt:Delete()

    TASK.CLEAR_PED_TASKS(mission_peds[1], true, true)
    
    TASK.TASK_GO_TO_ENTITY(mission_peds[2], mission_peds[1], -1, 80.0, 1.5, 0.0, 0)
    TASK.TASK_MOUNT_ANIMAL(mission_peds[1], mission_peds[2], 15000, -1, 3.0, task_flags.None, 0, 0)

    prompt = Graphics.Text.DrawText("Leave the area", DisplayX/2-100, DisplayY - 45, 255, 255, 255, 255, "Arial", 24)

    while ScriptStillWorking and isMissionStillActive() and math_utils.GetDistanceBetweenCoords(ENTITY.GET_ENTITY_COORDS(PLAYER.PLAYER_PED_ID(), true, true), odriscolls_ranch) < 160.0 do
        if PED.GET_MOUNT(mission_peds[1]) ~= 0.0 then
            TASK.TASK_SMART_FLEE_PED(mission_peds[1], PLAYER.PLAYER_PED_ID(), 500.0, -1, 0, 3.0, 0)
        end
        
        missionUpdate()
        Wait(200)
    end

    missionUtils.StopMusic()

    Wait(500)

    endMission(false)

    prompt:Delete()
end

missionMain()