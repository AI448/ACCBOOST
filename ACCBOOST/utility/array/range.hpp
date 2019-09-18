#ifndef ACCBOOST_UTILITY_ARRAY_RANGE_HPP_
#define ACCBOOST_UTILITY_ARRAY_RANGE_HPP_


#include "../misc.hpp"


namespace ACCBOOST
{

  namespace _impl_array_range
  {

    template<std::size_t... I>
    decltype(auto) impl(std::index_sequence<I...>)
    {
      return std::array<std::size_t, sizeof...(I)>{I...};
    }
    
  }

  /// range<N>() は [0, 1, ..., N] を返す．
  template<std::size_t N>
  decltype(auto) range() noexcept
  {
    return ACCBOOST::_impl_array_range::impl(std::make_index_sequence<N>());
  }

}


#endif
