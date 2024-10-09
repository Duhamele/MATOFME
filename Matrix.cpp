//
// Created by duhamel on 04/10/24.
//

#include "Matrix.h"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ostream>
#include <vector>
using namespace std;
//Created Matrix
Matrix Create_Matrix(int row, int col) {
        if(row<=0 || col<=0 ) {
                throw runtime_error("Invalid Matrix Size");
        }
        return Matrix(row, col);
}
Matrix Create_Matrix_Identity(int size) {
        if(size<=0) {
                throw runtime_error("Matrix size must be greater than zero");
        }
        Matrix m(size, size);
        for (int i = 0; i < size; i++) {
                m.data[i][i] = 1;
        }
        return m;
}

/**
 * TODO
 */
Matrix::~Matrix() = default;

Matrix::Matrix(int row, const int col) {
        if(row<=0 || col<=0 ) {
                throw runtime_error("Invalid Matrix Size");
        }
        this->row = row;
        this->col = col;
        vector<vector<double>> vec(row, vector<double> (col, 0));
        this->data = vec;

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

Matrix::Matrix(MatrixFunctionGenerative func, int row, int col) {
        if(row<=0 || col<=0 ) {
                throw runtime_error("Invalid Matrix Size");
        }
        if(func==nullptr) {
                throw runtime_error("Invalid Matrix Function");
        }
        this->row = row;
        this->col = col;
        vector<vector<double>> vec(row, vector<double> (col, 0));
        this->data = vec;
        for(int i = 0; i < this->row; i++) {
                for(int j = 0; j < this->col; j++) {
                        this->data[i][j] = func(i,j);
                }
        }
}
//Operatoc

Matrix operator+(const Matrix &lhs, const Matrix &rhs) {
        if(!lhs.EqualSize(rhs)) {
                throw runtime_error("Matrix does not have the same size");
        }
        Matrix lhs1(lhs);
        return lhs1 += rhs;
}

Matrix operator-(const Matrix &lhs, const Matrix &rhs) {
        if(!lhs.EqualSize(rhs)) {
                throw runtime_error("Matrix does not have the same size");
        }
        Matrix lhs1(lhs);
        return lhs1 -= rhs;
}

Matrix operator*(const Matrix &lhs, const Matrix &rhs) {
        Matrix lhs1(lhs);
        return lhs1 *= rhs;
}

Matrix operator^(const Matrix &lhs, const int &rhs) {
        if(!lhs.IsSquare()) {
                throw runtime_error("Matrix isn't Square for the power");
        }
        Matrix lhs1(lhs);
        if(rhs==1) {
                return lhs1;
        }
        if(rhs>1) {
                for(int i=1; i<rhs; i++) {
                        lhs1 = lhs1 * lhs;
                }
        }
        return lhs1 ;
}

Matrix operator*(const int &lhs, const Matrix &rhs) {
        Matrix rhs1(rhs);
        return rhs1 *= lhs;
}
Matrix operator*(const double &lhs, const Matrix &rhs) {
        Matrix rhs1(rhs);
        return rhs1 *= lhs;
}
Matrix Matrix::operator*=(const int &rhs) {
        for(int i=0; i<this->row; i++) {
                for(int j=0; j<this->col; j++) {
                        this->data[i][j] *= rhs;
                }
        }
        return *this;
}
Matrix Matrix::operator*=(const double &rhs) {
        for(int i=0; i<this->row; i++) {
                for(int j=0; j<this->col; j++) {
                        this->data[i][j] *= rhs;
                }
        }
        return *this;
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

Matrix abs(Matrix &lhs) {
        Matrix lhs1(lhs);
        for (int i = 0; i < lhs1.row; i++) {
                for (int j = 0; j < lhs1.col; j++) {
                        lhs1.data[i][j] = abs(lhs.data[i][j]);
                }
        }
        return lhs1;
}

/**
 *
 * @param rhs
 * @return
 */
Matrix Matrix::operator*=(const Matrix &rhs) {
        if(this->row!=rhs.col) {
                throw runtime_error("Matrix does not have the same size");
        }
        Matrix lhs(*this);
        vector<vector<double>> vec(row, vector<double> (rhs.col, 0));
        this->data = vec;
        for(int i = 0; i < this->row; i++) {
                for(int j = 0; j < this->col; j++) {

                        double sum = 0;
                        for(int k = 0; k < lhs.col; k++) {
                                sum += lhs.data[i][k] * rhs.data[k][j];

                        }
                        this->data[i][j] = sum;
                }
        }

        return *this;
}




Matrix Matrix::operator+=(const Matrix &rhs) {
        if(!this->EqualSize(rhs)) {
                throw runtime_error("Matrix does not have the same size");

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
                throw runtime_error("Matrix does not have the same size");

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


//Methode
void Matrix::GetSize(int &row, int &col) const {
        row = this->row;
        col = this->col;
}

bool Matrix::IsSquare() const {
        return this->col==this->row;
}

bool Matrix::EqualSize(const Matrix &other) const {
        return this->row == other.row && this->col == other.col;
}
void Matrix::Print() const {
        printf("Matrix:\n[");
        for(int i = 0; i < this->row; i++) {
                printf("[");
                for(int j = 0; j < this->col; j++) {
                        printf("%.2f ", this->data[i][j]);
                }
                printf("]\n");
        }
        printf("]\n");
}

double Matrix::sum() const {
        double sum=0;
        for (int i=0;i<this->row;i++) {
                for(int j=0;j<this->col;j++) {
                        sum+=this->data[i][j];
                }
        }
        return sum;
}

double Matrix::trace() const {
        double sum=0;
        for (int i=0;i<this->row&&(i<this->col);i++) {
                sum+=this->data[i][i];
        }
        return sum;
}

int Matrix::WriteMatrixCreatedFile(std::string name, std::string path) const {
        if(name.empty()) {
                throw runtime_error("Matrix name cannot be empty");
        }
        if(path.empty()) {
                path = "./" + name + ".mat.matrix";
        }else {
                path.append("/" + name + ".mat.matrix");
        }
        std::ofstream fichier(path.c_str());
        if(!fichier.is_open()) {
                perror("Error opening file");
                return 1;
        }
        for(int i=0;i<this->row;i++) {
                for(int j=0;j<this->col;j++) {
                        fichier << this->data[i][j] << ";";
                }
                fichier << "\n";
        }
        fichier.close();
        return 0;


}

