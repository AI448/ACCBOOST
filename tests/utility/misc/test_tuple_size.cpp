#include <array>
#include <iostream>
#include "tuple_size.hpp"

int main()
{
  int a[2];
  std::array<int, 2> b;
  std::tuple<int, double> c;
  
  std::cout << ACCBOOST::tuple_size<decltype(a)>::value << std::endl;
  std::cout << ACCBOOST::tuple_size<decltype(b)>::value << std::endl;
  std::cout << ACCBOOST::tuple_size<decltype(c)>::value << std::endl;    

  return 0;
}
