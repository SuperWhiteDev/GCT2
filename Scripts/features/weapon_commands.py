import GCT

def add_ammo_weapon():
    amount = int(GCT.Input("Enter the number of ammo you want to add: ", False))
    
    weapon_hash = WEAPON._GET_PED_CURRENT_HELD_WEAPON(PLAYER.PLAYER_PED_ID())
    WEAPON._ADD_AMMO_TO_PED(PLAYER.PLAYER_PED_ID(), weapon_hash, amount, 0x2CD419DC)


def give_weapon():
    # This function will only work in singleplayer and multiplayer it does not work I have not found a solution to this problem
    import GCT
    from RDR2 import WEAPON, PLAYER, MISC
    
    weapon_hash = MISC.GET_HASH_KEY(GCT.Input("Enter the weapon you want to give to player: ", False))
    WEAPON.GIVE_DELAYED_WEAPON_TO_PED(PLAYER.PLAYER_PED_ID(), weapon_hash, 100, 1, 0x2cd419dc)
    WEAPON.SET_PED_AMMO(PLAYER.PLAYER_PED_ID(), weapon_hash, 100)
    WEAPON.SET_CURRENT_PED_WEAPON(PLAYER.PLAYER_PED_ID(), weapon_hash, 1, 0, 0, 0)
    
def set_infinity_ammo_weapon():
    import GCT
    from RDR2 import WEAPON, PLAYER
    
    enable_infinity_ammo = GCT.Input("Enable an infinite ammunition on weapon currently held by the player? [Y/n]: ", True)
    
    if enable_infinity_ammo == "y":
        WEAPON.SET_PED_INFINITE_AMMO(PLAYER.PLAYER_PED_ID(), True, WEAPON._GET_PED_CURRENT_HELD_WEAPON(PLAYER.PLAYER_PED_ID()))
    elif enable_infinity_ammo == "n":
        WEAPON.SET_PED_INFINITE_AMMO(PLAYER.PLAYER_PED_ID(), False, WEAPON._GET_PED_CURRENT_HELD_WEAPON(PLAYER.PLAYER_PED_ID()))
    
def set_infinity_clip_weapon():
    from RDR2 import WEAPON, PLAYER
    
    enable_infinity_clip = GCT.Input("Enable an infinite clip on weapon currently held by the player? [Y/n]: ", True)
    
    if enable_infinity_clip == "y":
        WEAPON._SET_PED_INFINITE_AMMO_CLIP(PLAYER.PLAYER_PED_ID(), True)
    elif enable_infinity_clip == "n":
        WEAPON._SET_PED_INFINITE_AMMO_CLIP(PLAYER.PLAYER_PED_ID(), False)
        
def clean_weapon():
    weapon_object = WEAPON._GET_PED_WEAPON_OBJECT(PLAYER.PLAYER_PED_ID(), True)
    if weapon_object:
        WEAPON._SET_WEAPON_DIRT(weapon_object, 0.0, True)
        WEAPON._SET_WEAPON_SOOT(weapon_object, 0.0, True)
        WEAPON._SET_WEAPON_DEGRADATION(weapon_object, 0.0)
        
def get_entity_player_aiming_for():
    """ This function continuously checks which entity the player is aiming at in the game. It displays the ID of the entity the player is currently aiming at. """
    import GCT
    import Game
    from RDR2 import PLAYER
    from utils.Graphics.graphicspp import Text
    from utils.Graphics.graphics_base import DeleteElement
    
    from time import sleep
    
    # Return a pointer to a new 4 byte memory
    targetp = GCT.New(4)
    
    text = Text("Current aiming ped is None", 5, 16, 200, 200, 0, 255, "", 16)
    
    #The cycle repeats until all scripts are restarted or the user presses the Escape button
    while GCT.IsScriptsStillWorking():
        player_id = PLAYER.PLAYER_ID()
        if GCT.IsPressedKey(GCT.ConvertStringToKeyCode("Escape")):
            break
        
        if PLAYER.GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(player_id, targetp):
            text.set_label(f"Current aiming ped is {Game.ReadInt(targetp)}")
        sleep(0.01)
        
    # Clears the allocated memory, but does not set the pointer to 0
    GCT.Delete(targetp)
    
    # Removes text from the screen
    DeleteElement(text.element_id)
def explosive_ammo_weapon():
    import GCT

    if GCT.IsGlobalVariableExist("feature_weapon_explosive_ammo_enabled"):
        if not GCT.GetGlobalVariable("feature_weapon_explosive_ammo_enabled"):    
            GCT.SetGlobalVariableValue("feature_weapon_explosive_ammo_enabled", 1)
            print("Explosive rounds have been activated")
        else:
            GCT.SetGlobalVariableValue("feature_weapon_explosive_ammo_enabled", 0)
            print("Explosive rounds have been disabled")
    else:
        print("Explosive rounds have been activated")
        GCT.RegisterGlobalVariable("feature_weapon_explosive_ammo_enabled", 1)
    
def fire_ammo_weapon():
    import GCT

    if GCT.IsGlobalVariableExist("feature_weapon_fire_ammo_enabled"):
        if not GCT.GetGlobalVariable("feature_weapon_fire_ammo_enabled"):    
            GCT.SetGlobalVariableValue("feature_weapon_fire_ammo_enabled", 1)
            print("Fire rounds have been activated")
        else:
            GCT.SetGlobalVariableValue("feature_weapon_fire_ammo_enabled", 0)
            print("Fire rounds have been disabled")
    else:
        print("Fire rounds have been activated")
        GCT.RegisterGlobalVariable("feature_weapon_fire_ammo_enabled", 1)
        
def rapid_fire_weapon():
    import GCT

    if GCT.IsGlobalVariableExist("feature_weapon_rapid_fire_enabled"):
        if not GCT.GetGlobalVariable("feature_weapon_rapid_fire_enabled"):    
            GCT.SetGlobalVariableValue("feature_weapon_rapid_fire_enabled", 1)
            print("Rapid fire have been activated")
        else:
            GCT.SetGlobalVariableValue("feature_weapon_rapid_fire_enabled", 0)
            print("Rapid fire have been disabled")
    else:
        print("Rapid fire have been activated")
        GCT.RegisterGlobalVariable("feature_weapon_rapid_fire_enabled", 1)
        
# Define a dictionary with commands and their functions
commands = {
    "give weapon": give_weapon,
    "add ammo": add_ammo_weapon,
    "set infinity ammo": set_infinity_ammo_weapon,
    "set infinity clip": set_infinity_clip_weapon,
    "clean weapon": clean_weapon,
    "get entity aiming for": get_entity_player_aiming_for,
    "explosive ammo": explosive_ammo_weapon,
    "fire ammo": fire_ammo_weapon,
    "rapid fire": rapid_fire_weapon, 
}

for command, function in commands.items():
    if not GCT.BindCommand(command, function):
       GCT.DisplayError(True, f"Failed to register the command: {command}")