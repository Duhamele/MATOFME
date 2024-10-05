//
// Created by duhamel on 04/10/24.
//

#include "Matrix.h"

#include <cstdlib>
#include <iostream>
#include <ostream>
#include <vector>
using namespace std;
Matrix Create_Matrix(int row, int col) {
        return Matrix(row, col);
}

Matrix operator+(const Matrix &lhs, const Matrix &rhs) {
        Matrix lhs1(lhs);
        return lhs1 += rhs;
}

Matrix operator-(const Matrix &lhs, const Matrix &rhs) {
        Matrix lhs1(lhs);
        return lhs1 -= rhs;
}

Matrix operator*(const Matrix &lhs, const Matrix &rhs) {
        Matrix lhs1(lhs);
        return lhs1 *= rhs;
}

bool operator==(const Matrix &lhs, const Matrix &rhs) {
        if (lhs.row != rhs.row || lhs.col != rhs.col) {return false;}
        for (int i = 0; i < lhs.row; i++) {
                for (int j = 0; j < lhs.col; j++) {
                        if (lhs.data[i][j] != rhs.data[i][j]) {return false;}
                }
        }
        return true;
}

bool operator!=(const Matrix &lhs, const Matrix &rhs) {
        return !(lhs == rhs);
}

/**
 * TODO
 * @param rhs
 * @return
 */
Matrix Matrix::operator*=(const Matrix &rhs) {
        return *this;
}

/**
 * TODO
 */
Matrix::~Matrix() = default;

Matrix::Matrix(int row, const int col) {
        this->row = row;
        this->col = col;
        vector<vector<double>> vec(row, vector<double> (col, 0));
        this->data = vec;

}


Matrix Matrix::operator+=(const Matrix &rhs) {
        if(!this->EqualSize(rhs)) {
                cout<<"Error in Matrix::operator+="<<endl;

        }
        else {
                for(int i = 0; i < this->row; i++) {
                        for(int j = 0; j < this->col; j++) {
                                this->data[i][j] = this->data[i][j] + rhs.data[i][j];
                        }
                }
        }
        return *this;
}

Matrix Matrix::operator-=(const Matrix &rhs) {
        if(!this->EqualSize(rhs)) {
                cout<<"Error in Matrix::operator+="<<endl;

        }
        else {
                for(int i = 0; i < this->row; i++) {
                        for(int j = 0; j < this->col; j++) {
                                this->data[i][j] = this->data[i][j] - rhs.data[i][j];
                        }
                }
        }
        return *this;
}

Matrix::Matrix(const Matrix &rhs) {
        this->row = rhs.row;
        this->col = rhs.col;
        vector<vector<double>> vec(row, vector<double> (col, 0));
        this->data = vec;
        for(int i = 0; i < this->row; i++) {
                for(int j = 0; j < this->col; j++) {
                        this->data[i][j] = rhs.data[i][j];
                }
        }
        }

void Matrix::GetSize(int &row, int &col) const {
        row = this->row;
        col = this->col;
}
bool Matrix::EqualSize(const Matrix &other) const {
        return this->row == other.row && this->col == other.col;
}

