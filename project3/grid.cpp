#include <iostream>
#include <fstream>
#include <string>
#include "d_matrix.h"
#include "grid.h"

using namespace std;

Grid::Grid() : m(matrix<char>()) {}

matrix<char> Grid::getMatrix() {
    return m;
}

void Grid::setMatrix(matrix<char> nm) {
    m = nm;
}

void Grid::setMatrix(string s) {
    int rows;
    int cols;
    ifstream f(s;

    if (!f.is_open()) {
        throw fileOpenError(s); 
    }

    f >> rows >> cols;
    m.resize(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            f >> m[i][j];
        }
    }

    f.close();
}