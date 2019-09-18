#ifndef ACCBOOST_UTILITY_TUPLE_ZIP_HPP_
#define ACCBOOST_UTILITY_TUPLE_ZIP_HPP_


#include "is_tuple.hpp"
#include "../misc.hpp"
#include "../array/is_array.hpp"


namespace ACCBOOST
{

  namespace _impl_tuple_zip
  {

    template<std::size_t I, class... X>
    decltype(auto) sub(X&&... x)
    {
      return ACCBOOST::capture_as_tuple(ACCBOOST::get<I>(std::forward<X>(x))...);
    }

    template<std::size_t... I, class... X>
    decltype(auto) impl(std::index_sequence<I...>, X&&... x)
    {
      return std::make_tuple(ACCBOOST::_impl_tuple_zip::sub<I>(std::forward<X>(x)...)...);
    }

  }

  /// std::tuple 用の zip
  /**
   * zip((a, b, c), (d, e, f)) は ((a, d), (b, e), (c, f)) を返す．
   */
  template<class X, class... Y,
    ACCBOOST_REQUIRES(ACCBOOST::is_tuple_v<std::remove_reference_t<X>> || ... || ACCBOOST::is_tuple_v<std::remove_reference_t<Y>>),  
    ACCBOOST_REQUIRES((ACCBOOST::is_tuple_v<std::remove_reference_t<X>> || ACCBOOST::is_array_v<std::remove_reference_t<X>>) &&
		                  ... && (ACCBOOST::is_tuple_v<std::remove_reference_t<Y>> || ACCBOOST::is_array_v<std::remove_reference_t<Y>>))>
  decltype(auto) zip(X&& x, Y&&... y)
  {
    static constexpr std::size_t N = ACCBOOST::tuple_size_v<std::remove_reference_t<X>>;
    static_assert(( ... && (ACCBOOST::tuple_size_v<std::remove_reference_t<Y>> == N)),
                  "Arguments of zip (for tuple) should be the same size.");
    return ACCBOOST::_impl_tuple_zip::impl(std::make_index_sequence<N>(), std::forward<X>(x), std::forward<Y>(y)...);
  }

  /// std::tuple 用の unzip
  /**
   * unzip(((a, d), (b, e), (c, f))) は ((a, b, c), (d, e, f)) を返す．
   */
  template<class X,
    ACCBOOST_REQUIRES(ACCBOOST::is_tuple_v<X>)>
  decltype(auto) unzip(X&& x)
  {
    return ACCBOOST::apply([](auto&&... z) ->decltype(auto)
    {
      return ACCBOOST::zip(std::forward<decltype(z)>(z)...);
    }, std::forward<X>(x));
  }

}

#endif
