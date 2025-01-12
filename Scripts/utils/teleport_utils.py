import GCT
global GCT

def TeleportEntity(entity : int, coords : tuple | dict) -> None:
    """ Teleports the entity to the specified coordinates. If z = 0 then the z coordinate will be found automatically."""
    import Game
    from RDR2 import ENTITY, MISC, PED, TASK
    
    heights = [ 100.0, 150.0, 50.0, 0.0, -50.0, -100.0, -150.0, 200.0, 250.0, 300.0, 325.0, 350.0, 400.0, 450.0, 500.0, 550.0, 600.0, 650.0, 700.0, 750.0, 800.0 ]
    coordZp = GCT.New(4)
    
    if isinstance(coords, dict):
        coords_new = [coords["x"], coords["y"], coords["z"]]
        coords = coords_new
    
    if coords[2] == 0.0:
        ENTITY.FREEZE_ENTITY_POSITION(entity, True)
        for height in heights:
            ENTITY.SET_ENTITY_COORDS(entity, coords[0], coords[1], height, False, False, True, True)
            if MISC.GET_GROUND_Z_FOR_3D_COORD(coords[0], coords[1], height, coordZp, False):
                ENTITY.SET_ENTITY_COORDS_NO_OFFSET(entity, coords[0], coords[1], Game.ReadFloat(coordZp) + 2.0, False, False, True)
                break
        ENTITY.FREEZE_ENTITY_POSITION(entity, False)
    else:
        ENTITY.SET_ENTITY_COORDS_NO_OFFSET(entity, coords[0], coords[1], coords[2] + 2.0, False, False, True)
    GCT.Delete(coordZp)
    
def TeleportEntityWithHeading(entity : int, coords : tuple | dict, heading : float) -> None:
    from RDR2 import ENTITY
    TeleportEntity(entity, coords)
    
    ENTITY.SET_ENTITY_HEADING(entity, heading)
    
    