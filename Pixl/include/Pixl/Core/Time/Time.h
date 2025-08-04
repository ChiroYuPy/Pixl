//
// Created by ChiroYuki on 04/08/2025.
//

#ifndef PIXLENGINE_TIME_H
#define PIXLENGINE_TIME_H

#include <cstdint>

namespace Pixl {

    class Time {
    public:

        static Time Zero();

        static Time Seconds(float amount);
        static Time Milliseconds(int32_t amount);
        static Time Microseconds(int64_t amount);

        float asSeconds() const;
        int32_t asMilliseconds() const;
        int64_t asMicroseconds() const;

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
        explicit Time( int64_t microseconds) : m_microseconds(microseconds) {}

        int64_t m_microseconds;
    };

}

#endif //PIXLENGINE_TIME_H
