#include <string>
#include "dllmain.h"
#include "Functions.h"
#include "Errors.h"
#include "Console.hpp"
#include "Graphics++.hpp"
#include "Network.h"

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        if (InitNativeCaller() && InitFunctions()) _beginthread((_beginthread_proc_type)ScriptMain, 0, hModule);
        DisableThreadLibraryCalls(hModule);

        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        UnloadScript(hModule);
        break;
    }
    return TRUE;
}

void ScriptMain(HMODULE hModule)
{
    Console::PrintColoured(DARK_AQUA, "Player ID: " + std::to_string(PLAYER::PLAYER_ID()));
    Console::PrintColoured(DARK_AQUA, "Player Name: " + std::string(PLAYER::GET_PLAYER_NAME_f(PLAYER::PLAYER_ID())));
    Console::PrintColoured(DARK_AQUA, "Player Ped ID: " + std::to_string(PLAYER::PLAYER_PED_ID()));

    UnloadScript(hModule);
}

void UnloadScript(HMODULE hModule)
{
    FreeLibraryAndExitThread(hModule, 0);
}