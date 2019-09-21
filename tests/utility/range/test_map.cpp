#include "map.hpp"
#include <vector>
#include "TEST_UTILS.hpp"


int main()
{
  {
    std::vector<int> a = {1, 2, 3, 4};
    std::vector<double> b = {0.1, 0.2, 0.3, 0.4, 0.5};
    std::vector<int> c = {10, 20, 30};
    TEST_UTILS::dump(ACCBOOST::map([](auto&& x, auto&& y, auto&& z){return x + y + z;}, a, b, c));
  }
  {
    TEST_UTILS::dump(ACCBOOST::map([](auto&& x){return x * 0.1;}, {1, 2, 3, 4}));
  }  

  return 0;
}
