#ifndef ACCBOOST_UTILITY_ARRAY_REVERSE_HPP_
#define ACCBOOST_UTILITY_ARRAY_REVERSE_HPP_


#include "is_array.hpp"
#include "zip.hpp"
#include "../misc.hpp"



namespace ACCBOOST
{

  namespace _impl_array_reverse
  {

    template<class X, std::size_t... I>
    decltype(auto) impl(X&& x, std::index_sequence<I...>)
    {
      return ACCBOOST::StaticArray<ACCBOOST::capture_of<ACCBOOST::result_type_of_get_from_array_t<X&&>>, sizeof...(I)>{ACCBOOST::get<sizeof...(I) - I - 1>(std::forward<X>(x))...};
    }

  }

  /// reverse([a, b, c]) は [c, b, a] を返す．
  template<class X,
	   ACCBOOST_REQUIRES(ACCBOOST::is_array_v<std::remove_reference_t<X>>)>
  decltype(auto) reverse(X&& x)
  {
    return ACCBOOST::_impl_array_reverse::impl(std::forward<X>(x), std::make_index_sequence<ACCBOOST::tuple_size_v<std::remove_reference_t<X>>>());
  }

  /// reverse([a, b, c], [d, e, f]) は [[c, f], [b, e], [a, d] を返す．
  template<class X, class Y, class... Z,
	   ACCBOOST_REQUIRES(ACCBOOST::is_array_v<std::remove_reference_t<X>>),
	   ACCBOOST_REQUIRES(ACCBOOST::is_array_v<std::remove_reference_t<Y>>),
	   ACCBOOST_REQUIRES((... && ACCBOOST::is_array_v<std::remove_reference_t<Z>>))>
  decltype(auto) reverse(X&& x, Y&& y, Z&&... z)
  {
    return ACCBOOST::reverse(ACCBOOST::zip(std::forward<X>(x), std::forward<Y>(y), std::forward<Z>(z)...));
  }

}


#endif
