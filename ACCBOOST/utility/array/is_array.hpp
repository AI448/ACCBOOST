#ifndef ACCBOOST_UTILITY_ARRAY_IS_ARRAY_HPP_
#define ACCBOOST_UTILITY_ARRAY_IS_ARRAY_HPP_


#include "../misc.hpp"


namespace ACCBOOST
{

  template<class X>
  struct is_array: std::false_type {};

  template<class X, std::size_t N>
  struct is_array<X[N]>: std::true_type {};
    
  template<class X, std::size_t N>
  struct is_array<std::array<X, N>>: std::true_type {};
    
  template<class X, std::size_t N>
  struct is_array<const std::array<X, N>>: std::true_type {};

  template<class X, std::size_t N>
  struct is_array<volatile std::array<X, N>>: std::true_type {};

  template<class X, std::size_t N>
  struct is_array<const volatile std::array<X, N>>: std::true_type {};

  template<class X, std::size_t N>
  struct is_array<ACCBOOST::StaticReferenceArray<X, N>>: std::true_type {};
    
  template<class X, std::size_t N>
  struct is_array<const ACCBOOST::StaticReferenceArray<X, N>>: std::true_type {};

  template<class X, std::size_t N>
  struct is_array<volatile ACCBOOST::StaticReferenceArray<X, N>>: std::true_type {};

  template<class X, std::size_t N>
  struct is_array<const volatile ACCBOOST::StaticReferenceArray<X, N>>: std::true_type {};

  template<class T>
  constexpr bool is_array_v = ACCBOOST::is_array<T>::value;

}


#endif
