#pragma once
#include "NativeFunctions.h"

void DisplayErrorMessageScreen(const char* title, const char* message, int duration) {
    const void* struct1[2] = { MISC::CreateVarString(10, "LITERAL_STRING", "Critical Error"), MISC::CreateVarString(10, "LITERAL_STRING", message) };

    int msgID = UISTICKYFEED::_UI_STICKY_FEED_CREATE_ERROR_MESSAGE((Any*)struct1, 0, true);

    Sleep(duration);

    UISTICKYFEED::_UI_STICKY_FEED_CLEAR_MESSAGE(msgID);
}