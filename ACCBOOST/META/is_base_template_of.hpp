#ifndef ACCBOOST_META_IS_BASE_TEMPLATE_OF_HPP_
#define ACCBOOST_META_IS_BASE_TEMPLATE_OF_HPP_


#include <type_traits>


namespace ACCBOOST::META
{

  namespace _is_base_template_of
  {

    template<template<class...> class  X, class... T>
    std::true_type test(const volatile X<T...>*);

    template<template<class...> class>
    std::false_type test(const volatile void*);

    template<template<class...> class X, class Y>
    struct impl: decltype(_is_base_template_of::test<X>(std::declval<Y*>())) {};

  }

  // note: Y が void のときに正しく動かない気がする．いずれ治す．
  template<template<class...> class X, class Y>
  struct is_base_template_of: META::_is_base_template_of::impl<X, std::remove_cv_t<Y>> {};

  template<template<class...> class X, class Y>
  constexpr bool is_base_template_of_v = META::is_base_template_of<X, Y>::value;

}


#endif