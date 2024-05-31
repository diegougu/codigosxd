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


class priorityq {
public:
    void add(int x);
    void pop();
    void print();
private:
    CBinNode* m_root = nullptr;
    vector<CBinNode*> treevec;
    void cams();
};

void priorityq::cams() {
    int actual = treevec.size() - 1;
    int compara = 0;
    while (true) {

        if (actual == 0) {
            break;
        }

        if (actual % 2 == 0) {
            compara = (actual / 2) - 1;
        }
        else if (actual % 2 != 0) {
            compara = actual / 2;
        }


        CBinNode* p = treevec[actual];
        CBinNode* q = treevec[compara];
        if (p->value > q->value) {
            swap(q->value, p->value);
        }
        else {
            break;
        }
        actual = compara;
    }
}

void priorityq::add(int x) {
    if (m_root == nullptr) {
        CBinNode* temp = new CBinNode(x);
        m_root = temp;
        treevec.push_back(m_root);
        return;
    }
    else {
        for (CBinNode* p : treevec) {

            if (p->value == x) {
                return;
            }

            if (p->nodes[0] == nullptr) {
                CBinNode* temp = new CBinNode(x);
                p->nodes[0] = temp;
                treevec.push_back(p->nodes[0]);
                cams();
                return;
            }
            if (p->nodes[1] == nullptr) {
                CBinNode* temp = new CBinNode(x);
                p->nodes[1] = temp;
                treevec.push_back(p->nodes[1]);
                cams();
                return;
            }
        }

    }

}

void priorityq::pop() {
    if (m_root == nullptr) {
        return;
    }
    else {
        CBinNode* p = m_root;
        CBinNode* q = treevec.back();
        swap(p->value, q->value);

        int borrar = treevec.size() - 1;
        int rec = 0;

        if (borrar % 2 == 0) {
            rec = (borrar / 2) - 1;
        }
        else if (borrar % 2 != 0) {
            rec = borrar / 2;
        }

        CBinNode* n = treevec[rec];
        if (n->nodes[0] == q) {
            n->nodes[0] = nullptr;
            delete q;
            treevec.pop_back();
        }
        else if (n->nodes[1] == q) {
            n->nodes[1] = nullptr;
            delete q;
            treevec.pop_back();
        }

        while (p->nodes[0] != nullptr && p->nodes[1] != nullptr) {
            
            if ((p->nodes[0]->value > p->value) && (p->nodes[0] != nullptr) && (p->nodes[0]->value > p->nodes[1]->value)) {
                swap(p->value, p->nodes[0]->value);
                p = p->nodes[0];
            }
            else if ((p->nodes[1]->value > p->value) && (p->nodes[1] != nullptr) && (p->nodes[1]->value > p->nodes[0]->value)) {
                swap(p->value, p->nodes[1]->value);
                p = p->nodes[1];
            }
            else {
                break;
            }

        }

    }

}

void priorityq::print() {
    for (CBinNode* p : treevec) {
        cout << p->value << " ";
    }
}





int main() {
    priorityq t;
    t.add(60);
    t.add(40);
    t.add(47);
    t.add(25);
    t.add(10);
    t.add(20);
    t.pop();
    t.print();


}
