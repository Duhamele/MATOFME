#include "../Matrix.h"
#include "../Matrix_Gentrice.h"
//
// Created by duhamel on 05/10/24.
//
double func(int i, int j) {
        return i+j;
}
int fonc(int i, int j) {
        return i+j;
}
int main() {
        Matrix_d m(func,10,10);
        m.Print();
        Matrix_d a=m+m;
        a.Print();
        a=a*m;
        a.Print();
        m=Create_Matrix_Identity(10);
        a*=m;
        a.Print();
        m*=6;
        m.Print();

        a=m;
        a*=0.3;
        a*=(0.9);
        a*=0.125868544754;
        a.Print();
        m.Print();
        Matrix<int> v(2,1,4);
        v.print();
        v=v.transpose();
        v.print();
        Matrix<int> v2(2,5,fonc);
        v2.print();
        return a.WriteMatrixCreatedFile("e","");
}