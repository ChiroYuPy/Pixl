//
// Created by ChiroYuki on 04/08/2025.
//

#ifndef PIXLENGINE_CLOCK_H
#define PIXLENGINE_CLOCK_H

#include <chrono>
#include "Time.h"

namespace Pixl {

    class Clock {
    public:
        Clock() : m_start(std::chrono::steady_clock::now()) {}

        Time getElapsedTime() const;
        Time restart();

    private:
        std::chrono::steady_clock::time_point m_start;
    };

}

#endif //PIXLENGINE_CLOCK_H
