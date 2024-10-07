#include "../Matrix.h"
//
// Created by duhamel on 05/10/24.
//
double func(int i, int j) {
        return i+j;
}
int main() {
        Matrix m= Matrix(func,10,10);
        m.Print();
        Matrix a=m+m;
        a.Print();
        a=a*m;
        a.Print();
        return 0;
}