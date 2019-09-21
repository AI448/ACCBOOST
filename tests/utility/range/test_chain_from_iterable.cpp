#include "chain_from_iterable.hpp"
#include "range.hpp"
#include "map.hpp"
#include "TEST_UTILS.hpp"


using namespace ACCBOOST;


int main()
{
  TEST_UTILS::dump(chain_from_iterable(map([](auto i){return range(i + 1);}, range(5))));
  TEST_UTILS::dump(chain_from_iterable({range(3), range(4)}));
  return 0;
}
