#ifndef ACCBOOST_UTILITY_MISC_TUPLE_ELEMENT_HPP_
#define ACCBOOST_UTILITY_MISC_TUPLE_ELEMENT_HPP_


#include <array>
#include <tuple>


namespace ACCBOOST
{

  /// T の I 番目の要素の型を返すメタ関数．
  /**
   * 配列にも対応している．
   */
  template<std::size_t I, class T>
  class tuple_element: public std::tuple_element<I, T> {};

  template<std::size_t I, class T, std::size_t N>
  class tuple_element<I, T[N]>
  {
  public:
    using type = T;
  };

  /// T の I 番目の要素の型．
  template<std::size_t I, class T>
  using tuple_element_t = typename ACCBOOST::tuple_element<I, T>::type;

}


#endif
