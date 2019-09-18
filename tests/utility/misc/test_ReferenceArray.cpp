#include "StaticArray.hpp"
#include "get.hpp"
#include "TEST_UTILS.hpp"


using namespace ACCBOOST;


int main()
{

  int x = 1;
  int y = 2;
  int z = 3;
  StaticArray<int&, 3> a = {x, y, z};

  TEST_UTILS::dump(a);

  a[0] = 5;
  ACCBOOST::get<1>(a) = 4;

  TEST_UTILS::dump(a);

//  std::array<int, 3> b = a;

//  TEST_UTILS::dump(b);

  return 0;
}
