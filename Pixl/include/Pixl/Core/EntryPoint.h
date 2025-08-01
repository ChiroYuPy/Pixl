//
// Created by ChiroYuki on 26/07/2025.
//

#ifndef PIXLENGINE_ENTRYPOINT_H
#define PIXLENGINE_ENTRYPOINT_H

#include "Application.h"

extern Pixl::Application* Pixl::CreateApplication();

int main()
{
    auto app = Pixl::CreateApplication();
    app->Run();
    delete app;
}

#endif //PIXLENGINE_ENTRYPOINT_H
