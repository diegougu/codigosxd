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
    void Print1();
    void Print2();
    void Print3();
private:
    bool Find(int x, CBinNode**& p);
    CBinNode** Rep(CBinNode** p);
    void PostOrder(CBinNode* p);
    void Preorder(CBinNode* n);
    void Reverse(CBinNode* n);
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


void CBinTree::Reverse(CBinNode* n) {
    if (!n) return;

    Reverse(n->nodes[1]);
    cout << n->value << " ";
    Reverse(n->nodes[0]);
}



void CBinTree::Print1() {
    Reverse(m_root);
    cout << endl;
}


void CBinTree::PostOrder(CBinNode* p) {
    if (!p) return;
    PostOrder(p->nodes[0]);
    PostOrder(p->nodes[1]);
    cout << p->value << " ";


}


void CBinTree::Print2() {
    PostOrder(m_root);
    cout << endl;
}


void CBinTree::Preorder(CBinNode* n) {
    if (!n) return;

    cout << n->value << " ";
    Preorder(n->nodes[0]);
    Preorder(n->nodes[1]);

}

void CBinTree::Print3() {
    Preorder(m_root);
    cout << endl;
}

int main()
{
    CBinTree t;
    t.Insert(45);
    t.Insert(23);
    t.Insert(65);
    t.Insert(2);
    t.Insert(38);
    t.Insert(7);
    t.Insert(52);
    t.Insert(96);
    t.Insert(48);

    cout << "Postorder" << endl;
    t.Print2();

    cout << "Preorder" << endl;
    t.Print3();

    cout << "Reverse " << endl;
    t.Print1();
}
