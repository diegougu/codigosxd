#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
using namespace std;

mutex mtx;

struct CBinNode
{
    CBinNode(int _v)
    {
        value = _v; nodes[0] = nodes[1] = 0;
    }
    int value;
    CBinNode* nodes[2];
};

class SumTree {
public:
    void Insert(int x);
    void Print();
private:
    CBinNode* m_root = nullptr;
    vector<int> cam;
    void Inorder(CBinNode* n);
    void Find(CBinNode* n, int x);
    void Ins(int a);
    CBinNode* pos = nullptr;
};


void SumTree::Find(CBinNode* n, int x) {
    if (!n) return;
    Find(n->nodes[0], x);
    
    if (n->nodes[0] == nullptr && n->nodes[1] == nullptr && n->value > x && cam.empty()) {
        cam.push_back(x);
        pos = n;
        return;
    }

    Find(n->nodes[1], x);
}


void SumTree::Ins(int a) {
    lock_guard<mutex> lock(mtx);
    if (pos->nodes[0] == nullptr) {
        CBinNode* temp = new CBinNode(a);
        pos->nodes[0] = temp;
    }
    else {
        CBinNode* temp = new CBinNode(a);
        pos->nodes[1] = temp;

    }
}

void SumTree::Insert(int x) {
    if (m_root == nullptr) {
        CBinNode* temp = new CBinNode(x);
        m_root = temp;
    }
    else if (pos == nullptr) {
        CBinNode* temp = m_root;
        Find(temp, x);
    }
    else if (pos != nullptr && x + cam.front() == pos->value) {
        cam.push_back(x);
        int dr = cam.front();
        int iz = cam.back();
        thread der(&SumTree::Ins, this, dr);
        thread izq(&SumTree::Ins, this, iz);
        der.join();
        izq.join();

        pos = nullptr;
        cam.clear();
    }
}

void SumTree::Inorder(CBinNode* n) {
    if (!n)  return;
    Inorder(n->nodes[0]);
    cout << n->value << " ";
    Inorder(n->nodes[1]);

}

void SumTree::Print() {
    Inorder(m_root);
    cout << endl;
}

int main() {
    SumTree t;
    t.Insert(10);
    t.Insert(6);
    t.Insert(4);
    t.Insert(3);
    t.Insert(3);

    t.Print();
}
