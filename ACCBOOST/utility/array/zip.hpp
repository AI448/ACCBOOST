#ifndef ACCBOOST_UTILITY_ARRAY_ZIP_HPP_
#define ACCBOOST_UTILITY_ARRAY_ZIP_HPP_


#include "is_array.hpp"
#include "../misc.hpp"


namespace ACCBOOST
{

  namespace _impl_array_zip
  {

    template<std::size_t I, class... X>
    decltype(auto) sub(X&&... x)
    {
      return std::tuple<ACCBOOST::capture_of<ACCBOOST::result_type_of_get_from_array_t<X&&>>...>(ACCBOOST::get<I>(std::forward<X>(x))...);
    }

    template<std::size_t N, std::size_t... I, class... X>
    decltype(auto) impl(std::index_sequence<I...>, X&&... x)
    {
      // sub の戻り値の型を特定
      using element_type = std::tuple<ACCBOOST::capture_of<ACCBOOST::result_type_of_get_from_array_t<X&&>>...>;
      // tuple の Array を返す
      return ACCBOOST::StaticArray<element_type, N>{ACCBOOST::_impl_array_zip::sub<I>(std::forward<X>(x)...)...};
    }

  }

  /**
   *  zip([a, b, c], [d, e, f]) は [[a, d], [b, e], [c, d]] を返す．
   */
  template<class X, class... Y,
	   ACCBOOST_REQUIRES(ACCBOOST::is_array_v<std::remove_reference_t<X>>),
	   ACCBOOST_REQUIRES((... && ACCBOOST::is_array_v<std::remove_reference_t<Y>>))>
  decltype(auto) zip(X&& x, Y&&... y)
  {
    static constexpr std::size_t N = ACCBOOST::tuple_size_v<std::remove_reference_t<X>>;
    static_assert((... && (ACCBOOST::tuple_size_v<std::remove_reference_t<Y>> == N)), "Arguments of zip (for array) should be the same size.");
    return ACCBOOST::_impl_array_zip::impl<N>(std::make_index_sequence<N>(), std::forward<X>(x), std::forward<Y>(y)...);
  }

  namespace _impl_array_unzip
  {

    template<std::size_t I, std::size_t... J, class X>
    decltype(auto) sub(std::index_sequence<J...>, X&& x)
    {
      using R = ACCBOOST::capture_of<decltype(ACCBOOST::get<I>(std::declval<ACCBOOST::result_type_of_get_from_array_t<X&&>>()))>;
      static constexpr std::size_t N = sizeof...(J);
      return ACCBOOST::StaticArray<R, N>{ACCBOOST::get<I>(ACCBOOST::get<J>(std::forward<X>(x)))...};
    }

    template<std::size_t... I, class X>
    decltype(auto) impl(std::index_sequence<I...>, X&& x)
    {
      static constexpr std::size_t M = ACCBOOST::tuple_size_v<std::remove_reference_t<X>>;
      return std::make_tuple(ACCBOOST::_impl_array_unzip::sub<I>(std::make_index_sequence<M>(), std::forward<X>(x))...);
    }

  }

  /**
   * unzip([(a, d), (b, e), (c, f)]) は ([a, b, c], [d, e, f]) を返す．
   */
  template<class X,
	   ACCBOOST_REQUIRES(ACCBOOST::is_array_v<std::remove_reference_t<X>>),
	   ACCBOOST_REQUIRES(ACCBOOST::META::is_template_of_v<std::tuple, std::remove_reference_t<ACCBOOST::result_type_of_get_from_array_t<X&&>>>)>
  decltype(auto) unzip(X&& x)
  {
    static constexpr std::size_t N = ACCBOOST::tuple_size_v<std::remove_reference_t<ACCBOOST::result_type_of_get_from_array_t<X&&>>>;
    return ACCBOOST::_impl_array_unzip::impl(std::make_index_sequence<N>(), std::forward<X>(x));
  }

}


#endif
