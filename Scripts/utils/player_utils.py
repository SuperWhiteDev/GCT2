def IsPlayerPlaying() -> bool:
    from RDR2 import HUD
    
    if not HUD.IS_PAUSE_MENU_ACTIVE():
        return True
    else:
        return False