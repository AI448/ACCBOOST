#include "get.hpp"
#include "StaticArray.hpp"
#include "TEST_UTILS.hpp"


using namespace ACCBOOST;


int main()
{
  int x = 1;
  int y = 2;
  int z = 3;
  
  StaticArray<int&, 3> a = {x, y, z};

  TEST_UTILS::dump(get<0>(a));

  int b[3] = {x, y, z};

  TEST_UTILS::dump(b);
  TEST_UTILS::dump(get<1>(b));

  StaticArray<int, 3> c = {x, y, z};

  TEST_UTILS::dump(get<2>(std::move(c)));

  return 0;
}
