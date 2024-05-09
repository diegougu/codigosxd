#include <iostream>
using namespace std;
template <class T>
struct CForwardNode
{
    CForwardNode(T x)
    {   value = x;  next = 0;   }
    T value;
    CForwardNode<T>* next;
};

template <class T>
class CForwardList
{
public:
    CForwardList();
    ~CForwardList();
    bool Find(T x, CForwardNode<T>**& p);
    bool Ins(T x);
    bool Rem(T x);
    void Print();
public:
    CForwardNode<T>* head;
};

template <class T>
CForwardList<T>::CForwardList()
{
    head = 0;
}

template <class T>
CForwardList<T>::~CForwardList()
{
    //...
}

template <class T>
bool CForwardList<T>::Find(T x, CForwardNode<T>**& p)
{
    for ( p = &head; *p && (*p)->value < x; p = &(*p)->next );
    return *p && (*p)->value == x;
}

template <class T>
bool CForwardList<T>::Ins(T x)
{
    CForwardNode<T>** p;
    if ( Find(x,p) ) return 0;
    CForwardNode<T>* t = new CForwardNode<T>(x);
    t->next = *p;
    *p = t;
    return 1;
}

template <class T>
bool CForwardList<T>::Rem(T x)
{
    CForwardNode<T>** p;
    if ( !Find(x,p) ) return 0;
    CForwardNode<T>* t = *p;
    *p = t->next;
    delete t;
    return 1;
}

template <class T>
void CForwardList<T>::Print()
{
    for ( CForwardNode<T>* t = head; t ; t = t->next )
        std::cout<<t->value<<" ";
    std::cout<<"\n";
}


template <class T>
struct multiplo_de_tres{
    bool operator()(T x){
        return x % 3 == 0;
    }
};

void proc1(CForwardList<int>* l, multiplo_de_tres<int> d){
    for(CForwardNode<int>* p = l->head; p ; p = p->next){
        if(d(p->value)){
            p->value = p->value + 10;
        }
    }
}



class compare{
  public:
  virtual bool comp(int a, int b) = 0;
};

class compare_min : public compare{
  public:
  bool comp(int a, int b) override{
    return a > b;
  }
};

void proc2(CForwardList<int>* l, compare_min c){
  CForwardNode<int>* q = l->head->next;
  for(CForwardNode<int>* p = l->head; p && q; p = p->next, q = p->next){
    if(c.comp(p->value, q->value)){
      p->next = q->next;
      CForwardNode<int>* temp = q;
      q = p;
      delete temp;
    }
  }
}

int main(){
    CForwardList<int> l;
    l.Ins(6);
    l.Ins(3);
    l.Ins(9);
    l.Ins(18);
    l.Ins(4);
    l.Ins(10);
    l.Print();
    cout << endl;
    multiplo_de_tres<int> d;
    proc1(&l, d);
    l.Print();
    cout << endl;
    compare_min c;
    proc2(&l, c);
    l.Print();
}
