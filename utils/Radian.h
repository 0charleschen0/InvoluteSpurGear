//
// Created by USER on 2018/3/10.
//
#ifndef GEARDEMO_C_ANGLEUTILS_H
#define GEARDEMO_C_ANGLEUTILS_H

#define _MATH_DEFINES_DEFINED
#include <cmath>
#include <map>
#include <string>
#include <limits>
#include <vector>

#ifndef MINGW
#define M_PI       3.14159265358979323846   // pi
#endif // !MINGW

class Radian {
public:
    explicit Radian(double t_angle)
            : m_angle(t_angle),
              m_radian(toRadian(t_angle)) {}

    const double getRadian() const {
        return m_radian;
    }

    const double getDegree() const {
        return m_angle;
    }

private:
    const double m_angle;
    const double m_radian;

    inline static double toRadian(double degree) {
        return degree*M_PI/180.0;
    }
};

inline static double sin(Radian angle) {
    return std::sin(angle.getRadian());
}

inline static double cos(Radian angle) {
    return std::cos(angle.getRadian());
}

inline static double tan(Radian angle) {
    return std::tan(angle.getRadian());
}

#endif //GEARDEMO_C_ANGLEUTILS_H
