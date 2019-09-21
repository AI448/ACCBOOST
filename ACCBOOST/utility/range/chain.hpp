#ifndef ACCBOOST_UTILITY_RANGE_CHAIN_HPP_
#define ACCBOOST_UTILITY_RANGE_CHAIN_HPP_


#include "../misc.hpp"
#include "../array.hpp"
#include "is_range.hpp"
#include "chain_from_iterable.hpp"


namespace ACCBOOST
{

  template<class X, class... Y,
	   ACCBOOST_REQUIRES(ACCBOOST::is_range_v<std::remove_reference_t<X>>),
	   ACCBOOST_REQUIRES(!ACCBOOST::is_array_v<std::remove_reference_t<X>>),
     ACCBOOST_REQUIRES((... && std::is_same_v<X, Y>))>
  decltype(auto) chain(X&& x, Y&&... y)
  {
    return ACCBOOST::chain_from_iterable(ACCBOOST::StaticArray<ACCBOOST::capture_of<X&&>, 1 + sizeof...(Y)>{std::forward<X>(x), std::forward<Y>(y)...});
  }

}


#endif
