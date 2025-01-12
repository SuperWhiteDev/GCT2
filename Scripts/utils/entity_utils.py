def is_entity_at_coords(entity, target_x, target_y, target_z, radius):
    coords = ENTITY.GET_ENTITY_COORDS(entity, True, True)
        
    # Check if the entity is within the specified area
    if (abs(coords[0] - target_x) <= radius and abs(coords[1] - target_y) <= radius and abs(coords[2] - target_z) <= radius):
        return True
        
    return False