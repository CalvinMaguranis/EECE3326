#include <iostream>
#include <limits.h>
#include <list>
#include <map>
#include <fstream>
#include <stack>
#include <queue>
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

    cout << "+";
    for (int j = 0; j <= cols - 3; j++) {
        cout << "=";
    }
    cout << "+" << endl;

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
    cout << "+";
    for (int j = 0; j <= cols - 3; j++) {
        cout << "=";
    }
    cout << "+" << endl;

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


bool findPathRec(graph &g, maze &m, int pos, bool print) {
    int row, col;
    m.getCoordForNode(pos, row, col);
    g.visit(pos);
	if (print) {
		m.print(m.numRows() - 1, m.numCols() - 1, row, col);
	}
    if (row == m.numRows() - 1 && col == m.numCols() - 1) {
        return true;
    } else {
        for (int n = 0; n < g.numNodes(); n++) {
            if (g.isEdge(pos, n)) {
                if (g.isVisited(n) == false) { // neighbor is unvisited
                    if (findPathRec(g, m, n, print)) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool findPathIt(graph &g, maze &m, int node) {
    stack<int> s;
    s.push(node);
    while (s.empty() == false) {
        int v, row, col;
        v = s.top();
        s.pop();
        m.getCoordForNode(v, row, col);
        m.print(m.numRows() - 1, m.numCols() - 1, row, col);
        if (row == m.numRows() - 1 && col == m.numCols() - 1) {
            return true; // found the end
        } else {
            if (g.isVisited(v) == false) {
                g.visit(v);
                for (int n = 0; n < g.numNodes(); n++) {
                    if (g.isEdge(v, n)) {
                        if (g.isVisited(n) == false) { s.push(n); }
                    }
                }
            }
        }
    }

    return false;
}

void shortestPathDFS(graph &g, vector<int> &sol, vector<int> &currentPath,
                     int currentNode, int endNode) {
	if (sol.size() > g.numNodes() || currentPath.size() > g.numNodes()) {
		// cannot find the end, graph is unconnected to endNode
		return;
	}
    g.visit(currentNode);
    currentPath.push_back(currentNode);
    if (currentNode == endNode) {
        if ((currentPath.size() < sol.size()) || sol.size() == 0) {
            sol = currentPath;
        }
        return;
    }

    for (int n = 0; n < g.numNodes(); n++) {
        if (g.isEdge(currentNode, n)) {
            if (g.isVisited(n) == false) { // neighbor is unvisited
                shortestPathDFS(g, sol, currentPath, n, endNode);
                g.unVisit(n);
                currentPath.pop_back();
            }
        }
    }
}

void findShortestPathDFS(graph &g, maze &m) {
    int endI = m.numRows() - 1;
    int endJ = m.numCols() - 1;
    int startNode = m.getNodeForCoord(0, 0);
    int endNode = m.getNodeForCoord(endI, endJ);
    
	if (findPathRec(g, m, startNode, false)) {
		vector<int> currentPath;
		vector<int> sol;
		g.clearVisit();
		shortestPathDFS(g, sol, currentPath, startNode, endNode);

		cout << "DFS: solution found:" << endl;
		for (vector<int>::iterator it = sol.begin(); it != sol.end(); it++) {
		int i, j;
		int n = *it;
		m.getCoordForNode(n ,i , j);
		m.print(endI, endJ, i, j);
		}
		cout << endl;
		cout << "Total steps : " << sol.size() - 1 << endl;
	} else {
		// cannot find the end, graph is unconnected to endNode
		cout << "DFS: cannot find path to end" << endl;
	}
}

void findShortestPathBFS(graph &g, maze &m) {
	queue<int> q;
	map<int, int> pred; // node, pred
	int endI = m.numRows() - 1;
	int endJ = m.numCols() - 1;
	int startNode = m.getNodeForCoord(0, 0);
	int endNode = m.getNodeForCoord(endI, endJ);
	g.clearVisit();
	q.push(startNode);
	pred[startNode] = -1; // only starnode has no predecessor

	while (q.empty() == false) {
		int v;
		v = q.front();
		q.pop();
		if (g.isVisited(v) == false) {
			g.visit(v);
			for (int n = 0; n < g.numNodes(); n++) {
				if (g.isEdge(v, n)) {
					if (g.isVisited(n) == false) { 
						q.push(n); 
						pred[n] = v;
					}
				}
			}
		}
	}

	// check if we got to the end
	if (findPathRec(g, m, startNode, false)) {
		cout << "BFS: solution found:" << endl;
		int node = endNode, count = -1;
		stack<int> s;
		s.push(node);

		while (node != startNode) {
			node = s.top();
			s.push(pred[node]);
			count++;
		}
		s.pop(); // startNode has no predecessor
		int i, j, n;
		while (!s.empty()) {
			m.getCoordForNode(s.top(), i, j);
			m.print(endI, endJ, i, j);
			s.pop();
		}
		cout << endl;
		cout << "Total steps : " << count << endl;
	} else {
		cout << "BFS: cannot find path to end" << endl;
	}
}

int main() {
    ifstream fin;

    // Read the maze from the file.
    string fileName = "maze1.txt";

    fin.open(fileName.c_str());
    if (!fin) {
        cerr << "Cannot open " << fileName << endl;
        system("PAUSE");
        exit(1);
    }

    try {
        graph g;
        if (fin && fin.peek() != 'Z') {
            maze m(fin);
            m.mapMazeToGraph(g);
          
			findShortestPathDFS(g, m);
			findShortestPathBFS(g, m);
			
        }

    } catch (indexRangeError &ex) {
        cout << ex.what() << endl;
        system("PAUSE");
        exit(1);
    } catch (rangeError &ex) {
        cout << ex.what() << endl;
        system("PAUSE");
        exit(1);
    }

    system("PAUSE");
}
