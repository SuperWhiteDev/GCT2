local teleportUtils = { }

--- Teleports the entity to the specified coordinates.
-- If z = 0, then the z coordinate will be found automatically.
-- @param entity number: The ID of the entity to teleport.
-- @param coords table: The coordinates to teleport to.
-- @return nil: This function does not return a value.
function teleportUtils.TeleportEntity(entity, coords)
    local heights = { 100.0, 150.0, 50.0, 0.0, -50.0, -100.0, -150.0, 200.0, 250.0, 300.0, 325.0, 350.0, 400.0, 450.0, 500.0, 550.0, 600.0, 650.0, 700.0, 750.0, 800.0 }

    local coordZp = New(4)

    if coords.z == 0.0 then
        for i = 1, #heights, 1 do
            ENTITY.SET_ENTITY_COORDS_NO_OFFSET(entity, coords.x, coords.y, heights[i], false, false, true)
            TASK.CLEAR_PED_TASKS_IMMEDIATELY(entity)
            if MISC.GET_GROUND_Z_FOR_3D_COORD(coords.x, coords.y, heights[i], coordZp) then
                ENTITY.SET_ENTITY_COORDS_NO_OFFSET(entity, coords.x, coords.y, Game.ReadFloat(coordZp) + 2.0, false, false, true)
                break
            end
        end
    else
        ENTITY.SET_ENTITY_COORDS_NO_OFFSET(entity, coords.x, coords.y, coords.z + 2.0, false, false, true)
    end

    Delete(coordZp)
end

--- Teleports the entity to the specified coordinates and with heading.
-- If z = 0, then the z coordinate will be found automatically.
-- @param entity number: The ID of the entity to teleport.
-- @param coords table: The coordinates to teleport to.
-- @param heading number Heading the player's body.
-- @return nil: This function does not return a value.
function teleportUtils.TeleportEntityWithHeading(entity, coords, heading)
    teleportUtils.TeleportEntity(entity, coords)
    
    ENTITY.SET_ENTITY_HEADING(entity, heading)
end

return teleportUtils