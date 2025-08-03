//
// Created by ChiroYuki on 26/07/2025.
//

#ifndef PIXLENGINE_ENTRYPOINT_H
#define PIXLENGINE_ENTRYPOINT_H

#include "Application.h"

extern Pixl::Application* Pixl::createApplication();

int main()
{
    auto app = Pixl::createApplication();
    app->run();
    delete app;
}

#endif //PIXLENGINE_ENTRYPOINT_H
