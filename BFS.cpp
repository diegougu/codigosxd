#include <iostream>
#include <forward_list>
#include <queue>
#include <vector>
#include <deque>;
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
    void BFS();
    void Print();
    vector<CNode> nodes;
private:
    bool verificador(vector<pair<CNode, bool>> nodos_pas, CNode comp);
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


bool CGraph::verificador(vector<pair<CNode, bool>> nodos_pas, CNode comp) {
    int id = comp.id_node;

    if (nodos_pas[id].first.id_node == comp.id_node && nodos_pas[id].second == true) {
        return true;
    }
    return false;
}


void CGraph::BFS() {
    int inicio = 0;
    queue<CNode> BFS_CAM;
    vector<pair<CNode, bool>> nodos_pas;
    deque<CNode> temp;
    for (size_t i = 0; i < nodes.size(); i++) {
        nodos_pas.push_back(make_pair(nodes[i], false));
    }

    BFS_CAM.push(nodes[inicio]);
    nodos_pas[inicio].second = true;


    while (!BFS_CAM.empty()) {
        CNode actual = BFS_CAM.front();
        BFS_CAM.pop();
        cout << actual.value << " ";

        for (auto e : actual.edges) {
            CNode p = nodes[e.id_node];
            if (!verificador(nodos_pas, p)) {
                temp.push_front(p);
                nodos_pas[p.id_node].second = true;
            }
        }

        for (size_t i = 0; i < temp.size(); i++) {
            BFS_CAM.push(temp[i]);
        }

        temp.clear();


    }

}

int main()
{
    CGraph g;
    g.InsNode('A');
    g.InsNode('B');
    g.InsNode('C');
    g.InsNode('D');
    g.InsNode('E');
    g.InsEdge(0, 1, 10);
    g.InsEdge(0, 2, 9);
    g.InsEdge(1, 3, 6);
    g.InsEdge(2, 3, 30);
    g.InsEdge(2, 4, 60);
    g.InsEdge(4, 3, 1);

    g.BFS();



    return 0;
}
