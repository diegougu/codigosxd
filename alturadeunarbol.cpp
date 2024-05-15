#include <iostream>
#include <stack>
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
    void Print();
    void printaltura(stack<int> nodesarbl);
private:
    void altura(CBinNode* n, stack<int>& nodesarbl);
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


void CBinTree::altura(CBinNode* n, stack<int>& nodesarbl) {
    if (!n) return;
    altura(n->nodes[0], nodesarbl);
    if (n->nodes[0] == nullptr && n->nodes[1] == nullptr) {
        nodesarbl.push(n->value);

    }
    altura(n->nodes[1], nodesarbl);
   
}


void CBinTree::printaltura(stack<int> nodesarbl) {
    altura(m_root, nodesarbl);
    int alt = 0;
    int temp = 0;

    while (!nodesarbl.empty()) {
        int iterator = nodesarbl.top();
        for (CBinNode** record = &m_root; *record; record = &((*record)->nodes[(*record)->value < iterator]), temp++);
        if (temp > alt) {
            alt = temp;
            temp = 0;

        }
        else {
            temp = 0;
        }

        nodesarbl.pop();
    }

    cout << "la altura del arbol es: " << alt << endl;

}

int main()
{
    CBinTree t;
    t.Insert(55);
    t.Insert(35);
    t.Insert(77);
    t.Insert(21);
    t.Insert(41);
    t.Insert(61);
    t.Insert(92);
    t.Insert(65);


    t.Print();
    stack<int> con;
    t.printaltura(con);



}
