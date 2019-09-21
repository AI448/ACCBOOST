#ifndef ACCBOOST_UTILITY_RANGE_ENUMERATE_HPP_
#define ACCBOOST_UTILITY_RANGE_ENUMERATE_HPP_


#include "../misc.hpp"
#include "../tuple.hpp"
#include "../iterator.hpp"
#include "is_range.hpp"
#include <algorithm>


namespace ACCBOOST
{

  namespace _range_enumerate
  {

    template<class... RangesT>
    class EnumerateRange
    {
      static_assert(!(... && std::is_rvalue_reference_v<RangesT>));
      static_assert(!(... && std::is_const_v<RangesT>));
    
    private:

      std::tuple<RangesT...> ranges_;

    public:

      template<class... RT,
        ACCBOOST_REQUIRES(sizeof...(RT) == sizeof...(RangesT))>

      explicit EnumerateRange(RT&&... ranges):
        ranges_(std::forward<RT>(ranges)...)
      {}

      EnumerateRange() = default;

      EnumerateRange(EnumerateRange&&) = default;

      EnumerateRange(const EnumerateRange&) = default;

      EnumerateRange& operator=(EnumerateRange&&) = default;

      EnumerateRange& operator=(const EnumerateRange&) = default;

      decltype(auto) begin() const
      {
        using std::begin;
        if constexpr ((... && ACCBOOST::is_random_access_range_v<std::remove_reference_t<RangesT>>)){
	        return ACCBOOST::apply([](auto&... r) ->decltype(auto)
	        {
	          return ACCBOOST::make_random_access_enumerated_iterator(0, begin(r)...);
	        }, ranges_);
        }else{
          return ACCBOOST::apply([](auto&... r) ->decltype(auto)
	        {
	          return ACCBOOST::make_enumerated_iterator(0, begin(r)...);
	        }, ranges_);          
        }
      }

      decltype(auto) end() const
      {
        using std::begin;        
        using std::end;
        if constexpr ((... && ACCBOOST::is_random_access_range_v<std::remove_reference_t<RangesT>>)){
          auto distances = ACCBOOST::map([](const auto& r){return end(r) - begin(r);}, ranges_);
          std::ptrdiff_t min_distance = ACCBOOST::apply([](const auto&... d){return std::min<std::ptrdiff_t>({d...});}, distances);
          return ACCBOOST::apply([min_distance](auto&... r) ->decltype(auto)
	        {
	          return ACCBOOST::make_random_access_enumerated_iterator(min_distance, begin(r) + min_distance...);
	        }, ranges_);
        }else{
          return ACCBOOST::apply([](auto&... r) ->decltype(auto)
	        {
	          return ACCBOOST::make_enumerated_iterator(std::numeric_limits<std::ptrdiff_t>::max(), end(r)...);
	        }, ranges_);
        }
      }

      decltype(auto) begin()
      {
        using std::begin;
        if constexpr ((... && ACCBOOST::is_random_access_range_v<std::remove_reference_t<RangesT>>)){
	        return ACCBOOST::apply([](auto&... r) ->decltype(auto)
	        {
	          return ACCBOOST::make_random_access_enumerated_iterator(0, begin(r)...);
	        }, ranges_);
        }else{
          return ACCBOOST::apply([](auto&... r) ->decltype(auto)
	        {
	          return ACCBOOST::make_enumerated_iterator(0, begin(r)...);
	        }, ranges_);
        }
      }

      decltype(auto) end()
      {
        using std::begin;
        using std::end;
        if constexpr ((... && ACCBOOST::is_random_access_range_v<std::remove_reference_t<RangesT>>)){
          auto distances = ACCBOOST::map([](const auto& r){return end(r) - begin(r);}, ranges_);
          std::ptrdiff_t min_distance = ACCBOOST::apply([](auto&... d){return std::min<std::ptrdiff_t>({d...});}, distances);
          return ACCBOOST::apply([min_distance](auto&... r) ->decltype(auto)
	        {
	          return ACCBOOST::make_random_access_enumerated_iterator(min_distance, begin(r) + min_distance...);
	        }, ranges_);
        }else{
          return ACCBOOST::apply([](auto&... r) ->decltype(auto)
	        {
	          return ACCBOOST::make_enumerated_iterator(std::numeric_limits<std::ptrdiff_t>::max(), end(r)...);
	        }, ranges_);
        }
      }

    };

  } // _range_enumerate

  template<class... X,
      ACCBOOST_REQUIRES(sizeof...(X) >= 1),
	    ACCBOOST_REQUIRES((... && ACCBOOST::is_range_v<std::remove_reference_t<X>>)),
      ACCBOOST_REQUIRES((... || !ACCBOOST::is_array_v<std::remove_reference_t<X>>))>
  decltype(auto) enumerate(X&&... x)
  {
    return ACCBOOST::_range_enumerate::EnumerateRange<ACCBOOST::capture_of<X&&>...>(std::forward<X>(x)...);
  }

  template<class X>
  decltype(auto) enumerate(const std::initializer_list<X>& x)
  {
    return ACCBOOST::_range_enumerate::EnumerateRange<const std::initializer_list<X>&>(x);
  }

  template<class X>
  decltype(auto) enumerate(std::initializer_list<X>& x)
  {
    return ACCBOOST::_range_enumerate::EnumerateRange<std::initializer_list<X>&>(x);
  }

  template<class X>
  decltype(auto) enumerate(std::initializer_list<X>&& x)
  {
    return ACCBOOST::_range_enumerate::EnumerateRange<std::initializer_list<X>>(std::move(x));
  }

}


#endif
