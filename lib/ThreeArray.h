
#ifndef LABWORK5_NIZAMUTDINOVEMIR_LIB_THREEARRAY_H_
#define LABWORK5_NIZAMUTDINOVEMIR_LIB_THREEARRAY_H_


#pragma once
#include <cstdint>
#include <iostream>

const int kDegree16 = 65536;
const int kDegree17 = 131072;

class ThreeArray {
 public:
  ThreeArray(int32_t xSize , int32_t ySize , int32_t zSize);
  ~ThreeArray();
  static ThreeArray make_array(int32_t x , int32_t y , int32_t z);
  ThreeArray operator+(ThreeArray& other) const;
  ThreeArray operator-(ThreeArray& other) const;
  ThreeArray operator*(int32_t value) const;
  ThreeArray& operator=(int32_t value);
  ThreeArray& operator[](int index);
  explicit operator int();

  friend std::ostream& operator<<(std::ostream& stream , ThreeArray& array);
  friend std::istream& operator>>(std::istream& stream , ThreeArray& array);
 private:
  int32_t x_size = 0;
  int32_t y_size = 0;
  int32_t z_size = 0;
  int32_t xIndex = -1;
  int32_t yIndex = -1;
  int32_t zIndex = -1;

  uint16_t* data_16;
  uint8_t* data_8;

  int FindPosition(int32_t x, int32_t y, int32_t z) const;
  void FindIndexArray(int32_t x, int32_t y, int32_t z, int32_t value);
  void Insert(int32_t Index, int32_t value);

};


#endif //LABWORK5_NIZAMUTDINOVEMIR_LIB_THREEARRAY_H_
