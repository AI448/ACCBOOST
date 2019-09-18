#include  "chain.hpp"
#include "TEST_UTILS.hpp"


int main()
{

  std::tuple<int, double, char> a = {1, 2.2, 'c'};
  std::tuple<std::string, double> b = {"four", 5.5};

  TEST_UTILS::dump(ACCBOOST::chain(a));

  TEST_UTILS::dump(ACCBOOST::chain(a, std::move(b)));

  TEST_UTILS::dump(ACCBOOST::chain(a, a, a));  

  return 0;
}
