#include <iostream>
#include "C:\labwork5\lib\BitArray3D.cpp"
int main() {
  ThreeArray arr = ThreeArray::make_array(3, 3, 3);
  int value = 0;
  for (size_t i = 0; i < 3; ++i) {
    for (size_t j = 0; j < 3; ++j) {
      for (size_t k = 0; k < 3; ++k) {
        arr[i][j][k] = value;
        value++;
      }
    }
  }
  ThreeArray ans = arr * 2;
  ThreeArray ans2 = ans + arr;
  std::cout << ans2;
  return 0;

}
