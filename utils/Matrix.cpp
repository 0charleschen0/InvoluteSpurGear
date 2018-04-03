//
// Created by USER on 2018/4/2.
//
#include <utility>
#include <algorithm>
#include <exception>
#include <stdexcept>
#include "Matrix.h"


Matrix::Matrix(int row, int col) {
    this->row = row;
    this->col = col;
    data = new double[row*col];
}

Matrix::Matrix(int row, int col, double* data) {
    this->row = row;
    this->col = col;
    this->data = new double[row*col];
    this->data = data;
}

//Transform x-y points vector to matrix
Matrix::Matrix(vector<Pair<double, double>> vec) {
    this->row = 2;
    this->col = (int) vec.size();
    data = new double[row*col];

    for (int i=0; i<vec.size(); i++) {
        data[0 + row*i] = vec[i].x();
        data[1 + row*i] = vec[i].y();
    }
}

Matrix Matrix::transpose() {
    Matrix mat = Matrix(this->col, this->row);
    for (int i=0; i<this->col; i++) {
        for (int j=0; j<this->row; j++) {
            mat.data[row*i + j] = this->data[col*j +i];
        }
    }
    return mat;
}

Matrix Matrix::multiply(Matrix matrix) {
    if (this->row != matrix.col) {
        throw invalid_argument("first matrix's row should be the same as second matrix's col");
    }

    Matrix result = Matrix(matrix.row, this->col);
    result.data = {0};

    for (int i=0; i<result.row; i++) {
        for (int j=0; j<result.col; j++) {
            for (int k=0; k<this->row; k++) {
                result.data[result.row*i + j] += this->data[row*k + i]*matrix.data[row*j + k];
            }
        }
    }
    return result;
}