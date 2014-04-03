// Project 6
//
// Assumes that directed edges in both directions (x,y) and (y,x) are present in the input file.
//

#include <iostream>
#include <limits.h>
#include "d_except.h"
#include <list>
#include <fstream>
#include "d_matrix.h"
#include "graph.h"
#include <queue>
#include <vector>

using namespace std;

int const NONE = -1;  // Used to represent a node that does not exist


void dfs(graph &g, graph &sf, int val, bool &cyclic) {
    int v = val; // start node
    int count = 0;
    g.visit(v);
    for (int w = 0; w < g.numNodes(); w++) {
        if (g.isEdge(v, w)) {
            if (g.isVisited(w)) {
                count++;
            } else {
                cout <<  "dfs v: " << v << " w: " << w << " numNodes(): " << sf.numNodes() << endl;
                node n = g.getNode(w);
                sf.addNode(n);
                sf.addEdge(v, w);

                dfs(g, sf, w, cyclic);
            }
        }
        if (count > 1) {
            cyclic = true;
        }
    }
}

// Returns true if the graph g contains a cycle.  Otherwise, returns false.
bool isCyclic(graph &g) {
    graph d;
    bool ret = false;

    for (int i = 0; i < g.numNodes(); i++) {
        if (g.isVisited(i) == false) {
            node v;
            v.setNode(i, 0, false, false);
            d.addNode(v);

            dfs(g, d, i, ret);
            if (ret) {
                return ret;
            }
        }
    }
    return ret;
}

// Returns true if the graph g is connected.  Otherwise returns false.
bool isConnected(graph &g) {
    bool whatever = false;
    graph c(1);

    dfs(g, c, 0, whatever);

    if (g.numNodes() != c.numNodes()) {
        return false;
    }
    return true;
}

// Create a graph sf that contains a spanning forest on the graph g.
void findSpanningForest(graph &g, graph &sf) {
    bool whatever = false;

    for (int i = 0; i < g.numNodes(); i++) {
        if (g.isVisited(i) == false) {
            // new spanning tree can be generated
            node v;
            v.setNode(i, 0, false, false);
            sf.addNode(v);

            cout << "sf size: " << sf.numNodes() << endl;

            dfs(g, sf, i, whatever);
        }
    }
}

int main() {
    char x;
    ifstream fin;
    stack <int> moves;
    string fileName;

    // Read the name of the graph from the keyboard or
    // hard code it here for testing.

    fileName = "graph2.txt";

    //   cout << "Enter filename" << endl;
    //   cin >> fileName;

    fin.open(fileName.c_str());
    if (!fin) {
        cerr << "Cannot open " << fileName << endl;
        exit(1);
    }

    try

    {
        cout << "Reading graph" << endl;
        graph g(fin);

        cout << g;

        bool connected;
        bool cyclic;

        connected = isConnected(g);
        cyclic = isCyclic(g);

        if (connected) {
            cout << "Graph is connected" << endl;
        } else {
            cout << "Graph is not connected" << endl;
        }

        if (cyclic) {
            cout << "Graph contains a cycle" << endl;
        } else {
            cout << "Graph does not contain a cycle" << endl;
        }

        cout << endl;

        cout << "Finding spanning forest" << endl;

        // Initialize an empty graph to contain the spanning forest
        graph sf(g.numNodes());
        findSpanningForest(g, sf);

        cout << endl;

        cout << sf;

        cout << "Spanning forest weight: " << sf.getTotalEdgeWeight() / 2 << endl;

        connected = isConnected(sf);
        cyclic = isCyclic(sf);

        if (connected) {
            cout << "Graph is connected" << endl;
        } else {
            cout << "Graph is not connected" << endl;
        }

        if (cyclic) {
            cout << "Graph contains a cycle" << endl;
        } else {
            cout << "Graph does not contain a cycle" << endl;
        }

        cout << endl;
    } catch (indexRangeError &ex) {
        cout << ex.what() << endl; exit(1);
    } catch (rangeError &ex) {
        cout << ex.what() << endl; exit(1);
    }
}

