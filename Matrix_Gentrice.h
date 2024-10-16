#ifndef MATRIX_GENTRICE_H
#define MATRIX_GENTRICE_H
#include <iostream>
template<typename T>
using function_gen= T (int row,int col);

template<typename Type>class Matrix {
protected:
        int rows;
        int cols;
        vector<vector<Type> > matrix;
        public:
        Matrix(int rows, int cols,Type valeur_base) {
                if (rows < 1 || cols < 1) {
                        throw std::invalid_argument("Invalid matrix size");
                }
                this->rows = rows;
                this->cols = cols;
                this->matrix = vector<vector<Type> >(rows, vector<Type>(cols, valeur_base));
        }
        Matrix(int rows, int cols,function_gen<Type> function ) {
                if (rows < 1 || cols < 1) {
                        throw std::invalid_argument("Invalid matrix size");
                }
                this->rows = rows;
                this->cols = cols;
                this->matrix = vector<vector<Type> >(rows, vector<Type>(cols, function(0,0)));
                for (int i = 0; i < rows; i++) {
                        for (int j = 0; j < cols; j++) {
                                this->matrix[i][j] = function(i,j);
                        }
                }
        }
        Matrix transpose() {
               Matrix m(cols,rows,0);
                for (int i = 0; i < cols; i++) {
                        for (int j = 0; j < rows; j++) {
                                m.matrix[i][j] = this->matrix[j][i];
                        }
                }
                return m;
        }
        inline void transpose_() {
                this=transpose();
        }
        void print() {
                for (int i = 0; i < rows; i++) {
                        for (int j = 0; j < cols; j++) {
                                std::cout << matrix[i][j] << " ";
                        }
                        std::cout << std::endl;
                }
        }

};


#endif