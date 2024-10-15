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
//Created Matrix_d
Matrix_d Create_Matrix(int row, int col) {
        if(row<=0 || col<=0 ) {
                throw runtime_error("Invalid Matrix_d Size");
        }
        return Matrix_d(row, col);
}
Matrix_d Create_Matrix_Identity(int size) {
        if(size<=0) {
                throw runtime_error("Matrix_d size must be greater than zero");
        }
        Matrix_d m(size, size);
        for (int i = 0; i < size; i++) {
                m.data[i][i] = 1;
        }
        return m;
}

/**
 * TODO
 */
Matrix_d::~Matrix_d() = default;

Matrix_d::Matrix_d(int row, const int col) {
        if(row<=0 || col<=0 ) {
                throw runtime_error("Invalid Matrix_d Size");
        }
        this->row = row;
        this->col = col;
        vector<vector<double>> vec(row, vector<double> (col, 0));
        this->data = vec;

}
Matrix_d::Matrix_d(const Matrix_d &rhs) {
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

Matrix_d::Matrix_d(MatrixFunctionGenerative func, int row, int col) {
        if(row<=0 || col<=0 ) {
                throw runtime_error("Invalid Matrix_d Size");
        }
        if(func==nullptr) {
                throw runtime_error("Invalid Matrix_d Function");
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

Matrix_d operator+(const Matrix_d &lhs, const Matrix_d &rhs) {
        if(!lhs.EqualSize(rhs)) {
                throw runtime_error("Matrix_d does not have the same size");
        }
        Matrix_d lhs1(lhs);
        return lhs1 += rhs;
}

Matrix_d operator-(const Matrix_d &lhs, const Matrix_d &rhs) {
        if(!lhs.EqualSize(rhs)) {
                throw runtime_error("Matrix_d does not have the same size");
        }
        Matrix_d lhs1(lhs);
        return lhs1 -= rhs;
}

Matrix_d operator*(const Matrix_d &lhs, const Matrix_d &rhs) {
        Matrix_d lhs1(lhs);
        return lhs1 *= rhs;
}

Matrix_d operator^(const Matrix_d &lhs, const int &rhs) {
        if(!lhs.IsSquare()) {
                throw runtime_error("Matrix_d isn't Square for the power");
        }
        Matrix_d lhs1(lhs);
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

Matrix_d operator*(const int &lhs, const Matrix_d &rhs) {
        Matrix_d rhs1(rhs);
        return rhs1 *= lhs;
}
Matrix_d operator*(const double &lhs, const Matrix_d &rhs) {
        Matrix_d rhs1(rhs);
        return rhs1 *= lhs;
}
Matrix_d Matrix_d::operator*=(const int &rhs) {
        for(int i=0; i<this->row; i++) {
                for(int j=0; j<this->col; j++) {
                        this->data[i][j] *= rhs;
                }
        }
        return *this;
}
Matrix_d Matrix_d::operator*=(const double &rhs) {
        for(int i=0; i<this->row; i++) {
                for(int j=0; j<this->col; j++) {
                        this->data[i][j] *= rhs;
                }
        }
        return *this;
}

bool operator==(const Matrix_d &lhs, const Matrix_d &rhs) {
        if (lhs.row != rhs.row || lhs.col != rhs.col) {return false;}
        for (int i = 0; i < lhs.row; i++) {
                for (int j = 0; j < lhs.col; j++) {
                        if (lhs.data[i][j] != rhs.data[i][j]) {return false;}
                }
        }
        return true;
}

bool operator!=(const Matrix_d &lhs, const Matrix_d &rhs) {
        return !(lhs == rhs);
}

Matrix_d abs(Matrix_d &lhs) {
        Matrix_d lhs1(lhs);
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
Matrix_d Matrix_d::operator*=(const Matrix_d &rhs) {
        if(this->row!=rhs.col) {
                throw runtime_error("Matrix_d does not have the same size");
        }
        Matrix_d lhs(*this);
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




Matrix_d Matrix_d::operator+=(const Matrix_d &rhs) {
        if(!this->EqualSize(rhs)) {
                throw runtime_error("Matrix_d does not have the same size");

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

Matrix_d Matrix_d::operator-=(const Matrix_d &rhs) {
        if(!this->EqualSize(rhs)) {
                throw runtime_error("Matrix_d does not have the same size");

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
void Matrix_d::GetSize(int &row, int &col) const {
        row = this->row;
        col = this->col;
}

bool Matrix_d::IsSquare() const {
        return this->col==this->row;
}

bool Matrix_d::EqualSize(const Matrix_d &other) const {
        return this->row == other.row && this->col == other.col;
}
void Matrix_d::Print() const {
        printf("Matrix_d:\n[");
        for(int i = 0; i < this->row; i++) {
                printf("[");
                for(int j = 0; j < this->col; j++) {
                        printf("%.2f ", this->data[i][j]);
                }
                printf("]\n");
        }
        printf("]\n");
}

double Matrix_d::sum() const {
        double sum=0;
        for (int i=0;i<this->row;i++) {
                for(int j=0;j<this->col;j++) {
                        sum+=this->data[i][j];
                }
        }
        return sum;
}

double Matrix_d::trace() const {
        double sum=0;
        for (int i=0;i<this->row&&(i<this->col);i++) {
                sum+=this->data[i][i];
        }
        return sum;
}

int Matrix_d::WriteMatrixCreatedFile(std::string name, std::string path) const {
        if(name.empty()) {
                throw runtime_error("Matrix_d name cannot be empty");
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

