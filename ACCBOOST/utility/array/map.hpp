#ifndef ACCBOOST_UTILITY_ARRAY_MAP_HPP_
#define ACCBOOST_UTILITY_ARRAY_MAP_HPP_


#include "is_array.hpp"
#include "zip.hpp"
#include "../misc.hpp"


namespace ACCBOOST
{

  /// map(f, [a, b, c]) は [f(a), f(b), f(c)] を返す．
  template<class F, class X,
    ACCBOOST_REQUIRES(ACCBOOST::is_array_v<std::remove_reference_t<X>>)>
  decltype(auto) map(F&& f, X&& x)
  {
    constexpr std::size_t N = ACCBOOST::tuple_size_v<std::remove_reference_t<X>>;
    using result_type = decltype(f(std::declval<ACCBOOST::result_type_of_get_from_array_t<X&&>>()));
    return ACCBOOST::apply([&](auto&&... y) ->decltype(auto)
    {
	    return ACCBOOST::StaticArray<ACCBOOST::capture_of<result_type&&>, N>{f(std::forward<decltype(y)>(y))...};
    }, std::forward<X>(x));
  }

  /// map(f, [a, b, c], [d, e, f]) は [f(a, d), f(b, e), f(c, f)] を返す．
  template<class F, class X, class Y, class... Z,
	   ACCBOOST_REQUIRES(ACCBOOST::is_array_v<std::remove_reference_t<X>>),
	   ACCBOOST_REQUIRES(ACCBOOST::is_array_v<std::remove_reference_t<Y>>),
	   ACCBOOST_REQUIRES((... && ACCBOOST::is_array_v<std::remove_reference_t<Z>>))>
  decltype(auto) map(F&& f, X&& x, Y&& y, Z&&... z)
  {
    auto g = [&](auto&& zipped) ->decltype(auto)
    {
      return std::apply(f, zipped);
    };
    return ACCBOOST::map(g, ACCBOOST::zip(std::forward<X>(x), std::forward<Y>(y), std::forward<Z>(z)...));
  }

}


#endif
