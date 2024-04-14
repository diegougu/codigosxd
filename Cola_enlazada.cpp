#include <iostream>
using namespace std;

struct node {
  int valor;
  node* next;

  node(int value) : valor(value), next(nullptr) {}

};



struct Cola_enlazada{
  node* top = nullptr;
  node* tail = nullptr;
  bool push(int v);
  bool pop(int &v);
  void print();
};

bool Cola_enlazada::push(int v){
  if(top == nullptr){
    top = new node(v);
    tail = top;
    return true;
  }
  else{
    tail = top;
    top = new node(v);
    top->next = tail;
    return true;
  }
  return false;
}

bool Cola_enlazada::pop(int &v){
  if(top == nullptr){
    return false;
  }
  else{
    v = top->valor;
    node* temp = top;
    top = top->next;
    tail = tail->next;
    delete temp;
    return true;
  }
}

void Cola_enlazada::print(){
  node* temp = top;
  for(; temp ; temp = temp->next){
    cout << temp->valor << " ";
  }
}


int main(){
  Cola_enlazada p;
  int elemento = 0;
  p.push(1);
  p.push(2);
  p.push(3);
  p.push(4);
  p.push(5);
  p.print();
  p.pop(elemento);
  cout << endl;
  cout << elemento << endl;
}
