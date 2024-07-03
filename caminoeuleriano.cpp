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
    int idf = 0;
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
    void CaminoEuleriano();
    vector<CNode> nodes;
    int cantidad_aristias = 0;
private:
    int verificacion();
    bool verificador_rep(vector<pair<CEdge, bool>> visitado, int comp);
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

int CGraph::verificacion() {
    vector<int> grado_salida;
    vector<int> grado_entrada(nodes.size() ,0);
    

    for (size_t i = 0; i < nodes.size(); i++) {
        int salida = 0;
        for (auto e : nodes[i].edges) {
            salida++;
        }
        grado_salida.push_back(salida);
    }
    for (size_t i = 0; i < nodes.size(); i++) {
        for (auto e : nodes[i].edges) {
            grado_entrada[e.id_node]++;
        }
    }
    
    int dos = 0;
    int ini = -1;
    for (size_t i = 0; i < nodes.size(); i++) {
        if (grado_entrada[i] > grado_salida[i]) {
            dos++;
            //ini = i;
        }
        else if (grado_entrada[i] < grado_salida[i]) {
            dos++;
            ini = i;
        }
    }
    if (dos != 2) {
        return -1;
    }
    else {

        return ini;
    }

}

bool CGraph::verificador_rep(vector<pair<CEdge, bool>> visitado, int comp) {

    for (size_t i = 0; i < visitado.size(); i++) {
        if (visitado[i].first.idf == comp && visitado[i].second == true) {
            return true;
        }
    }
    return false;
}


void CGraph::CaminoEuleriano() {
    int ini = verificacion();
    if (ini == -1) {
        return;
    }
    stack<CEdge> aristas;
    vector<char> camino;
    vector<pair<CEdge, bool>> visitado;
    int idf = 0;
    for (int i = 0; i < nodes.size(); i++) {
        for (auto& e : nodes[i].edges) {

            e.idf = idf;
            if (i == ini) {
                aristas.push(e);
            }
            visitado.push_back(make_pair(e,false));
            
            idf++;

        }

    }

    camino.push_back(nodes[ini].value);

    while (!aristas.empty()) {
        ini = aristas.top().id_node;
        int id = aristas.top().idf;
        if (verificador_rep(visitado, id)) {
            aristas.pop();
        }
        else {
            aristas.pop();
            visitado[id].second = true;
            camino.push_back(nodes[ini].value);
            for (auto e : nodes[ini].edges) {
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
    g.InsEdge(0, 3, 3);
    g.InsEdge(0, 4, 23);
    g.InsEdge(1, 0, 9);
    g.InsEdge(2, 1, 20);
    g.InsEdge(3, 1, 7);
    g.InsEdge(3, 2, 37);
    g.InsEdge(4, 3, 79);

    g.Print();
    g.CaminoEuleriano();
}
