#ifndef ACCBOOST_UTILITY_MISC_APPLY_HPP_
#define ACCBOOST_UTILITY_MISC_APPLY_HPP_


#include <tuple>
#include <array>
#include "tuple_size.hpp"
#include "tuple_element.hpp"
#include "get.hpp"


namespace ACCBOOST
{

  namespace _impl_apply
  {

      template<class F, class X, std::size_t... I>
      decltype(auto) impl(F&& f, X&& x, std::index_sequence<I...>)
      {
        static_assert(std::is_invocable_v<F&&, decltype(ACCBOOST::get<I>(std::forward<X>(x)))...>);
        return std::forward<F>(f)(ACCBOOST::get<I>(std::forward<X>(x))...);
      }
  }

  /// x を展開して f に適用する．
  /**
   * std::get ではなく ACCBOOST::get を使用していることを除き， std::array と同じ．
   */
  template<class F, class X>
  decltype(auto) apply(F&& f, X&& x)
  {
    static constexpr std::size_t N = ACCBOOST::tuple_size_v<std::remove_reference_t<X>>;
    return _impl_apply::impl(std::forward<F>(f), std::forward<X>(x), std::make_index_sequence<N>());
  }

}

#endif
