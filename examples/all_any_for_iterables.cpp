#include <iostream>
#include <vector>
#include "ACCBOOST/utility.hpp"
using namespace ACCBOOST;
int main()
{
  std::vector<int> a = {1, 2, 3, 4};
  std::vector<int> b = {2, 4};
  std::vector<int> c = {1, 3, 5};
  std::cout << all([](auto&& x){return x % 2 == 0;}, a) << std::endl;
  std::cout << all([](auto&& x){return x % 2 == 0;}, b) << std::endl;
  std::cout << all([](auto&& x){return x % 2 == 0;}, c) << std::endl;    
  std::cout << any([](auto&& x){return x % 2 == 0;}, a) << std::endl;
  std::cout << any([](auto&& x){return x % 2 == 0;}, b) << std::endl;
  std::cout << any([](auto&& x){return x % 2 == 0;}, c) << std::endl;
}
