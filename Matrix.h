//
// Created by duhamel on 04/10/24.
//

#ifndef MATRIX_H
#define MATRIX_H
#include <fstream>
#include <string>

#include <vector>
using namespace std;
/**
* MatrixFunctionGenerative
* is a function to genera a matrix that
* M[i][j]=f(i,j)
*/
typedef double (*MatrixFunctionGenerative)(int,int) ;
/** Class Matrix is a matrix of type double in 2 dimension
*
*
*
*/
class Matrix {
// friend
        friend Matrix Create_Matrix(int row, int col);
        friend Matrix Create_Matrix_Identity(int size);
//operator
        /**
        *@param lhs size must is equal size's rhs
        *@param rhs size must is equal size's lhs
*/
        friend Matrix operator+(const Matrix& lhs, const Matrix& rhs);
        /**
        *@param lhs size must is equal size's rhs
        *@param rhs size must is equal size's lhs
*/
        friend Matrix operator-(const Matrix& lhs, const Matrix& rhs);
        friend Matrix operator*(const Matrix& lhs, const Matrix& rhs);
        /**
        * TODO is not implement for negative integer
        * ^ is the power
*/
        friend Matrix operator^(const Matrix& lhs, const int& rhs);
        friend Matrix operator*(const int& lhs, const Matrix& rhs);
        friend Matrix operator*(const double &lhs, const Matrix &rhs);
        friend bool operator==(const Matrix& lhs, const Matrix& rhs);
        friend bool operator!=(const Matrix& lhs, const Matrix& rhs);
        friend Matrix abs(Matrix& lhs);

public:
        Matrix operator+=(const Matrix& rhs);
        Matrix operator-=(const Matrix& rhs);
        Matrix operator*=(const Matrix& rhs);
        Matrix operator*=(const int& rhs);
        Matrix operator*=(const double& rhs);

        Matrix(const Matrix& rhs);
        Matrix(MatrixFunctionGenerative func, int row, int col);
        ~Matrix();

        //methode
        /**
         *@brief
        * @param row
        * @param col
*/
        void GetSize(int& row, int& col) const;
        [[nodiscard]] bool IsSquare() const;
        void Print() const;
        [[nodiscard]] double sum() const;
        [[nodiscard]] double trace() const;
        int WriteMatrixCreatedFile(std::string name,std::string path ) const;





private:
        Matrix(int row, int col);
int row{};
int col{};
        // row[col]
vector<vector<double>> data;

        //methode interne
        [[nodiscard]] bool EqualSize(const Matrix& other) const;
};
/**
*
*/
[[nodiscard]] Matrix Create_Matrix(int row, int col);
/**
* @param size > 0 is the size of matrix
* @return the matrix I of size size
*/
[[nodiscard]] Matrix Create_Matrix_Identity(int size);

#endif //MATRIX_H
