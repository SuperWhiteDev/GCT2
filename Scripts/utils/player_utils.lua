local playerUtils = { }

function playerUtils.IsPlayerPlaying()
    if not HUD.IS_PAUSE_MENU_ACTIVE() then
        return true
    else
        return false
    end
end

return playerUtils