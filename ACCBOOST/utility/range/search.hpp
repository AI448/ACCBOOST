#ifndef ACCBOOST_UTILITY_RANGE_SEARCH_HPP_
#define ACCBOOST_UTILITY_RANGE_SEARCH_HPP_


#include "is_range.hpp"
#include "map.hpp"


namespace ACCBOOST
{

  template<class X, class R,
    ACCBOOST_REQUIRES(ACCBOOST::is_range_v<std::remove_reference_t<R>>)>
  bool in(X&& x, R&& r)
  {
    for(auto&& y: r){ // note ranged for では r は 2 回使用されるので， forward してはいけない．
      if(x == y) return true;
    }
    return false;
  }

  template<class F, class R,
    ACCBOOST_REQUIRES(ACCBOOST::is_range_v<std::remove_reference_t<R>>)>
  bool all(F&& f, R&& r)
  {
    return !in(false, ACCBOOST::map(std::forward<F>(f), std::forward<R>(r)));
  }

  template<class F, class R,
    ACCBOOST_REQUIRES(ACCBOOST::is_range_v<std::remove_reference_t<R>>)>  
  bool any(F&& f, R&& r)
  {
    return in(true, ACCBOOST::map(std::forward<F>(f), std::forward<R>(r)));
  }

}

#endif
