#ifndef ACCBOOST_UTILITY_RANGE_IS_RANGE_HPP_
#define ACCBOOST_UTILITY_RANGE_IS_RANGE_HPP_


#include "../iterator/is_iterator.hpp"



namespace ACCBOOST
{

  template<class T>
  struct is_range: std::bool_constant<
    !std::is_reference_v<T> &&
    ACCBOOST::META::is_valid_to_begin_v<T&> &&
    ACCBOOST::META::is_valid_to_end_v<T&> &&
    ACCBOOST::is_iterator_v<ACCBOOST::META::result_of_begin<T&>>>
  {};

  template<>
  struct is_range<void>: std::false_type {};

  template<class T>
  constexpr bool is_range_v = ACCBOOST::is_range<T>::value;

  template<class T>
  struct is_bidirectional_range: std::bool_constant<
    !std::is_reference_v<T> &&
    ACCBOOST::META::is_valid_to_begin_v<T&> &&
    ACCBOOST::META::is_valid_to_end_v<T&> &&
    ACCBOOST::is_bidirectional_iterator_v<ACCBOOST::META::result_of_begin<T&>> &&
    ACCBOOST::is_bidirectional_iterator_v<ACCBOOST::META::result_of_end<T&>>>
  {};

  template<>
  struct is_bidirectional_range<void>: std::false_type {};

  template<class T>
  constexpr bool is_bidirectional_range_v = ACCBOOST::is_bidirectional_range<T>::value;

  template<class T>
  struct is_random_access_range: std::bool_constant<
    !std::is_reference_v<T> &&
    ACCBOOST::META::is_valid_to_begin_v<T&> &&
    ACCBOOST::META::is_valid_to_end_v<T&> &&
    ACCBOOST::is_random_access_iterator_v<ACCBOOST::META::result_of_begin<T&>> &&
    ACCBOOST::is_random_access_iterator_v<ACCBOOST::META::result_of_end<T&>>>
  {};

  template<>
  struct is_random_access_range<void>: std::false_type {};

  template<class T>
  constexpr bool is_random_access_range_v = ACCBOOST::is_random_access_range<T>::value;

  using std::begin;

  template<class T>
  using value_type_of_range = decltype(begin(std::declval<T&>()));

}


#endif
