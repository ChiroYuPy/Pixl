//
// Created by ChiroYuki on 04/08/2025.
//

#ifndef PIXLENGINE_SCHEDULER_H
#define PIXLENGINE_SCHEDULER_H

#include "Pixl/Core/Time/Time.h"
#include "Pixl/Core/Time/Timer.h"

#include <vector>
#include <functional>
#include <algorithm>

namespace Pixl {

    class Scheduler {
    public:
        using Handle = std::uint64_t;

        Handle scheduleOnce(Time delay, std::function<void()> fn);
        Handle scheduleRepeating(Time interval, std::function<void()> fn);

        void update(Time deltaTime);
        bool cancel(Handle handle);

    private:
        struct Task {
            Handle handle;
            Time interval;
            std::function<void()> fn;
            bool repeating;
            Timer timer;

            Task(Handle h, Time i, std::function<void()> f, bool r)
            : handle(h), interval(i), fn(std::move(f)), repeating(r), timer(i) {}
        };

        std::vector<Task> m_tasks;
        Handle m_nextHandle = 1;
    };

}

#endif //PIXLENGINE_SCHEDULER_H
