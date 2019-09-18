#include "map.hpp"
#include "TEST_UTILS.hpp"


int main()
{
  std::array<int, 2> a = {1, 2};

  TEST_UTILS::dump(ACCBOOST::map([](auto&& i){return i * 2;}, a));

  int b[] = {2, 3};

  TEST_UTILS::dump(ACCBOOST::map([](auto&& i){return i * 2;}, b));

  TEST_UTILS::dump(ACCBOOST::map([](auto&& i, auto&& j){return i + j;}, a, b));
  
  TEST_UTILS::dump(ACCBOOST::map([](auto&& i)->decltype(auto){return std::forward<decltype(i)>(i);}, a));
  TEST_UTILS::dump(ACCBOOST::map([](auto&& i)->decltype(auto){return std::forward<decltype(i)>(i);}, std::move(a)));

  return 0;
}
