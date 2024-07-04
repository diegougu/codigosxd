#include <iostream>
#include <forward_list>
#include <vector>
#include <stack>
#include <deque>
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
    void DFS();
    vector<CNode> nodes;
private:
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

void CGraph::DFS() {
    vector<pair<CNode, bool>> visited;
    stack<CNode> guardar;
    deque<CNode> pasar;
    int ini = 0;
    for (size_t i = 0; i < nodes.size(); i++) {
        visited.push_back(make_pair(nodes[i], false));
    }
    guardar.push(nodes[ini]);

    while (!guardar.empty()) {
        CNode temp = guardar.top();
        guardar.pop();
        cout << temp.value << " ";
        if (visited[temp.id_node].second == false) {
            visited[temp.id_node].second = true;
            for (auto e : nodes[temp.id_node].edges) {
                CNode p = nodes[e.id_node];
                if (visited[p.id_node].second == false) {
                    guardar.push(p);
                }
            }
        }
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
    g.InsNode('F');
    g.InsNode('G');
    g.InsNode('H');

    g.InsEdge(0, 1, 10);
    g.InsEdge(0, 2, 9);
    g.InsEdge(1, 3, 8);
    g.InsEdge(3, 4, 7);
    g.InsEdge(3, 5, 6);
    g.InsEdge(2, 6, 5);
    g.InsEdge(2, 7, 4);

    g.DFS();
    return 0;
}
