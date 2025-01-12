local graphics = require("graphics++")

local current_session_id = 0
local session_idp = nil

local players_list = nil

function getPlayerList()
    local players = {}

    for i = 1, NETWORK.NETWORK_GET_NUM_CONNECTED_PLAYERS()+1, 1 do
        players[i] = PLAYER.GET_PLAYER_NAME(i)
    end

    return players
end

function comparePlayerLists(table1, table2)
    for _, value in ipairs(table2) do
        local found = false
        for _, v in ipairs(table1) do
            if value == v then
                found = true
                break
            end
        end
        if not found then
            return value
        end
    end
    return nil
end

session_idp = New(4)

while ScriptStillWorking do
    if not SCRIPTS.IS_LOADING_SCREEN_VISIBLE() then
        NETWORK._NETWORK_SESSION_GET_SESSION_ID(session_idp)

        if Game.ReadInt(session_idp) ~= current_session_id then
            current_session_id = Game.ReadInt(session_idp)
            players_list = getPlayerList()
        end
    
        local players = getPlayerList()

        local res = comparePlayerLists(players_list, players)
        if res then
            players_list = players                                                                                                                                                                                                   
            graphics.Notification.NotificationWithDuration("Player \"" .. res .. "\" has joined", 6)
        end
        local res = comparePlayerLists(players, players_list)
        if res then
            players_list = players
            graphics.Notification.NotificationWithDuration("Player \"" .. res .. "\" has disconnected", 6)
            
        end
    end

    Wait(2000)
end

Delete(session_idp)