import GCT

def set_time():
    from math import floor
    from RDR2 import CLOCK, NETWORK
    
    # Print the current game time in HH:MM:SS format
    current_time = f"{str(floor(CLOCK.GET_CLOCK_HOURS())).zfill(2)}:{str(floor(CLOCK.GET_CLOCK_MINUTES())).zfill(2)}:{str(floor(CLOCK.GET_CLOCK_SECONDS())).zfill(2)}"
    print(f"Current time is {current_time}")

    try:
        hours = int(GCT.Input("Enter hours: ", False))
        minutes = int(GCT.Input("Enter minutes: ", False))
        seconds = int(GCT.Input("Enter seconds: ", False))

        NETWORK._NETWORK_CLOCK_TIME_OVERRIDE(hours, minutes, seconds, 5000, False)
    except Exception:
        GCT.DisplayError(False, "Uncorrect input")

def set_weather():
    import GCT
    from RDR2 import MISC
    import enums.weather_types as weather_types
    
    weathers = []
    for weather, _ in weather_types.weather_types.items():
        weathers.append(weather)
        
    weatherID = GCT.InputFromList("Enter what weather you want: ", weathers)
    
    if weather != -1:
        weather = weather_types.weather_types[weathers[weatherID]]
        MISC.SET_WEATHER_TYPE(weather, True, True, True, 10.0, True)

def set_wind_speed():
    from RDR2 import MISC
    from time import sleep
    
    print(F"The wind speed is now {MISC.GET_WIND_SPEED()} mps")
    
    try:
        speed = int(GCT.Input("Enter wind speed: ", False))
        
        if speed >= 150.0:
            GCT.DisplayError(False, "Uncorrect input")
            return None
        
        # Gradually increase the wind speed to the desired value
        for i in range(int(MISC.GET_WIND_SPEED()), speed+1):
            MISC.SET_WIND_SPEED(float(i))
            sleep(0.10)
    except Exception:
        GCT.DisplayError(False, "Uncorrect input")

def set_snow():
    from RDR2 import MISC, GRAPHICS
    
    userChoice = GCT.Input("You want to turn on the snow? [Y/n]: ", True)
    if userChoice == "y":
        GRAPHICS._SET_SNOW_COVERAGE_TYPE(2)
        MISC._SET_SNOW_LEVEL(10.0)
    elif userChoice == "n":
        GRAPHICS._SET_SNOW_COVERAGE_TYPE(0)
        MISC._SET_SNOW_LEVEL(0.0)

def freeze_time():
    from RDR2 import CLOCK, NETWORK
    
    userChoice = GCT.Input("You want to stop the time change? [Y/n]: ", True)
    if userChoice == "y":
        # Stop the time change
        NETWORK._NETWORK_CLOCK_TIME_OVERRIDE(CLOCK.GET_CLOCK_HOURS(), CLOCK.GET_CLOCK_MINUTES(), CLOCK.GET_CLOCK_SECONDS(), 0, True)
    elif userChoice == "n":
        # Resume the time change
        NETWORK.NETWORK_CLEAR_CLOCK_TIME_OVERRIDE()
def freeze_weather():
    from RDR2 import MISC
    
    userChoice = GCT.Input("You want to make the weather permanent? [Y/n]: ", True)
    if userChoice == "y":
        MISC._SET_WEATHER_TYPE_FROZEN(True)
    elif userChoice == "n":
        MISC._SET_WEATHER_TYPE_FROZEN(False)

# Define a dictionary with commands and their functions
commands = {
    "set time": set_time,
    "set weather": set_weather,
    "set wind speed": set_wind_speed,
    "set snow": set_snow,
    "freeze time": freeze_time,
    "freeze weather": freeze_weather,
}

for command, function in commands.items():
    if not GCT.BindCommand(command, function):
        GCT.DisplayError(True, f"Failed to register the command: {command}")