#include <iostream>
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
    int altura_profundidad = 0;
    int altura_balanceo;
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

    void Print3();
    void Print2();
private:
    bool Find(int x, CBinNode**& p);
    int alturaP(CBinNode* n);
    void calcular_alturaB(CBinNode* n);
    void recalcular_altura_tree(CBinNode* n);
    void avl(vector<CBinNode*> camino);

    void Printlautra(CBinNode* n);
    void Printbalance(CBinNode* n);

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


int CBinTree::alturaP(CBinNode* n) {
    if (!n) return 0;
    int leftHeight = n->nodes[0] ? n->nodes[0]->altura_profundidad : 0;
    int rightHeight = n->nodes[1] ? n->nodes[1]->altura_profundidad : 0;
    return 1 + max(leftHeight, rightHeight);
}

void CBinTree::recalcular_altura_tree(CBinNode* n) {
    if (!n) return;
    recalcular_altura_tree(n->nodes[0]);
    recalcular_altura_tree(n->nodes[1]);

    n->altura_profundidad = alturaP(n);
}

bool CBinTree::Find(int x, CBinNode**& p)
{
    for (p = &m_root;
        *p && (*p)->value != x;
        p = &((*p)->nodes[(*p)->value < x]));
    return *p && (*p)->value == x;
}


void CBinTree::calcular_alturaB(CBinNode* n) {
    if (!n) return;

    calcular_alturaB(n->nodes[0]);
    calcular_alturaB(n->nodes[1]);

    int altura_izquierda = n->nodes[0] ? n->nodes[0]->altura_profundidad : 0;
    int altura_derecha = n->nodes[1] ? n->nodes[1]->altura_profundidad : 0;

    n->altura_balanceo = altura_derecha - altura_izquierda;
}



void CBinTree::avl(vector<CBinNode*> camino) {
    
    int fin = camino.size() - 1;
    CBinNode* p = camino[fin];

    while (true) {
        if (p->altura_balanceo == 2 || p->altura_balanceo == -2) {
            if (p->altura_balanceo = 2 &&  p->nodes[1] != nullptr && p->nodes[1]->altura_balanceo == 1) {
                
                CBinNode* b = p->nodes[1];
                CBinNode* c = p->nodes[1]->nodes[1];
                if (p == m_root) {
                    m_root = b;
                    p->nodes[1] = b->nodes[0]; //posible poner if para ver si es null o no
                    b->nodes[0] = p;
                    break;
                }
                else {
                    int previo = fin - 1;
                    CBinNode* prev = camino[previo];
                    prev->nodes[1] = b;
                    p->nodes[1] = b->nodes[0];
                    b->nodes[0] = p;
                    break;
                }
            }
            else if (p->altura_balanceo = -2 && p->nodes[0] != nullptr && p->nodes[0]->altura_balanceo == -1) {
                CBinNode* b = p->nodes[0];
                CBinNode* a = p->nodes[0]->nodes[0];
                if (p == m_root) {
                    m_root = b;
                    p->nodes[0] = b->nodes[1];
                    b->nodes[1] = p;
                    break;
                }
                else {
                    int previo = fin - 1;
                    CBinNode* prev = camino[previo];
                    prev->nodes[0] = b;
                    p->nodes[0] = b->nodes[1];
                    b->nodes[1] = p;
                    break;
                }

            }
            else if (p->altura_balanceo = -2 && p->nodes[0] != nullptr && p->nodes[0]->altura_balanceo == 1) {
                CBinNode* a = p->nodes[0];
                CBinNode* b = a->nodes[1];
                if (p == m_root) {
                    m_root = b;
                    a->nodes[1] = b->nodes[0];
                    b->nodes[0] = a;
                    p->nodes[0] = b->nodes[1];
                    b->nodes[1] = p;
                    break;
                }
                else {
                    int previo = fin - 1;
                    CBinNode* prev = camino[previo];
                    prev->nodes[0] = b;
                    a->nodes[1] = b->nodes[0];
                    b->nodes[0] = a;
                    p->nodes[0] = b->nodes[1];
                    b->nodes[1] = p;
                    break;
                }

            }
            else if (p->altura_balanceo = 2 && p->nodes[1] != nullptr && p->nodes[1]->altura_balanceo == -1) {
                CBinNode* c = p->nodes[1];
                CBinNode* b = c->nodes[0];
                if (p == m_root) {
                    m_root = b;
                    c->nodes[0] = b->nodes[1];
                    b->nodes[1] = c;
                    p->nodes[1] = b->nodes[0];
                    b->nodes[0] = p;
                    break;
                }
                else {
                    int previo = fin - 1;
                    CBinNode* prev = camino[previo];
                    prev->nodes[1] = b;
                    c->nodes[0] = b->nodes[1];
                    b->nodes[1] = c;
                    p->nodes[1] = b->nodes[0];
                    b->nodes[0] = p;
                    break;
                }
            }
        }
        if (fin == 0) break;  
        p = camino[--fin];

    }
    recalcular_altura_tree(m_root);
    calcular_alturaB(m_root);

}

void CBinTree::Printbalance(CBinNode* n) {
    if (!n) return;
    Printbalance(n->nodes[0]);
    cout << n->altura_balanceo << " ";
    Printbalance(n->nodes[1]);

}

void CBinTree::Print3() {
    Printbalance(m_root);
}

bool CBinTree::Insert(int x)
{
    CBinNode** p;
    if (Find(x, p)) return 0;
    *p = new CBinNode(x);

    CBinNode** n = &m_root;
    vector<CBinNode*> camino;
    for (; *n; n = &((*n)->nodes[(*n)->value < x])) {
        camino.push_back(*n);
        if ((*n)->value == x) {
            break;
        }
    }

    recalcular_altura_tree(m_root);
    calcular_alturaB(m_root);
    avl(camino);


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

void CBinTree::Printlautra(CBinNode* n) {
    if (!n) return;

    Printlautra(n->nodes[0]);
    cout << n->altura_profundidad << " ";
    Printlautra(n->nodes[1]);


}

void CBinTree::Print2() {
    Printlautra(m_root);
}


int main()
{
    CBinTree t;
    t.Insert(30);
    t.Insert(20);
    t.Insert(10);
    t.Insert(25);
    t.Insert(40);
    t.Insert(50);
    t.Insert(35);
    t.Insert(15);



    t.Print();
}
