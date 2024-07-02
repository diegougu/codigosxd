#include <iostream>
#include <forward_list>
#include <vector>
using namespace std;
struct CEdge
{
    CEdge(int idn = -1, int v = 0)
    {
        id_node = idn;
        value = v;
    }
    int id_node;
    int value;
};

struct CNode
{
    CNode(int id = -1, char v = 0)
    {
        id_node = id;
        value = v;
    }
    int id_node;
    char value;
    forward_list<CEdge> edges;
};

class CGraph
{
public:
    void InsNode(char v);
    void InsEdge(int idn1, int idn2, int v);
    void RemNode(int idn);
    void RemEdge(int idn1, int idn2, int v);
    void Print();
    void Dijkstra_recursivo(int actual, vector<bool>& visitado, vector<int>& camino, int final);
    void Dijkstra(int start);
    vector<CNode> nodes;
};

void CGraph::InsNode(char v)
{
    CNode n(nodes.size(), v);
    nodes.push_back(n);
}

void CGraph::InsEdge(int idn1, int idn2, int v)
{
    CEdge e(idn2, v);
    nodes[idn1].edges.push_front(e);
}

void CGraph::Print()
{
    for (auto n : nodes)
    {
        cout << n.value << " ";
        for (auto e : n.edges)
            cout << "->" << nodes[e.id_node].value << " " << e.value;
        cout << "\n";
    }
}

void CGraph::Dijkstra_recursivo(int actual, vector<bool>& visitado, vector<int>& camino, int final) {
    visitado[actual] = true;

    if (nodes[actual].id_node == nodes[final].id_node) {
        return;
    }

    for (auto& e : nodes[actual].edges) {
        int peso_ar = e.value;
        int id = e.id_node;
        if (camino[actual] + peso_ar < camino[id]) {
            camino[id] = camino[actual] + peso_ar;
            //cout << camino[id] << "pos-> " << id << " ";
        }
    }

    int next_node = -1;
    int min = INT_MAX;

    for (size_t i = 0; i < nodes.size(); ++i) {
        if (!visitado[i] && camino[i] < min) {
            min = camino[i];
            next_node = i;
        }
    }


    if (next_node != -1) {
        Dijkstra_recursivo(next_node, visitado, camino, final);
    }

}


void CGraph::Dijkstra(int start) {
    vector<bool> visitado(nodes.size(), false);
    vector<int> camino(nodes.size(), INT_MAX);
    camino[start] = 0;
    int final = nodes[nodes.size() - 1].id_node;
    Dijkstra_recursivo(start, visitado, camino, final);
    for (size_t i = 0; i < camino.size(); i++) {
        cout << nodes[i].value << " " << camino[i] << "->";
    }



}

int main()
{
    CGraph g;
    g.InsNode('A');    g.InsNode('B');
    g.InsNode('C');    g.InsNode('D');
    g.InsNode('X');
    g.InsEdge(0, 1, 3);    g.InsEdge(0, 2, 7); //A
    g.InsEdge(1, 3, 4);    g.InsEdge(1, 2, 2); //B
    g.InsEdge(2, 3, 1);    g.InsEdge(2, 4, 5); //C
    g.Print();

    g.Dijkstra(0);

    return 0;
}
