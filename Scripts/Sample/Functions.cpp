#include <Windows.h>
#include "Functions.h"

typedef int(__cdecl* _GetGCTVersion)();
_GetGCTVersion GetGCTVersionF;
typedef const char*(__cdecl* _GetGCTStringVersion)();
_GetGCTStringVersion GetGCTStringVersionF;
typedef int64_t(__cdecl* _ConvertStringToKeyCode)(char* Key);
_ConvertStringToKeyCode ConvertStringToKeyCodeF;
typedef bool(__cdecl* _IsPressedKey)(int64_t Key);
_IsPressedKey IsPressedKeyF;
typedef bool(__cdecl* _IsScriptsStillWorking)();
_IsScriptsStillWorking IsScriptsStillWorkingF;
typedef bool(__cdecl* _RestartScripts)();
_RestartScripts RestartScriptsF;
typedef void(__cdecl* _GCTDisplayError)(const std::string& message);
_GCTDisplayError GCTDisplayErrorF;
typedef std::mutex& (__cdecl* _GetConsoleMutex)();
_GetConsoleMutex GetConsoleMutexF;
typedef bool(__cdecl* _RegisterGlobalVariableNumber)(const std::string& name, INT64 value);
_RegisterGlobalVariableNumber RegisterGlobalVariableNumberF;
typedef bool(__cdecl* _RegisterGlobalVariableDouble)(const std::string& name, double value);
_RegisterGlobalVariableDouble RegisterGlobalVariableDoubleF;
typedef bool(__cdecl* _RegisterGlobalVariableString)(const std::string& name, std::string value);
_RegisterGlobalVariableString RegisterGlobalVariableStringF;
typedef bool(__cdecl* _RegisterGlobalVariableVectorOfNumbers)(const std::string& name, const std::vector<INT64> value);
_RegisterGlobalVariableVectorOfNumbers RegisterGlobalVariableVectorOfNumbersF;
typedef bool(__cdecl* _RegisterGlobalVariableVectorOfDoubles)(const std::string& name, const std::vector<double> value);
_RegisterGlobalVariableVectorOfDoubles RegisterGlobalVariableVectorOfDoublesF;
typedef bool(__cdecl* _RegisterGlobalVariableVectorOfStrings)(const std::string& name, const std::vector<std::string> value);
_RegisterGlobalVariableVectorOfStrings RegisterGlobalVariableVectorOfStringsF;
typedef INT64(__cdecl* _GetGlobalVariableAsNumber)(const std::string& name);
_GetGlobalVariableAsNumber GetGlobalVariableAsNumberF;
typedef double(__cdecl* _GetGlobalVariableAsDouble)(const std::string& name);
_GetGlobalVariableAsDouble GetGlobalVariableAsDoubleF;
typedef std::string(__cdecl* _GetGlobalVariableAsString)(const std::string& name);
_GetGlobalVariableAsString GetGlobalVariableAsStringF;
typedef std::vector<INT64>(__cdecl* _GetGlobalVariableAsVectorOfNumbers)(const std::string& name);
_GetGlobalVariableAsVectorOfNumbers GetGlobalVariableAsVectorOfNumbersF;
typedef std::vector<double>(__cdecl* _GetGlobalVariableAsVectorOfDoubles)(const std::string& name);
_GetGlobalVariableAsVectorOfDoubles GetGlobalVariableAsVectorOfDoublesF;
typedef std::vector<std::string>(__cdecl* _GetGlobalVariableAsVectorOfStrings)(const std::string& name);
_GetGlobalVariableAsVectorOfStrings GetGlobalVariableAsVectorOfStringsF;
typedef void(__cdecl* _SetGlobalVariableValueNumber)(const std::string& name, INT64 value);
_SetGlobalVariableValueNumber SetGlobalVariableValueNumberF;
typedef void(__cdecl* _SetGlobalVariableValueDouble)(const std::string& name, double value);
_SetGlobalVariableValueDouble SetGlobalVariableValueDoubleF;
typedef void(__cdecl* _SetGlobalVariableValueString)(const std::string& name, std::string value);
_SetGlobalVariableValueString SetGlobalVariableValueStringF;
typedef void(__cdecl* _SetGlobalVariableValueVectorOfNumbers)(const std::string& name, std::vector<INT64> value);
_SetGlobalVariableValueVectorOfNumbers SetGlobalVariableValueVectorOfNumbersF;
typedef void(__cdecl* _SetGlobalVariableValueVectorOfDoubles)(const std::string& name, std::vector<double> value);
_SetGlobalVariableValueVectorOfDoubles SetGlobalVariableValueVectorOfDoublesF;
typedef void(__cdecl* _SetGlobalVariableValueVectorOfStrings)(const std::string& name, std::vector<std::string> value);
_SetGlobalVariableValueVectorOfStrings SetGlobalVariableValueVectorOfStringsF;
typedef GlobalVariableType(__cdecl* __GetGlobalVariableType)(const std::string& name);
__GetGlobalVariableType _GetGlobalVariableTypeF;
typedef bool(__cdecl* __IsGlobalVariableExist)(const std::string& name);
__IsGlobalVariableExist _IsGlobalVariableExistF;
typedef void(__cdecl* __ClearGlobalVariablesStore)();
__ClearGlobalVariablesStore _ClearGlobalVariablesStoreF;
typedef bool(__cdecl* _BindCommand)(const char* Command, CommandCallBack callback);
_BindCommand BindCommandF;
typedef bool(__cdecl* _UnBindCommand)(const char* Command);
_UnBindCommand UnBindCommandF;
typedef bool(__cdecl* _IsCommandExist)(const char* Command);
_IsCommandExist IsCommandExistF;


/* GCT Functions */

int GetGCTVersion() { return GetGCTVersionF(); }
const char* GetGCTStringVersion() { return GetGCTStringVersionF(); }
int64_t ConvertStringToKeyCode(char* Key) { return ConvertStringToKeyCodeF(Key); }
bool IsPressedKey(int64_t Key) { return IsPressedKeyF(Key); }
bool IsScriptsStillWorking() { return IsScriptsStillWorkingF(); }
bool RestartScripts() { return RestartScriptsF(); }
void GCTDisplayError(const std::string& message) { return GCTDisplayErrorF(message); }


/* Communication */

bool RegisterGlobalVariable(const std::string& name, INT64 value) { return RegisterGlobalVariableNumberF(name, value); }
bool RegisterGlobalVariable(const std::string& name, double value) { return RegisterGlobalVariableDoubleF(name, value); }
bool RegisterGlobalVariable(const std::string& name, std::string value) { return RegisterGlobalVariableStringF(name, value); }
bool RegisterGlobalVariable(const std::string& name, std::vector<INT64> value) { return RegisterGlobalVariableVectorOfNumbersF(name, value); }
bool RegisterGlobalVariable(const std::string& name, std::vector<double> value) { return RegisterGlobalVariableVectorOfDoublesF(name, value); }
bool RegisterGlobalVariable(const std::string& name, std::vector<std::string> value) { return RegisterGlobalVariableVectorOfStringsF(name, value); }

GlobalVariableType GetGlobalVariableType(const std::string& name) { return _GetGlobalVariableTypeF(name); }

INT64 GetGlobalVariableAsNumber(const std::string& name) { return GetGlobalVariableAsNumberF(name); }
double GetGlobalVariableAsDouble(const std::string& name) { return GetGlobalVariableAsDoubleF(name); }
std::string GetGlobalVariableAsString(const std::string& name) { return GetGlobalVariableAsStringF(name); }
std::vector<INT64> GetGlobalVariableAsVectorOfNumbers(const std::string& name) { return GetGlobalVariableAsVectorOfNumbersF(name); }
std::vector<double> GetGlobalVariableAsVectorOfDoubles(const std::string& name) { return GetGlobalVariableAsVectorOfDoublesF(name); }
std::vector<std::string> GetGlobalVariableAsVectorOfStrings(const std::string& name) { return GetGlobalVariableAsVectorOfStringsF(name); }

void SetGlobalVariableValue(const std::string& name, INT64 value) { SetGlobalVariableValueNumberF(name, value); }
void SetGlobalVariableValue(const std::string& name, double value) { SetGlobalVariableValueDoubleF(name, value); }
void SetGlobalVariableValue(const std::string& name, std::string value) { SetGlobalVariableValueStringF(name, value); }
void SetGlobalVariableValue(const std::string& name, std::vector<INT64> value) { SetGlobalVariableValueVectorOfNumbersF(name, value); }
void SetGlobalVariableValue(const std::string& name, std::vector<double> value) { SetGlobalVariableValueVectorOfDoublesF(name, value); }
void SetGlobalVariableValue(const std::string& name, std::vector<std::string> value) { SetGlobalVariableValueVectorOfStringsF(name, value); }

bool IsGlobalVariableExist(const std::string& name) { return _IsGlobalVariableExistF(name);}

void ClearGlobalVariablesStore() { _ClearGlobalVariablesStoreF(); }


/* Terminal */

std::mutex& GetConsoleMutex() { return GetConsoleMutexF(); }
bool BindCommand(const char* Command, CommandCallBack callback) { return BindCommandF(Command, callback); }
bool UnBindCommand(const char* Command) { return UnBindCommandF(Command); }
bool IsCommandExist(const char* Command) { return IsCommandExistF(Command); }


bool InitFunctions()
{
    HMODULE hModule = GetModuleHandleA("GameCommandTerminal2.dll");

    if (!hModule) {
        std::cerr << "The GameCommandTerminal2.dll library was not founded. The GameCommandTerminal2.dll library is required for this script to work." << "\n";
        return false;
    }

    // Getting addresses of functions
    GetGCTVersionF = (_GetGCTVersion)GetProcAddress(hModule, "GetGCTVersion");
    if (!GetGCTVersionF) { std::cerr << "Failed to get the address of the GetGCTVersion function\n"; return false; }

    GetGCTStringVersionF = (_GetGCTStringVersion)GetProcAddress(hModule, "GetGCTStringVersion");
    if (!GetGCTStringVersionF) { std::cerr << "Failed to get the address of the GetGCTStringVersion function\n"; return false; }

    ConvertStringToKeyCodeF = (_ConvertStringToKeyCode)GetProcAddress(hModule, "ConvertStringToKeyCodeF");
    if (!ConvertStringToKeyCodeF) { std::cerr << "Failed to get the address of the ConvertStringToKeyCodeF function\n"; return false; }

    IsPressedKeyF = (_IsPressedKey)GetProcAddress(hModule, "IsPressedKey");
    if (!IsPressedKeyF) { std::cerr << "Failed to get the address of the IsPressedKey function\n"; return false; }

    IsScriptsStillWorkingF = (_IsScriptsStillWorking)GetProcAddress(hModule, "IsScriptsStillWorking");
    if (!IsScriptsStillWorkingF) { std::cerr << "Failed to get the address of the IsScriptsStillWorking function\n"; return false; }

    RestartScriptsF = (_RestartScripts)GetProcAddress(hModule, "RestartScripts");
    if (!RestartScriptsF) { std::cerr << "Failed to get the address of the RestartScripts function\n"; return false; }

    GCTDisplayErrorF = (_GCTDisplayError)GetProcAddress(hModule, "GCTDisplayError");
    if (!GCTDisplayErrorF) { std::cerr << "Failed to get the address of the GCTDisplayError function\n"; return false; }

    GetConsoleMutexF = (_GetConsoleMutex)GetProcAddress(hModule, "GetConsoleMutex");
    if (!GetConsoleMutexF) { std::cerr << "Failed to get the address of the GetConsoleMutex function\n"; return false; }

    BindCommandF = (_BindCommand)GetProcAddress(hModule, "BindCommand");
    if (!BindCommandF) { std::cerr << "Failed to get the address of the BindCommand function\n"; return false; }

    UnBindCommandF = (_UnBindCommand)GetProcAddress(hModule, "UnBindCommand");
    if (!UnBindCommandF) { std::cerr << "Failed to get the address of the UnBindCommand function\n"; return false; }

    IsCommandExistF = (_IsCommandExist)GetProcAddress(hModule, "IsCommandExist");
    if (!IsCommandExistF) { std::cerr << "Failed to get the address of the IsCommandExist function\n"; return false; }

    RegisterGlobalVariableNumberF = (_RegisterGlobalVariableNumber)GetProcAddress(hModule, "RegisterGlobalVariableNumber");
    if (!RegisterGlobalVariableNumberF) { std::cerr << "Failed to get the address of the RegisterGlobalVariableNumber function\n"; return false; }

    RegisterGlobalVariableDoubleF = (_RegisterGlobalVariableDouble)GetProcAddress(hModule, "RegisterGlobalVariableDouble");
    if (!RegisterGlobalVariableDoubleF) { std::cerr << "Failed to get the address of the RegisterGlobalVariableDouble function\n"; return false; }

    RegisterGlobalVariableStringF = (_RegisterGlobalVariableString)GetProcAddress(hModule, "RegisterGlobalVariableString");
    if (!RegisterGlobalVariableStringF) { std::cerr << "Failed to get the address of the RegisterGlobalVariableString function\n"; return false; }

    RegisterGlobalVariableVectorOfNumbersF = (_RegisterGlobalVariableVectorOfNumbers)GetProcAddress(hModule, "RegisterGlobalVariableVectorOfNumbers");
    if (!RegisterGlobalVariableVectorOfNumbersF) { std::cerr << "Failed to get the address of the RegisterGlobalVariableVectorOfNumbers function\n"; return false; }

    RegisterGlobalVariableVectorOfDoublesF = (_RegisterGlobalVariableVectorOfDoubles)GetProcAddress(hModule, "RegisterGlobalVariableVectorOfDoubles");
    if (!RegisterGlobalVariableVectorOfDoublesF) { std::cerr << "Failed to get the address of the RegisterGlobalVariableVectorOfDoubles function\n"; return false; }

    RegisterGlobalVariableVectorOfStringsF = (_RegisterGlobalVariableVectorOfStrings)GetProcAddress(hModule, "RegisterGlobalVariableVectorOfStrings");
    if (!RegisterGlobalVariableVectorOfStringsF) { std::cerr << "Failed to get the address of the RegisterGlobalVariableVectorOfStrings function\n"; return false; }

    GetGlobalVariableAsNumberF = (_GetGlobalVariableAsNumber)GetProcAddress(hModule, "GetGlobalVariableAsNumber");
    if (!GetGlobalVariableAsNumberF) { std::cerr << "Failed to get the address of the GetGlobalVariableAsNumber function\n"; return false; }

    GetGlobalVariableAsDoubleF = (_GetGlobalVariableAsDouble)GetProcAddress(hModule, "GetGlobalVariableAsDouble");
    if (!GetGlobalVariableAsDoubleF) { std::cerr << "Failed to get the address of the GetGlobalVariableAsDouble function\n"; return false; }

    GetGlobalVariableAsStringF = (_GetGlobalVariableAsString)GetProcAddress(hModule, "GetGlobalVariableAsString");
    if (!GetGlobalVariableAsStringF) { std::cerr << "Failed to get the address of the GetGlobalVariableAsString function\n"; return false; }

    GetGlobalVariableAsVectorOfNumbersF = (_GetGlobalVariableAsVectorOfNumbers)GetProcAddress(hModule, "GetGlobalVariableAsVectorOfNumbers");
    if (!GetGlobalVariableAsVectorOfNumbersF) { std::cerr << "Failed to get the address of the GetGlobalVariableAsVectorOfNumbers function\n"; return false; }

    GetGlobalVariableAsVectorOfDoublesF = (_GetGlobalVariableAsVectorOfDoubles)GetProcAddress(hModule, "GetGlobalVariableAsVectorOfDoubles");
    if (!GetGlobalVariableAsVectorOfDoublesF) { std::cerr << "Failed to get the address of the GetGlobalVariableAsVectorOfDoubles function\n"; return false; }

    GetGlobalVariableAsVectorOfStringsF = (_GetGlobalVariableAsVectorOfStrings)GetProcAddress(hModule, "GetGlobalVariableAsVectorOfStrings");
    if (!GetGlobalVariableAsVectorOfStringsF) { std::cerr << "Failed to get the address of the GetGlobalVariableAsVectorOfStrings function\n"; return false; }

    SetGlobalVariableValueNumberF = (_SetGlobalVariableValueNumber)GetProcAddress(hModule, "SetGlobalVariableValueNumber");
    if (!SetGlobalVariableValueNumberF) { std::cerr << "Failed to get the address of the SetGlobalVariableValueNumber function\n"; return false; }

    SetGlobalVariableValueDoubleF = (_SetGlobalVariableValueDouble)GetProcAddress(hModule, "SetGlobalVariableValueDouble");
    if (!SetGlobalVariableValueDoubleF) { std::cerr << "Failed to get the address of the SetGlobalVariableValueDouble function\n"; return false; }

    SetGlobalVariableValueStringF = (_SetGlobalVariableValueString)GetProcAddress(hModule, "SetGlobalVariableValueString");
    if (!SetGlobalVariableValueStringF) { std::cerr << "Failed to get the address of the SetGlobalVariableValueString function\n"; return false; }

    SetGlobalVariableValueVectorOfNumbersF = (_SetGlobalVariableValueVectorOfNumbers)GetProcAddress(hModule, "SetGlobalVariableValueVectorOfNumbers");
    if (!SetGlobalVariableValueVectorOfNumbersF) { std::cerr << "Failed to get the address of the SetGlobalVariableValueVectorOfNumbers function\n"; return false; }

    SetGlobalVariableValueVectorOfDoublesF = (_SetGlobalVariableValueVectorOfDoubles)GetProcAddress(hModule, "SetGlobalVariableValueVectorOfDoubles");
    if (!SetGlobalVariableValueVectorOfDoublesF) { std::cerr << "Failed to get the address of the SetGlobalVariableValueVectorOfDoubles function\n"; return false; }

    SetGlobalVariableValueVectorOfStringsF = (_SetGlobalVariableValueVectorOfStrings)GetProcAddress(hModule, "SetGlobalVariableValueVectorOfStrings");
    if (!SetGlobalVariableValueVectorOfStringsF) { std::cerr << "Failed to get the address of the SetGlobalVariableValueVectorOfStrings function\n"; return false; }

    _GetGlobalVariableTypeF = (__GetGlobalVariableType)GetProcAddress(hModule, "_GetGlobalVariableType");
    if (!_GetGlobalVariableTypeF) { std::cerr << "Failed to get the address of the _GetGlobalVariableType function\n"; return false; }

    _IsGlobalVariableExistF = (__IsGlobalVariableExist)GetProcAddress(hModule, "_IsGlobalVariableExist");
    if (!_IsGlobalVariableExistF) { std::cerr << "Failed to get the address of the _IsGlobalVariableExist function\n"; return false; }

    _ClearGlobalVariablesStoreF = (__ClearGlobalVariablesStore)GetProcAddress(hModule, "_ClearGlobalVariablesStore");
    if (!_ClearGlobalVariablesStoreF) { std::cerr << "Failed to get the address of the _ClearGlobalVariablesStore function\n"; return false; }

    return true;
}