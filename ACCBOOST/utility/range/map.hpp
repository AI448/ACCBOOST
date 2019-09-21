#ifndef ACCBOOST_UTILITY_RANGE_MAP_HPP_
#define ACCBOOST_UTILITY_RANGE_MAP_HPP_


#include "../misc.hpp"
#include "../iterator.hpp"
#include "zip.hpp"


namespace ACCBOOST
{

  namespace _range_map
  {

    template<class FunctorT, class RangeT>
    class MapRange
    {
      static_assert(!std::is_rvalue_reference_v<FunctorT>);
      static_assert(!std::is_const_v<FunctorT>);
      static_assert(!std::is_rvalue_reference_v<RangeT>);
      static_assert(!std::is_const_v<RangeT>);

    private:

      FunctorT functor_;
      RangeT range_;

    public:

      template<class FT, class RT>
      MapRange(FT&& functor, RT&& range):
        functor_(std::forward<FT>(functor)), range_(std::forward<RT>(range))
      {}

      MapRange() = default;
      MapRange(MapRange&&) = default;
      MapRange(const MapRange&) = default;
      MapRange& operator=(MapRange&&) = default;
      MapRange& operator=(const MapRange&) = default;

      decltype(auto) begin() const
      {
        using std::begin;
        return ACCBOOST::make_map_iterator(functor_, begin(range_));
      }

      decltype(auto) end() const
      {
        using std::end;
        return ACCBOOST::make_map_iterator(functor_, end(range_));
      }

      decltype(auto) begin()
      {
        using std::begin;
        return ACCBOOST::make_map_iterator(functor_, begin(range_));
      }

      decltype(auto) end()
      {
        using std::end;
        return ACCBOOST::make_map_iterator(functor_, end(range_));
      }

    };

    namespace _make_one_argument_function
    {

      template<class F>
      struct Impl
      {
      private:
  
      	F f_;

      public:

        Impl(F&& f): f_(std::forward<F>(f)) {}

        Impl() = default;
        Impl(Impl&&) = default;
        Impl(const Impl&) = default;
        Impl& operator=(Impl&&) = default;
        Impl& operator=(const Impl&) = default;

        template<class X>
        decltype(auto) operator()(X&& x) const
        {
          return ACCBOOST::apply(f_, std::forward<X>(x));
        }

      };

    }

    template<class F>
    decltype(auto) make_one_argument_function(F&& f)
    {
      // note この関数名でこの機能は変だろうか...
      return ACCBOOST::_range_map::_make_one_argument_function::Impl<ACCBOOST::capture_of<F&&>>(std::forward<F>(f));
    }

  } // _range_map

  template<class F, class X,
	    ACCBOOST_REQUIRES(ACCBOOST::is_range_v<std::remove_reference_t<X>>),
	    ACCBOOST_REQUIRES(!ACCBOOST::is_array_v<std::remove_reference_t<X>>)>
  decltype(auto) map(F&& f, X&& x)
  {
    return ACCBOOST::_range_map::MapRange<ACCBOOST::capture_of<F&&>, ACCBOOST::capture_of<X&&>>(std::forward<F>(f), std::forward<X>(x));
  }

  template<class F, class... X,
      ACCBOOST_REQUIRES(sizeof...(X) >= 2),
	    ACCBOOST_REQUIRES((... && ACCBOOST::is_range_v<std::remove_reference_t<X>>)),
	    ACCBOOST_REQUIRES(!(... && ACCBOOST::is_array_v<std::remove_reference_t<X>>))>
  decltype(auto) map(F&& f, X&&... x)
  {
    return ACCBOOST::map(ACCBOOST::_range_map::make_one_argument_function(std::forward<F>(f)), ACCBOOST::zip(std::forward<X>(x)...));
  }

  template<class F, class X>
  decltype(auto) map(F&& f, const std::initializer_list<X>& x)
  {
    return ACCBOOST::_range_map::MapRange<ACCBOOST::capture_of<F&&>, const std::initializer_list<X>&>(std::forward<F>(f), x);
  }

  template<class F, class X>
  decltype(auto) map(F&& f, std::initializer_list<X>& x)
  {
    return ACCBOOST::_range_map::MapRange<ACCBOOST::capture_of<F&&>, std::initializer_list<X>&>(std::forward<F>(f), x);
  }

  template<class F, class X>
  decltype(auto) map(F&& f, std::initializer_list<X>&& x)
  {
    return ACCBOOST::_range_map::MapRange<ACCBOOST::capture_of<F&&>, std::initializer_list<X>>(std::forward<F>(f), std::move(x));
  }

}


#endif
