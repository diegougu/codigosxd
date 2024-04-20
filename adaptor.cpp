#include <iostream>
using namespace std;

struct node {
  int valor;
  node* next;
  node* prev;

  node(int value) : valor(value), next(nullptr), prev(nullptr) {}

};

struct Clist {
  node* head = nullptr;
  node* tail = nullptr;
  void push_front(int val);
  void push_back(int val);
  void pop_front();
  void pop_back();
  void print();
  node* operator[](int val);



};

void Clist::push_front(int val) {
  if (head == NULL) {
    head = new node(val);
    tail = head;
  }
  else {
    head->prev = new node(val);
    head->prev->next = head;
    head = head->prev;
  }

}

void Clist::push_back(int val) {
  if (head == NULL) {
    head = new node(val);
    tail = head;
  }
  else {
    tail->next = new node(val);
    tail->next->prev = tail;
    tail = tail->next;
  }
}

void Clist::pop_front() {
  if (head == NULL) {
    cout << "lista vacia" << endl;
  }
  else {
    node* temp = head;
    head = head->next;
    delete temp;
  }
}

void Clist::pop_back() {
  if (head == NULL) {
    cout << "lista vacia" << endl;
  }
  else {
    node* temp = tail;
    tail = tail->prev;
    tail->next = nullptr;
    delete temp;
  }
}

void Clist::print() {
  node* tmp = head;
  while (tmp != nullptr) {
    cout << tmp->valor << " ";
    tmp = tmp->next;
  }
}

node* Clist::operator[](int val) {
  node* tmp = head;
  for (int i = 0; i < val && tmp != NULL; tmp = tmp->next, i++){ 
    //cout << tmp->valor << " ";
  }
  return tmp;
}


struct Cvector {
  int *arr = nullptr;
  int *head = nullptr;
  int *tail = nullptr;
  int tam = 5;
  int elemt = 0;

  void push_front(int val);
  void push_back(int val);
  void pop_front();
  void pop_back();
  void rescribir(int newtam);
  void print();
  int &operator[](int val);

};

void Cvector::rescribir(int newtam) {
  int *newarr = new int[newtam];
  int *ini = head;
  int av = 0;

  if (head != nullptr) {
    while (ini <= tail) {
      *(newarr + av) = *ini;
      ini++;
      av++;
    }
  }

  delete[] arr;
  arr = newarr;
  tam = newtam;
  head = arr;
  if (head != nullptr)
    tail = arr + av - 1;
}

void Cvector::push_front(int val) {
  if (arr == nullptr) {
    arr = new int[tam];
    head = arr;
    tail = arr;
    *head = val;
    elemt++;
    return;
  }

  if (tail == arr + elemt - 1) {
    rescribir(tam * 2);
  }

  int *ini = tail + 1;

  while (ini > head) {
    *ini = *(ini - 1);
    ini--;
  }

  *head = val;
  tail++;
  elemt++;
}

void Cvector::push_back(int val) {
  if (arr == nullptr) {
    arr = new int[tam];
    head = arr;
    tail = arr;
    *head = val;
    elemt++;
    return;
  }

  if (tail == arr + elemt - 1) {
    rescribir(tam * 2);
  }

  *(tail + 1) = val;
  tail++;
  elemt++;
}

void Cvector::pop_front() {
  if (head == nullptr) {
    return;
  }

  int *ini = head;

  while (ini < tail) {
    *ini = *(ini + 1);
    ini++;
  }

  *tail = 0;
  elemt--;
  tail--;
}

void Cvector::pop_back() {
  if (tail == nullptr) {
    return;
  }

  *tail = 0;
  elemt--;
  tail--;
}
void Cvector::print() {
  for (int *ini = head; ini <= tail; ini++) {
    cout << *ini << " ";
  }
}

int &Cvector::operator[](int val) {
  int i = 0;
  for (; i < val; i++);
  return arr[i];
}

template<class T, class K>
struct Adaptor{
  K ctnr;
  void push_back(T val){
    ctnr.push_back(val);
  }
  void popback(){
    ctnr.pop_back();
  }
  void print(){
    ctnr.print();
  }
};



int main() {
  Adaptor<int, Cvector> adaptor;
  adaptor.ctnr.push_back(5);
  adaptor.ctnr.push_back(6);
  adaptor.ctnr.push_back(7);
  adaptor.ctnr.push_back(8);
  adaptor.ctnr.push_back(9);
  adaptor.ctnr.pop_back();
  adaptor.ctnr.print();


  cout << endl;

  Adaptor<int, Clist> adaptorv2;
  adaptorv2.ctnr.push_back(1);
  adaptorv2.ctnr.push_back(2);
  adaptorv2.ctnr.push_back(3);
  adaptorv2.ctnr.push_back(4);
  adaptorv2.ctnr.push_back(5);
  adaptorv2.ctnr.pop_back();
  


}
