#pragma once
#include <string>
#include <Windows.h>
#include <sstream>


enum class MessageBoxState {
    ID_OK = 1,            // Button "OK"
    ID_CANCEL = 2,       // Button "Cancel"
    ID_ABORT = 3,        // Button "Abort"
    ID_RETRY = 4,        // Button "Retry"
    ID_IGNORE = 5,       // Button "Ignore"
    ID_YES = 6,          // Button "Yes"
    ID_NO = 7,           // Button "No"
    ID_HELP = 0x00004000 // Button "Help"
};

std::string GetPathFromPATH(const std::string & folderName);