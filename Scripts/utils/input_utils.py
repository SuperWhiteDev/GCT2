
def input_vehicle() -> int:
    import GCT
    from RDR2 import ENTITY, PED, PLAYER
    
    vehicles = ["Pesonal vehicle", "Last vehicle", "Currect vehicle", "Custom"]
    vehicle = GCT.InputFromList("Choose vehicle: ", vehicles)
    
    if vehicle == 0:
        pass
    elif vehicle == 1:
        return PED.GET_VEHICLE_PED_IS_IN(PLAYER.PLAYER_PED_ID(), True)
    elif vehicle == 2:
        return PED.GET_VEHICLE_PED_IS_IN(PLAYER.PLAYER_PED_ID(), False)
    elif vehicle == 3:
        veh = int(input("Enter vehicle handle: "))
    
        if not veh and not ENTITY.DOES_ENTITY_EXIST(veh):
            GCT.DisplayError(False, "Uncorrect input")
        else:
            return veh
    else:
        return None
    
def input_coords() -> tuple:
    x = float(input("Enter X coord: "))
    y = float(input("Enter Y coord: "))
    z = float(input("Enter Z coord: "))
    return (x, y, z)