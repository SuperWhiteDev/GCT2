import GCT

global drop_gold_thread

def drop_one_gold():
    import Game
    from RDR2 import DEBUG
    from time import sleep
    
    address = None
    
    if DEBUG.GET_GAME_VERSION_NAME() != "1491.50_dev_live_tu":
        return
    else:
        base = Game.GetBaseAddress()
        address = base+0xBAA0CF
        
    replaced_bytes = [0x30, 0xC0, 0x90]
    original_bytes = [0x84, 0x51, 0x14]
        
    Game.WriteBytes(address, replaced_bytes)
        
    sleep(1)
        
    Game.WriteBytes(address, original_bytes)
        
def drop_gold():
    import GCT
    
    if GCT.GetGlobalVariable("feature_gold_dropper_dropping_gold"): 
        GCT.SetGlobalVariableValue("feature_gold_dropper_dropping_gold", 0)
        print("Gold's dropping has stalled")
    else:
        userChoice = GCT.Input("You agree to start giving gold to you. But remember that such actions may be detected by Rockstar and your account may be blocked? [Y/n]: ", True)
    
        if userChoice == "y":
            if GCT.IsGlobalVariableExist("feature_gold_dropper_gold_dropping_time"):
                GCT.SetGlobalVariableValue("feature_gold_dropper_gold_dropping_time", float(GCT.Input("Enter the duration of time for which you will receive gold, in seconds: ", False)))
            else:
                GCT.RegisterGlobalVariable("feature_gold_dropper_gold_dropping_time", float(GCT.Input("Enter the duration of time for which you will receive gold, in seconds: ", False)))
            
            if GCT.IsGlobalVariableExist("feature_gold_dropper_dropping_gold"):
                if not GCT.GetGlobalVariable("feature_gold_dropper_dropping_gold"):    
                    GCT.SetGlobalVariableValue("feature_gold_dropper_dropping_gold", 1)
                    print("The gold dropping is about to begin")
            else:
                print("The gold dropping is about to begin")
                GCT.RegisterGlobalVariable("feature_gold_dropper_dropping_gold", 1)

# Define a dictionary with commands and their functions
commands = {
    "drop one gold": drop_one_gold,
    "drop gold": drop_gold,
}

for command, function in commands.items():
    if not GCT.BindCommand(command, function):
       GCT.DisplayError(True, f"Failed to register the command: {command}")