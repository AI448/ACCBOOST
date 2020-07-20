#ifndef ACCBOOST_UTILITY_MISC_SLICE_HPP_
#define ACCBOOST_UTILITY_MISC_SLICE_HPP_


#include "is_tuple.hpp"
#include "../misc.hpp"


namespace ACCBOOST
{

  namespace _slice
  {
    template<std::size_t N, std::size_t... I, class X>
    decltype(auto) impl(X&& x, std::index_sequence<I...>)
    {
      static_assert(N + I <= ACCBOOST::tuple_size<std::remove_reference_t<X>>());
      return ACCBOOST::capture_as_tuple(ACCBOOST::get<N + I>(std::forward<X>(x))...);
    }
  }


  template<std::size_t FROM, std::size_t TO, class X,
    ACCBOOST_REQUIRES(ACCBOOST::is_tuple<std::remove_reference_t<X>>())>
  decltype(auto) slice(X&& x)
  {
    static_assert(FROM <= TO);
    return ACCBOOST::_slice::impl<FROM>(std::forward<X>(x), std::make_index_sequence<TO - FROM>());
  }

}


#endif
