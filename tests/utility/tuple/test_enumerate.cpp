#include "enumerate.hpp"
#include "TEST_UTILS.hpp"


int main()
{
  std::tuple<int, double> a = {1, 0.1};

  TEST_UTILS::dump(ACCBOOST::enumerate(a));
  
}
