#include <iostream>
using namespace std;

struct deque {
  int tam = 5;
  int tam_mapa = 5;
  int **mapa = new int *[tam];
  int **ini = mapa + (tam / 2);
  int **fin = mapa + (tam / 2);
  int *ini_array = nullptr;
  int *fin_array = nullptr;
  void aumentar_tamano_mapa(int newtam);
  void push_back(int n);
  void push_front(int n);
  void pop_back();
  void pop_front();
  void print();
  int numarrs = 0;
  int& operator[](int val);
};

void deque::aumentar_tamano_mapa(int newtam) {
  int **newmap = new int *[newtam];
  int **ini_tmp = ini;
  int i = 0;
  while (ini_tmp <= fin) {
    newmap[i + numarrs] = *ini_tmp;
    if (ini_tmp == ini) {
      ini = newmap + i + numarrs;
    }
    if (ini_tmp == fin) {
      fin = newmap + i + numarrs;
      break;
    }
    i++;
    ini_tmp++;
  }
  mapa = newmap;
}

void deque::push_back(int n) {
  if (fin == ini && fin_array == nullptr) {
    *fin = new int[tam];
    fin_array = *fin + (tam / 2);
    ini_array = fin_array;
    ini_array--;
    numarrs++;
  }
  if (fin_array > *fin + (tam - 1)) {
    fin++;
    *fin = new int[tam];
    fin_array = *fin;
    *fin_array = n;
    fin_array++;
    numarrs++;
  }
  else {
    *fin_array = n;
    fin_array++;
  }
  if (fin == mapa + (tam_mapa - 1)) {
    aumentar_tamano_mapa(tam_mapa * 2);
  } 


}

void deque::push_front(int n) {
  if (ini == fin && ini_array == nullptr) {
    *ini = new int[tam];
    ini_array = *ini + (tam / 2);
    fin_array = ini_array;
    fin_array++;
    numarrs++;
  }
  if (ini_array == *ini - 1) {
    ini--;
    *ini = new int[tam];
    ini_array = *ini + (tam - 1);
    *ini_array = n;
    ini_array--;
    numarrs++;
  }
  else {
    *ini_array = n;
    ini_array--;
  }
  if (ini == mapa) {
    aumentar_tamano_mapa(tam_mapa * 2);
  } 

}

void deque::pop_front(){
  if(fin == ini && ini_array == nullptr){
    return;
  }
  if(ini_array == *ini + (tam - 1)){
    int** temp_ini = ini;
    ini++;
    delete[] *temp_ini;
    ini_array = *ini - 1;
    numarrs--;
  }
  else{
    int* tmp = *ini + (tam - 1);
    *ini = nullptr;
    *ini = new int[tam];
    ini_array++;
    int* temp_array = ini_array;
    ini_array = *ini + (tam - 1);
    while(tmp >= temp_array){
      if(tmp == temp_array){
        break;
      }
      *ini_array = *tmp;
      ini_array--;
      tmp--;
    }
  }
}

void deque::pop_back(){
  if(fin == ini && fin_array == nullptr){
    return;
  }
  if(fin_array == *fin){
    int** temp_fin = fin;
    fin--;
    delete[] *temp_fin;
    fin_array = *fin + (tam);
    numarrs--;
  }
  else{
    int* tmp = *fin;
    *fin = nullptr;
    *fin = new int[tam];
    fin_array--;
    int* temp_array = fin_array;
    fin_array = *fin;
    while(tmp <= temp_array){
      if(tmp == temp_array){
        break;
      }
      *fin_array = *tmp;
      fin_array++;
      tmp++;
    }
  }

}

void deque::print(){
  int** temp_ini = ini;
  int* ini_array_temp = ini_array+1;
  for(;temp_ini <= fin; temp_ini++, ini_array_temp = *temp_ini){
    for(;ini_array_temp <= *temp_ini + (tam - 1) ; ini_array_temp++){
      cout << *ini_array_temp << " ";
      if(ini_array_temp == fin_array-1){
        break;
      }
    }
    cout << endl;
  }

}


int main() {
  deque c;

  for(int i = 1; i < 5; i++){
    c.push_front(i);
  }
  for(int i = 5; i <= 9; i++){
    c.push_back(i);
  }
  c.print();

}
