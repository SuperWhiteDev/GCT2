local mapUtils = { }

function mapUtils.GetWaypointCoords()
    if MAP.IS_WAYPOINT_ACTIVE() then
        return MAP._GET_WAYPOINT_COORDS()
    else
        return nil
    end
end

return mapUtils