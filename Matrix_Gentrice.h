#ifndef MATRIX_GENTRICE_H
#define MATRIX_GENTRICE_H
#include <iostream>
template<typename T>
using function_gen= T (int row,int col);

template<typename Type>
class Matrix {
        friend Matrix<Type> operator+(Matrix<Type> const &m1,Matrix<Type> const &m2);
        friend Matrix<Type> operator-(Matrix<Type> const &m1,Matrix<Type> const &m2);
        friend Matrix<Type> operator*(Matrix<Type> const &m1,Matrix<Type> const &m2);





protected:
        int rows;
        int cols;
        vector<vector<Type> > matrix;
        public:
        Matrix(Matrix<Type> const &m1) {
                rows = m1.rows;
                cols = m1.cols;
                matrix= vector<vector<Type> >(rows,vector<Type>(cols));
                for(int i=0;i<rows;i++) {
                        for(int j=0;j<cols;j++) {
                                matrix[i][j] = m1.matrix[i][j];
                        }
                }
        }
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
        template<typename Typeother>
        explicit Matrix(Matrix<Typeother> const&m1) {
                rows = m1.rows;
                cols = m1.cols;
                matrix= vector<vector<Type> >(rows, vector<Type>(cols, Type(0)));
                for(int i=0;i<rows;i++) {
                        for(int j=0;j<cols;j++) {
                                matrix[i][j] = dynamic_cast<Type>(m1.matrix[i][j]);
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
template<typename Type>
Matrix<Type> operator+(Matrix<Type> const &m1,Matrix<Type> const &m2) {
        if (m1.rows != m2.rows || m1.cols != m2.cols) {
                throw std::invalid_argument("Invalid matrix size");
        }
        Matrix<Type> result(m1.rows,m1.cols,Type(0));
        for (int i = 0; i < m1.rows; i++) {
                for (int j = 0; j < m1.cols; j++) {
                        result.matrix[i][j] = m1.matrix[i][j] + m2.matrix[i][j];
                }
        }
        return result;

}
template<typename Type>
Matrix<Type> operator-(Matrix<Type> const &m1,Matrix<Type> const &m2) {
        if (m1.rows != m2.rows || m1.cols != m2.cols) {
                throw std::invalid_argument("Invalid matrix size");
        }
        Matrix<Type> result(m1.rows,m1.cols,Type(0));
        for (int i = 0; i < m1.rows; i++) {
                for (int j = 0; j < m1.cols; j++) {
                        result.matrix[i][j] = m1.matrix[i][j] - m2.matrix[i][j];
                }
        }
        return result;
}
template<typename  Type>
Matrix<Type> operator*(Matrix<Type> const &m1,Matrix<Type> const &m2) {
        if(m1.cols!=m2.rows) {
                throw std::invalid_argument("Invalid matrix size");
        }
        Matrix<Type> result(m1.rows,m2.cols,Type(0));
        for (int i = 0; i < m1.rows; i++) {
                for (int j = 0; j < m2.cols; j++) {
                        Type sum = Type(0);
                        for (int k = 0; k < m1.cols; k++) {
                                sum += m1.matrix[i][k] * m2.matrix[k][j];
                        }
                        result.matrix[i][j] = sum;
                }
        }
        return result;
}


#endif