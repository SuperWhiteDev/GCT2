
local networkUtils = require("network_utils")
local mathUtils = require("math_utils")
local weapons = require("weapons")

local bodyguards_list = { }

function bodyGuardsListCommand()
    local peds = {}
    local models = {}

    for ped, model in pairs(bodyguards_list) do
        if model ~= nil then
            table.insert(peds, ped)
            table.insert(models, model)
        end
    end

    if #models ~= 0 then
        local bodyguard_id = InputFromList("Choose the bodyguard you want to interact with: ", models)
        if bodyguard_id ~= -1 then
            local bodyguard = peds[bodyguard_id+1]

            local options = { "Control bodyguard", "Delete" }
            local option = InputFromList("Choose what you want to: ", options)

            if option == 0 then
                controlBodyguard(bodyguard)
            elseif option == 1 then
                networkUtils.DeleteNetPed(bodyguard)

                if not ENTITY.DOES_ENTITY_EXIST(bodyguard) then
                    bodyguards_list[bodyguard] = nil
                end
            end
        end
    else
        print("There are no bodyguards on the bodyguards list yet")
    end
end

function controlBodyguard(bodyguard)
    local options = { "Follow me", "Stay here", "Attack close enemy", "Set invincible", "Add weapon" }
    local option = InputFromList("Choose what you want to: ", options)

    networkUtils.RequestControlOf(bodyguard)
    if option == 0 then
        TASK.TASK_FOLLOW_TO_OFFSET_OF_ENTITY(bodyguard, PLAYER.PLAYER_PED_ID(), 0.0, -1.0, 0.0, 15.0, 100000, 1000.0, true, true, false, false, false, false)
    elseif option == 1 then
        TASK.TASK_STAND_STILL(bodyguard, -1)
    elseif option == 2 then
        TASK.TASK_COMBAT_HATED_TARGETS_AROUND_PED(bodyguard, 100.0, 0, 0)
        TASK.TASK_COMBAT_HATED_TARGETS(bodyguard, 100.0)

        local weaponp = New(4)

        local target = NETWORK.NETWORK_GET_ENTITY_KILLER_OF_PLAYER(PLAYER.PLAYER_ID(), weaponp)
        TASK.TASK_SHOOT_AT_ENTITY(bodyguard, target, 10000, 0, false)
        TASK.TASK_COMBAT_PED(bodyguard, target, 0, 0)

        Delete(weaponp)
    elseif option == 3 then
        local bodyguard_invincible = Input("Set the bodyguard invincible? [Y/n]: ", true)

        if bodyguard_invincible == "y" then
            ENTITY.SET_ENTITY_INVINCIBLE(bodyguard, true)
        elseif bodyguard_invincible == "n" then
            ENTITY.SET_ENTITY_INVINCIBLE(bodyguard, false)
        end
    elseif option == 4 then
        local weapon = Input("Enter weapon(https://github.com/femga/rdr3_discoveries/blob/master/weapons/weapons.lua): ", false)

        WEAPON.GIVE_DELAYED_WEAPON_TO_PED(bodyguard, MISC.GET_HASH_KEY(weapon), 100, true, 0x2CD419DC)
        WEAPON.SET_CURRENT_PED_WEAPON(bodyguard, MISC.GET_HASH_KEY(weapon), true, 0, false, false)
    end
end

function setPedAsBodyguard(bodyguard, player_ped)

    -- Stops the current action of the ped
    TASK.CLEAR_PED_TASKS(bodyguard, true, true)
    TASK.CLEAR_PED_SECONDARY_TASK(bodyguard)

    -- Sets a player as a leader in his own group
    local player_ped_group = PED.GET_PED_GROUP_INDEX(player_ped)
    PED.SET_PED_AS_GROUP_LEADER(PLAYER.PLAYER_PED_ID(), player_ped_group, true)
    
    -- Adds a ped to the player's group
    PED.SET_PED_RELATIONSHIP_GROUP_HASH(bodyguard, 0xB5A1D680)
    PED.SET_GROUP_SEPARATION_RANGE(player_ped_group, 400.0)
    PED.SET_GROUP_FORMATION_SPACING(player_ped_group, 1.5, -1.0, -1.0)
    PED.SET_PED_AS_GROUP_MEMBER(bodyguard, player_ped_group)
    -- Sets a flag that the ped will never leave player group
    PED.SET_PED_CONFIG_FLAG(bodyguard, 279, true)
    PED.SET_PED_CONFIG_FLAG(bodyguard, 569, false)

    -- Sets other settings for the bodyguard
    PED.SET_PED_CAN_RAGDOLL(bodyguard, false)
	PED.SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(bodyguard, false)
	PED.SET_PED_COMBAT_RANGE(bodyguard, 500)
	PED.SET_PED_COMBAT_ABILITY(bodyguard, 2)
    PED.SET_PED_COMBAT_MOVEMENT(bodyguard, 2)
    PED.SET_PED_COMBAT_ATTRIBUTES(bodyguard, 17, false)
    PED.SET_PED_COMBAT_ATTRIBUTES(bodyguard, 113, true)
    PED.SET_PED_COMBAT_ATTRIBUTES(bodyguard, 46, true)
    PED.SET_PED_COMBAT_ATTRIBUTES(bodyguard, 58, true)
	PED.SET_PED_ACCURACY(bodyguard, 100)
    PED.SET_PED_FIRING_PATTERN(bodyguard, 0xC6EE6B4C)
	PED.SET_PED_SHOOT_RATE(bodyguard, 200)
	PED.SET_PED_KEEP_TASK(bodyguard, true)

    local bodyguard_invincible = Input("Make the bodyguard invincible? [Y/n]: ", true)

    if bodyguard_invincible == "y" then
        ENTITY.SET_ENTITY_INVINCIBLE(bodyguard, true)
    end 

    local give_bodyguard_weapon = Input("You want to give bodyguard the weapon? [Y/n]: ", true)

    if give_bodyguard_weapon == "y" then
        local options = { "Random", "Custom" }
        local option = InputFromList("Enter the weapon you want to give to the bodyguard: ", options)

        if option == 0 then
            local first_weapons = { weapons.weapon_rifle_springfield, weapons.weapon_sniperrifle_carcano, weapons.weapon_sniperrifle_rollingblock, weapons.weapon_shotgun_semiauto, weapons.weapon_shotgun_pump }
            local second_weapons = { weapons.weapon_pistol_m1899, weapons.weapon_pistol_mauser, weapons.weapon_pistol_semiauto, weapons.weapon_repeater_winchester }
            local grenades = { weapons.weapon_thrown_dynamite, weapons.weapon_thrown_molotov }

            local primary_weapon = first_weapons[math.random(1, #first_weapons)]
            local secondary_weapon = second_weapons[math.random(1, #second_weapons)]

            WEAPON.GIVE_DELAYED_WEAPON_TO_PED(bodyguard, primary_weapon, 100, true, 0x2cd419dc)
            WEAPON.GIVE_DELAYED_WEAPON_TO_PED(bodyguard, secondary_weapon, 100, true, 0x2CD419DC)
            WEAPON.GIVE_DELAYED_WEAPON_TO_PED(bodyguard, grenades[math.random(1, #grenades)], 100, true, 0x2CD419DC)

            WEAPON.SET_CURRENT_PED_WEAPON(bodyguard, primary_weapon, true, 0, false, false)
            WEAPON.SET_CURRENT_PED_WEAPON(bodyguard, secondary_weapon, true, 2, false, false)
        elseif option == 1 then
            local weapon = Input("Enter weapon(https://github.com/femga/rdr3_discoveries/blob/master/weapons/weapons.lua): ", false)

            WEAPON.GIVE_DELAYED_WEAPON_TO_PED(bodyguard, MISC.GET_HASH_KEY(weapon), 100, true, 0x2CD419DC)
            WEAPON.SET_CURRENT_PED_WEAPON(bodyguard, MISC.GET_HASH_KEY(weapon), true, 0, false, false)
        end
    end 

	PED.SET_PED_KEEP_TASK(bodyguard, true)
end

function createBodyguardCommand()
    local player_ped = nil
    local model_name = nil

    local options = { "Me", "Player" }
    local option = InputFromList("Enter who you want to create a bodyguard for: ", options)

    if option == 0 then
        player_ped = PLAYER.PLAYER_PED_ID()
    elseif option == 1 then
        io.write()
        local player = tonumber(Input("Enter player ID: ", false))
    
        if player then
            player_ped = PLAYER.GET_PLAYER_PED(player)
        end
    else
        return nil
    end

    local models = { "Sherrif", "Police", "Pinkerton guard", "Military guard", "Bounty hunter", "Gang guard", "Custom" }
    local model = InputFromList("Enter a model for the bodyguard: ", models)

    if model == 0 then
        local sherrif_guard_models = { "CS_strsheriff_01", "MP_S_M_M_REVENUEAGENTS_01", "U_M_M_RhdSheriff_01", "U_M_M_StrSherriff_01", "U_M_O_AsbSheriff_01" }
        model_name = sherrif_guard_models[math.random(1, #sherrif_guard_models)]
    elseif model == 1 then
        local police_guard_models = { "S_M_M_AmbientBlWPolice_01" }
        model_name = police_guard_models[math.random(1, #police_guard_models)]
    elseif model == 2 then
        local pinkerton_guard_models = { "CS_PinkertonGoon", "S_M_M_PinLaw_01" }
        model_name = pinkerton_guard_models[math.random(1, #pinkerton_guard_models)]
    elseif model == 3 then
        local military_guard_models = { "S_M_M_Army_01", "S_M_Y_Army_01", "U_M_M_ARMYTRN4_01", }
        model_name = military_guard_models[math.random(1, #military_guard_models)]
    elseif model == 4 then
        local bounty_hunter_guard_models = { "G_M_M_BountyHunters_01", " U_M_M_UniBountyHunter_01", "U_M_M_UniBountyHunter_02" }
        model_name = bounty_hunter_guard_models[math.random(1, #bounty_hunter_guard_models)]
    elseif model == 5 then
        local gang_guard_models = { "G_M_M_UniAfricanAmericanGang_01", "MSP_GANG2_MALES_01", "U_M_M_NbxBankerBounty_01" }
        model_name = gang_guard_models[math.random(1, #gang_guard_models)]
    elseif model == 6 then
        model_name = Input("Enter ped model(https://www.rdr2mods.com/wiki/peds/): ", false)
    else
        return nil
    end

    local coords = ENTITY.GET_ENTITY_COORDS(PLAYER.PLAYER_PED_ID(), true, true)
    local forward = ENTITY.GET_ENTITY_FORWARD_VECTOR(PLAYER.PLAYER_PED_ID())
    
    coords = mathUtils.SumVectors(coords, mathUtils.MultVector(forward, -2.0))

    local ped = networkUtils.CreateNetPed(MISC.GET_HASH_KEY(model_name), coords, ENTITY.GET_ENTITY_HEADING(PLAYER.PLAYER_PED_ID()), {sprite = "blip_ambient_companion", scale = 0.2, name = "Bodyguard"})
    if ped then
        bodyguards_list[ped] = model_name

        ENTITY.SET_ENTITY_AS_MISSION_ENTITY(ped, true, true)
        setPedAsBodyguard(ped, player_ped)
        
        printColoured("green", "Succesfully created new bodyguard. Ped ID is " .. ped)
    else
        DisplayError(false, "Failed to create bodyguard")
    end
end

-- Define a table with commands and their functions
local commands = {
    ["bodyguards"] = bodyGuardsListCommand,
    ["create bodyguard"] = createBodyguardCommand,
}

-- Loop for registering commands
for command_name, command_function in pairs(commands) do
    if not BindCommand(command_name, command_function) then
        DisplayError(true, "Failed to register the command: " .. command_name)
    end
end