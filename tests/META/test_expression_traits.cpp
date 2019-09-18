#include "expression_traits.hpp"


using namespace ACCBOOST;

int main()
{
  static_assert(META::is_valid_to_pre_inclement_v<int&>); // int&
  static_assert(std::is_same_v<META::result_of_pre_inclement<int&>, int&>);
  static_assert(!META::is_valid_to_pre_inclement_v<const int&>);
  static_assert(META::is_valid_to_add_v<const int&, const int&>);
  static_assert(std::is_same_v<int, META::result_of_add<const char&, const char&>>);

  return 0;
}

