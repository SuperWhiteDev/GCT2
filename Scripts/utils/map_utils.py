def GetWaypointCoords() -> tuple:
    from RDR2 import MAP
    
    if MAP.IS_WAYPOINT_ACTIVE():
        return MAP._GET_WAYPOINT_COORDS()
    else:
        return None
