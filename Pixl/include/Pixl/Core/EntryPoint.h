//
// Created by ChiroYuki on 26/07/2025.
//

#ifndef PIXLENGINE_ENTRYPOINT_H
#define PIXLENGINE_ENTRYPOINT_H

#include "Application.h"
#ifdef _WIN32
#include <windows.h>
#endif

namespace PlatformCompatibility {
    void EnableVirtualTerminalProcessing() {
#ifdef _WIN32
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hOut == INVALID_HANDLE_VALUE) return;

        DWORD dwMode = 0;
        if (!GetConsoleMode(hOut, &dwMode)) return;

        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hOut, dwMode);
#endif
    }
}

extern Pixl::Application* Pixl::createApplication();

int main() {
    PlatformCompatibility::EnableVirtualTerminalProcessing();

    auto app = Pixl::createApplication();
    app->run();
    delete app;
}

#endif //PIXLENGINE_ENTRYPOINT_H
