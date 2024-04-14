#include <iostream>
using namespace std;

struct Cola {
  int A[10];
  int *head = nullptr;
  int *tail = nullptr;
  bool push(int v);
  bool pop(int &v);
  void print();
};

bool Cola::push(int v) {
  if (tail == nullptr) {
    tail = A;
    head = A;
    *tail = v;
    tail++;
    return true;
  }
  if (tail > A + 9 && head != A) {
    tail = A;
    *tail = v;
    tail++;
    return true;
  }
  if (tail > A + 10 && head == A) {
    return false;
  } 
  else {
    *tail = v;
    tail++;
    return true;
  }
}

bool Cola::pop(int &v) {
  if (head == nullptr) {
    return false;
  }
  if(head > A + 9 && tail != A + 10){
    head = A;
    v = *head;
    return true;
  }
  if(tail > A + 9 && head > A + 9){
    return false;
  }
  if(tail == head){
    return false;
  }
  else {
    v = *head;
    head++;
    return true;
  }
}

void Cola::print(){
  if(head == tail - 1){
    cout << "Cola vacia" << endl;
  }
  else if(head != A && tail != A + 10){
      int* temp = A + 10;
      int* p = head;
      for(; p < temp; p++){
        cout << *p << " ";
      }
      if(p > A + 9){
        p = A;
        for(;p < tail; p++){
          cout << *p << " ";
        }
      }
    
    }
  else{
    for(int* p = head; p < tail; p++){
      cout << *p << " ";
    }
  }
}

int main(){
  Cola c;
  for(int i = 0; i < 10; i++){
    c.push(i);
  }
  for(int i = 0; i < 4; i++){
    c.pop(i);
  }
  c.push(11);

  c.print();
} 
