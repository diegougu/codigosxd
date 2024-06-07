#include <vector>
#include <iostream>
#include <string>
using namespace std;

#define SEPARADOR -99

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
    void suma_raiz_hoja();
private:
    bool Find(int x, CBinNode**& p);
    void camino(CBinNode* n, vector<int>& valores);
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


void CBinTree::camino(CBinNode* n, vector<int>& valores) {
    if (!n) return;
    camino(n->nodes[0], valores);

    if (n->nodes[0] == nullptr && n->nodes[1] == nullptr) {
        CBinNode** p = &m_root;
        for (; *p; p = &((*p)->nodes[(*p)->value < n->value])) {
            valores.push_back((*p)->value);
        }
        valores.push_back(SEPARADOR);
    }

    camino(n->nodes[1], valores);
}

void CBinTree::suma_raiz_hoja() {
    vector<int> valores;
    camino(m_root, valores);
    vector<int> newvalues;
    string concatenar;
    for (size_t i = 0; i < valores.size(); i++) {
        if (valores[i] != SEPARADOR) {
            cout << valores[i] << "->";
            int acu = valores[i];
            string a = to_string(acu);
            concatenar = concatenar + a;
        }        
        else if (valores[i] == SEPARADOR) {
            int add = stoi(concatenar);
            newvalues.push_back(add);
            cout << " valor: " << add << endl;
            concatenar = "";
        }
    }

    cout << endl;

    long long suma = 0;
    for (size_t i = 0; i < newvalues.size(); i++) {
        cout << newvalues[i] << " + ";
        suma = suma + newvalues[i];
    }

    cout << endl;
    cout << "suma: " << suma;
}

int main()
{
    CBinTree t;
    t.Insert(9);
    t.Insert(5);
    t.Insert(10);
    t.Insert(3);
    t.Insert(7);
    t.Insert(6);
    t.Insert(8);
    t.Insert(20);
    t.Print();

    t.suma_raiz_hoja();

}
