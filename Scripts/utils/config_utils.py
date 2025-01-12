def get_feature_settings():
    import GCT
    import json
    
    with open(GCT.GetGCTFolder() + "\\Settings\\feature_settings.json", "r", encoding="utf-8") as f:
        settings = json.load(f)
    
    return settings
    
def save_feature_settings(settings):
    import GCT
    import json
    
    with open(GCT.GetGCTFolder() + "\\Settings\\feature_settings.json", "w", encoding="utf-8") as f:
        settings = json.dump(settings, f, indent=4)
        
def GetCurrentLanguage():
    import GCT
    import json
    
    with open(GCT.GetGCTFolder() + "\\Settings\\config.json", "r", encoding="utf-8") as f:
        config = json.load(f)
        
    if "language" in config:
        return config["language"]
    else:
        return ""
            
def GetString(key : str):
    import GCT
    import json
    
    global language_file
    
    try:
        if key in language_file:
            return language_file[key]
        else:
            return ""
    except NameError:
        with open(GCT.GetGCTFolder() + f"\\Language\\{GetCurrentLanguage()}.json", "r", encoding="utf-8") as f:
            language_file = json.load(f)
        return GetString(key)
        
        