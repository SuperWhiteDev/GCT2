import GCT
from time import sleep

global start_drop_gold, stop_drop_gold, increase_iters

global is_gold_dropping, iters
is_gold_dropping = False
iters = 0

def start_drop_gold():
    import Game
    from RDR2 import DEBUG
    
    if DEBUG.GET_GAME_VERSION_NAME() != "1491.50_dev_live_tu":
        address = None
    else:
        base = Game.GetBaseAddress()
        address = base+0xBAA0CF
    
    if address:
        replaced_bytes = [0x30, 0xC0, 0x90]
        
        Game.WriteBytes(address, replaced_bytes)
    
        is_gold_dropping = True
    iters = 0
    
def stop_drop_gold():
    import Game
    from RDR2 import DEBUG

    if DEBUG.GET_GAME_VERSION_NAME() != "1491.50_dev_live_tu":
        address = None
    else:
        base = Game.GetBaseAddress()
        address = base+0xBAA0CF
    if address:
        original_bytes = [0x84, 0x51, 0x14]
        
        Game.WriteBytes(address, original_bytes)
        
        is_gold_dropping = False
    
def increase_iters():
    global iters
    iters = iters + 1
    
def update():
    from time import sleep
    
    if iters > GCT.GetGlobalVariable("feature_gold_dropper_gold_dropping_time"):
        stop_drop_gold()
        
        GCT.SetGlobalVariableValue("feature_gold_dropper_dropping_gold", 0)
        GCT.SetGlobalVariableValue("feature_gold_dropper_gold_dropping_time", 0.0)
    else:
        if GCT.GetGlobalVariable("feature_gold_dropper_dropping_gold") and not is_gold_dropping:
            start_drop_gold()
        elif not GCT.GetGlobalVariable("feature_gold_dropper_dropping_gold") and is_gold_dropping:
            stop_drop_gold()
            
    if GCT.GetGlobalVariable("feature_gold_dropper_dropping_gold"):
        increase_iters()

def initialize_settings():
    if not GCT.IsGlobalVariableExist("feature_gold_dropper_gold_dropping_time"):
        GCT.RegisterGlobalVariable("feature_gold_dropper_gold_dropping_time", 0.0)

if __name__ == "__main__":
    sleep(1)
    
    initialize_settings()
    
    while GCT.IsScriptsStillWorking():
        update()
        sleep(1)
        