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
	void pushfront(int val);
	void pushback(int val);
	void popfront();
	void popback();
	void print();
	node* operator[](int val);

	

};

void Clist::pushfront(int val) {
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

void Clist::pushback(int val) {
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

void Clist::popfront() {
	if (head == NULL) {
		cout << "lista vacia uwu" << endl;
	}
	else {
		node* temp = head;
		head = head->next;
		delete temp;
	}
}

void Clist::popback() {
	if (head == NULL) {
		cout << "lista vacia uwu" << endl;
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

int main() {
	Clist lis;
	for (int i = 1; i < 5; ++i) {
		lis.pushfront(i);
	}

	for (int i = 10; i < 12; i++) {
		lis.pushback(i);
	}

	lis.print();
	cout << endl;
	lis.popfront();
	lis.popback();

	lis.print();
	cout << endl;
	node* val = lis[3];

	cout << val->valor;


}
