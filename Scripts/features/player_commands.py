import GCT

global set_model

def set_model(model : str) -> bool:
    import GCT
    from RDR2 import STREAMING, MISC, PLAYER
    from time import sleep
    
    model_hash = MISC.GET_HASH_KEY(model)
    
    if STREAMING.IS_MODEL_IN_CDIMAGE(model_hash) and STREAMING.IS_MODEL_VALID(model_hash):
        STREAMING.REQUEST_MODEL(model_hash, True)
        
        iters = 0
        while not STREAMING.HAS_MODEL_LOADED(model_hash):
            if iters > 50:
                GCT.DisplayError(False, f"Failed to load model {model}")
                return False

            sleep(0.1)
            iters = iters + 1
            
        player_ped = PLAYER.PLAYER_PED_ID()
        
        PED.SET_PED_CONFIG_FLAG(player_ped, 265, 0)
        PLAYER.SET_PLAYER_MODEL(player_ped, model_hash, True)
        PED._SET_RANDOM_OUTFIT_VARIATION(player_ped, 1)
        
        STREAMING.SET_MODEL_AS_NO_LONGER_NEEDED(model_hash)
        
        return True
    else:
	    return False

def save_model():
    pass

def change_model():
    import GCT
    
    options = [ "Male", "Female", "Animal", "Bird", "Custom" ]
    option = GCT.InputFromList("Choose the type of model that you want: ", options)
    
    if option == 0:
        options = [ "Sheriff", "Marine", "Pinkerton", "Miner", "John Marston", "Dutch", "Arthur Morgan" ]
        option = GCT.InputFromList("Choose the model that you want: ", options)
        
        model = ""
        if option == 0:
            model = "U_M_M_RhdSheriff_01"
        elif option == 1:
            model = "A_M_M_AsbMiner_01"
        elif option == 2:
            model = "CS_PinkertonGoon"
        elif option == 3:
            model = "U_M_M_ARMYTRN4_01"
        elif option == 4:
            model = "CS_johnmarston"
        elif option == 5:
            model = "CS_dutch_02"
        elif option == 6:
            model = "Player_Zero"
            
        set_model(model)
    elif option == 1:
        options = [ "Abigail Roberts", "Sadie Adler", "Mary Beth", "German Daughter" ]
        option = GCT.InputFromList("Choose the model that you want: ", options)
        
        model = ""
        if option == 0:
            model = "CS_abigailroberts"
        elif option == 1:
            model = "CS_mrsadler"
        elif option == 2:
            model = "CS_marybeth"
        elif option == 3:
            model = "CS_GermanDaughter"
            
        set_model(model)
    elif option == 2:
        options = [ "Alligator", "Bear", "Cat", "Deer", "Andalusian RoseGray" ]
        option = GCT.InputFromList("Choose the model that you want: ", options)
        
        model = ""
        if option == 0:
            model = "A_C_ALLIGATOR_01"
        elif option == 1:
            model = "A_C_Bear_01"
        elif option == 2:
            model = "A_C_Cat_01"
        elif option == 3:
            model = "A_C_Deer_01"
        elif option == 4:
            model = "A_C_Horse_Andalusian_RoseGray"
            
        set_model(model)
    elif option == 3:
        options = [ "Crow", "Eagle" ]
        option = GCT.InputFromList("Choose the model that you want: ", options)
        
        model = ""
        if option == 0:
            model = "A_C_Crow_01"
        elif option == 1:
            model = "A_C_Eagle_01"
            
        set_model(model)
    elif option == 4:
        set_model(GCT.Input("Enter the model that you want: ", False))

def outfit():
    import GCT
    from RDR2 import PED, PLAYER
    
    # Get the number of available outfit variations for the player's character
    num_outfits = PED.GET_NUM_META_PED_OUTFITS(PLAYER.PLAYER_PED_ID())
    
    outfit = int(GCT.Input(f"Enter an outfit index in the range 0 to {num_outfits}: ", False))
    
    if outfit > -1 and outfit < num_outfits:
        PED._EQUIP_META_PED_OUTFIT_PRESET(PLAYER.PLAYER_PED_ID(), outfit, True) 
    else:
        GCT.DisplayError(False, "Uncorrect input")

# Define a dictionary with commands and their functions
commands = {
    "save model": save_model,
    "change model": change_model,
    "outfit": outfit,
}

for command, function in commands.items():
    if not GCT.BindCommand(command, function):
       GCT.DisplayError(True, f"Failed to register the command: {command}")