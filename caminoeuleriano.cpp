#include <iostream>
#include <forward_list>
#include <vector>
#include <stack>
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
    bool find_arr_rep(CEdge ite, vector<CEdge> aristas_visitadas);
    void Print();
    void camino_euleriano();
    vector<CNode> nodes;
    int cantidad_aristias = 0;
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
    cantidad_aristias = cantidad_aristias + 1;
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

bool CGraph::find_arr_rep(CEdge ite, vector<CEdge> aristas_visitadas) {
    if (aristas_visitadas.empty()) {
        return false;
    }

    for (size_t i = 0; i < aristas_visitadas.size(); i++) {
        if (ite.id_node == aristas_visitadas[i].id_node && ite.value == aristas_visitadas[i].value) {
            return true;
        }
    }
    return false;
}

void CGraph::camino_euleriano() {
    int ini = 0;
    vector<CEdge> aristas_visitadas;
    vector<char> camino;
    stack<CEdge> aristas;
    camino.push_back(nodes[ini].value);

    for (auto& e : nodes[ini].edges) {
        aristas.push(e);
    }

    while (!aristas.empty()) {
        CEdge ite = aristas.top();
        ini = ite.id_node;
        if (find_arr_rep(ite, aristas_visitadas)) {
            aristas.pop();
        }
        else {
            camino.push_back(nodes[ini].value);
            aristas.pop();
            aristas_visitadas.push_back(ite);
            for (auto& e : nodes[ini].edges) {
                aristas.push(e);
            }
        }
    }

    for (size_t i = 0; i < camino.size(); i++) {
        cout << camino[i];
        if (i < camino.size() - 1) {
            cout << " -> ";
        }
    }
    cout << endl;
}




int main()
{
    CGraph g;
    g.InsNode('A'); g.InsNode('B'); g.InsNode('C'); g.InsNode('D'); g.InsNode('E');

    g.InsEdge(0, 1, 5);  
    g.InsEdge(1, 2, 4);  
    g.InsEdge(2, 0, 3);  
    g.InsEdge(2, 3, 10);  
    g.InsEdge(3, 4, 12);  
    g.InsEdge(4, 2, 34); 

    g.Print();
    g.camino_euleriano();
}
