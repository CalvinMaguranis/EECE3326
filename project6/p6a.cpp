// Project 6
//
// Assumes that directed edges in both directions (x,y) and (y,x) are present in the input file.
//

#include <iostream>
#include <fstream>
#include <list>
#include <set>
#include <queue>
#include <vector>
#include <limits.h>
#include "d_except.h"
#include "d_matrix.h"
#include "graph.h"

using namespace std;

void dfs(graph &g, graph &sf, bool &cyclic, int v, int x) {
    g.visit(v);
    int count = 0;
    for (int w = 0; w < g.numNodes(); w++) {
        if (g.isEdge(v, w)) {
            if (g.isVisited(w)) {
                count++;
            } else {
                int z = g.getEdge(v, w).getWeight();
                int y = sf.addNode();
                sf.addEdge(x, y, z);
                dfs(g, sf, cyclic, w, y);
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
    bool cyclic = false;
    for (int i = 0; i < g.numNodes(); i++) {
        if (g.isVisited(i) == false) {
            int x = d.addNode();
            dfs(g, d, cyclic, i, x);
            if (cyclic) {
                break;
            }
        }
    }
    g.clearVisit();
    return cyclic;
}

// Returns true if the graph g is connected.  Otherwise returns false.
bool isConnected(graph &g) {
    bool cyclic = false;
    graph d(1);
    dfs(g, d, cyclic, 0, 0);
    g.clearVisit();
    return (g.numNodes() == d.numNodes());
}

// Create a graph sf that contains a spanning forest on the graph g.
void findSpanningForest(graph &g, graph &sf) {
    bool cyclic = false;
    for (int i = 0; i < g.numNodes(); i++) {
        if (g.isVisited(i) == false) {
            // new spanning tree can be generated
            int x = sf.addNode();
            dfs(g, sf, cyclic, i, x);
        }
    }
    g.clearVisit();
}

// Create a graph sf that contains a minimum spanning forest on the graph g.
// sf is expected to be an graph with same number of nodes as g but with no edges
void prim(graph &g, graph &sf) {
    // set up
    set<int> s;
    for (int i = 1; i < sf.numNodes(); i++) {
        sf.getNode(i).setWeight(INT_MAX);
        sf.getNode(i).setId(0);
    }
    sf.getNode(0).setWeight(0);

    while((int)s.size() != g.numNodes()) {
        int minWeight = INT_MAX;
        int minVertex = -1;
        for (int i = 0; i < sf.numNodes(); i++) {
            if(s.find(i) == s.end()) {
                int w = sf.getNode(i).getWeight();
                if (w < minWeight) {
                    minWeight = w;
                    minVertex = i;
                }
            }
        }

        if (minVertex == -1) {
            for (int i = 0; i < sf.numNodes(); i++) {
                if(s.find(i) == s.end()) {
                    minVertex = i;
                    minWeight = 0;
                    sf.getNode(i).setWeight(0);
                    sf.getNode(i).setId(i);
                    break;
                }
            }
        }

        s.insert(minVertex);
        if (sf.getNode(minVertex).getId() != minVertex) {
            sf.addEdge(sf.getNode(minVertex).getId(), minVertex, minWeight);
        }

        for (int i = 0; i < g.numNodes(); i++) {
            if (g.isEdge(minVertex, i)) {
                node n = sf.getNode(i);
                edge e = g.getEdge(minVertex, i);
                if (n.getWeight() > e.getWeight()) {
                    sf.setNodeWeight(i, e.getWeight());
                    sf.getNode(i).setId(minVertex);
                }
            }
        }
    }

    // clean up
    for (int i = 0; i < sf.numNodes(); i++) {
        sf.getNode(i).setWeight(0);
        sf.getNode(i).setId(i);
    }
}

void kruskal(graph &g, graph &sf) {

}

int main() {
    ifstream fin;
    stack <int> moves;
    string fileName;

    // Read the name of the graph from the keyboard or
    // hard code it here for testing.

    fileName = "graph4.txt";

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
        graph sf;
        findSpanningForest(g, sf);

        cout << endl;

        cout << sf;

        cout << "Spanning forest weight: " << sf.getTotalEdgeWeight() << endl;

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

        graph msf(g.numNodes());
        prim(g, msf);
        cout << "Finding minimum spanning forest" << endl;
        cout << msf;
        cout << "Minimum spanning forest weight: " << msf.getTotalEdgeWeight() << endl;

    } catch (indexRangeError &ex) {
        cout << ex.what() << endl; exit(1);
    } catch (rangeError &ex) {
        cout << ex.what() << endl; exit(1);
    }
}

