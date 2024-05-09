#include <iostream>

using namespace std;

struct node{
  int valor;
  node* next;
  node(int v, node* n = nullptr): valor(v), next(n){}
};

struct lista{
  node* head = nullptr;
  void push_front(int v);
  void print();
  void eliminacion_de_repetidos();
};

void lista::push_front(int v){
  if(head == nullptr){
    head = new node(v);
  }
  else{
    node* temp = new node(v);
    temp->next = head;
    head = temp;
  }
}

void lista::print(){
  for(node* p = head; p ; p = p->next){
    cout << p->valor << " ";
  }
}

void lista::eliminacion_de_repetidos(){
  node* p = head;

  while(p != nullptr){
    if(p->valor == p->next->valor){
      node* eleminar = p->next;
      p->next = p->next->next;
      delete eleminar;
    }
    else{
      p = p->next;
    }
  }
}


int main(){
  lista l;
  l.push_front(1);
  l.push_front(1);
  l.push_front(5);
  l.push_front(1);
  l.push_front(3);
  l.push_front(3);
  l.push_front(3);

  l.print();
  cout << endl;
  l.eliminacion_de_repetidos();
  l.print();
}
