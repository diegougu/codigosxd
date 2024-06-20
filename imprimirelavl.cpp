#include <iostream>
#include <queue>
#include <stack>
#include <cmath>
#include <vector>

#define VALORNULL -99

using namespace std;


struct CBinNode
{
    CBinNode(int _v)
    {
        value = _v; nodes[0] = nodes[1] = 0;
    }
    int value;
    int altura_profundidad = 0;
    int altura_balanceo;
    int altura_dos;
    int size;
    CBinNode* nodes[2];
};

class CBinTree
{
public:
    CBinTree();
    bool Insert(int x);
    bool Remove(int x);
    void Print();
    void Print2();
    void printaltura(stack<int> nodesarbl, int& alturaf);

private:
    bool Find(int x, CBinNode**& p);
    int alturaP(CBinNode* n);
    void calcular_alturaB(CBinNode* n);
    void recalcular_altura_tree(CBinNode* n);
    void avl(vector<CBinNode*> camino);

    void imprimir_arbol(CBinNode* n);
    int inputsize(CBinNode* n, int lvl);
    void altura(CBinNode* n, stack<int>& nodesarbl);


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


void CBinTree::altura(CBinNode* n, stack<int>& nodesarbl) {
    if (!n) return;
    altura(n->nodes[0], nodesarbl);
    if (n->nodes[0] == nullptr && n->nodes[1] == nullptr) {
        nodesarbl.push(n->value);

    }
    altura(n->nodes[1], nodesarbl);
}

void CBinTree::printaltura(stack<int> nodesarbl, int& altura_f) {
    altura(m_root, nodesarbl);
    altura_f = 0;
    int temp = 0;

    while (!nodesarbl.empty()) {
        int iterator = nodesarbl.top();
        for (CBinNode** record = &m_root; *record; record = &((*record)->nodes[(*record)->value < iterator]), temp++);
        if (temp > altura_f) {
            altura_f = temp;
            temp = 0;

        }
        else {
            temp = 0;
        }

        nodesarbl.pop();
    }
}


int CBinTree::inputsize(CBinNode* n, int lvl) {
    if (!n) return 1;
    n->size = inputsize(n->nodes[0], lvl + 1) + 1 + inputsize(n->nodes[1], lvl + 1);
    n->altura_dos = lvl;
    return n->size;
}

void CBinTree::imprimir_arbol(CBinNode* n) {
    queue<CBinNode*> valores;
    stack<int> st;

    valores.push(n);
    int post_alt = n->altura_dos;
    int current_alt = 0;
    int espaciado = 0;
    int altura_limite = 0;
    int root_size = 32;


    printaltura(st, altura_limite);


    while (!valores.empty()) {

        CBinNode* current = valores.front();

        current_alt = current->altura_dos;

        if (current_alt >= altura_limite) {
            break;
        }

        if (current_alt != post_alt && current != nullptr) {
            cout << endl;
            root_size = root_size / 2;
        }
        int mitad = ceil(root_size / 2);
        int mitad2 = ceil(root_size / 2);

        espaciado = mitad;


        for (int i = 0; i < mitad + espaciado; ++i) {
            cout << " ";
        }

        if (current->value == VALORNULL) {
            cout << " ";
        }
        else {
            cout << current->value;

        }

        for (int i = 0; i < mitad2 + espaciado; ++i) {
            cout << " ";
        }

        if (current->nodes[0] == nullptr) {
            CBinNode* n = new CBinNode(VALORNULL);
            current->nodes[0] = n;
            int a = 0;
            inputsize(m_root, a);

        }
        valores.push(current->nodes[0]);
        if (current->nodes[1] != nullptr) {
            valores.push(current->nodes[1]);
        }
        else if (current->nodes[1] == nullptr) {
            CBinNode* n = new CBinNode(VALORNULL);
            current->nodes[1] = n;
            int a = 0;
            inputsize(m_root, a);
            valores.push(current->nodes[1]);
        }



        valores.pop();
        post_alt = current_alt;
    }
}

void CBinTree::Print2() {
    int a = 0;
    inputsize(m_root, a);
    imprimir_arbol(m_root);


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
            if (p->altura_balanceo = 2 && p->nodes[1] != nullptr && p->nodes[1]->altura_balanceo == 1) {

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
                    if (prev->nodes[0] == p) {
                        prev->nodes[0] = b;

                    }
                    else if (prev->nodes[1] == p) {
                        prev->nodes[1] = b;

                    }
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
                    if (prev->nodes[0] == p) {
                        prev->nodes[0] = b;

                    }
                    else if (prev->nodes[1] == p) {
                        prev->nodes[1] = b;

                    }
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
                    if (prev->nodes[0] == p) {
                        prev->nodes[0] = b;

                    }
                    else if (prev->nodes[1] == p) {
                        prev->nodes[1] = b;

                    }
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
                    if (prev->nodes[0] == p) {
                        prev->nodes[0] = b;

                    }
                    else if (prev->nodes[1] == p) {
                        prev->nodes[1] = b;

                    }
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


int main()
{
    CBinTree t;
    t.Insert(1);
    t.Insert(8);
    t.Insert(9);
    t.Insert(4);
    t.Insert(7);
    t.Insert(6);
    t.Insert(2);
    t.Insert(3);
    t.Print();
    t.Print2();
}
