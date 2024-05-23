#include <queue>
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
    void Print();
    void Print2();
private:
    void printpornivel(CBinNode* n);
    bool Find(int x, CBinNode**& p);
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



void CBinTree::printpornivel(CBinNode* n) {
    queue<CBinNode*> valores;
    valores.push(n);
    valores.push(nullptr);

    while (!valores.empty()) {
        CBinNode* current = valores.front();

        if (current != nullptr) {
            cout << current->value << " ";
            if (current->nodes[0] != nullptr) {
                valores.push(current->nodes[0]);
            }
            if (current->nodes[1] != nullptr) {
                valores.push(current->nodes[1]);
            }

            valores.push(nullptr);

            valores.pop();
        }
        else if (current == nullptr) {
            valores.pop();
        }

    }
}


void CBinTree::Print2() {
    printpornivel(m_root);
    cout << endl;
}


int main()
{
    CBinTree t;
    
    t.Insert(70);
    t.Insert(50);
    t.Insert(100);
    t.Insert(20);
    t.Insert(24);
    t.Insert(90);
    t.Insert(200);
    t.Insert(80);
    t.Insert(400);
    t.Insert(500);

    t.Print2();
}
