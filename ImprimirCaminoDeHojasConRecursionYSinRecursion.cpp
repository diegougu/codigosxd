#include <iostream>
#include <stack>
#include <vector>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////

struct CBinNode
{
    CBinNode(int _v)
    {
        value = _v; nodes[0] = nodes[1] = 0;
    }
    int value;
    CBinNode* nodes[2];
};

////////////////////////////////////////////////////////////////////////////////////////////////////////

class CBinTree
{
public:
    CBinTree();
    ~CBinTree();
    bool Insert(int x);
    bool Remove(int x);
    void printcam();
    void Print();
    void printcamsinR();


private:
    void print_camino_hojas(CBinNode* p);
    bool Find(int x, CBinNode**& p);
    CBinNode** Rep(CBinNode** p);
    void InOrder(CBinNode* n);
    CBinNode* m_root;
    bool m_b;
};

CBinTree::CBinTree()
{
    m_root = 0;
    m_b = 0;
}

CBinTree::~CBinTree()
{
    // ?
}

bool CBinTree::Find(int x, CBinNode**& p)
{
    for (p = &m_root;
        *p && (*p)->value != x;
        p = &((*p)->nodes[(*p)->value < x]));
    return *p && (*p)->value == x;
}

bool CBinTree::Insert(int x)
{
    CBinNode** p;
    if (Find(x, p)) return 0;
    *p = new CBinNode(x);
    return 0;
}
bool CBinTree::Remove(int x)
{
    CBinNode** p;
    if (!Find(x, p)) return 0;
    if ((*p)->nodes[0] && (*p)->nodes[1])
    {
        CBinNode** q = Rep(p);
        (*p)->value = (*q)->value;
        p = q;
    }
    CBinNode* t = *p;
    *p = (*p)->nodes[(*p)->nodes[0] == 0];
    delete t;
    return 1;
}

CBinNode** CBinTree::Rep(CBinNode** q)
{
    m_b = !m_b;
    q = &((*q)->nodes[!m_b]);
    while ((*q)->nodes[m_b])
        q = &((*q)->nodes[m_b]);
    return q;
}

void CBinTree::InOrder(CBinNode* n)
{
    if (!n) return;
    InOrder(n->nodes[0]);
    cout << n->value << " ";
    InOrder(n->nodes[1]);
}

void CBinTree::Print()
{
    InOrder(m_root);
    cout << endl;
}

void CBinTree::printcam() {
    print_camino_hojas(m_root);
    cout << endl;
}

void CBinTree::print_camino_hojas(CBinNode* p) {

    if (p->nodes[0] == nullptr && p->nodes[1] == nullptr) {
        CBinNode** camino = &m_root;

        for (; *camino; camino = &((*camino)->nodes[(*camino)->value < p->value])) {
            cout << (*camino)->value << "->";
        }
        cout << endl;
        return;
    }
    print_camino_hojas(p->nodes[0]);
    print_camino_hojas(p->nodes[1]);


}



void CBinTree::printcamsinR() {
    CBinNode* n = m_root;
    stack<CBinNode*> q1;
    vector<CBinNode*> q2;


    q1.push(n);

    while (!q1.empty()) {
        n = q1.top();
        q1.pop();
        if (n->nodes[0] != nullptr) {
            q1.push(n->nodes[0]);
        }

        if (n->nodes[1] != nullptr) {
            q1.push(n->nodes[1]);
        }

        if (n->nodes[0] == nullptr && n->nodes[1] == nullptr) {
            q2.push_back(n);
        }

    }

    for (int i = 0; i < q2.size(); ++i) {
        n = q2[i];
        for (CBinNode** camino = &m_root; *camino; camino = &((*camino)->nodes[(*camino)->value < n->value])) {
            cout << (*camino)->value << "->";
        }
        cout << endl;
    }



}

int main()
{
    CBinTree t;
    t.Insert(60);
    t.Insert(80);
    t.Insert(30);
    t.Insert(20);
    t.Insert(40);
    t.Insert(70);
    t.Insert(100);

    t.printcam();

    cout << "print cam sin recursion: " << endl;

    t.printcamsinR();

}
