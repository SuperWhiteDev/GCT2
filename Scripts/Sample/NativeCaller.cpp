#include <iostream>
#include "NativeCaller.h"

typedef HASH(__cdecl* _HashString)(const std::string& functionName);
_HashString HashStringF;

typedef uint64_t(__cdecl* _FindFunctionAddress)(const HASH functionHash);
_FindFunctionAddress FindFunctionAddressF;

typedef Vector3* (__cdecl* _GetVector)();
_GetVector GetVectorF;

typedef void(__cdecl* _DeleteVector)(Vector3* vector);
_DeleteVector DeleteVectorF;

typedef float(__cdecl* _ToFloat)(UINT32 value);
_ToFloat ToFloatF;

typedef Ped(__cdecl* _Call_PLAYER_PED_ID)();
_Call_PLAYER_PED_ID Call_PLAYER_PED_IDF;

typedef uintptr_t* (__cdecl* _GetEntityStruct)(Entity entity);
_GetEntityStruct GetEntityStructF;

typedef size_t(__cdecl* _GetAllEntities)(Entity* arrayOfEntities, size_t size);
_GetAllEntities GetAllEntitiesF;

typedef size_t(__cdecl* _GetAllPeds)(Ped* arrayOfPeds, size_t size);
_GetAllPeds GetAllPedsF;

typedef size_t(__cdecl* _GetAllVehicles)(Vehicle* arrayOfVehicles, size_t size);
_GetAllVehicles GetAllVehiclesF;

typedef size_t(__cdecl* _GetAllObjects)(Object* arrayOfObjects, size_t size);
_GetAllObjects GetAllObjectsF;

typedef void(__cdecl* _NativeReset)();
_NativeReset NativeResetF;

typedef void(__cdecl* _NativePush)(void* arg);
_NativePush NativePushF;

typedef void* (__cdecl* _NativeCall)(UINT64 FunctionAddress);
_NativeCall NativeCallF;

typedef std::mutex& (__cdecl* _GetCallMutex)();
_GetCallMutex GetCallMutexF;

HASH HashString(const std::string& functionName) { return HashStringF(functionName); }
uint64_t FindFunctionAddress(const HASH functionHash) { return FindFunctionAddressF(functionHash); }

Vector3* GetVector() { return GetVectorF(); }
void DeleteVector(Vector3* vector) { return DeleteVectorF(vector); }
float ToFloat(UINT32 value) { return ToFloatF(value); }

Player Call_PLAYER_PED_ID() { return Call_PLAYER_PED_IDF(); }
uintptr_t* GetEntityStruct(Entity entity) { return GetEntityStructF(entity); }
size_t GetAllEntities(Entity* arrayOfEntities, size_t size) { return GetAllEntitiesF(arrayOfEntities, size); }
size_t GetAllPeds(Ped* arrayOfPeds, size_t size) { return GetAllPedsF(arrayOfPeds, size); }
size_t GetAllVehicles(Vehicle* arrayOfVehicles, size_t size) { return GetAllVehiclesF(arrayOfVehicles, size); }
size_t GetAllObjects(Object* arrayOfObjects, size_t size) { return GetAllObjectsF(arrayOfObjects, size); }

void NativeReset(){ return NativeResetF(); }
void NativePush(void* arg) { return NativePushF(arg); }
void* NativeCall(UINT64 FunctionAddress) { return NativeCallF(FunctionAddress); }
std::mutex& GetCallMutex() { return GetCallMutexF(); }

bool InitNativeCaller()
{
	HMODULE hModule = GetModuleHandleA("GameCommandTerminal2.dll");

    if (!hModule) {
        std::cerr << "The GameCommandTerminal2.dll library was not founded. The GameCommandTerminal2.dll library is required for this script to work." << "\n";
        return false;
    }

    // Getting addresses of functions
    HashStringF = (_HashString)GetProcAddress(hModule, "HashString");
    if (!HashStringF) {
        std::cerr << "Failed to get the address of the function HashString\n";
        return false;
    }

    FindFunctionAddressF = (_FindFunctionAddress)GetProcAddress(hModule, "FindFunctionAddress");
    if (!FindFunctionAddressF) {
        std::cerr << "Failed to get the address of the function FindFunctionAddress\n";
        return false;
    }

    GetVectorF = (_GetVector)GetProcAddress(hModule, "GetVector");
    if (!GetVectorF) {
        std::cerr << "Failed to get the address of the function GetVector\n";
        return false;
    }

    DeleteVectorF = (_DeleteVector)GetProcAddress(hModule, "DeleteVector");
    if (!DeleteVectorF) {
        std::cerr << "Failed to get the address of the function DeleteVector\n";
        return false;
    }

    ToFloatF = (_ToFloat)GetProcAddress(hModule, "ToFloat");
    if (!ToFloatF) {
        std::cerr << "Failed to get the address of the function ToFloat\n";
        return false;
    }

    Call_PLAYER_PED_IDF = (_Call_PLAYER_PED_ID)GetProcAddress(hModule, "Call_PLAYER_PED_ID");
    if (!Call_PLAYER_PED_IDF) {
        std::cerr << "Failed to get the address of the function Call_PLAYER_PED_ID\n";
        return false;
    }

    GetEntityStructF = (_GetEntityStruct)GetProcAddress(hModule, "GetEntityStruct");
    if (!GetEntityStructF) {
        std::cerr << "Failed to get the address of the function GetEntityStruct\n";
        return false;
    }

    GetAllEntitiesF = (_GetAllEntities)GetProcAddress(hModule, "GetAllEntities");
    if (!GetAllEntitiesF) {
        std::cerr << "Failed to get the address of the function GetAllEntities\n";
        return false;
    }

    GetAllPedsF = (_GetAllPeds)GetProcAddress(hModule, "GetAllPeds");
    if (!GetAllPedsF) {
        std::cerr << "Failed to get the address of the function GetAllPeds\n";
        return false;
    }

    GetAllVehiclesF = (_GetAllVehicles)GetProcAddress(hModule, "GetAllVehicles");
    if (!GetAllVehiclesF) {
        std::cerr << "Failed to get the address of the function GetAllVehicles\n";
        return false;
    }

    GetAllObjectsF = (_GetAllObjects)GetProcAddress(hModule, "GetAllObjects");
    if (!GetAllObjectsF) {
        std::cerr << "Failed to get the address of the function GetAllObjects\n";
        return false;
    }

    NativeResetF = (_NativeReset)GetProcAddress(hModule, "NativeReset");
    if (!NativeResetF) {
        std::cerr << "Failed to get the address of the function NativeReset\n";
        return false;
    }

    NativePushF = (_NativePush)GetProcAddress(hModule, "NativePush");
    if (!NativePushF) {
        std::cerr << "Failed to get the address of the function NativePush\n";
        return false;
    }

    NativeCallF = (_NativeCall)GetProcAddress(hModule, "NativeCall");
    if (!NativeCallF) {
        std::cerr << "Failed to get the address of the function NativeCall\n";
        return false;
    }

    GetCallMutexF = (_GetCallMutex)GetProcAddress(hModule, "GetCallMutex");
    if (!GetCallMutexF) {
        std::cerr << "Failed to get the address of the function GetCallMutex\n";
        return false;
    }

	return true;
}