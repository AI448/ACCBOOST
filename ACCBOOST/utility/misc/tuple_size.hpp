#ifndef ACCBOOST_UTILITY_MISC_TUPLE_SIZE_HPP_
#define ACCBOOST_UTILITY_MISC_TUPLE_SIZE_HPP_


#include <array>
#include <tuple>


namespace ACCBOOST
{

  /// T 要素数を返すメタ関数．
  /**
   * 配列にも対応している．
   */
  template<class T>
  struct tuple_size: std::tuple_size<T> {};

  template<class T, std::size_t N>
  struct tuple_size<T[N]>: std::integral_constant<std::size_t, N> {};

  /// T の要素数．
  template<class T>
  constexpr std::size_t tuple_size_v = ACCBOOST::tuple_size<T>::value;

}


#endif
