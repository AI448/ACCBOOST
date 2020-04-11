#include "list.hpp"
#include <iostream>
#include "TEST_UTILS.hpp"

int main()
{
  using list0 = ACCBOOST::META::list<>;
  using list1 = ACCBOOST::META::list<char, char&, const char&>;  
  using list2 = ACCBOOST::META::list<int, int&, const int&>;
  using list3 = ACCBOOST::META::list<double, double&, const double&>;  

  std::cout << TEST_UTILS::demangle<ACCBOOST::META::product<>>() << std::endl;
  std::cout << TEST_UTILS::demangle<ACCBOOST::META::product<list0>>() << std::endl;
  std::cout << TEST_UTILS::demangle<ACCBOOST::META::product<list0, list1>>() << std::endl;  
  std::cout << TEST_UTILS::demangle<ACCBOOST::META::product<list1, list0>>() << std::endl;
  std::cout << TEST_UTILS::demangle<ACCBOOST::META::product<list1>>() << std::endl;
  std::cout << TEST_UTILS::demangle<ACCBOOST::META::product<list1, list2>>() << std::endl;
  std::cout << TEST_UTILS::demangle<ACCBOOST::META::product<list1, list2, list3>>() << std::endl;

  return 0;
}