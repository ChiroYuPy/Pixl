//
// Created by ChiroYuki on 04/08/2025.
//

#include "Pixl/Core/Time/Scheduler.h"

namespace Pixl {

    Scheduler::Handle Scheduler::scheduleOnce(Time delay, std::function<void()> fn) {
        Handle h = m_nextHandle++;
        m_tasks.emplace_back(h, delay, std::move(fn), false);
        return h;
    }

    Scheduler::Handle Scheduler::scheduleRepeating(Time interval, std::function<void()> fn) {
        Handle h = m_nextHandle++;
        m_tasks.emplace_back(h, interval, std::move(fn), true);
        return h;
    }

    void Scheduler::update(Time deltaTime) {
        for (auto& task : m_tasks) {
            task.timer.update(deltaTime);
        }

        for (auto& task : m_tasks) {
            if (task.timer.isDone()) {
                task.fn();
                if (task.repeating) {
                    task.timer.restart(task.interval);
                }
            }
        }

        std::erase_if(m_tasks, [](const Task& t) {
            return !t.repeating && t.timer.isDone();
        });
    }

    bool Scheduler::cancel(Handle handle) {
        auto it = std::remove_if(m_tasks.begin(), m_tasks.end(),
                                 [handle](const Task& t) { return t.handle == handle; });
        bool removed = (it != m_tasks.end());
        m_tasks.erase(it, m_tasks.end());
        return removed;
    }

}