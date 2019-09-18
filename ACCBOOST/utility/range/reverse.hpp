#ifndef ACCBOOST_UTILITY_RANGE_REVERSE_HPP_
#define ACCBOOST_UTILITY_RANGE_REVERSE_HPP_


#include "../misc.hpp"
#include "../iterator.hpp"
#include "is_range.hpp"
#include "zip.hpp"


namespace ACCBOOST
{

  namespace _range_reverse
  {

    template<class RangeT>
    class ReverseRange
    {
      static_assert(!std::is_rvalue_reference_v<RangeT>);
      static_assert(!std::is_const_v<RangeT>);

    private:

      RangeT range_;

    public:

      template<class T,
        ACCBOOST_REQUIRES(!std::is_same_v<std::remove_cv_t<std::remove_reference_t<T>>, ReverseRange>)>
      explicit ReverseRange(T&& range):
        range_(std::forward<T>(range))
      {}

      ReverseRange() = default;
      ReverseRange(ReverseRange&&) = default;
      ReverseRange(const ReverseRange&) = default;
      ReverseRange& operator=(ReverseRange&&) = default;
      ReverseRange& operator=(const ReverseRange&) = default;

      decltype(auto) begin()
      {
        using std::end;
        return ACCBOOST::make_reverse_iterator(--end(range_));
      }

      decltype(auto) end()
      {
        using std::begin;
        return ACCBOOST::make_reverse_iterator(--begin(range_));
      }

      decltype(auto) begin() const
      {
        using std::end;
        return ACCBOOST::make_reverse_iterator(--end(range_));
      }

      decltype(auto) end() const
      {
        using std::begin;
        return ACCBOOST::make_reverse_iterator(--begin(range_));
      }

    };

  }

  template<class X,
	   ACCBOOST_REQUIRES(ACCBOOST::is_bidirectional_range_v<std::remove_reference_t<X>>),
	   ACCBOOST_REQUIRES(!ACCBOOST::is_array_v<std::remove_reference_t<X>>)>
  decltype(auto) reverse(X&& x)
  {
    return ACCBOOST::_range_reverse::ReverseRange<ACCBOOST::capture_of<X>>(std::forward<X>(x));
  }

  /**
   * reverse(x, y, z) は， zip(reverse(x), reverse(y), reverse(z)) と等価．
   * reverse(zip(x, y, z)) ではないことに注意．
   */
  template<class... X,
      ACCBOOST_REQUIRES(sizeof...(X) >= 2),
 	    ACCBOOST_REQUIRES((... && ACCBOOST::is_bidirectional_range_v<std::remove_reference_t<X>>)),
	    ACCBOOST_REQUIRES(!(... && ACCBOOST::is_array_v<std::remove_reference_t<X>>))>
  decltype(auto) reverse(X&&... x)
  {
    return ACCBOOST::zip(ACCBOOST::reverse(std::forward<X>(x))...);
  }

}



#endif
