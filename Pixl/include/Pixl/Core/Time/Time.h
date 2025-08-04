//
// Created by ChiroYuki on 04/08/2025.
//

#ifndef PIXLENGINE_TIME_H
#define PIXLENGINE_TIME_H

#include <cstdint>

namespace Pixl {

    class Time {
    public:
        using TimeUnit = std::int64_t;

        static Time Zero();

        static Time Seconds(float amount);
        static Time Milliseconds(TimeUnit amount);
        static Time Microseconds(TimeUnit amount);

        float asSeconds() const;
        TimeUnit asMilliseconds() const;
        TimeUnit asMicroseconds() const;

        Time operator+(const Time& right) const;
        Time operator-(const Time& right) const;
        Time operator*(float scalar) const;
        Time operator/(float scalar) const;

        Time& operator+=(const Time& right);
        Time& operator-=(const Time& right);
        Time& operator*=(float scalar);
        Time& operator/=(float scalar);

        bool operator==(const Time& right) const;
        bool operator!=(const Time& right) const;
        bool operator< (const Time& right) const;
        bool operator<=(const Time& right) const;
        bool operator> (const Time& right) const;
        bool operator>=(const Time& right) const;

    private:
        explicit Time(TimeUnit microseconds) : m_microseconds(microseconds) {}

        TimeUnit m_microseconds;
    };

}

#endif //PIXLENGINE_TIME_H
