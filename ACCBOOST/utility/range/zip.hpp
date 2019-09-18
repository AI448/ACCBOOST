#ifndef ACCBOOST_UTILITY_RANGE_ZIP_HPP_
#define ACCBOOST_UTILITY_RANGE_ZIP_HPP_


#include "../misc.hpp"
#include "../tuple.hpp"
#include "../iterator.hpp"
#include "is_range.hpp"
#include <algorithm>


namespace ACCBOOST
{

  namespace _range_zip
  {

    template<class... RangesT>
    class ZipRange
    {
      static_assert((... && !std::is_rvalue_reference_v<RangesT>));
      static_assert((... && !std::is_const_v<RangesT>));
    
    private:

      std::tuple<RangesT...> ranges_;

    public:

      template<class... T,
        ACCBOOST_REQUIRES((... && !std::is_same_v<std::remove_cv_t<std::remove_reference_t<T>>, ZipRange>))>
      explicit ZipRange(T&&... ranges):
        ranges_(std::forward<T>(ranges)...)
      {}

      ZipRange() = default;

      ZipRange(ZipRange&&) = default;

      ZipRange(const ZipRange&) = default;

      ZipRange& operator=(ZipRange&&) = default;

      ZipRange& operator=(const ZipRange&) = default;

      decltype(auto) begin() const
      {
        using std::begin;
        if constexpr ((... && ACCBOOST::is_random_access_range_v<std::remove_reference_t<const RangesT>>)){
          return ACCBOOST::apply([](const auto&... r) ->decltype(auto)
          {
            return ACCBOOST::make_random_access_zip_iterator(0, begin(r)...);
          }, ranges_);
        }else{
          return ACCBOOST::apply([](const auto&... r)
          {
            return ACCBOOST::make_zip_iterator(begin(r)...);
          }, ranges_);
        }
      }

      decltype(auto) end() const
      {
        using std::begin;
        using std::end;        
        if constexpr ((... && ACCBOOST::is_random_access_range_v<std::remove_reference_t<const RangesT>>)){
          auto distances = ACCBOOST::map([](const auto& r){return end(r) - begin(r);}, ranges_);
          std::ptrdiff_t min_distance = ACCBOOST::apply([](const auto&... d){return std::min<std::ptrdiff_t>({d...});}, distances);
          return ACCBOOST::apply([min_distance](const auto&... r)->decltype(auto)
          {
            return ACCBOOST::make_random_access_zip_iterator(min_distance, begin(r) + min_distance...);
          }, ranges_);
        }else{
          return ACCBOOST::apply([](const auto&... r) ->decltype(auto)
          {
            return ACCBOOST::make_zip_iterator(end(r)...);
          }, ranges_);
        }
      }

      decltype(auto) begin()
      {
        using std::begin;
        if constexpr ((... && ACCBOOST::is_random_access_range_v<std::remove_reference_t<RangesT>>)){
          return ACCBOOST::apply([](auto&... r) ->decltype(auto)
          {
            return ACCBOOST::make_random_access_zip_iterator(0, begin(r)...);
          }, ranges_);
        }else{
          return ACCBOOST::apply([](auto&... r)->decltype(auto)
          {
            return ACCBOOST::make_zip_iterator(begin(r)...);
          }, ranges_);
        }
      }

      decltype(auto) end()
      {
        using std::begin;
        using std::end;
        if constexpr ((... && ACCBOOST::is_random_access_range_v<std::remove_reference_t<RangesT>>)){
          auto distances = ACCBOOST::map([](const auto& r){return end(r) - begin(r);}, ranges_);
          std::ptrdiff_t min_distance = ACCBOOST::apply([](const auto&... d){return std::min<std::ptrdiff_t>({d...});}, distances);
          return ACCBOOST::apply([min_distance](auto&... r) ->decltype(auto)
          {
            return ACCBOOST::make_random_access_zip_iterator(min_distance, begin(r) + min_distance...);
          }, ranges_);
        }else{
          return ACCBOOST::apply([](auto&... r) ->decltype(auto)
          {
            return ACCBOOST::make_zip_iterator(end(r)...);
          }, ranges_);          
        }
      }

    };

  } // _range_zip

  template<class... X,
      ACCBOOST_REQUIRES(sizeof...(X) >= 1),
	    ACCBOOST_REQUIRES((... && ACCBOOST::is_range_v<std::remove_reference_t<X>>)),
	    ACCBOOST_REQUIRES(!(... && ACCBOOST::is_array_v<std::remove_reference_t<X>>))>
  decltype(auto) zip(X&&... x)
  {
    return ACCBOOST::_range_zip::ZipRange<ACCBOOST::capture_of<X&&>...>(std::forward<X>(x)...);
  }

}


#endif
