#ifndef ACCBOOST_UTILITY_ARRAY_CHAIN_HPP_
#define ACCBOOST_UTILITY_ARRAY_CHAIN_HPP_


#include "../misc.hpp"
#include "is_array.hpp"


namespace ACCBOOST
{

  namespace _array_chain
  {

    template<class T, std::size_t N, class X, class... Y>
    decltype(auto) sub(X&& x, Y&&... y_j)
    {
      return ACCBOOST::apply([&](auto&&... x_i) ->decltype(auto)
      {
        return ACCBOOST::StaticArray<T, N>{std::forward<decltype(x_i)>(x_i)..., std::forward<Y>(y_j)...};
      }, std::forward<X>(x));
    }

    template<class X>
    decltype(auto) impl(X&& x)
    {
      using T = ACCBOOST::capture_of<ACCBOOST::result_type_of_get_from_array_t<X&&>>;
      static constexpr std::size_t N = ACCBOOST::tuple_size_v<std::remove_reference_t<X>>;
      return ACCBOOST::apply([](auto&&... x_i)
      {
        return ACCBOOST::StaticArray<T, N>{std::forward<decltype(x_i)>(x_i)...};
      }, std::forward<X>(x));
    }

    template<class X, class Y>
    decltype(auto) impl(X&& x, Y&& y)
    {
      using L = ACCBOOST::result_type_of_get_from_array_t<X&&>;
      using R = ACCBOOST::result_type_of_get_from_array_t<Y&&>;
      using T = std::conditional_t<
        std::is_rvalue_reference_v<L> || std::is_rvalue_reference_v<R>,
        std::remove_cv_t<std::remove_reference_t<L>>,
        std::conditional_t<
          std::is_const_v<std::remove_reference_t<L>> || std::is_const_v<std::remove_reference_t<R>>,
          const std::remove_reference_t<L>&,
          L>>;
      constexpr std::size_t N = ACCBOOST::tuple_size_v<std::remove_reference_t<X>> + ACCBOOST::tuple_size_v<std::remove_reference_t<Y>>;
      return ACCBOOST::apply([&](auto&&... y_j)->decltype(auto)
      {
        // note: ラムダ式を入れ子にしてコンパイラのバグっぽいものに遭遇したことがあるので， sub を呼び出す実装にしている．
        return ACCBOOST::_array_chain::sub<T, N>(std::forward<X>(x), std::forward<decltype(y_j)>(y_j)...);
      }, std::forward<Y>(y));
    }

  }

  template<class X,
    ACCBOOST_REQUIRES(ACCBOOST::is_array_v<std::remove_reference_t<X>>)>
  decltype(auto) chain(X&& x)
  {
    return ACCBOOST::_array_chain::impl(std::forward<X>(x));
  }

  template<class X, class Y, class... Z,
    ACCBOOST_REQUIRES(ACCBOOST::is_array_v<std::remove_reference_t<X>>),
    ACCBOOST_REQUIRES(ACCBOOST::is_array_v<std::remove_reference_t<Y>>),
    ACCBOOST_REQUIRES((... && ACCBOOST::is_array_v<std::remove_reference_t<Z>>))>
  decltype(auto) chain(X&& x, Y&& y, Z&&... z)
  {
    return ACCBOOST::chain(ACCBOOST::_array_chain::impl(std::forward<X>(x), std::forward<Y>(y)), std::forward<Z>(z)...);
  }

}


#endif
