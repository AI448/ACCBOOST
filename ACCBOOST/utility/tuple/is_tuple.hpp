#ifndef ACCBOOST_UTILITY_TUPLE_IS_TUPLE_HPP_
#define ACCBOOST_UTILITY_TUPLE_IS_TUPLE_HPP_


#include <tuple>
#include "../misc.hpp"


namespace ACCBOOST
{

  template<class T>
  struct is_tuple: ACCBOOST::META::is_template_of<std::tuple, T> {};

  template<class T>
  constexpr bool is_tuple_v = ACCBOOST::is_tuple<T>::value;

}


#endif
