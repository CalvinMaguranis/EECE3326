#ifndef GRID_H
#define GRID_H

//#include <string>
//#include "d_matrix.h"

using namespace std;

class Grid {
    public:
        Grid();
        matrix<char> getMatrix();
        void setMatrix(matrix<char>);
        void setMatrix(string);
    private:
        matrix<char> m;
};


#endif /* GRID_H */