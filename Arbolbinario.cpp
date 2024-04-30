#include <iostream>
using namespace std;

struct node{
  int valor;
  node* izquierda;
  node* derecha;
  node(int v, node* i = nullptr, node* d = nullptr) : valor(v), izquierda(i), derecha(d) {}
};


struct Arbol{
  node* raiz = nullptr;
  void insertar(int v);
  void remove(int v);
  bool find(int v, node**& p);
  void print(node* n);
};

void Arbol::insertar(int v){
  if(raiz == nullptr){
    raiz = new node(v);
    return;
  }
  node** temp = &raiz;
  if(!find(v, temp)){
    *temp = new node(v);
  }
  return;
}

void Arbol::remove(int v){
  node** temp = &raiz;
  if(v == raiz->valor){
    temp = &((*temp)->izquierda);
    while((*temp)->derecha != nullptr){
      temp = &((*temp)->derecha);
    }
    if((*temp)->izquierda == nullptr){
      raiz->valor = (*temp)->valor;
      *temp = nullptr;
      return;
    }
    else if((*temp)->izquierda != nullptr){
      raiz->valor = (*temp)->valor;
      *temp = (*temp)->izquierda;
      return;  
    }
  }
  if(find(v, temp)){
    if((*temp)->izquierda == nullptr && (*temp)->derecha == nullptr){
      *temp = nullptr;
      return;
    }
    else if((*temp)->izquierda == nullptr && (*temp)->derecha != nullptr){
      *temp = (*temp)->derecha;
    }
    else if((*temp)->izquierda != nullptr && (*temp)->derecha == nullptr){
      *temp = (*temp)->izquierda;
    }
    else{
      node* a = (*temp)->izquierda;
      *temp = (*temp)->derecha;
      while((*temp)->izquierda != nullptr){
        temp = &((*temp)->izquierda);
      }
      (*temp)->izquierda = a;
  
    }
    return;
    
  }
  
}



bool Arbol::find(int v, node**& p){
  p = &raiz;
  while(*p != nullptr && (*p)->valor != v){
    if((*p)->valor < v){
      p = &((*p)->derecha);
    }
    else{
      p = &((*p)->izquierda);
    }
  }
  return *p;
}

void Arbol::print(node* n){
  if(n == nullptr){
    return;
  }
  if(n->izquierda){
    print(n->izquierda);
  }
  cout << n->valor << " ";
  if(n->derecha){
    print(n->derecha);
  }
}

int main(){
  Arbol a;
  a.insertar(52);
  a.insertar(41);
  a.insertar(64);
  a.insertar(55);
  a.insertar(32);
  a.insertar(44);
  a.insertar(73);
  a.insertar(56);

  node* temp = a.raiz;
  a.print(temp);

  cout << endl;
  a.remove(52);
  a.print(temp);

  cout << endl;
  a.remove(44);
  a.print(temp);
  
}
