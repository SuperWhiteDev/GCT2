local vector1 = { }
local vector2 = { }

local sum = {}

math.randomseed(os.time())

for i = 1, 10 do
    vector1[i] = math.random(2, (i+1)^3)
    vector2[i] = math.random(2, vector1[i]+(math.random(0, i*i) - i))
end

SetOutputLockon(true)
for i = 1, 10 do
    sum[i] = vector1[i] * vector2[i]
    io.write_anonym(sum[i] .. ", ")
end
io.write_anonym("\n")
SetOutputLockon(false)