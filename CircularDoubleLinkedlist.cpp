#include <iostream>
using namespace std;

struct node{
  int valor;
  node* next;
  node* prev;
  node(int v, node* n = nullptr, node* p = nullptr) : valor(v), next(n), prev(p){}
};

struct Circular_double_linked{
  node* head = nullptr;
  node* tail = nullptr;
  void insert(int v);
  void remove(int v);
  void print();
};

void Circular_double_linked::insert(int v){
  if(head == nullptr){
    head = new node(v);
    tail = head;
    head->next = head;
    head->prev = head;
  }
  else{
    node* temp = new node(v);
    node* i = head;
    do{
      if(i->valor > v && i == head){
        temp->next = head;
        head->prev = temp;
        head = temp;
        tail->next = head;
        head->prev = tail;
        break;
      }
      if(i->valor > v && i != head){
        node* temp2 = i->prev;
        temp2->next = temp;
        temp->prev = temp2;
        temp->next = i;
        i->prev = temp;
        break;
      }
      if(i->next == head){
        i->next = temp;
        temp->prev = i;
        temp->next = head;
        head->prev = temp;
        tail = temp;
        break;
      }
      i = i->next;  
    }while(i != head);
  }
}

void Circular_double_linked::remove(int v){
  if(head == nullptr){
    cout << "La lista esta vacia" << endl;
  }
  else{
    node* temp = head;
    do{
      if(temp->valor == v && temp == head){
        head = head->next;
        head->prev = tail;
        tail->next = head;
        delete temp;
        break;
      }
      if(temp->valor == v && temp == tail){
        tail = tail->prev;
        tail->next = head;
        head->prev = tail;
        delete temp;
        break;
      }
      if(temp->valor == v && temp != head){
        node* temp3 = temp->prev;
        node* temp4 = temp->next;
        temp3->next = temp4;
        temp4->prev = temp3;
        delete temp;
        break;
      }
      temp = temp->next;  

    }while(temp != head);
  }
}

void Circular_double_linked::print(){
  node* temp = head;
  do{
    cout << temp->valor << " ";
    temp = temp->next;  
    
  }while(temp != head);
}


int main(){
  Circular_double_linked lista;
  lista.insert(5);
  lista.insert(3);
  lista.insert(7);
  lista.insert(1);
  lista.insert(3);

  lista.print();

  lista.remove(1);
  lista.remove(7);
  lista.remove(3);
  cout << endl;
  lista.print();
}
