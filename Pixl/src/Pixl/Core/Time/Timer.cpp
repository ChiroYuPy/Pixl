//
// Created by ChiroYuki on 04/08/2025.
//

#include "Pixl/Core/Time/Timer.h"

namespace Pixl {

    void Timer::update(Time deltaTime) {
        if (m_running && m_remaining > Time::Zero()) {
            m_remaining -= deltaTime;
            if (m_remaining < Time::Zero()) m_remaining = Time::Zero();
        }
    }

    bool Timer::isDone() const { return m_remaining == Time::Zero(); }
    void Timer::restart(Time newDuration) { m_remaining = newDuration; m_running = true; }
    void Timer::stop() { m_running = false; }
    Time Timer::remaining() const { return m_remaining; }
}