#include <iostream>
#include <vector>
#include "ACCBOOST/utility.hpp"
using namespace ACCBOOST;
int main()
{
  std::cout << in(2, {1, 2, 3}) << std::endl;
  std::cout << in(0, {1, 2, 3}) << std::endl;
}
