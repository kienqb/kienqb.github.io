#pragma once

#include <cmath>
#include <cstdint>

// Solar -> Vietnamese lunar calendar (UTC+7), after Hồ Ngọc Đức's algorithm.
namespace waze_hud::lunar {

struct SolarDate { int year; int month; int day; };
struct LunarDate { int day; int month; int year; bool leap; };

namespace detail {

constexpr double kPi = 3.14159265358979323846;
constexpr double kTimeZone = 7.0;

inline int floorInt(double value) { return static_cast<int>(std::floor(value)); }

inline int julianDay(int day, int month, int year) {
    const int a = (14 - month) / 12;
    const int y = year + 4800 - a;
    const int m = month + 12 * a - 3;
    int jd = day + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045;
    if (jd < 2299161) jd = day + (153 * m + 2) / 5 + 365 * y + y / 4 - 32083;
    return jd;
}

inline double newMoon(int k) {
    const double T = k / 1236.85, T2 = T * T, T3 = T2 * T, dr = kPi / 180.0;
    double jd1 = 2415020.75933 + 29.53058868 * k + 0.0001178 * T2 - 0.000000155 * T3;
    jd1 += 0.00033 * std::sin((166.56 + 132.87 * T - 0.009173 * T2) * dr);
    const double M = 359.2242 + 29.10535608 * k - 0.0000333 * T2 - 0.00000347 * T3;
    const double Mpr = 306.0253 + 385.81691806 * k + 0.0107306 * T2 + 0.00001236 * T3;
    const double F = 21.2964 + 390.67050646 * k - 0.0016528 * T2 - 0.00000239 * T3;
    double c1 = (0.1734 - 0.000393 * T) * std::sin(M * dr) + 0.0021 * std::sin(2 * dr * M);
    c1 -= 0.4068 * std::sin(Mpr * dr) - 0.0161 * std::sin(dr * 2 * Mpr);
    c1 -= 0.0004 * std::sin(dr * 3 * Mpr);
    c1 += 0.0104 * std::sin(dr * 2 * F) - 0.0051 * std::sin(dr * (M + Mpr));
    c1 -= 0.0074 * std::sin(dr * (M - Mpr)) - 0.0004 * std::sin(dr * (2 * F + M));
    c1 -= 0.0004 * std::sin(dr * (2 * F - M)) + 0.0006 * std::sin(dr * (2 * F + Mpr));
    c1 += 0.0010 * std::sin(dr * (2 * F - Mpr)) + 0.0005 * std::sin(dr * (2 * Mpr + M));
    const double deltat = T < -11
        ? 0.001 + 0.000839 * T + 0.0002261 * T2 - 0.00000845 * T3 - 0.000000081 * T * T3
        : -0.000278 + 0.000265 * T + 0.000262 * T2;
    return jd1 + c1 - deltat;
}

inline double sunLongitude(double jdn) {
    const double T = (jdn - 2451545.0) / 36525.0, T2 = T * T, dr = kPi / 180.0;
    const double M = 357.52910 + 35999.05030 * T - 0.0001559 * T2 - 0.00000048 * T * T2;
    const double L0 = 280.46645 + 36000.76983 * T + 0.0003032 * T2;
    double dl = (1.914600 - 0.004817 * T - 0.000014 * T2) * std::sin(dr * M);
    dl += (0.019993 - 0.000101 * T) * std::sin(dr * 2 * M) + 0.000290 * std::sin(dr * 3 * M);
    double L = L0 + dl;
    const double omega = 125.04 - 1934.136 * T;
    L = L - 0.00569 - 0.00478 * std::sin(omega * dr);
    L *= dr;
    L -= kPi * 2 * std::floor(L / (kPi * 2));
    return L;
}

inline int sunLongitudeIndex(int dayNumber) {
    return floorInt(sunLongitude(dayNumber - 0.5 - kTimeZone / 24.0) / kPi * 6);
}

inline int newMoonDay(int k) { return floorInt(newMoon(k) + 0.5 + kTimeZone / 24.0); }

inline int lunarMonth11(int year) {
    const int off = julianDay(31, 12, year) - 2415021;
    const int k = floorInt(off / 29.530588853);
    int nm = newMoonDay(k);
    if (sunLongitudeIndex(nm) >= 9) nm = newMoonDay(k - 1);
    return nm;
}

inline int leapMonthOffset(int a11) {
    const int k = floorInt((a11 - 2415021.076998695) / 29.530588853 + 0.5);
    int last = 0, i = 1;
    int arc = sunLongitudeIndex(newMoonDay(k + i));
    do {
        last = arc;
        ++i;
        arc = sunLongitudeIndex(newMoonDay(k + i));
    } while (arc != last && i < 14);
    return i - 1;
}

}  // namespace detail

inline LunarDate solarToLunar(int day, int month, int year) {
    using namespace detail;
    const int dayNumber = julianDay(day, month, year);
    const int k = floorInt((dayNumber - 2415021.076998695) / 29.530588853);
    int monthStart = newMoonDay(k + 1);
    if (monthStart > dayNumber) monthStart = newMoonDay(k);
    int a11 = lunarMonth11(year);
    int b11 = a11;
    int lunarYear;
    if (a11 >= monthStart) {
        lunarYear = year;
        a11 = lunarMonth11(year - 1);
    } else {
        lunarYear = year + 1;
        b11 = lunarMonth11(year + 1);
    }
    const int lunarDay = dayNumber - monthStart + 1;
    const int diff = (monthStart - a11) / 29;
    bool leap = false;
    int lunarMonth = diff + 11;
    if (b11 - a11 > 365) {
        const int leapDiff = leapMonthOffset(a11);
        if (diff >= leapDiff) {
            lunarMonth = diff + 10;
            if (diff == leapDiff) leap = true;
        }
    }
    if (lunarMonth > 12) lunarMonth -= 12;
    if (lunarMonth >= 11 && diff < 4) lunarYear -= 1;
    return {lunarDay, lunarMonth, lunarYear, leap};
}

// Days since 1970-01-01 -> civil date (proleptic Gregorian).
inline SolarDate civilFromDays(int64_t days) {
    days += 719468;
    const int64_t era = (days >= 0 ? days : days - 146096) / 146097;
    const int64_t doe = days - era * 146097;
    const int64_t yoe = (doe - doe / 1460 + doe / 36524 - doe / 146096) / 365;
    const int64_t doy = doe - (365 * yoe + yoe / 4 - yoe / 100);
    const int64_t mp = (5 * doy + 2) / 153;
    const int day = static_cast<int>(doy - (153 * mp + 2) / 5 + 1);
    const int month = static_cast<int>(mp < 10 ? mp + 3 : mp - 9);
    const int year = static_cast<int>(yoe + era * 400 + (month <= 2 ? 1 : 0));
    return {year, month, day};
}

// 0 = Sunday ... 6 = Saturday.
inline int weekdayFromDays(int64_t days) {
    const int64_t value = (days + 4) % 7;
    return static_cast<int>(value < 0 ? value + 7 : value);
}

inline const char *canName(int lunarYear) {
    static const char *const names[] = {"Canh", "Tân", "Nhâm", "Quý", "Giáp",
                                        "Ất", "Bính", "Đinh", "Mậu", "Kỷ"};
    return names[((lunarYear % 10) + 10) % 10];
}

inline const char *chiName(int lunarYear) {
    static const char *const names[] = {"Thân", "Dậu", "Tuất", "Hợi", "Tý", "Sửu",
                                        "Dần", "Mão", "Thìn", "Tỵ", "Ngọ", "Mùi"};
    return names[((lunarYear % 12) + 12) % 12];
}

}  // namespace waze_hud::lunar
