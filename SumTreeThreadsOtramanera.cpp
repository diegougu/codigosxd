#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <queue>
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
    void ins(int v, int lado);
    CBinNode* m_root = nullptr;
    void Inorder(CBinNode* n);
    vector<int> suma_actual;
    CBinNode* actual = nullptr;
    deque<CBinNode*> proximo;
};



void SumTree::ins(int x, int lado) {
    lock_guard<mutex> lock(mtx);
    CBinNode* temp = new CBinNode(x);
    actual->nodes[lado] = temp;
}


void SumTree::Insert(int x) {
    if (m_root == nullptr) {
        CBinNode* temp = new CBinNode(x);
        m_root = temp;
        actual = m_root;
        proximo.push_back(actual);
    }
    else {
        if (x < actual->value) {
            suma_actual.push_back(x);
        }
        else {
            return;
        }
        if (suma_actual.size() == 2) {
            thread cero(&SumTree::ins, this, suma_actual[0], 0);
            thread uno(&SumTree::ins, this, suma_actual[1], 1);
            cero.join();
            uno.join();

            suma_actual.clear();
            proximo.pop_front();
            proximo.push_back(actual->nodes[0]);
            proximo.push_back(actual->nodes[1]);
            actual = proximo.front();
        }


    }
}


void SumTree::Print() {
    Inorder(m_root);
}

void SumTree::Inorder(CBinNode* n) {
    if (!n) return;
    Inorder(n->nodes[0]);
    cout << n->value << " ";
    Inorder(n->nodes[1]);
}


int main() {
    SumTree t;
    t.Insert(10);
    t.Insert(4);
    t.Insert(6);
    t.Insert(2);
    t.Insert(2);
    t.Insert(3);
    t.Insert(3);
    t.Insert(1);
    t.Insert(1);
    t.Print();
}
