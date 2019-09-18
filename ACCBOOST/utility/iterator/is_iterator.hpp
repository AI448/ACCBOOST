#ifndef ACCBOOST_UTILITY_ITERATOR_IS_ITERATOR_HPP_
#define ACCBOOST_UTILITY_ITERATOR_IS_ITERATOR_HPP_


#include <iterator>
#include "../misc.hpp"


namespace ACCBOOST
{

  namespace _is_iterator
  {

    struct None {};

    template<class T>
    auto test(T&) -> typename T::iterator_category;

    template<class T>
    auto test(T*&) -> std::random_access_iterator_tag;

    None test(void*&);

    None test(...);

    template<class T>
    using iterator_category_of = decltype(ACCBOOST::_is_iterator::test(std::declval<std::remove_cv_t<std::remove_reference_t<T>>&>()));

  }
  
  template<class T>
  struct is_iterator: std::bool_constant<
    !std::is_reference_v<T> &&
    std::is_base_of_v<std::input_iterator_tag, ACCBOOST::_is_iterator::iterator_category_of<T>>>
  {};

  template<class T>
  constexpr bool is_iterator_v = ACCBOOST::is_iterator<T>::value;

  template<class T>
  struct is_forward_iterator: std::bool_constant<
    !std::is_reference_v<T> &&
    std::is_base_of_v<std::forward_iterator_tag, ACCBOOST::_is_iterator::iterator_category_of<T>>>
  {};

  template<class T>
  constexpr bool is_forward_iterator_v = ACCBOOST::is_forward_iterator<T>::value;

  template<class T>
  struct is_bidirectional_iterator: std::bool_constant<
    !std::is_reference_v<T> &&
    std::is_base_of_v<std::bidirectional_iterator_tag, ACCBOOST::_is_iterator::iterator_category_of<T>>>
  {};

  template<class T>
  constexpr bool is_bidirectional_iterator_v = ACCBOOST::is_bidirectional_iterator<T>::value;

  template<class T>
  struct is_random_access_iterator: std::bool_constant<
    !std::is_reference_v<T> &&
    std::is_base_of_v<std::random_access_iterator_tag, ACCBOOST::_is_iterator::iterator_category_of<T>>>
  {};

  template<class T>
  constexpr bool is_random_access_iterator_v = ACCBOOST::is_random_access_iterator<T>::value;
  
}


#endif

