#include "chain.hpp"
#include "range.hpp"
#include "filter.hpp"
#include "TEST_UTILS.hpp"


using namespace ACCBOOST;


int main()
{
  {
    TEST_UTILS::dump(filter([](auto&& x){return x % 2 == 0;}, range(10)));
  }
  {
    auto a = range(10);
    TEST_UTILS::dump(filter([](auto&& x){return x % 2 == 0;}, a));
  }
  {
    TEST_UTILS::dump(filter([](auto&& x){return x % 2 == 0;}, {0, 1, 2, 3, 4}));
  }
  return 0;
}
