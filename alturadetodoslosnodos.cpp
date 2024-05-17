#include <iostream>
#include <stack>
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
    void Print3(vector<pair<CBinNode*, int>> guard);
    void altura_nodos(vector<pair<CBinNode*, int>>& guard, CBinNode* ptr, CBinNode* ptr2, int altura_node );

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


void CBinTree::altura_nodos(vector<pair<CBinNode*, int>>& guard, CBinNode* ptr, CBinNode* ptr2, int altura_node) {
    if (!ptr && !ptr2) return;
    altura_node = altura_node + 1;
    if (ptr == m_root && ptr2 == m_root) {
        guard.push_back(make_pair(ptr, altura_node));
        altura_nodos(guard, ptr->nodes[0], ptr2->nodes[1], altura_node);
        ptr = ptr->nodes[0];
        ptr2 = ptr2->nodes[1];
    }
    else if (ptr == nullptr && ptr2 != nullptr) {
        ptr = ptr2;
        guard.push_back(make_pair(ptr2, altura_node)); 
        altura_nodos(guard, ptr->nodes[0], ptr->nodes[1], altura_node);
    }
    else if (ptr != nullptr && ptr2 == nullptr) {
        ptr2 = ptr;
        guard.push_back(make_pair(ptr, altura_node));
        altura_nodos(guard, ptr->nodes[0], ptr->nodes[1], altura_node);
    }
    else {
        if (ptr != nullptr) {
            guard.push_back(make_pair(ptr, altura_node));
        }
        if (ptr2 != nullptr) {
            guard.push_back(make_pair(ptr2, altura_node));
        }
        altura_nodos(guard, ptr->nodes[0], ptr->nodes[1], altura_node);
        altura_nodos(guard, ptr2->nodes[0], ptr2->nodes[1], altura_node);
    }
}

void CBinTree::Print3(vector<pair<CBinNode*, int>> guard) {
    int a = 0;
    altura_nodos(guard, m_root, m_root, a);
    int temp = 0;
    for (size_t i = 0; i < guard.size(); i++) {
        CBinNode* node = guard[i].first;
        int val = guard[i].second;
        cout << node->value << endl;
        cout << " altura: " << val << endl;
    }

}



int main()
{
    CBinTree t;
    t.Insert(70);
    t.Insert(50);
    t.Insert(90);
    t.Insert(30);
    t.Insert(60);
    t.Insert(80);
    t.Insert(110);

    vector<pair<CBinNode*, int>> BV;
    t.Print3(BV);

}
