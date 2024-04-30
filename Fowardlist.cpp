#include <iostream>
using namespace std;

struct node{
  int valor;
  node* next;
  node(int v, node* n = nullptr){
    valor = v;
    next = n;
  }
};

struct Fowardlist{
  node* head = nullptr;
  bool find(int x, node**& p);
  bool insert(int x);
  bool remove(int x);
  void print();
};

bool Fowardlist::find(int x, node**& p){
  p = &head;
  for(;*p && (*p)->valor < x; p = &(*p)->next);
  return *p && (*p)->valor == x;
}

bool Fowardlist::insert(int x){
  node** p;
  if(find(x,p)){
    return false;
  }
  node* temp = new node(x);
  temp->next = *p;
  *p = temp;
  return true;
}

bool Fowardlist::remove(int x){
  node** p;
  if(!find(x,p)){
    return false;
  }
  node* temp = *p;
  *p = (*p)->next;
  delete temp;
  return true;
}

void Fowardlist::print(){
  node* i = head;
  for(;i;i = i->next){
    cout << i->valor << " ";
  }
}

int main(){
  Fowardlist l;
  l.insert(2);
  l.insert(3);
  l.insert(5);
  l.insert(4);
  l.insert(1);

  l.print();

  cout << endl;

  l.remove(3);
  l.remove(1);
  l.remove(5);
  l.print();
}
