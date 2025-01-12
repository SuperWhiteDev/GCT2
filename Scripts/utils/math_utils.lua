local mathUtils = { }

function mathUtils.BooleanToNumber(value)
    if type(value) == "boolean" then
        if value then
            return 1
        else
            return 0
        end
    end
    
    return 0
end

function mathUtils.pow(base, exponent)
    if exponent < 0 then
        return 1 / pow(base, -exponent)
    end

    local result = 1
    for i = 1, exponent do
        result = result * base
    end

    return result
end

function mathUtils.SumVectors(vec1, vec2)
    return {
        x = vec1.x + vec2.x,
        y = vec1.y + vec2.y,
        z = vec1.z + vec2.z
    }
end

function mathUtils.SubtractVectors(vec1, vec2)
    return {
        x = vec1.x - vec2.x,
        y = vec1.y - vec2.y,
        z = vec1.z - vec2.z
    }
end

function mathUtils.MultVector(vec1, num)
    return {
        x = vec1.x * num,
        y = vec1.y * num,
        z = vec1.z * num
    }
end

function mathUtils.GetDistanceBetweenCoords(point1, point2)
    local xDiff = point2.x - point1.x
    local yDiff = point2.y - point1.y
    local zDiff = point2.z - point1.z

    local distance = math.sqrt(mathUtils.pow(xDiff, 2) + mathUtils.pow(yDiff, 2) + mathUtils.pow(zDiff, 2))

    return distance
end

return mathUtils