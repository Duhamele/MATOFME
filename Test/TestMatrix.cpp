#include "../Matrix.h"
//
// Created by duhamel on 05/10/24.
//
int main() {
        Matrix m=Create_Matrix(10,12);
        int a,b;
        m.GetSize(a,b);
        m+=m;
        return a;
}