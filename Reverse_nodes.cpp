#include <iostream>
using namespace std;

struct node{
  int valor;
  node* next;
  node(int v, node* n = nullptr) : valor(v), next(n){}
};

struct lista{
  node* head = nullptr;
  void push_front(int v);
  void print();
  void reverse();
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

void lista::reverse(){
  node* temp = head;
  node* desp = temp->next;
  node* limite = head;
  for(;limite; limite = limite->next){
    if(limite->next == nullptr){
      break;
    }
  }


  while(head != limite){
    for(;desp; desp = desp->next, temp = temp->next){
      if(desp->next == nullptr){
        desp->next = temp;
        temp->next = nullptr;
        desp = temp;
        if(temp == head){
          head = limite;
        }
      }
    }
    temp = head;
    desp = temp->next;
  }
}

void lista::print(){
  for(node* p = head; p; p = p->next){
    cout << p->valor << " ";
  }
}

int main(){
  lista l;
  l.push_front(1);
  l.push_front(2);
  l.push_front(3);
  l.push_front(4);

  l.print();
  cout << endl;

  l.reverse();
  l.print();
}
