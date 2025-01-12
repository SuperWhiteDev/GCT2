import GCT
import os
import time

global set_mission_flag

def set_mission_flag(state):
    if GCT.IsGlobalVariableExist("missions_mission_flag_state"):
        GCT.SetGlobalVariableValue("missions_mission_flag_state", state)
    else:
        GCT.RegisterGlobalVariable("missions_mission_flag_state", state)

def missions_view():
    if GCT.GetGlobalVariable("missions_mission_flag_state"):
        GCT.DisplayError(False, "There is already one active mission at the moment")      
        return None
    
    missions = {}

    missions_folder = GCT.GetGCTFolder()+"\\Scripts\\missions"

    for filename in os.listdir(missions_folder):
        full_path = os.path.join(missions_folder, filename)

        if os.path.isfile(full_path):
            # Получение имени файла без расширения
            name = os.path.splitext(filename)[0]

            missions[name] = full_path

    if os.path.isfile(os.path.join(GCT.GetGCTFolder(), "Scripts", "examples", "Example mission.lua")):
        missions["Example mission"] = GCT.GetGCTFolder()+"\\Scripts\\examples\\Example mission.lua"
    
    mission_names = list(missions.keys())
    mission = GCT.InputFromList("Choose which mission you want to start: ", mission_names)

    if mission != -1:
        file_path = missions[mission_names[mission]]
        _, extension = os.path.splitext(file_path)
        
        if extension == ".py":
            GCT.RunScript(file_path)
            set_mission_flag(1)
        elif extension == ".lua":
            GCT.RunLuaScript(file_path)
            set_mission_flag(1)
        else:
            GCT.DisplayError(False, "Unknown mission file name extension")      
        
    time.sleep(1.0)  

#Define a dictionary with commands and their functions
commands = {
    "missions": missions_view
}

for command, function in commands.items():
    if not GCT.BindCommand(command, function):
       GCT.DisplayError(True, f"Failed to register the command: {command}")