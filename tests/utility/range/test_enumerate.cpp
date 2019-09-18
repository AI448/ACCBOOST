#include "enumerate.hpp"
#include <vector>
#include "TEST_UTILS.hpp"


int main()
{
  std::vector<int> a = {1, 2, 3};
  std::vector<double> b = {0.1, 0.2, 0.3};
  TEST_UTILS::dump(ACCBOOST::enumerate(a, b));

  return 0;
}
