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
        if (p->value < q->value) {
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
        CBinNode* temp = treevec.back();
        CBinNode* q = treevec.back();

        swap(p->value, q->value);

        int actual = treevec.size() - 1;
        int compara = 0;

        if (actual == 0) {
            CBinNode* n = m_root;
            m_root = nullptr;
            delete n;
            return;
        }

        if (actual % 2 == 0) {
            compara = (actual / 2) - 1;
        }
        else if (actual % 2 != 0) {
            compara = actual / 2;
        }

        q = treevec[compara];
        delete temp;
        treevec.pop_back();

        actual = compara;
        compara = 0;


        while (true) {
            CBinNode* p = treevec[0];
            CBinNode* q = treevec[actual];

            if (q->value < p->value) {
                swap(p->value, q->value);
                break;
            }
            else {

                if (actual == 0) {
                    break;
                }

                if (actual % 2 == 0) {
                    int temp = (actual / 2) - 1;
                    actual = temp;

                }
                else if (actual % 2 != 0) {
                    int temp = actual / 2;
                    actual = temp;
                }

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

    t.add(10);
    t.add(20);
    t.add(30);
    t.add(5);

    t.pop();

    t.print();

}
