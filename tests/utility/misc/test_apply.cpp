#include "apply.hpp"
#include <iostream>

int main()
{
  int a[] = {1, 2};

  ACCBOOST::apply([](auto&& x, auto&& y){std::cout << x << ' ' << y << std::endl;}, a);

  return 0;
  
}
