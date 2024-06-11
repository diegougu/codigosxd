#include <iostream>
using namespace std;

struct node {
	int valor;
	pair<int, int> xy;
	node* right = nullptr;
	node* down = nullptr;

	node(int v, pair<int, int> xy2, node* r = nullptr, node* d = nullptr) : valor(v), xy(xy2), right(r), down(d) {}
};


class matrizesparsa {
public:
	matrizesparsa() {
		for (int i = 0; i < tam; ++i) {
			eje_x[i] = nullptr;
			eje_y[i] = nullptr;
		}
	}

	void get(int x, int y);
	void set(int x, int y, int v);
	void print();
private:
	bool Insert(int x, int y, int v);
	bool FindRight(node**& p, int y);
	bool FindDown(node**& q, int x);
	bool Remove(int x, int y, int v);
	static const int tam = 4;
	node* eje_x[tam];
	node* eje_y[tam];
};


bool matrizesparsa::FindRight(node**& p, int y) {
	while (*p && (*p)->xy.second < y) {
		p = &((*p)->right);
	}
	return *p && (*p)->xy.second == y;
}

bool matrizesparsa::FindDown(node**& q, int x) {
	while (*q && (*q)->xy.first < x) {
		q = &((*q)->down);
	}
	return *q && (*q)->xy.first == x;
}


bool matrizesparsa::Insert(int x, int y, int v) {
	if (v == 0) {
		return false;
	}
	else if (x > tam || y > tam) {
		return false;
	}

	node** p = &eje_x[x];
	node** q = &eje_y[y];

	if (FindRight(p, y)) {
		return false;
	}

	if (FindDown(q, x)) {
		return false;
	}

	pair<int, int> xy;
	xy.first = x;
	xy.second = y;
	node* temp = new node(v, xy);
	temp->right = *p;
	*p = temp;
	temp->down = *q;
	*q = temp;
	return true;
}


bool matrizesparsa::Remove(int x, int y, int v) {
	node** p = &eje_x[x];
	node** q = &eje_y[y];
	
	if (FindRight(p, y) && FindDown(q, x)) {
		node* temp = *p;
		*p = (*p)->right;
		node* temp2 = *q;
		*q = (*q)->down;
		delete temp;
		return true;
	}
	else {
		return false;
	}

}

void matrizesparsa::set(int x, int y, int v) {
	if (x > tam && y > tam) {
		cout << "el tamaño pedido sobrepasa al de la matriz" << endl;
		return;
	}
	else if (v == 0) {
		Remove(x, y, v);
	}
	else {
		node** p = &eje_x[x];
		node** q = &eje_y[y];
		if (FindRight(p, y)) {
			(*p)->valor = v;
			return;
		}
		if (FindDown(q, x)) {
			(*q)->valor = v;
			return;
		}
		else {
			Insert(x, y, v);
			return;
		}

	}
}


void matrizesparsa::get(int x, int y) {
	if (x > tam && y > tam) {
		cout << "el tamaño pedido sobrepasa al de la matriz" << endl;
		return;
	}
	node** p = &eje_x[x];
	node** q = &eje_y[y];

	if (FindRight(p, y)) {
		cout << (*p)->valor << endl;
		return;
	}
	if (FindDown(q, x)) {
		cout << (*q)->valor << endl;
		return;
	}
	else {
		cout << 0 << endl;
		return;
	}


}

int main() {
	matrizesparsa t;
	t.set(0, 0, 4);
	t.set(2, 0, 10);
	t.set(1, 0, 5);
	t.set(1, 0, 0);
	t.get(1, 0);

}
