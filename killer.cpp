#include <iostream>
#include <vector>
#include <algorithm>
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
    void killer(int k);
    void Print();
private:
    void caminofun(CBinNode* n, vector<pair<CBinNode*, int>>& caminos, int x);
    bool Find(int x, CBinNode**& p);
    CBinNode** Rep(CBinNode** p);
    void InOrder(CBinNode* n);
    void elem(CBinNode* n, vector<int>& borrar);
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

void CBinTree::caminofun(CBinNode* n, vector<pair<CBinNode*, int>>& caminos, int x) {
    if (!n) return;

    caminofun(n->nodes[0], caminos, x);
    if (n->nodes[0] == nullptr && n->nodes[1] == nullptr) {
        x = 0;
        CBinNode** m = &m_root;
        for (; *m; m = &((*m)->nodes[(*m)->value < n->value])) {
            if (*m != nullptr) {
                x = x + (*m)->value;
            }
        }
        caminos.push_back(make_pair(n, x));

        x = 0;
    }
    caminofun(n->nodes[1], caminos, x);

}
bool compararPorSecond(const pair<CBinNode*, int>& a, const pair<CBinNode*, int>& b) {
    return a.second < b.second;
}

void CBinTree::elem(CBinNode* n, vector<int>& borrar) {
    if (!n) return;
    elem(n->nodes[0], borrar);
    borrar.push_back(n->value);
    elem(n->nodes[1], borrar);
}

void CBinTree::killer(int k) {
    vector<pair<CBinNode*, int>> caminos;
    int x = 0;
    caminofun(m_root, caminos, x);
    sort(caminos.begin(), caminos.end(), compararPorSecond);
    pair<CBinNode*, int >& ultimo = caminos.back();
    int valor_mayor = ultimo.second;

    if (k > valor_mayor) {
        vector<int> borrar;
        elem(m_root, borrar);
        for (size_t i = 0; i < borrar.size(); i++) {
            Remove(borrar[i]);
        }
        return;
    }

    for (size_t i = 0; i < caminos.size(); i++) {
        if (k > caminos[i].second) {
            CBinNode* n = caminos[i].first;
            CBinNode* m = caminos[i + 1].first;
            int actual_valor = caminos[i].second;
            int m_valor = caminos[i + 1].second;
            vector<int> vaciar;
            CBinNode** b1 = &m_root;
            CBinNode** b2 = &m_root;
            while (*b1) {
                if ((*b1)->value != (*b2)->value) {
                    vaciar.push_back((*b1)->value);
                }
                if ((*b2)->nodes[0] != nullptr || (*b2)->nodes[1] != nullptr) {
                    b2 = &((*b2)->nodes[(*b2)->value <= m->value]);
                }
                b1 = &((*b1)->nodes[(*b1)->value <= n->value]);
            }
            for (size_t j = 0; j < vaciar.size(); j++) {
                Remove(vaciar[j]);
            }


        }
    }
}


int main()
{
    CBinTree t;
    t.Insert(10);
    t.Insert(8);
    t.Insert(15);
    t.Insert(6);
    t.Insert(9);
    t.Insert(13);
    t.Insert(20);
    t.Insert(5);
    t.Insert(7);
    t.Print();
    t.killer(100);
    t.Print();

}
