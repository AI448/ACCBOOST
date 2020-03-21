#include <iostream>
#include <tuple>
#include "ACCBOOST/utility.hpp"
using namespace ACCBOOST;
int main()
{
  std::tuple<int, double, double> a = {1, 1e-2, 0};
  std::tuple<int, double, double> b = {2, 1e-2, -1e-1};
  std::cout << in(0, a) << std::endl;
  std::cout << in(0, b) << std::endl;  
}
