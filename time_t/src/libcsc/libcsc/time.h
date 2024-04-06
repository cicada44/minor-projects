#pragma once

#include <iostream>
#include <limits>
#include <tuple>

namespace time_utils {

using ulli = unsigned long long int;
using time_view = std::tuple<ulli, ulli, ulli, ulli>;

namespace {

constexpr inline ulli SecsInDay = 86400;
constexpr inline ulli SecsInHour = 3600;
constexpr inline ulli SecsInMinute = 60;

constexpr inline auto nan = std::numeric_limits<unsigned long long int>::quiet_NaN();

ulli to_secs(const ulli d, const ulli h, const ulli m, const ulli s) {
    return d * SecsInDay + h * SecsInHour + m * SecsInMinute + s;
}

}  // namespace

struct TimeSpan {
    TimeSpan(const ulli secs) : s_(secs) {}

    ulli s_;

    TimeSpan operator+(const TimeSpan& ts) const { return (ts.s_ + s_); }

    TimeSpan operator-(const TimeSpan& ts) const {
        return (ts.s_ > s_) ? nan : s_ - ts.s_;
    }
};

class Time {
public:
    Time(const ulli d = 0, const ulli h = 0, const ulli m = 0, const ulli s = 0)
        : d_(d), h_(h), m_(m), s_(s) {
        m_ += s_ / 60;
        s_ = s_ % 60;
        h_ += m_ / 60;
        m_ = m_ % 60;
        d_ += h_ / 24;
        h_ = h_ % 24;
    }

    TimeSpan operator-(const Time& ts) const {
        if (to_secs(d_, h_, m_, s_) < to_secs(ts.d_, ts.h_, ts.m_, ts.s_))
            return nan;
        else
            return to_secs(d_ - ts.d_, h_ - ts.h_, m_ - ts.m_, s_ - ts.s_);
    }

    Time operator+(const TimeSpan& ts) const { return Time{d_, h_, m_, s_ + ts.s_}; }

    Time operator-(const TimeSpan& ts) const {
        const ulli secs = to_secs(d_, h_, m_, s_);
        if (secs >= ts.s_)
            return Time{0, 0, 0, secs - ts.s_};
        else
            return Time{nan, nan, nan, nan};
    }

    auto operator<=>(const Time& t) const {
        return to_secs(d_, h_, m_, s_) <=> to_secs(t.d_, t.h_, t.m_, t.s_);
    }

    time_view get_time() const { return {d_, h_, m_, s_}; }

private:
    ulli d_, h_, m_, s_;
};

std::ostream& operator<<(std::ostream& os, const Time& t) {
    ulli d, h, m, s;
    std::tie(d, h, m, s) = t.get_time();
    os << d << "d " << h << "h " << m << "m " << s << "s'";
    return os;
}

namespace literals {

inline Time operator"" _d(const ulli days) { return Time{days, 0, 0, 0}; }
inline Time operator"" _h(const ulli hours) { return Time{0, hours, 0, 0}; }
inline Time operator"" _m(const ulli minutes) { return Time{0, 0, minutes, 0}; }
inline Time operator"" _s(const ulli seconds) { return Time{0, 0, 0, seconds}; }
inline TimeSpan operator"" _ss(const ulli seconds) { return TimeSpan{seconds}; }
inline TimeSpan operator"" _sd(const ulli days) { return TimeSpan{days * SecsInDay}; }
inline TimeSpan operator"" _sh(const ulli hours) { return TimeSpan{hours * SecsInHour}; }
inline TimeSpan operator"" _sm(const ulli minutes) {
    return TimeSpan{minutes * SecsInMinute};
}

}  // namespace literals

}  // namespace time_utils
