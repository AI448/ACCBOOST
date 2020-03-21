#include <iostream>
#include <vector>
#include <list>
#include "ACCBOOST/utility.hpp"
using namespace ACCBOOST;
int main()
{
  std::vector<int> a = {1, 2, 3};
  std::list<double> b = {0.1, 0.2, 0.3};
  for(auto&& z: map([](auto&& x, auto&& y){return x + y;}, a, b)){
  std::cout << z << std::endl;
  }
  return 0;
}
