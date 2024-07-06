#include <iostream>
#include <forward_list>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

struct CEdge {
    CEdge(int idn = -1, int v = 0) {
        id_node = idn;
        value = v;
    }
    int id_node;
    int value;
};

struct CNode {
    CNode(int id = -1, char v = 0) {
        id_node = id;
        value = v;
    }
    int id_node;
    char value;
    forward_list<CEdge> edges;
};

class CGraph {
public:
    void InsNode(char v);
    void InsEdge(int idn1, int idn2, int v);
    void RemNode(int idn);
    void RemEdge(int idn1, int idn2, int v);
    void Print();
    void Dijkstra(int start);
    vector<CNode> nodes;
};

void CGraph::InsNode(char v) {
    CNode n(nodes.size(), v);
    nodes.push_back(n);
}

void CGraph::InsEdge(int idn1, int idn2, int v) {
    CEdge e(idn2, v);
    nodes[idn1].edges.push_front(e);
}

void CGraph::Print() {
    for (auto& n : nodes) {
        cout << n.value << " ";
        for (auto& e : n.edges)
            cout << "->" << nodes[e.id_node].value << " " << e.value;
        cout << "\n";
    }
}

void CGraph::Dijkstra(int start) {
    int INF = 1000000000;
    vector<int> dist(nodes.size(), INF);
    vector<bool> visited(nodes.size(), false);
    dist[start] = 0;

    for (size_t i = 0; i < nodes.size(); ++i) {
        int u = -1;

        for (size_t j = 0; j < nodes.size(); ++j) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }

        if (dist[u] == INF) {
            break;
        }

        visited[u] = true;

        for (const CEdge& edge : nodes[u].edges) {
            int v = edge.id_node;
            int weight = edge.value;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    for (size_t i = 0; i < dist.size(); ++i) {
        if (dist[i] == INF) {
            cout << nodes[start].value << " to " << nodes[i].value << " " << endl;
        }
        else {
            cout << nodes[start].value << " to " << nodes[i].value << " " << dist[i] << endl;
        }
    }
}

int main() {
    CGraph g;
    g.InsNode('A'); //0
    g.InsNode('B'); //1
    g.InsNode('C'); //2
    g.InsNode('D'); //3
    g.InsNode('E'); //4
    g.InsNode('F'); //5
    g.InsNode('G'); //6
    g.InsNode('H'); //7
    g.InsNode('I'); //8
    g.InsNode('J'); //9
    g.InsNode('K'); //10
    g.InsEdge(0, 1, 2);
    g.InsEdge(0, 2, 4);
    g.InsEdge(1, 2, 5);
    g.InsEdge(1, 3, 3);
    g.InsEdge(2, 9, 2);
    g.InsEdge(2, 5, 3);
    g.InsEdge(3, 9, 5);
    g.InsEdge(5, 9, 3);
    g.InsEdge(9, 6, 2);
    g.InsEdge(9, 4, 2);
    g.InsEdge(6, 10, 6);
    g.InsEdge(4, 7, 1);
    g.InsEdge(4, 8, 1);
    g.InsEdge(7, 10, 3);
    g.InsEdge(8, 10, 2);
    g.Print();

    g.Dijkstra(0); // inicio osea el A

    return 0;
}
