#include <iostream>
#include <vector>
#include "ACCBOOST/utility.hpp"
using namespace ACCBOOST;
int main()
{
  std::cout << all([](auto&& x){return x % 2 == 0;}, {1, 2, 3, 4}) << std::endl;
  std::cout << all([](auto&& x){return x % 2 == 0;}, {2, 4}) << std::endl;
  std::cout << all([](auto&& x){return x % 2 == 0;}, {1, 3, 5}) << std::endl;    
  std::cout << any([](auto&& x){return x % 2 == 0;}, {1, 2, 3, 4}) << std::endl;
  std::cout << any([](auto&& x){return x % 2 == 0;}, {2, 4}) << std::endl;
  std::cout << any([](auto&& x){return x % 2 == 0;}, {1, 3, 5}) << std::endl;
}
