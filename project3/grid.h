#ifndef GRID_H
#define GRID_H

#include <string>
#include "d_matrix.h"
using namespace std;

class grid {
    public:
        grid();
		grid(string file);
		matrix<char> getMatrix() { return m; }
		void setMatrix(matrix<char> matrix) { m=matrix; }
		void setMatrix(string s);
    private:
        matrix<char> m;
};


#endif /* GRID_H */