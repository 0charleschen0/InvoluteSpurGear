//
// Created by USER on 2018/3/10.
//
#ifndef GEARDEMO_C_ANGLEUTILS_H
#define GEARDEMO_C_ANGLEUTILS_H

#include <cmath>
#include <map>
#include <string>
#include <limits>
#include <vector>

#include "VectorUtils.h"

using namespace std;

class AngleUtils {
private:
    class Radian {
    private:
        double number;

    public:
        Radian() = default;

        explicit Radian(double number) {
            this->number = number;
        }

        double get() {
            return number;
        }

        void set (double radian) {
            this->number = radian;
        }

        Radian toComplementary() {
            return Radian(M_PI/2.0 - this->number);
        }
    } radian;

    class Degree {
    private:
        double number;
    public:
        Degree() = default;

        explicit Degree(double number) {
            this->number = number;
        }

        double get() {
            return number;
        }

        void set(double degree) {
            this->number = degree;
        }

        Degree toComplementary() {
            return Degree(90.0 - this->number);
        }
    } degree;

//    class ComputeCache {
//    private:
//        static map<string, double> cacheMap;
//        static
//        static vector<string> keyArray;
//
//        double getValue(string key) {
//            if (isValidKey(key))
//                return cacheMap[key];
//            return numeric_limits<double>::quiet_NaN();
//        }
//
//        void setValue(string key, double value) {
//            if (!isValidKey(key))
//                return;
//            if (!isnan(value)) {
//                cacheMap[key] = value;
//            }
//        }
//
//        bool isValidKey(string key) {
//            return VectorUtils::contains(keyArray, key);
//        }
//    public:
//        ComputeCache() {
//            keyArray = vector(3);
//            keyArray.push_back("sin");
//            keyArray.push_back("cos");
//            keyArray.push_back("tan");
//
//            cacheMap = map();
//            for (string key : keyArray) {
//                cacheMap[key] = numeric_limits<double>::quiet_NaN();
//            }
//        };
//
//        double getSinValue() {
//            return getValue("sin");
//        }
//
//        double getCosValue() {
//            return getValue("cos");
//        }
//
//        double getTanValue() {
//            return getValue("tan");
//        }
//
//        void setSinValue(double value) {
//            setValue("sin", value);
//        }
//
//        void setCosValue(double value) {
//            setValue("cos", value);
//        }
//
//        void setTanValue(double value) {
//            setValue("tan", value);
//        }
//    } cache;

public:
    AngleUtils();
    AngleUtils(Degree degree, Radian radian);

    void setRadian(double radian);
    void setDegree(double degree);

    Radian getRadian() {
        return this->radian;
    }

    double getRadianValue() {
        return this->radian.get();
    }

    Degree getDegree() {
        return this->degree;
    }

    double getDegreeValue() {
        return this->degree.get();
    }

    AngleUtils toComplementary();

    inline double sin();
    inline double cos();
    inline double tan();

    inline static double toDegree(double radian) {
        return radian/M_PI*180.0;
    }

    inline static double toRadian(double degree) {
        return degree*M_PI/180.0;
    }
};
#endif //GEARDEMO_C_ANGLEUTILS_H
