#include <iostream>
#include <forward_list>
#include <vector>
#include <tuple>
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
    int id_aristas = 0;
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
    void CicloEuleriano(int inicio);
    vector<CNode> nodes;
    int cantidad_aristias = 0;
private:
    bool verificacion();
    bool arista_repetida(vector<pair<CEdge, bool>> visitado, int comp);
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


bool CGraph::verificacion() {
    vector<int> grado_salida;
    vector<int> grado_entrada(nodes.size(), 0);

    for (size_t i = 0; i < nodes.size(); i++) {
        int out = 0;
        for (auto e : nodes[i].edges) {
            out++;
        }
        grado_salida.push_back(out);
    }

    for (size_t i = 0; i < nodes.size(); i++) {
        for (auto e : nodes[i].edges) {
            grado_entrada[e.id_node]++;
        }
    }
    int inicio = 0;
    for (size_t i = 0; i < nodes.size(); i++) {
        if (grado_entrada[i] == grado_salida[i]) {
            inicio++;
        }
    }
    if (inicio == nodes.size()) {
        return true;
    }

    return false;

}

bool CGraph::arista_repetida(vector<pair<CEdge, bool>> visitado, int comp ) {
    for (size_t i = 0; i < visitado.size(); i++) {
        if (visitado[i].first.id_aristas == comp && visitado[i].second == true) {
            return true;
        }
    }
    return false;
}


void CGraph::CicloEuleriano(int inicio) {
    if (!verificacion()) {
        return;
    }
    else if (inicio > nodes.size() - 1) {
        return;
    }
    deque<CEdge> aristas;
    vector<char> camino;
    vector<pair<CEdge, bool>> visitado;
    int id_ar = 0;
    for (size_t i = 0; i < nodes.size(); i++) {
        for (auto& e : nodes[i].edges) {
            e.id_aristas = id_ar;
            if (i == inicio) {
                aristas.push_back(e);
            }
            visitado.push_back(make_pair(e, false));
            id_ar++;

        }
    }

    int temp_ini = inicio;

    camino.push_back(nodes[inicio].value);
    while (!aristas.empty()) {
        inicio = aristas.back().id_node;
        CEdge actual = aristas.back();
        int id_actual_arr = actual.id_aristas;
        if (arista_repetida(visitado, id_actual_arr)) {
            aristas.pop_back();
        }
        else {
            aristas.pop_back();
            visitado[id_actual_arr].second = true;
            camino.push_back(nodes[inicio].value);
            for (auto e : nodes[inicio].edges) {
                if (e.id_node != nodes[temp_ini].id_node) {
                    aristas.push_back(e);
                }
                else {
                    aristas.push_front(e);
                }
            }
        }
    }
    for (size_t i = 0; i < camino.size(); i++) {
        cout << camino[i] << " ";
    }
}


int main()
{
    CGraph g;
    g.InsNode('A'); g.InsNode('B'); g.InsNode('C'); g.InsNode('D'); g.InsNode('E');
    g.InsEdge(0, 1, 99);
    g.InsEdge(1, 4, 87);
    g.InsEdge(2, 4, 77);
    g.InsEdge(3, 2, 8);
    g.InsEdge(4, 0, 12);
    g.InsEdge(4, 3, 29);
    g.CicloEuleriano(0);
}
