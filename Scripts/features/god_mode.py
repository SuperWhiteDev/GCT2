import GCT

def god_mode_command():
    import GCT
    import Game
    from RDR2 import ENTITY, PLAYER, UITUTORIAL
    from time import sleep
    
    if 0:
        pass
    else:
        if GCT.IsGlobalVariableExist("feature_godmode_godmode_enabled"):
            if not GCT.GetGlobalVariable("feature_godmode_godmode_enabled"):    
                GCT.SetGlobalVariableValue("feature_godmode_godmode_enabled", 1)
                UITUTORIAL._UITUTORIAL_SET_RPG_ICON_VISIBILITY(5, 3)
                print("God mode have been activated")
            else:
                GCT.SetGlobalVariableValue("feature_godmode_godmode_enabled", 0)
                UITUTORIAL._UITUTORIAL_SET_RPG_ICON_VISIBILITY(5, 0)
                print("God mode have been disabled")
                
                sleep(0.05)
                
                ENTITY.SET_ENTITY_INVINCIBLE(PLAYER.PLAYER_PED_ID(), False)
        else:
            UITUTORIAL._UITUTORIAL_SET_RPG_ICON_VISIBILITY(5, 3)
            print("God mode have been activated")
            GCT.RegisterGlobalVariable("feature_godmode_godmode_enabled", 1)
            
def auto_heal_command():
    import GCT
    
    if GCT.IsGlobalVariableExist("feature_godmode_autoheal_enabled"):
        if not GCT.GetGlobalVariable("feature_godmode_autoheal_enabled"):    
            GCT.SetGlobalVariableValue("feature_godmode_autoheal_enabled", 1)
            print("Auto heal have been activated")
        else:
            GCT.SetGlobalVariableValue("feature_godmode_autoheal_enabled", 0)
            print("Auto heal have been disabled")
    else:
        print("Auto heal have been activated")
        GCT.RegisterGlobalVariable("feature_godmode_autoheal_enabled", 1)

# Define a dictionary with commands and their functions
commands = {
    "god mode": god_mode_command,
    "auto heal": auto_heal_command
}

for command, function in commands.items():
    if not GCT.BindCommand(command, function):
       GCT.DisplayError(True, f"Failed to register the command: {command}")