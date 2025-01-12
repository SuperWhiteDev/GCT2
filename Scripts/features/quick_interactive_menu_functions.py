def refil_ammo():
    import Game
    import GCT
    from RDR2 import WEAPON, PLAYER, ENTITY, OBJECT, MISC
    from enums.ammo_types import hashammo_type_to_pickup_object, weaponhash_to_pickup_object

    weapon_hash = WEAPON._GET_PED_CURRENT_HELD_WEAPON(PLAYER.PLAYER_PED_ID())

    if weapon_hash in weaponhash_to_pickup_object:
        pickup_object = MISC.GET_HASH_KEY(weaponhash_to_pickup_object[weapon_hash])
            
        ammop = GCT.New(4)
        WEAPON.GET_MAX_AMMO(PLAYER.PLAYER_PED_ID(), ammop, WEAPON._GET_PED_CURRENT_HELD_WEAPON(PLAYER.PLAYER_PED_ID()))
        max_ammo = Game.ReadInt(ammop) - WEAPON.GET_AMMO_IN_PED_WEAPON(PLAYER.PLAYER_PED_ID(), WEAPON._GET_PED_CURRENT_HELD_WEAPON(PLAYER.PLAYER_PED_ID()))
        if max_ammo >= 6:
            max_ammo = int(max_ammo / 6)
            
        player_coords = ENTITY.GET_ENTITY_COORDS(PLAYER.PLAYER_PED_ID(), True, True)
            
        iters = 0
        count = 0
        while iters <= 50:
            if OBJECT.CREATE_PICKUP(pickup_object, player_coords[0], player_coords[1], player_coords[2], 8, 0, False, 0, 0, 0, 0):
                count += 1
            if count >= max_ammo:
                break
            iters += 1
    else:
        ammo_type_hash = WEAPON._GET_CURRENT_PED_WEAPON_AMMO_TYPE(PLAYER.PLAYER_PED_ID(), WEAPON._GET_PED_WEAPON_OBJECT(PLAYER.PLAYER_PED_ID(), True))
        if ammo_type_hash in hashammo_type_to_pickup_object:
            pickup_object = hashammo_type_to_pickup_object[ammo_type_hash]
                
            ammop = GCT.New(4)
            WEAPON.GET_MAX_AMMO(PLAYER.PLAYER_PED_ID(), ammop, WEAPON._GET_PED_CURRENT_HELD_WEAPON(PLAYER.PLAYER_PED_ID()))
            max_ammo = Game.ReadInt(ammop) - WEAPON.GET_AMMO_IN_PED_WEAPON(PLAYER.PLAYER_PED_ID(), WEAPON._GET_PED_CURRENT_HELD_WEAPON(PLAYER.PLAYER_PED_ID())) + 1
                
            player_coords = ENTITY.GET_ENTITY_COORDS(PLAYER.PLAYER_PED_ID(), True, True)
                
            if max_ammo >= 1:
                iters = 0
                count = 0
                while iters < 25:
                    if OBJECT.CREATE_PICKUP(MISC.GET_HASH_KEY(pickup_object), player_coords[0], player_coords[1], player_coords[2], 8, 0, False, 0, 0, 0, 0):
                        count += 1

                        if count >= max_ammo:
                            break
                    iters += 1

                GCT.Delete(ammop)
    #print(WEAPON._GET_WEAPON_NAME_2(WEAPON._GET_PED_CURRENT_HELD_WEAPON(PLAYER.PLAYER_PED_ID())))
        
    #object = WEAPON._GET_PED_WEAPON_OBJECT(PLAYER.PLAYER_PED_ID(), True)
    #WEAPON._GET_CURRENT_PED_WEAPON_AMMO_TYPE(PLAYER.PLAYER_PED_ID(), object)
def get_on_my_horse():
    from RDR2 import PLAYER, PED
    horse = PLAYER.GET_MOUNT_OWNED_BY_PLAYER(PLAYER.PLAYER_ID())
    if not horse:
        horse = PED._GET_LAST_MOUNT(PLAYER.PLAYER_PED_ID())
    if horse:
        PED.SET_PED_ONTO_MOUNT(PLAYER.PLAYER_PED_ID(), horse, -1, True)
def end_pursuit():
    from RDR2 import PLAYER, LAW
    from time import sleep
        
    #LAW.SET_BOUNTY(PLAYER.PLAYER_ID(), 0)
    LAW.SET_WANTED_SCORE(PLAYER.PLAYER_ID(), 0)
    PLAYER.SET_WANTED_LEVEL_MULTIPLIER(0.0)
    sleep(0.25)
    PLAYER.SET_WANTED_LEVEL_MULTIPLIER(1.0)

def explode_coords(coords, radius, count = 35):
    from RDR2 import PLAYER, MISC
    from random import randint
    from time import sleep
        
    for i in range(count):
        for i in range(2):
            x_offset = randint(-radius, radius)
            y_offset = randint(-radius, radius)
                
            MISC.SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords[0]+x_offset+0.15, coords[1]+y_offset-0.15, 200, coords[0]+x_offset, coords[1]+y_offset, coords[2], 50, True, 0x7067E7A7, PLAYER.PLAYER_PED_ID(), True, False, 0xbf800000, False)
            MISC.SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords[0]+x_offset-0.15, coords[1]-y_offset-0.15, 200, coords[0]+x_offset, coords[1]+y_offset, coords[2], 50, True, 0x7067E7A7, PLAYER.PLAYER_PED_ID(), True, False, 0xbf800000, False)
            sleep(randint(6, 16) / 100)
        sleep(0.25)
        
    MISC.SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords[0]-0.1, coords[1]+0.1, 200, coords[0]+x_offset, coords[1]+y_offset, coords[2], 50, True, 0x7067E7A7, PLAYER.PLAYER_PED_ID(), True, False, 0xbf800000, False)
    MISC.SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords[0]+0.1, coords[1]-0.1, 200, coords[0]+x_offset, coords[1]+y_offset, coords[2], 50, True, 0x7067E7A7, PLAYER.PLAYER_PED_ID(), True, False, 0xbf800000, False)
        
def explode_area():
    import GCT
    import utils.map_utils as map_utils
    import utils.Graphics
    import utils.Graphics.graphicspp as Graphics
    import threading
    from time import sleep
    
    x, y = Graphics.graphics_base.GetDisplaySize()
    
    width = 395
    height = 80
    rect = Graphics.RectWithBorders(x - width, 5, width, height, 166, 0, 0, 179, 20, 20, 20, 4, 1)
    text = Graphics.Text("Set waypoing to the area you want to blow up", x - width + 5, 35, 255, 255, 255, 255, "Arial", 16)
    
    coords = None
    while not coords and GCT.IsScriptsStillWorking():
        coords = map_utils.GetWaypointCoords()
        sleep(0.05)
    
    del rect
    del text
        
    if coords:
        explode_coords(coords, 30.0)
        #threading.Thread(target=explode_coords, args=(coords, 30.0), daemon=True)
        
def godmode():
    import GCT
    import Game
    from RDR2 import ENTITY, PLAYER, UITUTORIAL
    from time import sleep
    
    if 0:
        pass
    else:
        if GCT.IsGlobalVariableExist("feature_godmode_godmode_enabled"):
            if not GCT.GetGlobalVariable("feature_godmode_godmode_enabled"):    
                UITUTORIAL._UITUTORIAL_SET_RPG_ICON_VISIBILITY(5, 3)
                GCT.SetGlobalVariableValue("feature_godmode_godmode_enabled", 1)
            else:
                UITUTORIAL._UITUTORIAL_SET_RPG_ICON_VISIBILITY(5, 0)
                GCT.SetGlobalVariableValue("feature_godmode_godmode_enabled", 0)
                
                sleep(0.05)
                
                ENTITY.SET_ENTITY_INVINCIBLE(PLAYER.PLAYER_PED_ID(), False)
        else:
            UITUTORIAL._UITUTORIAL_SET_RPG_ICON_VISIBILITY(5, 3)
            GCT.RegisterGlobalVariable("feature_godmode_godmode_enabled", 1)
            
def suicide():
    from RDR2 import ENTITY, PLAYER
    from enums.weapons import weapons
    ENTITY.SET_ENTITY_HEALTH(PLAYER.PLAYER_PED_ID(), 0, 0)
    #ENTITY._CHANGE_ENTITY_HEALTH(PLAYER.PLAYER_PED_ID(), 0.0, 0, weapons["weapon_bleeding"]) 