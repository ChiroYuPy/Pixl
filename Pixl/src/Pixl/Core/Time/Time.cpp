//
// Created by ChiroYuki on 04/08/2025.
//

#include "Pixl/Core/Time/Time.h"

namespace Pixl {
    Time Time::Zero() { return Time(0); }

    Time Time::Seconds(float amount) { return Time(static_cast<TimeUnit>(amount * 1000000)); }
    Time Time::Milliseconds(Time::TimeUnit amount) { return Time(amount * 1000); }
    Time Time::Microseconds(Time::TimeUnit amount) { return Time(amount); }

    float Time::asSeconds() const { return m_microseconds / 1000000.f; }
    Time::TimeUnit Time::asMilliseconds() const { return m_microseconds / 1000; }
    Time::TimeUnit Time::asMicroseconds() const { return m_microseconds; }

    Time Time::operator+(const Time &right) const { return Time(m_microseconds + right.m_microseconds); }
    Time Time::operator-(const Time &right) const { return Time(m_microseconds - right.m_microseconds); }
    Time Time::operator*(float scalar) const { return Time(static_cast<TimeUnit>(m_microseconds * scalar)); }
    Time Time::operator/(float scalar) const { return Time(static_cast<TimeUnit>(m_microseconds / scalar)); }

    Time &Time::operator+=(const Time &right) { m_microseconds += right.m_microseconds; return *this; }
    Time &Time::operator-=(const Time &right) { m_microseconds -= right.m_microseconds; return *this; }
    Time &Time::operator*=(float scalar) { m_microseconds = static_cast<TimeUnit>(m_microseconds * scalar); return *this; }
    Time &Time::operator/=(float scalar) { m_microseconds = static_cast<TimeUnit>(m_microseconds / scalar); return *this; }

    bool Time::operator==(const Time &right) const { return m_microseconds == right.m_microseconds; }
    bool Time::operator!=(const Time &right) const { return m_microseconds != right.m_microseconds; }
    bool Time::operator<(const Time &right) const { return m_microseconds <  right.m_microseconds; }
    bool Time::operator<=(const Time &right) const { return m_microseconds <= right.m_microseconds; }
    bool Time::operator>(const Time &right) const { return m_microseconds >  right.m_microseconds; }
    bool Time::operator>=(const Time &right) const { return m_microseconds >= right.m_microseconds; }
}