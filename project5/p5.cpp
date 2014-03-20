// Project 5

#include <iostream>
#include <limits.h>
#include "d_except.h"
#include <list>
#include <fstream>
#include "d_matrix.h"
#include "graph.h"

using namespace std;

class maze {
public:
    maze(ifstream &fin);

    int numRows() {
        return rows;
    };
    int numCols() {
        return cols;
    };

    void print(int, int, int, int);
    bool isLegal(int i, int j);

    void setMap(int i, int j, int n);
    int getMap(int i, int j) const;
    void getMazeCoordinates(int, int &, int &) const

    void mapMazeToGraph(graph &g);

private:
    int rows; // number of rows in the maze
    int cols; // number of columns in the maze

    matrix<int> value;
    list<int[3]> mazeCoord;
    list<int[2]> adj;
};

void maze::setMap(int i, int j, int n)
// Set mapping from maze cell (i,j) to graph node n.
{
    value[i][j] = n;

    mazeCoord[n][0] = i;
    mazeCoord[n][1] = j;
}

int maze::getMap(int i, int j) const
// Return graph node at maze cell (i,j).
{
    return value[i][j];
}

void maze::getMazeCoordinates(int n, int &i, int &j) const
// Return reverse mapping of node n to it's maze i value.
{
    i = mazeCoord[n][0];
    j = mazeCoord[n][1];
}

maze::maze(ifstream &fin)
// Initializes a maze by reading values from fin.  Assumes that the
// number of rows and columns indicated in the file are correct.
{
    fin >> rows;
    fin >> cols;

    char x;
    int nodeVal = 1;
    mazeCoord.push_back({ -1, -1}); // n=0 is not used
    value.resize(rows, cols);
    for (int i = 0; i <= rows - 1; i++) {
        for (int j = 0; j <= cols - 1; j++) {
            arr[0] = i;
            arr[1] = j;
            fin >> x;
            if (x == 'O') {
                value[i][j] = nodeVal;
                mazeCoord.push_back({i, j});
                
                nodeVal++;
            } else {
                value[i][j] = 0;
            }
        }
    }

    // set up adjacent values
    adj.push_back({ -1,  0}); // UP == 0
    adj.push_back({ 1,  0}); // DOWN
    adj.push_back({ 0, -1}); // LEFT
    adj.push_back({ 0,  1}); // RIGHT == 4

}

void maze::print(int goalI, int goalJ, int currI, int currJ)
// Print out a maze, with the goal and current cells marked on the
// board.
{
    cout << endl;

    if (goalI < 0 || goalI > rows || goalJ < 0 || goalJ > cols) {
        throw rangeError("Bad value in maze::print");
    }

    if (currI < 0 || currI > rows || currJ < 0 || currJ > cols) {
        throw rangeError("Bad value in maze::print");
    }

    for (int i = 0; i <= rows - 1; i++) {
        for (int j = 0; j <= cols - 1; j++) {
            if (i == goalI && j == goalJ) {
                cout << "*";
            } else if (i == currI && j == currJ) {
                cout << "+";
            } else if (value[i][j]) {
                cout << " ";
            } else {
                cout << "X";
            }
        }
        cout << endl;
    }
    cout << endl;
}

bool maze::isLegal(int i, int j)
// Return the value stored at the (i,j) entry in the maze, indicating
// whether it is legal to occupy cell (i,j).
{
    if (i < 0 || i > rows || j < 0 || j > cols) {
        throw rangeError("Bad value in maze::isLegal");
    }

    return value[i][j];
}

void maze::mapMazeToGraph(graph &g)
// Create a graph g that represents the legal moves in the maze m.
{
    int n = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] > 0) {
                g.addNode(matrix[i][j]);
            }
        }
    }

    // edges
    for (int n=1; n<mapCoord.size()-1; n++) {
        for (int a = 0; a < 4; a++) {
            if (adj[a][0] + mapCoord[]) {
            }
        }
    }
}

bool checkAdjacent(graph &g, int n) {
}

int main() {
    char x;
    ifstream fin;

    // Read the maze from the file.
    string fileName = "maze.txt";

    fin.open(fileName.c_str());
    if (!fin) {
        cerr << "Cannot open " << fileName << endl;
        exit(1);
    }

    try {
        graph g;
        while (fin && fin.peek() != 'Z') {
            maze m(fin);
        }
    } catch (indexRangeError &ex) {
        cout << ex.what() << endl; exit(1);
    } catch (rangeError &ex) {
        cout << ex.what() << endl; exit(1);
    }
}
