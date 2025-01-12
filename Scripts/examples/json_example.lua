local data = {
    name = "John Doe",
    age = 30,
    is_student = false,
    courses = {"Math", "Physics", "Computer Science"}
}

local configfile = "myconfig.json"

-- Saving data to a file
JsonSave(configfile, data)
print("Saving data to " .. configfile)

-- Reading data from a file
local jsonData = JsonRead(configfile)
print(jsonData.name, jsonData.age, jsonData.is_student)
for _, course in ipairs(jsonData.courses) do
    print(course)
end