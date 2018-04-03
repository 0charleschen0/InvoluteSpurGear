//
// Created by USER on 2018/4/2.
//

#ifndef INVOLUTESPURGEAR_MATRIX_H
#define INVOLUTESPURGEAR_MATRIX_H

#include <vector>
#include "Pair.h"

using namespace std;
class Matrix{
private:
    int row;
    int col;
    double *data;
public:
    Matrix(int row, int col);
    Matrix(vector<Pair<double, double>> vec);
    Matrix(int row, int col, double* data);
    Matrix multiply(Matrix matrix);
    Matrix transpose();
};
#endif //INVOLUTESPURGEAR_MATRIX_H
