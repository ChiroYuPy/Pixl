//
// Created by ChiroYuki on 08/08/2025.
//

#ifndef PIXLENGINE_SANDBOX_H
#define PIXLENGINE_SANDBOX_H

#include "Pixl/Pixl.h"
#include "Pixl/Core/EntryPoint.h"

class SandboxApp : public Pixl::Application {
public:
    explicit SandboxApp(const Pixl::ApplicationSpecification& specification);

    ~SandboxApp() override = default;
};

#endif //PIXLENGINE_SANDBOX_H
