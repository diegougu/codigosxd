#include <iostream>
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
    void flipbinarytree();
private:
    bool Find(int x, CBinNode**& p);
    void flepi(CBinNode* n);
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

void CBinTree::flepi(CBinNode* n) {
    if (!n) return;
    flepi(n->nodes[0]);


    if (n == m_root) {
        return;
    }

    if (n->nodes[0] == nullptr && n->nodes[1] == nullptr) {

        CBinNode** p = &m_root;
        for (; *p && (*p)->nodes[0]->value != n->value; p = &((*p)->nodes[(*p)->value < n->value]));
        n->nodes[1] = *p;
        n->nodes[0] = (*p)->nodes[1];
        (*p)->nodes[0] = nullptr;
        (*p)->nodes[1] = nullptr;
        return;
    }
}

void CBinTree::flipbinarytree() {
    CBinNode* temp = m_root;
    for (; temp->nodes[0]; temp = temp->nodes[0]);
    flepi(m_root);
    m_root = temp;
}


int main()
{
    CBinTree t;
    t.Insert(30);
    t.Insert(20);
    t.Insert(70);
    t.Insert(10);
    t.Insert(25);
    t.Insert(65);
    t.Insert(85);
    t.Print();

    t.flipbinarytree();
    t.Print();


}
