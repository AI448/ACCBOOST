#ifndef ACCBOOST_UTILITY_TUPLE_CHAIN_HPP_
#define ACCBOOST_UTILITY_TUPLE_CHAIN_HPP_


#include "../misc.hpp"
#include "../array.hpp"
#include "is_tuple.hpp"


namespace ACCBOOST
{

  namespace _tuple_chain
  {

    template<class X, class... Y>
    decltype(auto) sub(X&& x, Y&&... y_j)
    {
      return ACCBOOST::apply([&](auto&&... x_i) ->decltype(auto)
      {
        return ACCBOOST::capture_as_tuple(std::forward<decltype(x_i)>(x_i)..., std::forward<Y>(y_j)...);
      }, std::forward<X>(x));
    }

    template<class X>
    decltype(auto) impl(X&& x)
    {
      return ACCBOOST::apply([](auto&&... x_i)
      {
        return ACCBOOST::capture_as_tuple(std::forward<decltype(x_i)>(x_i)...);
      }, std::forward<X>(x));
    }

    template<class X, class Y>
    decltype(auto) impl(X&& x, Y&& y)
    {
      return ACCBOOST::apply([&](auto&&... y_j)->decltype(auto)
      {
        // note: ラムダ式を入れ子にしてコンパイラのバグっぽいものに遭遇したことがあるので， sub を呼び出す実装にしている．
        return ACCBOOST::_tuple_chain::sub(std::forward<X>(x), std::forward<decltype(y_j)>(y_j)...);
      }, std::forward<Y>(y));
    }

  }

  template<class X,
    ACCBOOST_REQUIRES(ACCBOOST::is_tuple_v<std::remove_reference_t<X>>)>
  decltype(auto) chain(X&& x)
  {
    return ACCBOOST::_tuple_chain::impl(std::forward<X>(x));
  }

  /// 2 つの tuple を結合した tuple を返す．
  /**
   * 引数の tuple の要素が右辺値参照型である場合には非参照型に変換される．
   */
  template<class X, class Y,
    ACCBOOST_REQUIRES((ACCBOOST::is_tuple_v<std::remove_reference_t<X>> || ACCBOOST::is_array_v<std::remove_reference_t<X>>) &&
                      (ACCBOOST::is_tuple_v<std::remove_reference_t<Y>> || ACCBOOST::is_array_v<std::remove_reference_t<Y>>)),
    ACCBOOST_REQUIRES(ACCBOOST::is_tuple_v<std::remove_reference_t<X>> || ACCBOOST::is_tuple_v<std::remove_reference_t<Y>>)>
  decltype(auto) chain(X&& x, Y&& y)
  {
    return ACCBOOST::_tuple_chain::impl(std::forward<X>(x), std::forward<Y>(y));
  }

  template<class X, class Y, class... Z,
    ACCBOOST_REQUIRES(sizeof...(Z) >= 1),
    ACCBOOST_REQUIRES(ACCBOOST::is_tuple_v<std::remove_reference_t<X>> || ACCBOOST::is_array_v<std::remove_reference_t<X>>),
    ACCBOOST_REQUIRES(ACCBOOST::is_tuple_v<std::remove_reference_t<Y>> || ACCBOOST::is_array_v<std::remove_reference_t<Y>>),
    ACCBOOST_REQUIRES((... && (ACCBOOST::is_tuple_v<std::remove_reference_t<Z>> || ACCBOOST::is_array_v<std::remove_reference_t<Z>>))),
    ACCBOOST_REQUIRES(ACCBOOST::is_tuple_v<std::remove_reference_t<X>> || ACCBOOST::is_tuple_v<std::remove_reference_t<Y>> || (... || ACCBOOST::is_tuple_v<std::remove_reference_t<Z>>))>
  decltype(auto) chain(X&& x, Y&& y, Z&&... z)
  {
    return ACCBOOST::chain(ACCBOOST::chain(std::forward<X>(x), std::forward<Y>(y)), std::forward<Z>(z)...);
  }

}


#endif
