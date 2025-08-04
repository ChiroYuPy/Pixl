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
        Clock() noexcept { restart(); }

        Time getElapsedTime() const noexcept;

        Time restart() noexcept;

    private:
        using ClockImpl = std::chrono::steady_clock;
        std::chrono::time_point<ClockImpl> _start;
    };

}

#endif //PIXLENGINE_CLOCK_H
