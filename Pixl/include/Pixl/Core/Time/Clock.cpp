//
// Created by ChiroYuki on 04/08/2025.
//

#include "Clock.h"

namespace Pixl {

    Time Clock::getElapsedTime() const noexcept
    {
        auto now   = ClockImpl::now();
        auto delta = std::chrono::duration_cast<std::chrono::microseconds>(now - _start);
        return Time(delta.count());
    }

    Time Clock::restart() noexcept
    {
        auto now   = ClockImpl::now();
        auto delta = std::chrono::duration_cast<std::chrono::microseconds>(now - _start);
        _start = now;
        return Time(delta.count());
    }

}