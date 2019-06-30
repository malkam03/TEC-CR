#include <iostream>
#include <cstdint>
#include <bitset>

union fpint {
  float f;
  uint32_t i;
};

int main() {

  fpint a;
  a.f = 2.5f;
  std::cout << "f=" << a.f << "   = " << std::bitset<32>(a.i) << std::endl;

  a.f = -2.5f;
  std::cout << "f=" << a.f << "  = " << std::bitset<32>(a.i) << std::endl;
  
  a.f = 0.001f;
  std::cout << "f=" << a.f << " = " << std::bitset<32>(a.i) << std::endl;

  a.f = 1.f;
  std::cout << "f=" << a.f << "     = " << std::bitset<32>(a.i) << std::endl;

}
  
