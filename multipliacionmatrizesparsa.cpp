#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

struct objx;
class matrizesparsa;

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

	int get_(int x, int y);
	void set(int x, int y, int v);
	objx operator()(int x, int y);
	static const int tam = 4;
	node* eje_x[tam];
	node* eje_y[tam];
	void multipliacion(matrizesparsa t);

private:
	bool Insert(int x, int y, int v);
	bool FindRight(node**& p, int y);
	bool FindDown(node**& q, int x);
	bool Remove(int x, int y, int v);

};

struct objx {
	matrizesparsa* m = nullptr;
	objx(matrizesparsa* n = nullptr) : m(n) {}
	pair<int, int> xy;
	objx operator=(int v) {
		m->set(xy.first, xy.second, v);
		return *this;
	}
	operator int() {
		return m->get_(xy.first, xy.second);
	};
	objx operator=(objx& ox) {
		m->set(xy.first, xy.second, ox.m->get_(ox.xy.first, ox.xy.second));
		return *this;
	}
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


int matrizesparsa::get_(int x, int y) {
	if (x > tam && y > tam) {
		cout << "el tamaño pedido sobrepasa al de la matriz" << endl;
		return 0;
	}
	node** p = &eje_x[x];
	node** q = &eje_y[y];

	if (FindRight(p, y)) {
		return (*p)->valor;
	}
	if (FindDown(q, x)) {
		return (*q)->valor;
	}
	else {
		return 0;
	}
}


objx matrizesparsa:: operator()(int x, int y) {
	objx ox(this);
	pair<int, int> x_y;
	x_y.first = x;
	x_y.second = y;
	ox.xy = x_y;
	return ox;
}


void matrizesparsa::multipliacion(matrizesparsa t) {
	for (int i = 0; i < tam; i++) {
		vector<tuple<int, int, int>> pos_val;
		node* recor = eje_x[i];
		for (; recor != nullptr; recor = recor->right) {
			pos_val.push_back(make_tuple(recor->valor, recor->xy.first, recor->xy.second));
		}
		for (int j = 0; j < tam; j++) {
			node* recor_y = t.eje_y[j];
			int w = 0;
			int suma = 0;
			while (recor_y != nullptr && w < pos_val.size()) {
				tuple<int, int, int> t = pos_val[w];
				int valor = get<0>(t);
				int e_x = get<1>(t);
				int e_y = get<2>(t);
				if (e_y == recor_y->xy.first) {
					suma = (valor * recor_y->valor) + suma;
					w++;
				}
				else if (e_y > recor_y->xy.first) {
					recor_y = recor_y->down;
				}
				else {
					w++;
				}
			}
			set(i, j, suma);
		}
	}
}


int main() {
	matrizesparsa m1, m2;
	m1.set(0, 0, 1);
	m1.set(0, 1, 2);
	m1.set(1, 0, 3);
	m1.set(1, 1, 4);

	m2.set(0, 0, 2);
	m2.set(0, 1, 0);
	m2.set(1, 0, 1);
	m2.set(1, 1, 2);

	m1.multipliacion(m2);

	cout << (int)m1(0, 0) << endl; 
	cout << (int)m1(0, 1) << endl; 
	cout << (int)m1(1, 0) << endl; 
	cout << (int)m1(1, 1) << endl;

}
