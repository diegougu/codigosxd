#include <iostream>
using namespace std;

struct Pila {
	int elem[10];
	int* top = nullptr;
	bool push(int a);
	bool pop(int& a);


};

bool Pila::push(int a) {
	if (top == nullptr) {
		*elem = a;
		top = elem;
		return true;
	}
	else if (top) {
		top++;
		*top = a;
		return true;
	}

	return false;

}

bool Pila::pop(int& a) {
	if (top >= elem) {
		a = *(top--);
		return true;
	}
	return false;
}

int main() {
	Pila pila;
	int elemento = 0;
	for (int i = 1; i <= 10; ++i) {
		pila.push(i);
	}

	for (int i = 0; i <= 3; ++i) {
		pila.pop(elemento);
		cout << "el elemento sacado de la pila es: " << elemento << endl;
	}


	
}
