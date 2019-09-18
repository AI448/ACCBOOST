#include "is_base_template_of.hpp"


using namespace ACCBOOST::META;


template<class X>
class A{};

class B: public A<int>{};


int main()
{

  static_assert(!is_base_template_of_v<A, int>);
  static_assert(is_base_template_of_v<A, B>);
  static_assert(is_base_template_of_v<A, const B>);

  return 0;
}