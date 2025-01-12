local entityUtils = { }

function entityUtils.IsEntityAtCoords(entity, targetX, targetY, targetZ, radius)
    local coords = ENTITY.GET_ENTITY_COORDS(entity, true, true)
        
    -- Check if the entity is within the specified area
    if math.abs(coords.x - targetX) <= radius and math.abs(coords.y - targetY) <= radius and math.abs(coords.z - targetZ) <= radius then
        return true
    end
    
    return false
end

return entityUtils