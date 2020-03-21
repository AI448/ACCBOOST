#include <iostream>
#include <vector>
#include "ACCBOOST/utility.hpp"
using namespace ACCBOOST;
int main()
{
  std::vector<int> a = {0, 1, 2, 3, 4, 5, 6};
  for(auto&& y: filter([](auto&& x){return x % 3 == 0;}, a)){
    std::cout << y << std::endl;
  }
  return 0;
}
