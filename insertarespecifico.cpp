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
  void insertar_especifico(int posicion, int v);
  int contador_de_nodos = 0;
};

void lista::push_front(int v){
  if(head == nullptr){
    head = new node(v);
    contador_de_nodos++;
  }
  else{
    node* temp = new node(v);
    temp->next = head;
    head = temp;
    contador_de_nodos++;
  }
}

void lista::insertar_especifico(int posicion, int v){
  if(posicion > contador_de_nodos){
    node* temp = new node(v);
    for(node* p = head; p; p = p->next){
      if(p->next == nullptr){
        p->next = temp;
        contador_de_nodos++;
        return;
      }
    }
  }
  else if(posicion == 1){
    node* temp = new node(v);
    temp->next = head; 
    head = temp;
    contador_de_nodos++;
  }
  else if(posicion <= contador_de_nodos){
    node* temp = new node(v);
    int contador = 1;
    for(node* p = head; p ; p = p->next, contador++){
      if(contador + 1 == posicion){
        node* q = p->next;
        p->next = temp;
        temp->next = q;
        contador_de_nodos++;
        return;
      }
    }
  }
}


void lista::print(){
  for(node* p = head; p ; p = p->next){
    cout << p->valor << " ";
  }
}

int main(){
  lista l;
  l.push_front(6);
  l.push_front(5);
  l.push_front(4);
  l.push_front(2);
  l.push_front(1);
  l.print();

  cout << endl;

  l.insertar_especifico(1, 7);
  l.print();
}
