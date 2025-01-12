local configUtils = { }
local language_file

function configUtils.GetFeatureSetting(section, setting)
    local featuresSettings = JsonRead("Settings\\feature_settings.json")
    
    return featuresSettings[section][setting]
end

function configUtils.SetFeatureSetting(section, setting, value)
    local featuresSettings = JsonRead("Settings\\feature_settings.json")
    
    featuresSettings[section][setting] = value

    JsonSave("feature_settings.json", featuresSettings)
end

function configUtils.GetCurrentLanguage()
    local config = JsonRead("Settings\\config.json")
        
    if config["language"] then
        return config["language"]
    else
        return ""
    end
end
            
function configUtils.GetString(key)
    if language_file == nil then
        language_file = JsonRead("Language\\" .. configUtils.GetCurrentLanguage() .. ".json")
    end

    if language_file[key] then
        return language_file[key]
    else
        return ""
    end
end

return configUtils