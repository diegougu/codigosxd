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
    void Print2(vector<int> valores);

private:
    bool Find(int x, CBinNode**& p);
    CBinNode** Rep(CBinNode** p);
    void InOrder(CBinNode* n);
    void Filas(vector<int>& valores, CBinNode* ptr, CBinNode* ptr2, CBinNode* ptr3, CBinNode* ptr4);

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


void CBinTree::Filas(vector<int>& valores, CBinNode* ptr, CBinNode* ptr2, CBinNode* ptr3, CBinNode* ptr4) {
    if (!ptr && !ptr2) return;

    if (ptr == m_root && ptr2 == m_root) {
        valores.push_back(ptr->value);
        Filas(valores, ptr->nodes[0], ptr2->nodes[1], ptr3, ptr4);
        ptr = ptr->nodes[0];
        ptr2 = ptr2->nodes[1];
    }

    else {
        if (ptr != nullptr) {
            valores.push_back(ptr->value);
        }
        
        if(ptr3 != nullptr){
            valores.push_back(ptr3->value);
        }
        
        if (ptr2 != nullptr) {
            valores.push_back(ptr2->value);
        }
        
        if(ptr4 != nullptr){
            valores.push_back(ptr4->value);

        }
        if(ptr == nullptr && ptr3 != nullptr){
            ptr = ptr3;
        }
        
        if(ptr != nullptr && ptr3 == nullptr){
            ptr3 = ptr;
        }
        
        if(ptr2 == nullptr && ptr4 != nullptr){
            ptr2 = ptr4;
        }
        
        if(ptr2 != nullptr && ptr4 == nullptr){
            ptr4 = ptr2;
        }
        
        Filas(valores, ptr->nodes[0], ptr2->nodes[0], ptr->nodes[1], ptr2->nodes[1]);
    }
}



void CBinTree::Print2(vector<int> valores) {
    CBinNode* ptr3 = nullptr;
    CBinNode* ptr4 = nullptr;

    Filas(valores, m_root, m_root, ptr3, ptr4);


    for (size_t i = 0; i < valores.size(); ++i) {
        cout << valores[i] << " ";
    }
}


int main()
{
    CBinTree t;
    t.Insert(55);
    t.Insert(35);
    t.Insert(77);
    t.Insert(20);
    t.Insert(1);
    t.Insert(200);
    t.Insert(300);
    t.Print();

    vector<int> val;

    t.Print2(val);
}
