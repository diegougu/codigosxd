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
    void Inorder_sin_recursividad();
    void Print();
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




void CBinTree::Inorder_sin_recursividad() {
    stack<pair<CBinNode*, int>> destino;
    CBinNode* record = m_root;


    for (; record; record = record->nodes[0]) {
        destino.push(make_pair(record, 1));
    }

    while (!destino.empty()) {
        pair<CBinNode*, int> actual = destino.top();
        CBinNode* nodeact = actual.first;
        int valoract = actual.second;

        if (nodeact->nodes[0] == nullptr && nodeact->nodes[1] == nullptr ) {
            cout << nodeact->value << " ";
            destino.pop();
        }
        else if (nodeact->nodes[0] != nullptr && nodeact->nodes[1] == nullptr) {
            cout << nodeact->value << " ";
            destino.pop();
        }

        else if (nodeact->nodes[1] != nullptr ) {
            cout << nodeact->value << " ";
            destino.pop();
            CBinNode* alterrecord = nodeact->nodes[1];
            for (; alterrecord; alterrecord = alterrecord->nodes[0]) {
                destino.push(make_pair(alterrecord, 1));
            }
            
        }
        
    }
}



int main()
{
    CBinTree t;
    t.Insert(51);
    t.Insert(33);
    t.Insert(11);
    t.Insert(42);
    t.Insert(77);
    t.Insert(61);
    t.Insert(84);
    t.Insert(36);
    t.Insert(65);

    t.Print();

    cout << "Inorder sin recursividad :" << endl;

    t.Inorder_sin_recursividad();

}
