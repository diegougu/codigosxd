
#include <iostream>
#include <queue>
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
    void Print();
    void ancestros_en_comun(int x, int y);
private:
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

void CBinTree::ancestros_en_comun(int x, int y) {
    vector<int> ruta_x;
    vector<int> ruta_y;


    CBinNode** p = &m_root;
    CBinNode** q = &m_root;

    for (; *p; p = &((*p)->nodes[(*p)->value < x])) {
        if ((*p)->value != x) {
            ruta_x.push_back((*p)->value);
        }
    }

    for (; *q; q = &((*q)->nodes[(*q)->value < y])) {
        if ((*q)->value != y) {
            ruta_y.push_back((*q)->value);
        }

    }


    for (int i = 0; i < ruta_x.size() && i < ruta_y.size(); i++) {
        if (ruta_x[i] == ruta_y[i]) {
            cout << ruta_x[i] << endl;
        }
    }
}



int main()
{
    CBinTree t;

    t.Insert(20);
    t.Insert(10);
    t.Insert(30);
    t.Insert(5);
    t.Insert(1);
    t.Insert(40);
    t.Insert(29);

    t.Print();
    cout << endl;
    t.ancestros_en_comun(29,1);
}
