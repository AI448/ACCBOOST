#include "map.hpp"
#include "TEST_UTILS.hpp"


int main()
{
  std::tuple<int, double> a = {1, 0.1};
  std::tuple<int, double> b = {2, 0.2};
  TEST_UTILS::dump(ACCBOOST::map([](auto&& x, auto&& y){return x + y;}, a, b));
  
  return 0;
}
