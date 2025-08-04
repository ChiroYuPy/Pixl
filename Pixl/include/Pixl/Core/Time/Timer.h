//
// Created by ChiroYuki on 04/08/2025.
//

#ifndef PIXLENGINE_TIMER_H
#define PIXLENGINE_TIMER_H

#include "Time.h"

namespace Pixl {

    class Timer {
    public:
        explicit Timer(Time duration) : m_remaining(duration), m_running(true) {}

        void update(Time deltaTime);

        bool isDone() const;
        void restart(Time newDuration);
        void stop();
        Time remaining() const;

    private:
        Time m_remaining;
        bool m_running;
    };

}

#endif //PIXLENGINE_TIMER_H
