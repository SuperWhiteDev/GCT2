
def SumVectors(vec1 : list, vec2 : list) -> list:
    import math
    
    return [
        vec1[0] + vec2[0],
        vec1[1] + vec2[1],
        vec1[2] + vec2[2]
    ]

def SubtractVectors(vec1 : list, vec2 : list) -> list:
    import math
    
    return [
        vec1[0] - vec2[0],
        vec1[1] - vec2[1],
        vec1[2] - vec2[2]
    ]

def MultVector(vec1 : list, num) -> list:
    import math
    
    return [
        vec1[0] * num,
        vec1[1] * num,
        vec1[2] * num
    ]

def GetDistanceBetweenCoords(point1 : list, point2 : list) -> float:
    import math
    
    x_diff = point2[0] - point1[0]
    y_diff = point2[1] - point1[1]
    z_diff = point2[2] - point1[2]

    return math.sqrt(math.pow(x_diff, 2) + math.pow(y_diff, 2) + math.pow(z_diff, 2))