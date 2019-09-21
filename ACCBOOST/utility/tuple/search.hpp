#ifndef ACCBOOST_UTILITY_TUPLE_SEARCH_HPP_
#define ACCBOOST_UTILITY_TUPLE_SEARCH_HPP_


#include "is_tuple.hpp"


namespace ACCBOOST
{

  namespace _tuple_search
  {

    template<class X, class Y>
    auto compare_if_comparable(const X& x, const Y& y) ->decltype(x == y)
    {
      return x == y;
    }

    bool compare_if_comparable(...)
    {
      return false;
    }

  }

  template<class X, class T,
    ACCBOOST_REQUIRES(ACCBOOST::is_tuple_v<std::remove_reference_t<T>>)>
  bool in(X&& x, T&& t)
  {
    auto f = [&](auto&&... y)
    {
      return (... || _tuple_search::compare_if_comparable(x, y));
    };
    return ACCBOOST::apply(f, std::forward<T>(t));
  }

  template<class F, class T,
    ACCBOOST_REQUIRES(ACCBOOST::is_tuple_v<std::remove_reference_t<T>>)>
  bool all(F&& f, T&& t)
  {
    auto g = [&](auto&&... x)
    {
      return (... && f(std::forward<decltype(x)>(x)));
    };
    return ACCBOOST::apply(g, std::forward<T>(t));
  }

  template<class F, class T,
    ACCBOOST_REQUIRES(ACCBOOST::is_tuple_v<std::remove_reference_t<T>>)>
  bool any(F&& f, T&& t)
  {
    auto g = [&](auto&&... x)
    {
      return (... || f(std::forward<decltype(x)>(x)));
    };
    return ACCBOOST::apply(g, std::forward<T>(t));
  }

}

#endif
