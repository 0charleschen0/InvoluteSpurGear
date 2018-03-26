//
// Created by USER on 2018/3/13.
//
#include "AngleUtils.h"

AngleUtils::AngleUtils() {
    this->radian = Radian();
    this->degree = Degree();
}

AngleUtils::AngleUtils(Degree degree, Radian radian) {
    this->radian = radian;
    this->degree = degree;
}

void AngleUtils::setDegree(double degree) {
    this->degree.set(degree);
    this->radian.set(toRadian(degree));
}

void AngleUtils::setRadian(double radian) {
    this->degree.set(toDegree(radian));
    this->radian.set(radian);
}

double AngleUtils::sin() {
//    if (isnan(cache.getSinValue())) {
//        cache.setSinValue(std::sin(radian.get()));
//    }
    return std::sin(radian.get());
}

double AngleUtils::cos() {
    return std::cos(radian.get());
}

double AngleUtils::tan() {
    return std::tan(radian.get());
}

AngleUtils AngleUtils::toComplementary() {
    return {this->degree.toComplementary(), this->radian.toComplementary()};
}