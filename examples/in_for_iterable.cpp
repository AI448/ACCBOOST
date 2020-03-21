#include <iostream>
#include <vector>
#include "ACCBOOST/utility.hpp"
using namespace ACCBOOST;
int main()
{
  std::vector<double> a = {1, 1e-2, 0};
  std::cout << in(1e-2, a) << std::endl;
  std::cout << in(3, a) << std::endl;
}

