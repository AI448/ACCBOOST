#ifndef ACCBOOST_UTILITY_TUPLE_MAP_HPP_
#define ACCBOOST_UTILITY_TUPLE_MAP_HPP_


#include "../misc.hpp"
#include "zip.hpp"


namespace ACCBOOST
{

  /// std::tuple 用の map
  /**
   * map(f, (a, b, c)) は (f(a), f(b), f(c)) を返す．
   */
  template<class F, class X,
	   ACCBOOST_REQUIRES(ACCBOOST::is_tuple_v<std::remove_reference_t<X>>)>
  decltype(auto) map(F&& f, X&& x)
  {
    auto g = [&](auto&&... y) ->decltype(auto)
    {
      static_assert((... && std::is_invocable_v<F, decltype(y)>));
      return ACCBOOST::capture_as_tuple(f(std::forward<decltype(y)>(y))...);
    };
    return ACCBOOST::apply(g, std::forward<X>(x));
  }

  /// std::tuple 用の map 複数引数版．
  /**
   * map(f, (a, b), (c, d)) は (f(a, c), f(b, d)) を返す．
   */
  template<class F, class X, class Y, class... Z,
	   ACCBOOST_REQUIRES(ACCBOOST::is_tuple_v<std::remove_reference_t<X>> ||
			                 ACCBOOST::is_tuple_v<std::remove_reference_t<Y>> ||
			                 ( ... || ACCBOOST::is_tuple_v<std::remove_reference_t<Z>>)),  
	   ACCBOOST_REQUIRES((ACCBOOST::is_tuple_v<std::remove_reference_t<X>> || ACCBOOST::is_array_v<std::remove_reference_t<X>>) &&
			                 (ACCBOOST::is_tuple_v<std::remove_reference_t<Y>> || ACCBOOST::is_array_v<std::remove_reference_t<Y>>) &&
			                 (... && (ACCBOOST::is_tuple_v<std::remove_reference_t<Z>> || ACCBOOST::is_array_v<std::remove_reference_t<Z>>)))>
  decltype(auto) map(F&& f, X&& x, Y&& y, Z&&... z)
  {
    auto g = [&](auto&& t) ->decltype(auto)
    {
      return ACCBOOST::apply(f, std::forward<decltype(t)>(t));
    };
    return ACCBOOST::map(g, ACCBOOST::zip(std::forward<X>(x), std::forward<Y>(y), std::forward<Z>(z)...));
  }

}

#endif
