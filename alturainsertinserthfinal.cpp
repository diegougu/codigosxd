#include <iostream>
#include <vector>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////

struct CBinNode
{
    CBinNode(int _v)
    {
        value = _v;
        nodes[0] = nodes[1] = 0;
        height = 1;
    }

    int value;
    CBinNode* nodes[2];
    unsigned int height;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////

class CAvlTree
{
public:
    CAvlTree();
    ~CAvlTree();
    bool Insert(int x);
    bool InsertH(int x, unsigned int h);
    bool Remove(int x);
    void Print();
private:
    int calcular_altura(CBinNode* n);
    bool Find(int x, CBinNode**& p);
    CBinNode** Rep(CBinNode** p);
    void InOrder(CBinNode* x);
    CBinNode* root;
    bool brep;
};

CAvlTree::CAvlTree()
{
    root = 0;
    brep = 0;
}

CAvlTree::~CAvlTree()
{
}

bool CAvlTree::Find(int x, CBinNode**& p)
{
    for ( p = &root;
         *p && (*p)->value != x;
         p = &((*p)->nodes[ (*p)->value < x ]) );
    return *p != 0;
}

bool CAvlTree::InsertH(int x, unsigned int h)
{
    // No modificar ni usar esta función InsertH
    CBinNode** p;
    if ( Find(x,p) ) return 0;
    *p = new CBinNode(x);
    (*p)->height = h;
    return 1;
}


int CAvlTree::calcular_altura(CBinNode* n){
  int left = n->nodes[0] ? n->nodes[0]->height : 0;
  int right = n->nodes[1] ? n->nodes[1]->height : 0;
  
  return 1 + max(left,right);
}


bool CAvlTree::Insert(int x)
{
    CBinNode** p;
    if ( Find(x,p) ) return 0;
    *p = new CBinNode(x);
    CBinNode** temp = &root;

    vector<CBinNode*> cam;

    for (; *temp != nullptr; temp = &((*temp)->nodes[(*temp)->value < (*p)->value])) {
        cam.push_back(*temp);
    }
    cam.pop_back();
    
    int tam = cam.size() - 1;
    CBinNode* actual = cam[tam];
    
    while(!cam.empty()){
        
        int nueva_altura = calcular_altura(actual);
        if(nueva_altura != actual->height){
            actual->height = nueva_altura;
        }
        cam.pop_back();
        if(cam.size() - 1 == -1){
            break;
        }
        tam = cam.size() - 1;
        actual = cam[tam];
        
    }
    
    
    
    
    return 1;
}

bool CAvlTree::Remove(int x)
{
    CBinNode** p;
    if ( !Find(x,p) ) return 0;
 
    if ( (*p)->nodes[0] && (*p)->nodes[1] ) //case 2
    {
        CBinNode** q = Rep(p);
        (*p)->value = (*q)->value;
        p = q;
    }
    // case 0 or case 1
    CBinNode* t = *p;
    *p = (*p)->nodes[ (*p)->nodes[1] != 0 ];
    delete t;
    return 1;
}

CBinNode** CAvlTree::Rep(CBinNode** p)
{
    CBinNode** q = p;
    for ( q = &((*q)->nodes[!brep]); *q; q = &((*q)->nodes[brep]) );
    brep = !brep;
    return q;
}

void CAvlTree::InOrder(CBinNode* x)
{
    if ( !x ) return;
    InOrder(x->nodes[0]);
    std::cout<<x->value<<"("<<x->height<<") ";
    InOrder(x->nodes[1]);
}

void CAvlTree::Print()
{
    InOrder(root);
    std::cout<<"\n--------------------\n";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    // No modificar esta función main
    CAvlTree t;
    t.InsertH(51,4); t.InsertH(33,2); t.InsertH(62,3);
    t.InsertH(21,1); t.InsertH(42,1); t.InsertH(55,2);
    t.InsertH(71,1); t.InsertH(57,1);
    t.Print();
    t.Insert(20); t.Insert(35); t.Insert(44); t.Insert(77);
    t.Insert(34); t.Insert(43); t.Insert(46); t.Insert(56);
    t.Insert(58); t.Insert(48);
    t.Print();
}
