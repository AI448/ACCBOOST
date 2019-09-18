#ifndef ACCBOOST_UTILITY_TUPLE_ENUMERATE_HPP_
#define ACCBOOST_UTILITY_TUPLE_ENUMERATE_HPP_


#include "../misc.hpp"
#include "../array.hpp"
#include "zip.hpp"


namespace ACCBOOST
{
  /// std::tuple 用の enumerate．
  /**
   *  enumerate([a, b, c]) は [[0, a], [1, b], [2, c]] を返す．
   */
  template<class X, class... Y,
    ACCBOOST_REQUIRES(ACCBOOST::is_tuple_v<std::remove_reference_t<X>> ||
		                  (... || ACCBOOST::is_tuple_v<std::remove_reference_t<Y>>)),
    ACCBOOST_REQUIRES((ACCBOOST::is_tuple_v<std::remove_reference_t<X>> || ACCBOOST::is_array_v<std::remove_reference_t<X>>) &&
		                  (... && (ACCBOOST::is_tuple_v<std::remove_reference_t<Y>> || ACCBOOST::is_array_v<std::remove_reference_t<Y>>)))>
  decltype(auto) enumerate(X&& x, Y&&... y)
  {
    static constexpr std::size_t N = ACCBOOST::tuple_size_v<std::remove_reference_t<X>>;
    return ACCBOOST::zip(ACCBOOST::range<N>(), std::forward<X>(x), std::forward<Y>(y)...);
  }

}

#endif
