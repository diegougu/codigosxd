#include <iostream>
#include <vector>
using namespace std;

template<class T>
class Node{
public:
    T val;
    Node<T>* next;

    Node(T v, Node<T>* nxt = nullptr){
        val = v;
        next = nxt;
    }

};


template<class T>
class LinkedList{

public:
    Node<T>* head = nullptr;

    LinkedList(){}

    void push_front(T val){

        Node<T>* newNode = new Node<T>(val, head);
        head = newNode;

    }

    void print(){

        cout << "Head -> ";
        for (Node<T>* p = head; p != nullptr; p = p->next){
            cout << p->val << " -> "; 
        }
        cout << "NULL" << endl;

    }


    void sort(){
      Node<T>* p = head;
      Node<T>* q = head;

      for(;p; p = p->next){
        q = p->next;
        for(;q; q = q->next){
          if(p->val > q->val && p == head){
            head = q;
            Node<T>* salvado = q->next;
            q->next = p;
            for(;p->next != head; p = p->next);
            p->next = salvado;
            p = head;
          }
          else{
            if(p->val > q->val){
              Node<T>* r = head;
              Node<T>* originalp = p;
              for(;r->next != p; r = r->next);
              Node<T>* salvado = q->next;
              r->next = q;
              q->next = p;
              for(;p->next != q; p = p->next);
              p->next = salvado;
              p = originalp;
            }
          }
        }
      }
    }
      



};


int main(){
    LinkedList<int> l;
    LinkedList<int> l2;
    l.push_front(3);
    l.push_front(2);
    l.push_front(1);
    l.push_front(7);
    l.push_front(4);

    l.sort();
    l.print();

    cout << endl;

    l2.push_front(3);
    l2.push_front(2);
    l2.sort();
    l2.print();
}
