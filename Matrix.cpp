//
// Created by duhamel on 04/10/24.
//

#include "Matrix.h"

#include <cstdlib>
#include <stdlib.h>
#include <vector>
using namespace std;
Matrix Create_Matrix(int row, int col) {
        return Matrix(row, col);
}

Matrix::Matrix(int row, const int col) {
        this->row = row;
        this->col = col;
        vector<vector<double>> vec(row, vector<double> (col, 0));
        this->data = vec;

}



