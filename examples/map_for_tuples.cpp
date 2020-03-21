#include <iostream>
#include <tuple>
#include "ACCBOOST/utility.hpp"
using namespace ACCBOOST;
int main()
{
  std::tuple<int, std::string> a = {1, "Hello"};
  std::tuple<double, std::string> b = {0.1, "World"};
  auto c = map([](auto&& x, auto&& y){return x + y;}, a, b);
  std::cout << std::get<0>(c) << std::endl;
  std::cout << std::get<1>(c) << std::endl;
  return 0;
}
