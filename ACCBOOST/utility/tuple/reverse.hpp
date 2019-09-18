#ifndef ACCBOOST_UTILITY_TUPLE_REVERSE_HPP_
#define ACCBOOST_UTILITY_TUPLE_REVERSE_HPP_


#include "../misc.hpp"
#include "zip.hpp"


namespace ACCBOOST
{

  namespace _tuple_reverse
  {

    template<class X, std::size_t... I>
    decltype(auto) impl(X&& x, std::index_sequence<I...>)
    {
      return ACCBOOST::capture_as_tuple(ACCBOOST::get<sizeof...(I) - I - 1>(std::forward<X>(x))...);
    }

  } // _tuple_reverse

  /// std::tuple 用の reverse
  template<class X,
    ACCBOOST_REQUIRES(ACCBOOST::is_tuple_v<std::remove_reference_t<X>>)>
  decltype(auto) reverse(X&& x)
  {
    static constexpr std::size_t N = std::tuple_size_v<std::remove_reference_t<X>>;
    return ACCBOOST::_tuple_reverse::impl(std::forward<X>(x), std::make_index_sequence<N>());
  }

  /// std::tuple 用の reverse 複数引数版
  template<class X, class Y, class... Z,
    ACCBOOST_REQUIRES(ACCBOOST::is_tuple_v<std::remove_reference_t<X>> ||
                      ACCBOOST::is_tuple_v<std::remove_reference_t<Y>> ||
	                    (... || ACCBOOST::is_tuple_v<std::remove_reference_t<Z>>)),
    ACCBOOST_REQUIRES((ACCBOOST::is_tuple_v<std::remove_reference_t<X>> || ACCBOOST::is_array_v<std::remove_reference_t<X>>) &&
                      (ACCBOOST::is_tuple_v<std::remove_reference_t<Y>> || ACCBOOST::is_array_v<std::remove_reference_t<Y>>) &&
                      (... && (ACCBOOST::is_tuple_v<std::remove_reference_t<Z>> || ACCBOOST::is_array_v<std::remove_reference_t<Z>>)))>
  decltype(auto) reverse(X&& x, Y&& y, Z&&... z)
  {
    return ACCBOOST::reverse(ACCBOOST::zip(std::forward<X>(x), std::forward<Y>(y), std::forward<Z>(z)...));
  }

}


#endif
