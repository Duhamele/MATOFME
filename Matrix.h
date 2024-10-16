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
class Matrix_d {
// friend
        friend Matrix_d Create_Matrix(int row, int col);
        friend Matrix_d Create_Matrix_Identity(int size);
//operator
        /**
        *@param lhs size must is equal size's rhs
        *@param rhs size must is equal size's lhs
*/
        friend Matrix_d operator+(const Matrix_d& lhs, const Matrix_d& rhs);
        /**
        *@param lhs size must is equal size's rhs
        *@param rhs size must is equal size's lhs
*/
        friend Matrix_d operator-(const Matrix_d& lhs, const Matrix_d& rhs);
        friend Matrix_d operator*(const Matrix_d& lhs, const Matrix_d& rhs);
        /**
        * TODO is not implement for negative integer
        * ^ is the power
*/
        friend Matrix_d operator^(const Matrix_d& lhs, const int& rhs);
        friend Matrix_d operator*(const int& lhs, const Matrix_d& rhs);
        friend Matrix_d operator*(const double &lhs, const Matrix_d &rhs);
        friend bool operator==(const Matrix_d& lhs, const Matrix_d& rhs);
        friend bool operator!=(const Matrix_d& lhs, const Matrix_d& rhs);
        friend Matrix_d abs(Matrix_d& lhs);

public:
        Matrix_d operator+=(const Matrix_d& rhs);
        Matrix_d operator-=(const Matrix_d& rhs);
        Matrix_d operator*=(const Matrix_d& rhs);
        Matrix_d operator*=(const int& rhs);
        Matrix_d operator*=(const double& rhs);

        Matrix_d(const Matrix_d& rhs);
        Matrix_d(MatrixFunctionGenerative func, int row, int col);
        ~Matrix_d();

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
        Matrix_d(int row, int col);
int row{};
int col{};
        // row[col]
vector<vector<double>> data;

        //methode interne
        [[nodiscard]] bool EqualSize(const Matrix_d& other) const;
};
/**
*
*/
[[nodiscard]] Matrix_d Create_Matrix(int row, int col);
/**
* @param size > 0 is the size of matrix
* @return the matrix I of size size
*/
[[nodiscard]] Matrix_d Create_Matrix_Identity(int size);

#endif //MATRIX_H
