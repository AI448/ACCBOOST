#include <iostream>
#include <tuple>
#include "ACCBOOST/utility.hpp"
using namespace ACCBOOST;
int main()
{
  std::tuple<int, double, char> a = {1, 1e-2, 0};
  std::tuple<int, double, char> b = {0, 0.0, 0};  
  std::cout << all([](auto&& x){return x == 0;}, a) << std::endl;
  std::cout << all([](auto&& x){return x == 0;}, b) << std::endl;  
  std::cout << any([](auto&& x){return x == 0;}, a) << std::endl;
  std::cout << any([](auto&& x){return x == 0;}, b) << std::endl;
}
