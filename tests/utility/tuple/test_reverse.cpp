#include "reverse.hpp"
#include "TEST_UTILS.hpp"

int main()
{
  std::tuple<int, double, char> a = {1, 0.1, 'x'};

  TEST_UTILS::dump(ACCBOOST::reverse(a));

  return 0;
}
