#ifndef ACCBOOST_UTILITY_RANGE_FILTER_HPP_
#define ACCBOOST_UTILITY_RANGE_FILTER_HPP_


#include "../iterator.hpp"
#include "is_range.hpp"


namespace ACCBOOST
{

  namespace _range_filter
  {

    template<class FunctorT, class RangeT>
    class FilterRange
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
      FilterRange(FT&& functor, RT&& range):
        functor_(std::forward<FT>(functor)), range_(std::forward<RT>(range))
      {}

      FilterRange() = default;
      FilterRange(FilterRange&&) = default;
      FilterRange(const FilterRange&) = default;
      FilterRange& operator=(FilterRange&&) = default;
      FilterRange& operator=(const FilterRange&) = default;

      decltype(auto) begin() const
      {
        using std::begin;
        using std::end;
        return ACCBOOST::make_filter_iterator(functor_, begin(range_), end(range_));
      }

      decltype(auto) end() const
      {
        using std::begin;
        using std::end;
        return ACCBOOST::make_last_filter_iterator(functor_, begin(range_), end(range_));
      }

      decltype(auto) begin()
      {
        using std::begin;
        using std::end;
        return ACCBOOST::make_filter_iterator(functor_, begin(range_), end(range_));
      }

      decltype(auto) end()
      {
        using std::begin;
        using std::end;
        return ACCBOOST::make_last_filter_iterator(functor_, begin(range_), end(range_));
      }

    };

  }

  template<class F, class X>
  decltype(auto) filter(F&& f, X&& x)
  {
    return ACCBOOST::_range_filter::FilterRange<ACCBOOST::capture_of<F&&>, ACCBOOST::capture_of<X&&>>(std::forward<F>(f), std::forward<X>(x));
  }

}

#endif
