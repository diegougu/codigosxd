#include <iostream>
using namespace std;

struct node{
  int valor;
  node* next;
  node(int v, node* n = nullptr) : valor(v), next(n){}
};

struct lista{
  node* head = nullptr;
  void insert(int v);
  void print();
  void mergue(lista& l_change);
};

void lista::insert(int v){
  if(head == nullptr){
    head = new node(v);
  }
  else{
    node* temp = head;
    while(temp->next != nullptr){
      temp = temp->next;
    }
    temp->next = new node(v);
  }
}


void lista::print(){
  for(node* temp = head; temp; temp = temp->next){
    cout << temp->valor << " ";
  }
}

void lista::mergue(lista &l_change){
  node* temp_l_change = l_change.head;
  for(node* temp = head ; temp; temp = temp->next){
    if(temp->next == nullptr){
      temp->next = temp_l_change;
      l_change.head = nullptr;
      break;
    }
  }

  for(node* temp = head; temp; temp = temp->next){
    for(node* compare = head; compare; compare = compare->next){
      if(temp->valor < compare->valor){
        int aux = temp->valor;
        int aux2 = compare->valor;
        temp->valor = aux2;
        compare->valor = aux;
      }
    }
  }
}

int main(){
  lista l1;
  l1.insert(3);
  l1.insert(2);
  l1.insert(1);

  lista l2;
  l2.insert(9);
  l2.insert(10);

  l1.mergue(l2);

  l1.print();	
  l2.print();
}
