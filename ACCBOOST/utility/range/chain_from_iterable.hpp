#ifndef ACCBOOST_UTILITY_RANGE_CHAIN_FROM_ITERABLE_HPP_
#define ACCBOOST_UTILITY_RANGE_CHAIN_FROM_ITERABLE_HPP_


#include "../iterator.hpp"
#include "is_range.hpp"


namespace ACCBOOST
{

  namespace _chain_from_iterable
  {

    template<class RangeT>
    class ChainFromIterableRange
    {
      static_assert(!std::is_rvalue_reference_v<RangeT>);
      static_assert(!std::is_const_v<RangeT>);

    private:

      RangeT range_;

    public:

      ChainFromIterableRange() = default;
      ChainFromIterableRange(ChainFromIterableRange&&) = default;
      ChainFromIterableRange(const ChainFromIterableRange&) = default;
      ChainFromIterableRange& operator=(ChainFromIterableRange&&) = default;
      ChainFromIterableRange& operator=(const ChainFromIterableRange&) = default;

      explicit ChainFromIterableRange(RangeT&& range):
        range_(std::forward<RangeT>(range))
      {}

      decltype(auto) begin() const
      {
        using std::begin;
        using std::end;
        return ACCBOOST::make_chain_iterator(begin(range_), end(range_));
      }

      decltype(auto) end() const
      {
        using std::begin;
        using std::end;
        return ACCBOOST::make_last_chain_iterator(begin(range_), end(range_));
      }

    };

  }

  template<class X,
	    ACCBOOST_REQUIRES(ACCBOOST::is_range_v<std::remove_reference_t<X>>)>
  decltype(auto) chain_from_iterable(X&& x)
  {
    using result_t = ACCBOOST::_chain_from_iterable::ChainFromIterableRange<ACCBOOST::capture_of<X&&>>;
    return result_t(std::forward<X>(x));
  }

  template<class X,
	    ACCBOOST_REQUIRES(ACCBOOST::is_range_v<std::remove_reference_t<X>>)>
  decltype(auto) chain_from_iterable(const std::initializer_list<X>& x)
  {
    using result_t = ACCBOOST::_chain_from_iterable::ChainFromIterableRange<const std::initializer_list<X>&>;
    return result_t(x);
  }

  template<class X,
	    ACCBOOST_REQUIRES(ACCBOOST::is_range_v<std::remove_reference_t<X>>)>
  decltype(auto) chain_from_iterable(std::initializer_list<X>& x)
  {
    using result_t = ACCBOOST::_chain_from_iterable::ChainFromIterableRange<std::initializer_list<X>&>;
    return result_t(x);
  }

  template<class X,
	    ACCBOOST_REQUIRES(ACCBOOST::is_range_v<std::remove_reference_t<X>>)>
  decltype(auto) chain_from_iterable(std::initializer_list<X>&& x)
  {
    using result_t = ACCBOOST::_chain_from_iterable::ChainFromIterableRange<std::initializer_list<X>>;
    return result_t(std::move(x));
  }

}


#endif
