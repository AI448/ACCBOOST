#include <iostream>
#include <vector>
#include "ACCBOOST/utility.hpp"
using namespace ACCBOOST;
int main()
{
  std::vector<std::vector<int>> a = {{1, 2}, {3, 4}, {5, 6}};
  for(auto&& y: chain_from_iterable(a)){
    std::cout << y << std::endl;
  }
  return 0;
}
