#include <iostream>
#include <fstream>
#include "grid.h"

using namespace std;

grid::grid() : m(matrix<char>()) {}

grid::grid(string file) : m(matrix<char>()) {
    setMatrix(file);
}

void grid::setMatrix(string s) {
    int rows;
    int cols;

    ifstream f(s);
    if (!f.is_open()) { throw fileOpenError(s); }

    f >> rows >> cols;
    m.resize(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            f >> m[i][j];
        }
    }
    f.close();
}
