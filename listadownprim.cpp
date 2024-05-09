#include <iostream>
using namespace std;

struct node{
  int valor;
  node* next;
  node* down;
  node(int v, node* n = nullptr, node* d = nullptr) : valor(v), next(n), down(d) {}
};

struct lista_prim{
  node* head = nullptr;
  void push_prim(int v);
  void print();
};


void lista_prim::push_prim(int v){
  if(head == nullptr){
    head = new node(v);
  }
  else{
    node* p = head;
    while(p->next != nullptr){
      if(p->valor == v){
        return;
      }

      else if(v % p->valor == 0 || p->valor % v == 0 && p->valor < v){
        if(p->down == nullptr){
          p->down = new node(v);
        }
        for(node* d = p; d ; d = d->down){
          if(d->valor == v){
            return;
          }
          else if(d->down == nullptr){
            d->down = new node(v);
            return;
          }
          else if(d->down->valor > v){
            node* temp = new node(v);
            temp->down = d->down;
            d->down = temp;
            return;
          }
        }
      }

      else if(v % p->valor == 0 || p->valor % v == 0 && p->valor > v){
        node* temp = new node(v);
        if(p == head){
          temp->next = p->next;
          temp->down = p;
          p->next = nullptr;
          head = temp;
          return; 
        }
        else{
          node* antesp = head;
          for(;antesp->next != p; antesp = antesp->next);
          antesp->next = temp;
          temp->next = p->next;
          temp->down = p;
          p->next = nullptr;
          return;
        }
      }
      p = p->next;
    }

   if(v % p->valor == 0 || p->valor % v == 0 && p->valor < v){
      if(p->down == nullptr){
        p->down = new node(v);
      }
      for(node* d = p; d ; d = d->down){
        if(d->valor == v){
          return;
        }
        else if(d->down == nullptr){
          d->down = new node(v);
          return;
        }
        else if(d->down->valor > v){
          node* temp = new node(v);
          temp->down = d->down;
          d->down = temp;
          return;
        }
      }
    }
    else if(v % p->valor == 0 || p->valor % v == 0 && p->valor > v){
      node* temp = new node(v);
      if(p == head){
        temp->next = p->next;
        temp->down = p;
        p->next = nullptr;
        head = temp;
        return; 
      }
      else{
        node* antesp = head;
        for(;antesp->next != p; antesp = antesp->next);
        antesp->next = temp;
        temp->next = p->next;
        temp->down = p;
        p->next = nullptr;
        return;
      }
    }
    node* temp = new node(v);
    p->next = temp;
    return;
  }
}


void lista_prim::print(){
  for(node* p = head; p ; p = p->next){
    cout << p->valor << " ";	
    if(p->down != nullptr){
      for(node* d = p->down; d ; d = d->down){
        cout << d->valor << " ";
      }
    }
  }

}

int main(){
  lista_prim l;
  l.push_prim(2);
  l.push_prim(8);
  l.push_prim(4);
  l.push_prim(25);
  l.push_prim(5);
  l.push_prim(7);
  l.print();

}
