--[[
��ʱ������
--]]

require("macros")
local humble = require("humble")
local utile = require("utile")

if not g_tChan then
    g_tChan = {}    
end
local tChan = g_tChan

function onStart()
    tChan.timer = humble.getChan("test")
end

function onStop()
    
end

function onTimer(uiTick, uiCount)
    tChan.timer:Send(utile.Pack(uiTick, uiCount))
    
    --1��
    if 0 == ((uiTick * uiCount) % 1000) then 
        --print("1 sec")
        --print(string.format("cur load %d.", humble.getCurLoad()))
    end
end
