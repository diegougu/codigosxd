#include <iostream>
#include <forward_list>
#include <vector>
#include <deque>
#include <tuple>
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
    bool find_arr_rep(tuple<int, int, char > rep, deque<tuple<int, int, char >> arristas_visitadas);
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

bool CGraph::find_arr_rep(tuple<int, int, char > rep, deque<tuple<int, int, char >> arristas_visitadas) {
    if (arristas_visitadas.empty()) {
        return false;
    }
    for (size_t i = 0; i < arristas_visitadas.size(); i++) {
        int arr = get<0>(rep);
        int val = get<1>(rep);
        char a = get<2>(rep);

        tuple<int, int, char > s = arristas_visitadas[i];
        int arr2 = get<0>(s);
        int val2 = get<1>(s);
        char a2 = get<2>(s);

        if (arr == arr2 && val == val2 && a == a2) {
            return true;
        }

    }
    return false;
}


void CGraph::camino_euleriano() {
    int ini = 0;
    deque<tuple<int, int, char >> arristas_visitadas;
    vector<char> camino;
    deque<tuple<int, int , char>> arristas;
    camino.push_back(nodes[ini].value);
    for (auto& e : nodes[ini].edges) {
        int arr = e.id_node;
        int val = e.value;
        char a = nodes[arr].value;
        arristas.push_front(make_tuple(arr, val, a));
    }

    while (!arristas.empty()) {
        tuple<int, int, char> ite = arristas.front();
        int arr = get<0>(ite);
        int val = get<1>(ite);
        char node_char = get<2>(ite);
        ini = arr;
        
        if (find_arr_rep(ite, arristas_visitadas)) {
            arristas.pop_front();
        }
        else {
            camino.push_back(node_char);
            arristas_visitadas.push_back(ite);
            arristas.pop_front();
            for (auto& e : nodes[ini].edges) {
                int arr = e.id_node;
                int val = e.value;
                char a = nodes[arr].value;
                arristas.push_front(make_tuple(arr, val, a));
            }
        }

    }
    for (size_t i = 0; i < camino.size(); i++) {
        cout << camino[i] << "->";
    }


}




int main()
{
    CGraph g;
    g.InsNode('B');    g.InsNode('A');
    g.InsNode('G');    g.InsNode('C');

    g.InsEdge(0, 1, 3);
    g.InsEdge(0, 2, 5);
    g.InsEdge(1, 2, 7);
    g.InsEdge(2, 3, 4);
    g.InsEdge(3, 0, 20);


    g.Print();
    g.camino_euleriano();



    return 0;
}
