
#include "ThreeArray.h"

ThreeArray::ThreeArray(int32_t xSize, int32_t ySize, int32_t zSize)
    : x_size(xSize)
    , y_size(ySize)
    , z_size(zSize)
    , xIndex(-1)
    , yIndex(-1)
    , zIndex(-1) {
  int32_t sizeArray = x_size * y_size * z_size;
  int32_t size8bit = sizeArray / 8 + 1;

  data_16 = new uint16_t [sizeArray]();
  data_8 = new uint8_t [size8bit]();
}



ThreeArray::~ThreeArray() {
  delete[] data_16;
  delete[] data_8;
}

ThreeArray ThreeArray::make_array(int32_t x, int32_t y, int32_t z) {
  return ThreeArray(x , y , z);
}

int ThreeArray::FindPosition(int32_t x, int32_t y, int32_t z) const {
  int32_t elementIndex = x * y_size * z_size + y * z_size + z;

  int32_t byteNumber = elementIndex / 8;
  int32_t bitOffset = elementIndex % 8;

  int32_t bitValue = (data_8[byteNumber] >> bitOffset) & 1;
  int32_t position = bitValue * kDegree16;

  return data_16[elementIndex] + position;
}


void ThreeArray::FindIndexArray(int32_t x, int32_t y, int32_t z, int32_t value) {
  Insert(x * y_size * z_size + y * z_size + z , value);
}

void ThreeArray::Insert(int32_t Index, int32_t value) {
  int32_t first_bit = Index / 8;
  int32_t second_bit = Index % 8;
  value%=kDegree17;

  if ((value >> 16) & 1) {
    data_8[first_bit] |= (1 << second_bit);
  } else {
    data_8[first_bit] &= ~(1 << second_bit);
  }
  data_16[Index] = value % kDegree16;
}

ThreeArray ThreeArray::operator+(ThreeArray& other) const {
  if (x_size != other.x_size || y_size != other.y_size || z_size != other.z_size) {
    std::cout << "Different sizes" << std::endl;
    exit(1);
  }

  ThreeArray result = make_array(x_size , y_size , z_size);
  int32_t size = x_size * y_size * z_size;

  for (int32_t i = 0; i < size; ++i) {
    int32_t first_bit = i / 8;
    int32_t second_bit = i % 8;

    int32_t sum = (data_16[i] + ((data_8[first_bit] >> second_bit) & 1) * kDegree17) + (other.data_16[i] + ((other.data_8[first_bit] >> second_bit) & 1) * kDegree17);
    result.Insert(i , sum);
  }
  return result;
}

ThreeArray ThreeArray::operator-(ThreeArray& other) const {
  if (x_size != other.x_size || y_size != other.y_size || z_size != other.z_size) {
    std::cout << "Ошибка: Размеры массивов не совпадают!" << std::endl;
    exit(1);
  }

  ThreeArray result = make_array(x_size , y_size , z_size);
  int32_t size = x_size * y_size * z_size;

  for (int32_t i = 0; i < size; ++i) {
    int32_t first_bit = i / 8;
    int32_t second_bit = i % 8;

    int32_t sum = data_16[i] - ((data_8[first_bit] >> second_bit) & 1) * kDegree17 -
        other.data_16[i] - ((other.data_8[first_bit] >> second_bit) & 1) * kDegree17;
    result.Insert(i , sum);
  }
  return result;
}

ThreeArray ThreeArray::operator*(int32_t value) const {
  ThreeArray result = make_array(x_size, y_size, z_size);
  int32_t size = x_size * y_size * z_size;
  for (int32_t i = 0;i < size;++i) {
    int32_t first_bit = i / 8;
    int32_t second_bit = i % 8;
    int32_t Multi = data_16[i] + ((data_8[first_bit] >> second_bit) & 1) * kDegree17;
    result.Insert(i , Multi * value);
  }
  return result;
}

ThreeArray& ThreeArray::operator=(int32_t value) {
  if (xIndex != -1 && yIndex != -1 && zIndex != -1) {
    FindIndexArray(xIndex , yIndex , zIndex , value);
    xIndex = yIndex = zIndex = -1;
  }
  return *this;
}

ThreeArray& ThreeArray::operator[](int index) {
  if (xIndex == -1) {
    xIndex = index;
  } else if (yIndex == -1){
    yIndex = index;
  } else {
    zIndex = index;
  }
  return *this;
}

ThreeArray::operator int() {
  return FindPosition(xIndex , yIndex , zIndex);
}


std::istream &operator>>(std::istream &stream, ThreeArray &array) {
  int32_t size = array.x_size * array.y_size * array.z_size;
  for (int32_t i = 0;i < size;++i) {
    int32_t value;
    stream >> value;
    array.Insert(i , value);

  }
  return stream;
}
std::ostream &operator<<(std::ostream &stream, ThreeArray &array) {
  if (array.xIndex != -1 && array.yIndex != -1 && array.zIndex != -1) {
    std::cout << array.FindPosition(array.xIndex , array.yIndex , array.zIndex);
    return stream;
  }
  for (int32_t i = 0; i < array.x_size;++i) {
    for (int32_t j = 0; j < array.y_size;++j) {
      for (int32_t k = 0;k < array.z_size;++k) {
        std::cout << array.FindPosition(i , j , k) << " ";
      }
      std::cout << "\n";
    }
    std::cout << "\n";
  }
  return stream;
}

