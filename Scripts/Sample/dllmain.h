#pragma once

#include <iostream>
#include <Windows.h>

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved);

void ScriptMain(HMODULE hModule);

void UnloadScript(HMODULE hModule);