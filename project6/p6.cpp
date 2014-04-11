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
#include <algorithm>
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

// sort using a custom function object
struct {
	bool operator()(edge a, edge b) {
		return a.getWeight() < b.getWeight();
	}
} EdgeCompare;

void kruskal(graph &g, graph &sf) {
	// set up
	for (int i =0; i < sf.numNodes(); i++) {
		sf.getNode(i).setWeight(0);
		sf.getNode(i).setId(0);
	}

	// clear any visits used
	g.clearVisit();
	g.clearMark();

	// make list of edges
	vector<edge> e;
	for (int i = 0; i < g.numNodes(); i++) {
		for (int j = 0; j < g.numNodes(); j++) {
			if (g.isEdge(i, j)) {
				e.push_back(g.getEdge(i, j));
			}
		}
	}
	

	// sort edges e in non-decreasing order by weight
	sort(e.begin(), e.end(), EdgeCompare);

	// create MSF
	for (int k = 0; k < g.numEdges(); k++) {
		bool srcMarked = sf.isMarked(e[k].getSource());
		bool destMarked = sf.isMarked(e[k].getDest());
		if ( !sf.isMarked(e[k].getSource()) || 
			 !sf.isMarked(e[k].getDest()) )
		{
			sf.mark(e[k].getSource());
			sf.mark(e[k].getDest());
			sf.addEdge(e[k].getSource(), e[k].getDest(), e[k].getWeight());

			if (isCyclic(sf)) {
				sf.removeEdge(e[k].getSource(), e[k].getDest());
			}
		}
	}
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

        bool connected = isConnected(g);
        bool cyclic = isCyclic(g);
		if (connected) { cout << "Graph is connected" << endl; }
		else { cout << "Graph is not connected" << endl; }
		if (cyclic) { cout << "Graph contains a cycle" << endl; }
		else { cout << "Graph does not contain a cycle" << endl; }
		cout << endl;

		// PROJECT 6a
		cout << "MSF Algorithm: " << endl;
		graph sf;
		cout << "Finding spanning forest" << endl;
        findSpanningForest(g, sf);
        cout << sf;
        cout << "Spanning forest weight: " << sf.getTotalEdgeWeight() << endl;

		// PROJECT 6b
		// PRIM
		cout << "Prim algorithm: " << endl;
        graph prim_msf(g.numNodes());
		prim(g, prim_msf);
		cout << prim_msf;
		cout << "Minimum spanning forest weight: " << prim_msf.getTotalEdgeWeight() << endl; 

		// KRUSKAL
		cout << "Kruskal algorithm: " << endl;
		graph kruskal_msf(g.numNodes());
		kruskal(g, kruskal_msf);
		cout << kruskal_msf;
		cout << "Minimum spanning forest weight: " << kruskal_msf.getTotalEdgeWeight() << endl;

		// COMPARISON
		cout << endl << endl;
		cout << "Comparison: MSF=" << sf.getTotalEdgeWeight()
			<< ", PRIM=" << prim_msf.getTotalEdgeWeight()
			<< ", KRUSKAL=" << kruskal_msf.getTotalEdgeWeight() << endl;

    } catch (indexRangeError &ex) {
        cout << ex.what() << endl; exit(1);
    } catch (rangeError &ex) {
        cout << ex.what() << endl; exit(1);
    }

	system("PAUSE");
}

