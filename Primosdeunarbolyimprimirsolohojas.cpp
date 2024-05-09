
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
    void Print2();
    void sobrinos_de(int x);
    void primos_de(int x);
private:
    bool Find(int x, CBinNode**& p);
    CBinNode** Rep(CBinNode** p);
    void InOrder(CBinNode* n);
    void print_hojas(CBinNode* x);
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



void CBinTree::primos_de(int x) {
    CBinNode** p = &m_root;
    CBinNode* q = nullptr;
    CBinNode* r = nullptr;

    if ((*p)->value == x) {
        cout << "la raiz no tiene primos" << endl;
    }

    for (; *p; p = &((*p)->nodes[(*p)->value < x])) {
        q = (*p)->nodes[0];
        r = (*p)->nodes[1];


        if (q->nodes[0]->value == x || q->nodes[1]->value == x) {
            if (r->nodes[0] != nullptr) {
                cout << r->nodes[0]->value << endl;
            }
            if (r->nodes[1] != nullptr) {
                cout << r->nodes[1]->value << endl;
            }
            return;
        }

        if (r->nodes[0]->value == x || r->nodes[1]->value == x) {
            if (q->nodes[0] != nullptr) {
                cout << q->nodes[0]->value << endl;
            }
            if (q->nodes[1] != nullptr) {
                cout << q->nodes[1]->value << endl;
            }
            return;
        }

    }

}

void CBinTree::sobrinos_de(int x) {
    CBinNode** p = &m_root;
    CBinNode* cero = nullptr;
    CBinNode* uno = nullptr;

    if ((*p)->value == x) {
        cout << "la raiz no tiene sobrinos " << endl;
        return;
    }

    for (; *p; p = p = &((*p)->nodes[(*p)->value < x])) {
        cero = (*p)->nodes[0];
        uno = (*p)->nodes[1];
        if (uno->value == x) {
            CBinNode* a = cero->nodes[0];
            CBinNode* b = cero->nodes[1];
            if (a != nullptr) {
                cout << a->value << endl;
            }
            if (b != nullptr) {
                cout << b->value << endl;
            }
            return;
        }
        else if (cero->value == x) {
            CBinNode* a = uno->nodes[0];
            CBinNode* b = uno->nodes[1];
            if (a != nullptr) {
                cout << a->value << endl;
            }
            if (b != nullptr) {
                cout << b->value << endl;
            }
            return;
        }
    }
}


void CBinTree::print_hojas(CBinNode* x) {
    if (!x) return;
    print_hojas(x->nodes[0]);
    if (x->nodes[0] == nullptr && x->nodes[1] == nullptr) {
        cout << x->value << " ";
    }
    print_hojas(x->nodes[1]);



}


void CBinTree::Print2() {
    print_hojas(m_root);
    cout << endl;
}



int main()
{
    CBinTree t;
    t.Insert(40);
    t.Insert(20);
    t.Insert(90);
    t.Insert(15);
    t.Insert(30);
    t.Insert(88);
    t.Insert(110);
    t.Insert(14);
    t.Insert(17);
    t.Insert(29);
    t.Insert(33);
    t.Insert(70);
    t.Insert(89);
    t.Insert(100);
    t.Insert(200);


    t.Print();

    cout << endl;

    t.primos_de(89);
}
