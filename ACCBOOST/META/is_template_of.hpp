#ifndef ACCBOOST_META_IS_TEMPLATE_OF_HPP_
#define ACCBOOST_META_IS_TEMPLATE_OF_HPP_


#include <type_traits>


namespace ACCBOOST::META
{

  namespace _is_template_of
  {

    template<template<class...> class T, class U>
    struct impl: std::false_type {};

    template<template<class...> class T, class... U>
    struct impl<T, T<U...>>: std::true_type {};

  } // _is_template_of

  /// ある T... が存在して X<T...> == Y となる場合に std::true_type から派生する．
  template<template<class...> class X, class Y>
  struct is_template_of: META::_is_template_of::impl<X, std::remove_cv_t<Y>> {};

  /// ある T... が存在して X<T...> == Y となる場合に true となる．
  template<template<class...> class X, class Y>
  constexpr bool is_template_of_v = META::is_template_of<X, Y>::value;

}

#endif
