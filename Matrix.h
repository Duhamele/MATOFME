//
// Created by duhamel on 04/10/24.
//

#ifndef MATRIX_H
#define MATRIX_H


/** Class Matrix is a matrix of type double in 2 dimension
*
*
*
*/
class Matrix {
// friend
friend Matrix Create_Matrix(int row, int col);
public:

        Matrix(int row, int col);

private:
int row;
int col;
double data[][];
};



#endif //MATRIX_H
