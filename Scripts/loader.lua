local scripts = {
    GetGCTFolder().."\\Scripts\\features\\free_camera.lua",
    GetGCTFolder().."\\Scripts\\features\\session_notifications.lua",
    GetGCTFolder().."\\Scripts\\features\\bodyguards.lua"
}

for _, script in ipairs(scripts) do
    if not RunScript(script) then
        DisplayError(true, "Failed to run the script: " .. script)
    end
end

--[[
local name = "~t3~∑Player"
local tag = HUD._CREATE_MP_GAMER_TAG(PLAYER.PLAYER_ID(), name, false, false, "", 0)
HUD._SET_MP_GAMER_TAG_TYPE(tag, MISC.GET_HASH_KEY("GENERIC_PLAYER"))
HUD._SET_MP_GAMER_TAG_VISIBILITY(tag, 3)
]]
