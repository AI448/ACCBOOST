#include <iostream>
#include <tuple>
#include "ACCBOOST/utility.hpp"
using namespace ACCBOOST;
int main()
{
  std::tuple<std::string, double> a = {"A", 0.1};
  auto b = enumerate(a);
  std::cout << std::get<0>(std::get<0>(b)) << ' ' << std::get<1>(std::get<0>(b)) << std::endl;
  std::cout << std::get<0>(std::get<1>(b)) << ' ' << std::get<1>(std::get<1>(b)) << std::endl;
}
