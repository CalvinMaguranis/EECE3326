#include <iostream>
#include <limits.h>
#include <list>
#include <map>
#include <fstream>
#include "d_matrix.h"
#include "d_except.h"
#include "graph.h"

using namespace std;

class maze {
    public:
        maze(ifstream &fin);

        int numRows() const {
            return rows;
        };

        int numCols() const {
            return cols;
        };

        void print(int, int, int, int) const;
        bool isLegal(int, int) const;

        void setMapping(int, int, int);
        int getNodeForCoord(int, int) const;
        void getCoordForNode(int, int &, int &);

        void mapMazeToGraph(graph &);

    private:
        int rows; // number of rows in the maze
        int cols; // number of columns in the maze

        matrix<bool> val;
        matrix<int> coord2Node;
        map<int, pair<int, int> > node2Coord;
};

void maze::setMapping(int i, int j, int n)
    // Set mapping from maze coordinate (i,j) to graph node n.
{
    coord2Node[i][j] = n;
    node2Coord[n] = pair<int, int>(i, j);
}

int maze::getNodeForCoord(int i, int j) const
    // Return graph node at maze coordinate (i,j).
{
    return coord2Node[i][j];
}

void maze::getCoordForNode(int n, int &i, int &j)
    // Return mapping of node n to it's maze coordinate.
{
    pair<int, int> p = node2Coord[n];
    i = p.first;
    j = p.second;
}

maze::maze(ifstream &fin)
    // Initializes a maze by reading values from fin.  Assumes that the
    // number of rows and columns indicated in the file are correct.
{
    fin >> rows;
    fin >> cols;

    char x;

    val.resize(rows,cols);
    for (int i = 0; i <= rows-1; i++)
    {
        for (int j = 0; j <= cols-1; j++)
        {
            fin >> x;
            if (x == 'O')
            {
                val[i][j] = true;
            }
            else
            {
                val[i][j] = false;
            }
        }
    }
}

void maze::print(int goalI, int goalJ, int currI, int currJ) const
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
            } else if (val[i][j]) {
                cout << " ";
            } else {
                cout << "X";
            }
        }
        cout << endl;
    }
    cout << endl;
}

bool maze::isLegal(int i, int j) const
    // Return the value stored at the (i,j) entry in the maze, indicating
    // whether it is legal to occupy cell (i,j).
{
    if (i < 0 || i > rows || j < 0 || j > cols) {
        throw rangeError("Bad value in maze::isLegal");
    }

    return val[i][j];
}

void maze::mapMazeToGraph(graph &g)
    // Create a graph g that represents the legal moves in the maze m.
{
    coord2Node.resize(rows,cols);

    // nodes
    int id = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (val[i][j]) {
                setMapping(i, j, id);
                node n = node();
                n.setId(id);
                g.addNode(n);
                id++;
            }
        }
    }

    // edges
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (val[i][j]) {
                int x = getNodeForCoord(i, j);
                if ((i-1) >= 0 && val[i-1][j]) {
                    int y = getNodeForCoord(i-1, j);
                    g.addEdge(x, y);
                }

                if ((i+1) < rows && val[i+1][j]) {
                    int y = getNodeForCoord(i+1, j);
                    g.addEdge(x, y);
                }

                if ((j-1) >= 0 && val[i][j-1]) {
                    int y = getNodeForCoord(i, j-1);
                    g.addEdge(x, y);
                }

                if ((j+1) < cols && val[i][j+1]) {
                    int y = getNodeForCoord(i, j+1);
                    g.addEdge(x, y);
                }
            }
        }
    }
}

int main() {
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
