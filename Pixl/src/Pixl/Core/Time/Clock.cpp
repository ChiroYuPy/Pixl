//
// Created by ChiroYuki on 04/08/2025.
//

#include "Pixl/Core/Time/Clock.h"

namespace Pixl {

    Time Clock::getElapsedTime() const {
        auto now = std::chrono::steady_clock::now();
        auto diff = std::chrono::duration_cast<std::chrono::microseconds>(now - m_start).count();
        return Time::Microseconds(diff);
    }

    Time Clock::restart() {
        auto now = std::chrono::steady_clock::now();
        auto diff = std::chrono::duration_cast<std::chrono::microseconds>(now - m_start).count();
        m_start = now;
        return Time::Microseconds(diff);
    }

}