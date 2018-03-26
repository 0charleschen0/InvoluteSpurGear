//
// Created by USER on 2018/3/21.
//

#ifndef GEARDEMO_C_VECTORUTILS_H
#define GEARDEMO_C_VECTORUTILS_H

#include <vector>

using namespace std;

template <class CType>
class VectorUtils {
public:
    static bool contains(vector<CType> vec, CType value) {
        for (CType e : vec) {
            if (e == value) {
                return true;
            }
        }
        return false;
    }
};
#endif //GEARDEMO_C_VECTORUTILS_H
