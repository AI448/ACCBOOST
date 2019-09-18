#ifndef ACCBOOST_UTILITY_RANGE_RANGE_HPP_
#define ACCBOOST_UTILITY_RANGE_RANGE_HPP_


#include "../misc.hpp"
#include "../iterator.hpp"
#include "is_range.hpp"


namespace ACCBOOST
{

  namespace _range_range
  {

    template<class FirstIterator, class LastIterator>
    class Range
    {
      static_assert(!std::is_reference_v<FirstIterator>);
      static_assert(!std::is_reference_v<LastIterator>);    

    private:

      FirstIterator first_;
      LastIterator last_;

    public:

      template<class I1, class I2>
      Range(I1&& first, I2&& last):
        first_(std::forward<I1>(first)), last_(std::forward<I2>(last))
      {}

      Range() = default;
      Range(Range&&) = default;
      Range(const Range&) = default;
      Range& operator=(Range&&) = default;
      Range& operator=(const Range&) = default;

      decltype(auto) begin() const
      {
        return first_;
      }

      decltype(auto) end() const
      {
        return last_;
      }

      template<class X = FirstIterator,
        ACCBOOST_REQUIRES(!std::is_copy_constructible_v<X>)>
      decltype(auto) begin()
      {
        // note FirstIterator がコピーコンストラクトできない型である場合に限りこちらが呼ばれる．
        return std::move(first_);
      }

      template<class X = LastIterator,
        ACCBOOST_REQUIRES(!std::is_copy_constructible_v<X>)>
      decltype(auto) end()
      {
        // note LastIterator がコピーコンストラクトできない型である場合に限りこちらが呼ばれる．        
        return std::move(last_);
      }

    };

  } // _range_range

  template<class First, class Last,
    ACCBOOST_REQUIRES(ACCBOOST::is_iterator_v<std::remove_reference_t<First>>),
    ACCBOOST_REQUIRES(ACCBOOST::is_iterator_v<std::remove_reference_t<Last>>)>
  decltype(auto) range(First&& first, Last&& last)
  {
    return ACCBOOST::_range_range::Range<std::remove_cv_t<std::remove_reference_t<First>>, std::remove_cv_t<std::remove_reference_t<Last>>>(
      std::forward<First>(first), std::forward<Last>(last));
  }

  template<class I,
	   ACCBOOST_REQUIRES(std::is_integral_v<std::remove_reference_t<I>>),
     ACCBOOST_REQUIRES(std::is_signed_v<std::remove_reference_t<I>>)>
  decltype(auto) range(I&& last)
  {
    using integer_t = std::remove_cv_t<std::remove_reference_t<I>>;
    if(last >= 0){
      return ACCBOOST::range(ACCBOOST::make_integer_iterator(integer_t(0)), ACCBOOST::make_integer_iterator(std::forward<I>(last)));
    }else{
      return ACCBOOST::range(ACCBOOST::make_integer_iterator(integer_t(0)), ACCBOOST::make_integer_iterator(integer_t(0)));
    }
  }

  template<class I,
	   ACCBOOST_REQUIRES(std::is_integral_v<std::remove_reference_t<I>>),
     ACCBOOST_REQUIRES(std::is_unsigned_v<std::remove_reference_t<I>>)>
  decltype(auto) range(I&& last)
  {
    using integer_t = std::remove_cv_t<std::remove_reference_t<I>>;
    return ACCBOOST::range(ACCBOOST::make_integer_iterator(integer_t(0)), ACCBOOST::make_integer_iterator(std::forward<I>(last)));
  }

} // ACCBOOST


#endif
