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

struct lista{
  node* head = nullptr;
  node* tail = nullptr;
  void add(int x);
  void reverse();
  void print();
};

void lista::add(int x){
  if(head == nullptr){
    head = new node(x);
    tail = head;
  }
  else{
    tail->next = new node(x);
    tail = tail->next;
  }
}

void lista::print(){
  for(node* p = head; p; p = p->next){
    cout << p->valor << " ";
  }
}

void lista::reverse(){
  node* temp = head;
  node* temp_next = nullptr;
  int valor_head = head->valor;
  int valor_tail = tail->valor;
  node* limit = tail;
  while(head->valor != valor_tail || tail->valor != valor_head){
      for(;temp < limit; temp = temp->next){
        temp_next = temp->next;
        int aux = temp->valor;
        int aux2 = temp_next->valor;
        temp->valor = aux2;
        temp_next->valor = aux;
        if(temp->next == limit){
          limit = temp;
        }
      }
      temp = head;
      temp_next = nullptr;
  }
}

int main(){
  lista l;
  l.add(1);
  l.add(2);
  l.add(3);
  l.add(4);
  l.reverse();
  l.print();
}
