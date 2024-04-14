#include <iostream>
using namespace std;

struct node {
  int valor;
  node* next;

  node(int value) : valor(value), next(nullptr) {}

};


struct Pila_enlazada{
  node* top = nullptr;
  bool push(int v);
  bool pop(int &v);
  void print();
};

bool Pila_enlazada::push(int v){
  if(top == nullptr){
    top = new node(v);
    return true;
  }
  else{
    node* temp = top;
    top = new node(v);
    top->next = temp;
    return true;
  }
  return false;
}

bool Pila_enlazada::pop(int &v){
  if(top == nullptr){
    return false;
  }
  else{
    v = top->valor;
    node* temp = top;
    top = top->next;
    delete temp;
    return true;
  }
}

void Pila_enlazada::print(){
  for(node* p = top; p; p = p->next){
    cout << p->valor << " ";
  }
}

int main(){
  Pila_enlazada p;
  p.push(1);
  p.push(2);
  p.push(3);
  p.push(4);
  p.push(5);
  p.print();

  cout << endl;

  int v = 0;
  p.pop(v);
  cout << v;
  cout << endl;
  p.print();
}
