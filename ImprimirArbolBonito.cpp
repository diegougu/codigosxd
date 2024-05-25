#include <queue>
#include <iostream>
#include <stack>
#include <cmath>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////

#define VALORNULL -99

struct CBinNode
{
    CBinNode(int _v)
    {
        value = _v; nodes[0] = nodes[1] = 0;
    }
    int altura;
    int value;
    int size;
    CBinNode* nodes[2];
};

////////////////////////////////////////////////////////////////////////////////////////////////////////

class CBinTree
{
public:
    CBinTree();
    ~CBinTree();
    bool Insert(int x);
    void Print();
    void Print2();
    void printaltura(stack<int> nodesarbl, int& alturaf);
private:
    void imprimir_arbol(CBinNode* n);
    bool Find(int x, CBinNode**& p);
    void InOrder(CBinNode* n);
    int inputsize(CBinNode* n, int lvl);
    void altura(CBinNode* n, stack<int>& nodesarbl);
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
    n->altura = lvl;
    return n->size;
}


void CBinTree::imprimir_arbol(CBinNode* n) {
    queue<CBinNode*> valores;
    stack<int> st;

    valores.push(n);
    int post_alt = n->altura;
    int current_alt = 0;
    int espaciado = 0;
    int altura_limite = 0;
    int root_size = 16;


    printaltura(st, altura_limite);


    while (!valores.empty()) {
        
        CBinNode* current = valores.front();
        
        current_alt = current->altura;

        if (current_alt >= altura_limite) {
            break;
        }

        if (current_alt != post_alt && current != nullptr) {
            cout << endl;
            root_size = root_size / 2;
        }
        int mitad = ceil(root_size/ 2);
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



int main()
{
    CBinTree t;

    t.Insert(5);
    t.Insert(8);
    t.Insert(4);
    t.Insert(3);
    t.Insert(6);
    t.Insert(7);

    t.Print2();

}
