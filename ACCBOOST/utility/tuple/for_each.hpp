#ifndef ACCBOOST_UTILITY_TUPLE_FOR_EACH_HPP_
#define ACCBOOST_UTILITY_TUPLE_FOR_EACH_HPP_


#include "../misc.hpp"
#include "is_tuple.hpp"
#include "zip.hpp"


namespace ACCBOOST
{

  namespace _impl_tuple_for_each
  {

    template<class Functor>
    void impl(Functor&&)
    {}

    template<class Functor, class X, class... Y>
    void impl(Functor& functor, X&& x, Y&&... y)
    {
      functor(std::forward<X>(x));
      ACCBOOST::_impl_tuple_for_each::impl(functor, std::forward<Y>(y)...);
    }

    template<class F, class G>
    void impl2(F&&, G&&)
    {}

    template<class F, class G, class X, class... Y>
    void impl2(F&& f, G&& g, X&& x, Y&&... y)
    {
      f(std::forward<X>(x));      
      try{
        ACCBOOST::_impl_tuple_for_each::impl2(f, g, std::forward<Y>(y)...);
      }catch(...){
        g(std::forward<X>(x));
        throw;
      }
    }

  }

  template<class F, class X,
    ACCBOOST_REQUIRES(ACCBOOST::is_tuple_v<std::remove_reference_t<X>>)>
  ACCBOOST::capture_of<F&&> for_each(F&& f, X&& x)
  {
    auto g = [&f](auto&&... x_i) ->decltype(auto)
    {
      ACCBOOST::_impl_tuple_for_each::impl(f, std::forward<decltype(x_i)>(x_i)...);
    };
    ACCBOOST::apply(g, std::forward<X>(x));
    return std::forward<F>(f);
  }

  template<class F, class G, class X,
    ACCBOOST_REQUIRES(!ACCBOOST::is_tuple_v<std::remove_reference_t<F>> && !ACCBOOST::is_array_v<std::remove_reference_t<F>>),
    ACCBOOST_REQUIRES(!ACCBOOST::is_tuple_v<std::remove_reference_t<G>> && !ACCBOOST::is_array_v<std::remove_reference_t<G>>),
    ACCBOOST_REQUIRES(ACCBOOST::is_tuple_v<std::remove_reference_t<X>>)>
  ACCBOOST::capture_of<F&&> for_each(F&& f, G&& g, X&& x)
  {
    ACCBOOST::apply([&f, &g](auto&&... x_i) ->decltype(auto)
    {
      ACCBOOST::_impl_tuple_for_each::impl2(f, g, std::forward<decltype(x_i)>(x_i)...);
    }, std::forward<X>(x));
    return std::forward<F>(f);
  }

  template<class F, class X, class Y, class... Z,
    ACCBOOST_REQUIRES(!ACCBOOST::is_tuple_v<std::remove_reference_t<F>> && !ACCBOOST::is_array_v<std::remove_reference_t<F>>),
	  ACCBOOST_REQUIRES(ACCBOOST::is_tuple_v<std::remove_reference_t<X>> ||
			                ACCBOOST::is_tuple_v<std::remove_reference_t<Y>> ||
		                  (... || ACCBOOST::is_tuple_v<std::remove_reference_t<Z>>)),
	  ACCBOOST_REQUIRES(ACCBOOST::is_tuple_v<std::remove_reference_t<X>> || ACCBOOST::is_array_v<std::remove_reference_t<X>>),
    ACCBOOST_REQUIRES(ACCBOOST::is_tuple_v<std::remove_reference_t<Y>> || ACCBOOST::is_array_v<std::remove_reference_t<Y>>),
		ACCBOOST_REQUIRES(( ... && (ACCBOOST::is_tuple_v<std::remove_reference_t<Z>> || ACCBOOST::is_array_v<std::remove_reference_t<Z>>)))>
  ACCBOOST::capture_of<F&&> for_each(F&& f, X&& x, Y&& y, Z&&... z)
  {
    auto g = [&f](auto&& xyz_i) ->decltype(auto)
    {
      ACCBOOST::apply(f, std::forward<decltype(xyz_i)>(xyz_i));
    };
    ACCBOOST::for_each(g, ACCBOOST::zip(std::forward<X>(x), std::forward<Y>(y), std::forward<Z>(z)...));
    return std::forward<F>(f);
  }

  template<class F, class G, class X, class Y, class... Z,
    ACCBOOST_REQUIRES(!ACCBOOST::is_tuple_v<std::remove_reference_t<F>> && !ACCBOOST::is_array_v<std::remove_reference_t<F>>),
    ACCBOOST_REQUIRES(!ACCBOOST::is_tuple_v<std::remove_reference_t<F>> && !ACCBOOST::is_array_v<std::remove_reference_t<F>>),    
	  ACCBOOST_REQUIRES(ACCBOOST::is_tuple_v<std::remove_reference_t<X>> ||
			                 ACCBOOST::is_tuple_v<std::remove_reference_t<Y>> ||
		                   (... || ACCBOOST::is_tuple_v<std::remove_reference_t<Z>>)),
	  ACCBOOST_REQUIRES(ACCBOOST::is_tuple_v<std::remove_reference_t<X>> || ACCBOOST::is_array_v<std::remove_reference_t<X>>),
    ACCBOOST_REQUIRES(ACCBOOST::is_tuple_v<std::remove_reference_t<Y>> || ACCBOOST::is_array_v<std::remove_reference_t<Y>>),
		ACCBOOST_REQUIRES(( ... && (ACCBOOST::is_tuple_v<std::remove_reference_t<Z>> || ACCBOOST::is_array_v<std::remove_reference_t<Z>>)))>
  ACCBOOST::capture_of<F&&> for_each(F&& f, G&& g, X&& x, Y&& y, Z&&... z)
  {
    auto f2 = [&f](auto&& xyz_i) ->decltype(auto)
    {
      ACCBOOST::apply(f, std::forward<decltype(xyz_i)>(xyz_i));
    };
    auto g2 = [&g](auto&& xyz_i) ->decltype(auto)
    {
      ACCBOOST::apply(g, std::forward<decltype(xyz_i)>(xyz_i));
    };
    ACCBOOST::for_each(f2, g2, ACCBOOST::zip(std::forward<X>(x), std::forward<Y>(y), std::forward<Z>(z)...));
    return std::forward<F>(f);
  }

}

#endif
