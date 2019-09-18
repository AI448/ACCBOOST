#ifndef ACCBOOST_UTILITY_ARRAY_ENUMERATE_HPP_
#define ACCBOOST_UTILITY_ARRAY_ENUMERATE_HPP_


#include "is_array.hpp"
#include "range.hpp"
#include "zip.hpp"
#include "../misc.hpp"


namespace ACCBOOST
{

  ///
  /**
   * enumerate([a, b, c]) は [[0, a], [1, b], [2, c]] を返す．
   */
  template<class X, class... Y,
    ACCBOOST_REQUIRES(ACCBOOST::is_array_v<std::remove_reference_t<X>>),
    ACCBOOST_REQUIRES((... && ACCBOOST::is_array_v<std::remove_reference_t<Y>>))>
  decltype(auto) enumerate(X&& x, Y&&... y)
  {
    static constexpr std::size_t N = ACCBOOST::tuple_size_v<std::remove_reference_t<X>>;    
    return ACCBOOST::zip(ACCBOOST::range<N>(), std::forward<X>(x), std::forward<Y>(y)...);
  }

}

#endif
