//
// Created by duhamel on 04/10/24.
//

#ifndef MATRIX_H
#define MATRIX_H
#include <vector>
using namespace std;
/** Class Matrix is a matrix of type double in 2 dimension
*
*
*
*/
class Matrix {
// friend
friend Matrix Create_Matrix(int row, int col);
public:



private:
        Matrix(int row, int col);
int row;
int col;
vector<vector<double>> data;
};
/**
*
*/
Matrix Create_Matrix(int row, int col);

#endif //MATRIX_H
