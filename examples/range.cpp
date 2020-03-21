#include <iostream>
#include "ACCBOOST/utility.hpp"
using namespace ACCBOOST;
int main()
{
  for(auto&& i: range(3)){
    std::cout << i << std::endl;
  }
  for(auto&& i: range(10, 13)){
    std::cout << i << std::endl;
  }
}
