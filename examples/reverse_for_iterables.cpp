#include <iostream>
#include <vector>
#include "ACCBOOST/utility.hpp"
using namespace ACCBOOST;
int main()
{
  std::vector<int> a = {1, 2, 3, 4};
  for(auto&& x: reverse(a)){
    std::cout << x << std::endl;
  }
}
