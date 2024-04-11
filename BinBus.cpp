#include <iostream>
using namespace std;


bool binbus(int* ini, int* fin, int*& Pos, int key) {
	while (ini <= fin) {
		int* mid = ini + (fin - ini) / 2;

		if (*mid == key) {
			Pos = mid;
			return true;
		}

		else if (*mid < key) {
			ini = mid + 1;
		}
		
		else if (*mid > key) {
			fin = mid - 1;
		}


	}
	Pos == NULL;
	return false;
}

int main() {
	int arr[5] = { 1,2,3,4,5 };
	int* pos;
	int key = 4;
	bool verificacion = binbus(arr, arr + 4, pos, key);

	if (verificacion) {
		cout << "se encontro: " << key;
	}
	else {
		cout << "ahi nomas";
	}
}
