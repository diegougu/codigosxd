#include <iostream>
#include <vector>
#include <list>

#define VACIO 0

using namespace std;

class matriz_esparsa {
public:
    matriz_esparsa(int x, int y);
    int get(int x, int y);
    void set(int x, int y, int v);

private:
    int eje_x;
    int eje_y;
    vector<list<int>> matriz;
};

matriz_esparsa::matriz_esparsa(int x, int y) {
    eje_x = x;
    eje_y = y;
    matriz.resize(eje_x);
    for (auto& columna : matriz) {
        columna.resize(eje_y, VACIO);
    }
}

int matriz_esparsa::get(int x, int y) {
    if (x >= eje_x || y >= eje_y || x < 0 || y < 0) {
        cout << "Índice fuera de rango" << endl;
        return 0;
    }
    auto& fila = matriz[x];
    auto ite_list = fila.begin();
    int posi = 0;
    for (; posi <= y; posi++, ite_list++) {
        if (posi == y) {
            cout << *ite_list << " ";
            return *ite_list;
        }
    }


}

void matriz_esparsa::set(int x, int y, int v) {
    if (x >= eje_x || y >= eje_y || x < 0 || y < 0) {
        cout << "Índice fuera de rango" << endl;
        return;
    }
    auto& fila = matriz[x];
    auto ite_list = fila.begin();
    int posi = 0;
    for (; posi <= y; posi++,ite_list++) {
        if (posi == y) {
            *ite_list = v;
            return;
        }
    }

}

int main() {
    matriz_esparsa t(5, 5);
    t.set(0, 1, 3);
    t.set(0, 0, 100);
    t.get(0, 0);
    t.get(0, 1);
}
