#include <iostream>
#include <tuple>
#include "ACCBOOST/utility.hpp"
using namespace ACCBOOST;
int main()
{
  std::tuple<int, double> a = {1, 0.1};
  std::tuple<double, char> b = {0.2, 'A'};
  auto c = zip(a, b);
  std::cout << std::get<0>(std::get<0>(c)) << ' ' << std::get<0>(std::get<1>(c)) << std::endl;
  std::cout << std::get<1>(std::get<0>(c)) << ' ' << std::get<1>(std::get<1>(c)) << std::endl;
}
