#pragma once
#include "NativeFunctions.h"
#include <string>

void RequestControlOf(Entity entity);
void RegisterAsNetwork(Entity entity);

Object CreateNetObject(std::string model, Vector3& coords, bool PlaceOnGround = true);
Object CreateNetObject(Hash hash, Vector3& coords, bool PlaceOnGround = true);
Object CreateNetObject(Hash hash, Vector3* coords, bool PlaceOnGround = true);

Ped CreateNetPed(std::string model, Vector3& coords, float heading, std::string sprite = "", std::string name = "", float scale = 0.0);
Ped CreateNetPed(Hash hash, Vector3& coords, float heading, std::string sprite = "", std::string name = "", float scale = 0.0);
Ped CreateNetPed(Hash hash, Vector3* coords, float heading, std::string sprite = "", std::string name = "", float scale = 0.0);

Vehicle CreateNetVehicle(std::string model, Vector3& coords, float heading, std::string sprite = "", std::string name = "", float scale = 0.0);
Vehicle CreateNetVehicle(Hash hash, Vector3& coords, float heading, std::string sprite = "", std::string name = "", float scale = 0.0);
Vehicle CreateNetVehicle(Hash hash, Vector3* coords, float heading, std::string sprite = "", std::string name = "", float scale = 0.0);

void DeleteNetObject(Object obj);
void DeleteNetPed(Ped ped);
void DeleteNetVehicle(Vehicle veh);
