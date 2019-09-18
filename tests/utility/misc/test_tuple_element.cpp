#include <array>
#include <iostream>
#include "tuple_element.hpp"


int main()
{
  int a[2];
  std::array<int, 2> b;
  std::tuple<int, double> c;

  std::cout << std::is_same_v<ACCBOOST::tuple_element_t<0, decltype(a)>, int> << std::endl;
  std::cout << std::is_same_v<ACCBOOST::tuple_element_t<0, decltype(b)>, int> << std::endl;  
  std::cout << std::is_same_v<ACCBOOST::tuple_element_t<0, decltype(c)>, int> << std::endl;

  return 0;
}
