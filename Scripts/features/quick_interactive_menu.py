import time
import GCT
import Gamepad

def InteractiveMenu():     
    import GCT
    import Gamepad
    from RDR2 import AUDIO
    from features.quick_interaction_menu import QuickInteractionMenu
    from features.quick_interactive_menu_functions import refil_ammo, get_on_my_horse, end_pursuit, explode_area, godmode, suicide
    from utils.player_utils import IsPlayerPlaying
    
    if not IsPlayerPlaying():
        return
        
    options = {}
    if GCT.GetGlobalVariable("feature_godmode_godmode_enabled"):
        options["Godmode: enabled"] = godmode
    else:
        options["Godmode: disabled"] = godmode
    options = { **options, **{
        "Refill ammunition": refil_ammo,
        "Get on my horse": get_on_my_horse,
        "End pursuit": end_pursuit,
        "Explode area": explode_area,
        "Suicide" : suicide
    } }
        
    menu = QuickInteractionMenu(options, 10, 10, 200, 40)
    time.sleep(0.1)
    
    while GCT.IsScriptsStillWorking() and not GCT.IsPressedKey(open_interactive_menu):
        pressed_key = QIM_gamepad.get_pressed_key()
        if GCT.IsPressedKey(interactive_menu_move_up_key):
            AUDIO.PLAY_SOUND_FRONTEND("NAV_RIGHT", "HUD_PLAYER_MENU", 0, 0)
            menu.move_up()
        elif GCT.IsPressedKey(interactive_menu_move_down_key):
            AUDIO.PLAY_SOUND_FRONTEND("NAV_RIGHT", "HUD_PLAYER_MENU", 0, 0)
            menu.move_down()
        elif GCT.IsPressedKey(interactive_menu_select_key):
            menu.select_option()
            break
        
        if pressed_key == gamepad_open_interactive_menu:
            break
        if pressed_key == gamepad_interactive_menu_move_down_key:
            AUDIO.PLAY_SOUND_FRONTEND("NAV_RIGHT", "HUD_PLAYER_MENU", 0, 0)
            menu.move_down()
        elif pressed_key == gamepad_interactive_menu_select_key:
            menu.select_option()
            break
        
        time.sleep(0.078)
    
    menu.destroy()
    time.sleep(0.5)

def initialize_settings():
    import utils.config_utils as config_utils
    
    global open_interactive_menu, interactive_menu_move_down_key, interactive_menu_move_up_key, interactive_menu_select_key, gamepad_open_interactive_menu, gamepad_interactive_menu_move_down_key, gamepad_interactive_menu_select_key
    
    feature_settings = config_utils.get_feature_settings()

    open_interactive_menu = GCT.ConvertStringToKeyCode(feature_settings["Hotkeys"]["OpenInteractiveMenu"])
    interactive_menu_move_down_key = GCT.ConvertStringToKeyCode(feature_settings["Hotkeys"]["InteractiveMenuMoveDownKey"])
    interactive_menu_move_up_key = GCT.ConvertStringToKeyCode(feature_settings["Hotkeys"]["InteractiveMenuMoveUpKey"])
    interactive_menu_select_key = GCT.ConvertStringToKeyCode(feature_settings["Hotkeys"]["InteractiveMenuSelectKey"])

    gamepad_open_interactive_menu = feature_settings["Hotkeys"]["GamepadOpenInteractiveMenu"]
    gamepad_interactive_menu_move_down_key = feature_settings["Hotkeys"]["GamepadInteractiveMenuMoveDownKey"]
    gamepad_interactive_menu_select_key = feature_settings["Hotkeys"]["GamepadInteractiveMenuSelectKey"]

initialize_settings()

global QIM_gamepad
QIM_gamepad = Gamepad.Gamepad()
while GCT.IsScriptsStillWorking():
    gamepad_key = QIM_gamepad.get_pressed_key()
    
    if GCT.IsPressedKey(open_interactive_menu):
        InteractiveMenu()
    if gamepad_key == gamepad_open_interactive_menu:
        InteractiveMenu()
    time.sleep(0.08)