#include <iostream>
#include <vector>
#include "ACCBOOST/utility.hpp"
using namespace ACCBOOST;
int main()
{
  std::vector<std::string> a = {"A", "B", "C"};
  std::vector<int> b = {20, 31, 42};
  for(auto&& [i, x, y]: enumerate(a, b)){
  std::cout << i << ' ' << x << ' ' << y << std::endl;
  }
  return 0;
}
