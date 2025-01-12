#include "Network.h"
#include "Functions.h"


//Sends a request to other players to allow the transfer of control of an entity
void RequestControlOf(Entity entity) {
    NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(entity);

    for (int i = 0; i < 50; ++i) {
        if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(entity)) break;

        NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(entity);
    }
}
//Registers the entity on the network and then the entity will be visible to all players
void RegisterAsNetwork(Entity entity) {
    NETWORK::NETWORK_REGISTER_ENTITY_AS_NETWORKED(entity);
    Sleep(10);
    RequestControlOf(entity);
    int netID = NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(entity);
    NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(netID, true);
}

Object CreateNetObject(std::string model, Vector3& coords, bool PlaceOnGround)
{
    int iters = 0;

    Hash model_hash = MISC::GET_HASH_KEY(model.c_str());

    if (STREAMING::IS_MODEL_IN_CDIMAGE(model_hash) && STREAMING::IS_MODEL_VALID(model_hash)) {
        STREAMING::REQUEST_MODEL(model_hash, true);


        while (!STREAMING::HAS_MODEL_LOADED(model_hash)) {
            if (iters > 50) {
                GCTDisplayError("Failed to load model " + model);
                return 0;
            }

            Sleep(100);
            iters = iters + 1;
        }
        Object obj = OBJECT::CREATE_OBJECT(model_hash, coords.x, coords.y, coords.z, false, false, true, false, false);
        if (obj != 0.0 && ENTITY::DOES_ENTITY_EXIST(obj)) {
            RegisterAsNetwork(obj);
            ENTITY::SET_ENTITY_COLLISION(obj, true, true);
            if (PlaceOnGround) OBJECT::PLACE_OBJECT_ON_GROUND_PROPERLY(obj, true);

            STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model_hash);

            return obj;
        }
    }
    else GCTDisplayError("Not valid model " + model);

    return 0;
}

Object CreateNetObject(Hash hash, Vector3& coords, bool PlaceOnGround)
{
    int iters = 0;

    if (STREAMING::IS_MODEL_IN_CDIMAGE(hash) && STREAMING::IS_MODEL_VALID(hash)) {
        STREAMING::REQUEST_MODEL(hash, true);


        while (!STREAMING::HAS_MODEL_LOADED(hash)) {
            if (iters > 50) {
                GCTDisplayError("Failed to load model " + hash);
                return 0;
            }

            Sleep(100);
            iters = iters + 1;
        }
        Object obj = OBJECT::CREATE_OBJECT(hash, coords.x, coords.y, coords.z, false, false, true, false, false);
        if (obj != 0.0 && ENTITY::DOES_ENTITY_EXIST(obj)) {
            RegisterAsNetwork(obj);
            ENTITY::SET_ENTITY_COLLISION(obj, true, true);
            if (PlaceOnGround) OBJECT::PLACE_OBJECT_ON_GROUND_PROPERLY(obj, true);

            STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);

            return obj;
        }
    }
    else GCTDisplayError("Not valid model " + hash);

    return 0;
}

Object CreateNetObject(Hash hash, Vector3* coords, bool PlaceOnGround)
{
    int iters = 0;

    if (STREAMING::IS_MODEL_IN_CDIMAGE(hash) && STREAMING::IS_MODEL_VALID(hash)) {
        STREAMING::REQUEST_MODEL(hash, true);


        while (!STREAMING::HAS_MODEL_LOADED(hash)) {
            if (iters > 50) {
                GCTDisplayError("Failed to load model " + hash);
                return 0;
            }

            Sleep(100);
            iters = iters + 1;
        }
        Object obj = OBJECT::CREATE_OBJECT(hash, coords->x, coords->y, coords->z, false, false, true, false, false);
        if (obj != 0.0 && ENTITY::DOES_ENTITY_EXIST(obj)) {
            RegisterAsNetwork(obj);
            ENTITY::SET_ENTITY_COLLISION(obj, true, true);
            if (PlaceOnGround) OBJECT::PLACE_OBJECT_ON_GROUND_PROPERLY(obj, true);

            STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);

            return obj;
        }
    }
    else GCTDisplayError("Not valid model " + hash);

    return 0;
}

Ped CreateNetPed(std::string model, Vector3& coords, float heading, std::string sprite, std::string name, float scale)
{
    int iters = 0;

    Hash model_hash = MISC::GET_HASH_KEY(model.c_str());

    if (STREAMING::IS_MODEL_IN_CDIMAGE(model_hash) && STREAMING::IS_MODEL_VALID(model_hash)) {
        STREAMING::REQUEST_MODEL(model_hash, true);


        while (!STREAMING::HAS_MODEL_LOADED(model_hash)) {
            if (iters > 50) {
                GCTDisplayError("Failed to load model " + model);
                return 0;
            }

            Sleep(100);
            iters = iters + 1;
        }

        Ped ped = PED::CREATE_PED(model_hash, coords.x, coords.y, coords.z, heading, false, false, true, true);
        if (ped != 0.0 && ENTITY::DOES_ENTITY_EXIST(ped)) {
            RegisterAsNetwork(ped);
            PED::_SET_RANDOM_OUTFIT_VARIATION(ped, true);
            ENTITY::SET_ENTITY_VISIBLE(ped, true);
            ENTITY::PLACE_ENTITY_ON_GROUND_PROPERLY(ped, true);
            PED::CLEAR_PED_ENV_DIRT(ped);

            if (sprite != "") {
                Blip blip = MAP::BLIP_ADD_FOR_ENTITY(1664425300, ped); //style
                MAP::SET_BLIP_SPRITE(blip, MISC::GET_HASH_KEY(sprite.c_str()), true);
                MAP::SET_BLIP_SCALE(blip, scale);
                MAP::_SET_BLIP_NAME(blip, name.c_str());
            }
        }
        STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model_hash);

        return ped;
    }
    else GCTDisplayError("Not valid model " + model);

    return 0;
}

Ped CreateNetPed(Hash hash, Vector3& coords, float heading, std::string sprite, std::string name, float scale)
{
    int iters = 0;

    if (STREAMING::IS_MODEL_IN_CDIMAGE(hash) && STREAMING::IS_MODEL_VALID(hash)) {
        STREAMING::REQUEST_MODEL(hash, true);


        while (!STREAMING::HAS_MODEL_LOADED(hash)) {
            if (iters > 50) {
                GCTDisplayError("Failed to load model " + hash);
                return 0;
            }

            Sleep(100);
            iters = iters + 1;
        }

        Ped ped = PED::CREATE_PED(hash, coords.x, coords.y, coords.z, heading, false, false, true, true);
        if (ped != 0.0 && ENTITY::DOES_ENTITY_EXIST(ped)) {
            RegisterAsNetwork(ped);
            PED::_SET_RANDOM_OUTFIT_VARIATION(ped, true);
            ENTITY::SET_ENTITY_VISIBLE(ped, true);
            ENTITY::PLACE_ENTITY_ON_GROUND_PROPERLY(ped, true);
            PED::CLEAR_PED_ENV_DIRT(ped);

            if (sprite != "") {
                Blip blip = MAP::BLIP_ADD_FOR_ENTITY(1664425300, ped); //style
                MAP::SET_BLIP_SPRITE(blip, MISC::GET_HASH_KEY(sprite.c_str()), true);
                MAP::SET_BLIP_SCALE(blip, scale);
                MAP::_SET_BLIP_NAME(blip, name.c_str());
            }
        }
        STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);

        return ped;
    }
    else GCTDisplayError("Not valid model " + hash);

    return 0;
}

Ped CreateNetPed(Hash hash, Vector3* coords, float heading, std::string sprite, std::string name, float scale)
{
    int iters = 0;

    if (STREAMING::IS_MODEL_IN_CDIMAGE(hash) && STREAMING::IS_MODEL_VALID(hash)) {
        STREAMING::REQUEST_MODEL(hash, true);


        while (!STREAMING::HAS_MODEL_LOADED(hash)) {
            if (iters > 50) {
                GCTDisplayError("Failed to load model " + hash);
                return 0;
            }

            Sleep(100);
            iters = iters + 1;
        }

        Ped ped = PED::CREATE_PED(hash, coords->x, coords->y, coords->z, heading, false, false, true, true);
        if (ped != 0.0 && ENTITY::DOES_ENTITY_EXIST(ped)) {
            RegisterAsNetwork(ped);
            PED::_SET_RANDOM_OUTFIT_VARIATION(ped, true);
            ENTITY::SET_ENTITY_VISIBLE(ped, true);
            ENTITY::PLACE_ENTITY_ON_GROUND_PROPERLY(ped, true);
            PED::CLEAR_PED_ENV_DIRT(ped);

            if (sprite != "") {
                Blip blip = MAP::BLIP_ADD_FOR_ENTITY(1664425300, ped); //style
                MAP::SET_BLIP_SPRITE(blip, MISC::GET_HASH_KEY(sprite.c_str()), true);
                MAP::SET_BLIP_SCALE(blip, scale);
                MAP::_SET_BLIP_NAME(blip, name.c_str());
            }
        }
        STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);

        return ped;
    }
    else GCTDisplayError("Not valid model " + hash);

    return 0;
}

Vehicle CreateNetVehicle(std::string model, Vector3& coords, float heading, std::string sprite, std::string name, float scale)
{
    int iters = 0;

    Hash model_hash = MISC::GET_HASH_KEY(model.c_str());

    if (STREAMING::IS_MODEL_IN_CDIMAGE(model_hash) && STREAMING::IS_MODEL_VALID(model_hash)) {
        STREAMING::REQUEST_MODEL(model_hash, true);


        while (!STREAMING::HAS_MODEL_LOADED(model_hash)) {
            if (iters > 50) {
                GCTDisplayError("Failed to load model " + model);
                return 0;
            }

            Sleep(100);
            iters = iters + 1;
        }

        Vehicle veh = VEHICLE::CREATE_VEHICLE(model_hash, coords.x, coords.y, coords.z, heading, false, false, false, true);
        if (veh != 0.0 && ENTITY::DOES_ENTITY_EXIST(veh)) {
            RegisterAsNetwork(veh);
            VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh, true);
            VEHICLE::SET_VEHICLE_ENGINE_ON(veh, true, true);

            if (sprite != "") {
                Blip blip = MAP::BLIP_ADD_FOR_ENTITY(1664425300, veh); //style
                MAP::SET_BLIP_SPRITE(blip, MISC::GET_HASH_KEY(sprite.c_str()), true);
                MAP::SET_BLIP_SCALE(blip, scale);
                MAP::_SET_BLIP_NAME(blip, name.c_str());
            }
        }
        STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model_hash);

        return veh;
    }
    else GCTDisplayError("Not valid model " + model);

    return 0;
}

Vehicle CreateNetVehicle(Hash hash, Vector3& coords, float heading, std::string sprite, std::string name, float scale)
{
    int iters = 0;

    if (STREAMING::IS_MODEL_IN_CDIMAGE(hash) && STREAMING::IS_MODEL_VALID(hash)) {
        STREAMING::REQUEST_MODEL(hash, true);


        while (!STREAMING::HAS_MODEL_LOADED(hash)) {
            if (iters > 50) {
                GCTDisplayError("Failed to load model " + hash);
                return 0;
            }

            Sleep(100);
            iters = iters + 1;
        }

        Vehicle veh = VEHICLE::CREATE_VEHICLE(hash, coords.x, coords.y, coords.z, heading, false, false, false, true);
        if (veh != 0.0 && ENTITY::DOES_ENTITY_EXIST(veh)) {
            RegisterAsNetwork(veh);
            VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh, true);
            VEHICLE::SET_VEHICLE_ENGINE_ON(veh, true, true);

            if (sprite != "") {
                Blip blip = MAP::BLIP_ADD_FOR_ENTITY(1664425300, veh); //style
                MAP::SET_BLIP_SPRITE(blip, MISC::GET_HASH_KEY(sprite.c_str()), true);
                MAP::SET_BLIP_SCALE(blip, scale);
                MAP::_SET_BLIP_NAME(blip, name.c_str());
            }
        }
        STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);

        return veh;
    }
    else GCTDisplayError("Not valid model " + hash);

    return 0;
}

Vehicle CreateNetVehicle(Hash hash, Vector3* coords, float heading, std::string sprite, std::string name, float scale)
{
    int iters = 0;

    if (STREAMING::IS_MODEL_IN_CDIMAGE(hash) && STREAMING::IS_MODEL_VALID(hash)) {
        STREAMING::REQUEST_MODEL(hash, true);


        while (!STREAMING::HAS_MODEL_LOADED(hash)) {
            if (iters > 50) {
                GCTDisplayError("Failed to load model " + hash);
                return 0;
            }

            Sleep(100);
            iters = iters + 1;
        }

        Vehicle veh = VEHICLE::CREATE_VEHICLE(hash, coords->x, coords->y, coords->z, heading, false, false, false, true);
        if (veh != 0.0 && ENTITY::DOES_ENTITY_EXIST(veh)) {
            RegisterAsNetwork(veh);
            VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh, true);
            VEHICLE::SET_VEHICLE_ENGINE_ON(veh, true, true);

            if (sprite != "") {
                Blip blip = MAP::BLIP_ADD_FOR_ENTITY(1664425300, veh); //style
                MAP::SET_BLIP_SPRITE(blip, MISC::GET_HASH_KEY(sprite.c_str()), true);
                MAP::SET_BLIP_SCALE(blip, scale);
                MAP::_SET_BLIP_NAME(blip, name.c_str());
            }
        }
        STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);

        return veh;
    }
    else GCTDisplayError("Not valid model " + hash);

    return 0;
}

void DeleteNetObject(Object obj) {
    RequestControlOf(obj);

    ENTITY::SET_ENTITY_AS_MISSION_ENTITY(obj, true, true);

    OBJECT::DELETE_OBJECT(&obj);
}
void DeleteNetPed(Ped ped) {
    RequestControlOf(ped);

    ENTITY::SET_ENTITY_AS_MISSION_ENTITY(ped, true, true);

    PED::DELETE_PED(&ped);
}
void DeleteNetVehicle(Vehicle veh) {
    RequestControlOf(veh);
    ENTITY::SET_ENTITY_AS_MISSION_ENTITY(veh, true, true);

    VEHICLE::DELETE_VEHICLE(&veh);
}