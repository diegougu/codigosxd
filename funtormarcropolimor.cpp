#include <iostream>
using namespace std;

template <class T> struct Cless {
  inline bool operator()(T a, T b) { return a < b; }
};

template <class T> struct CGreaster {
  inline bool operator()(T a, T b) { return a > b; }
};

class Comparator {
public:
  virtual bool comp(int a, int b) = 0;
};

class Clesspoli : public Comparator {
public:
  bool comp(int a, int b) override { return a < b; }
};

class CGreaterpoli : public Comparator {
public:
  bool comp(int a, int b) override { return a > b; }
};

template <class C> void sort(int *arr, int n, C k) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (k(arr[j], arr[j + 1])) {
        swap(arr[j], arr[j + 1]);
      }
    }
  }
}

void sort_poli(int *arr, int n, CGreaterpoli *p) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (p->comp(arr[j], arr[j + 1])) {
        swap(arr[j], arr[j + 1]);
      }
    }
  }
}

int main() {
  int n = 5;
  int arr[5] = {2, 3, 4, 5, 1};
  /*
  sort_poli(arr, n, p);
  for (int i = 0; i <= 4; i++) {
      cout << arr[i] << " ";
  }
   */

  CGreaster<int> g;
  sort(arr, n, g);

  for (int i = 0; i <= 4; i++) {
    cout << arr[i] << " ";
  }
}
