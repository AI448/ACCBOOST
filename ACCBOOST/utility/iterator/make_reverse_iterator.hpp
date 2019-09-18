#ifndef ACCBOOST_UTILITY_ITERATOR_MAKE_REVERSE_ITERATOR_HPP_
#define ACCBOOST_UTILITY_ITERATOR_MAKE_REVERSE_ITERATOR_HPP_


#include "../misc.hpp"
#include "is_iterator.hpp"
#include "make_arrow_wrapper.hpp"


namespace ACCBOOST
{


  namespace _make_reverse_iterator
  {

    template<class IteratorT>
    class ReverseIterator
    {
      static_assert(ACCBOOST::is_bidirectional_iterator_v<IteratorT>);

    public:

      using iterator_category = typename std::iterator_traits<IteratorT>::iterator_category;

      using difference_type = typename std::iterator_traits<IteratorT>::difference_type;

      using value_type = typename std::iterator_traits<IteratorT>::value_type;

      using reference = typename std::iterator_traits<IteratorT>::reference;

      using pointer = typename std::iterator_traits<IteratorT>::pointer;

    private:

      IteratorT iterator_;

    public:

      template<class IT,
        ACCBOOST_REQUIRES(std::is_constructible_v<IteratorT, IT&&>)>
      explicit ReverseIterator(IT&& iterator) noexcept(std::is_nothrow_constructible_v<IteratorT, IT&&>):
        iterator_(std::forward<IT>(iterator))
      {}

      ReverseIterator() = default;
      ReverseIterator(ReverseIterator&&) = default;
      ReverseIterator(const ReverseIterator&) = default;
      ReverseIterator& operator=(ReverseIterator&&) = default;
      ReverseIterator& operator=(const ReverseIterator&) = default;

      template<class IT,
        ACCBOOST_REQUIRES(ACCBOOST::META::is_valid_to_equal_v<const IteratorT&, const IT&>)>
      bool operator==(const ReverseIterator<IT>& other) const
      {
        return iterator_ == other.iterator_;
      }

      template<class IT,
        ACCBOOST_REQUIRES(ACCBOOST::META::is_valid_to_inequal_v<const IteratorT&, const IT&>)>
      bool operator!=(const ReverseIterator<IT>& other) const
      {
        return iterator_ != other.iterator_;
      }

      template<class IT,
        ACCBOOST_REQUIRES(ACCBOOST::META::is_valid_to_greater_v<const IteratorT&, const IT&>)>
      bool operator<(const ReverseIterator<IT>& other) const
      {
        return iterator_ > other.iterator_;
      }

      template<class IT,
        ACCBOOST_REQUIRES(ACCBOOST::META::is_valid_to_less_v<const IteratorT&, const IT&>)>
      bool operator>(const ReverseIterator<IT>& other) const
      {
        return iterator_ < other.iterator_;
      }

      template<class IT,
        ACCBOOST_REQUIRES(ACCBOOST::META::is_valid_to_greater_equal_v<const IteratorT&, const IT&>)>
      bool operator<=(const ReverseIterator<IT>& other) const
      {
        return iterator_ >= other.iterator_;
      }

      template<class IT,
        ACCBOOST_REQUIRES(ACCBOOST::META::is_valid_to_less_equal_v<const IteratorT&, const IT&>)>
      bool operator>=(const ReverseIterator<IT>& other) const
      {
        return iterator_ <= other.iterator_;
      }

      template<class IT,
        ACCBOOST_REQUIRES(ACCBOOST::META::is_valid_to_subtract_v<const IteratorT&, const IT&>)>
      difference_type operator-(const ReverseIterator<IT>& other) const
      {
        return -(iterator_ - other.iterator_);
      }

      template<class IT = IteratorT,
        ACCBOOST_REQUIRES(ACCBOOST::META::is_valid_to_indirect_v<const IT&>)>
      reference operator*() const
      {
        return *iterator_;
      }

      template<class IT = IteratorT,
        ACCBOOST_REQUIRES(ACCBOOST::META::is_valid_to_indirect_v<const IT&>)>
      pointer operator->() const
      {
        return ACCBOOST::make_arrow_wrapper(operator*());
      }

      template<class IT = IteratorT,
        ACCBOOST_REQUIRES(ACCBOOST::META::is_valid_to_subscript_v<const IT&, const std::ptrdiff_t&>)>
      reference operator[](difference_type d) const
      {
        return iterator_[-d];
      }

      template<class RI = ReverseIterator, class IT = IteratorT,
        ACCBOOST_REQUIRES(std::is_copy_constructible_v<RI>),
        ACCBOOST_REQUIRES(ACCBOOST::META::is_valid_to_subtract_v<const IT&, const difference_type&>)>
      ReverseIterator operator+(difference_type d) const
      {
        return ReverseIterator(iterator_ - d);
      }

      template<class RI = ReverseIterator, class IT = IteratorT,
        ACCBOOST_REQUIRES(std::is_copy_constructible_v<RI>),
        ACCBOOST_REQUIRES(ACCBOOST::META::is_valid_to_assign_v<const IT&, const difference_type&>)>
      ReverseIterator operator-(difference_type d) const
      {
        return ReverseIterator(iterator_ + d);
      }

      template<class IT = IteratorT,
        ACCBOOST_REQUIRES(ACCBOOST::META::is_valid_to_pre_declement_v<IT&>)>
      ReverseIterator& operator++()
      {
        --iterator_;
        return *this;
      }

      template<class IT = IteratorT,
        ACCBOOST_REQUIRES(ACCBOOST::META::is_valid_to_pre_inclement_v<IT&>)>
      ReverseIterator& operator--()
      {
        ++iterator_;
        return *this;
      }

      template<class IT = IteratorT,
        ACCBOOST_REQUIRES(ACCBOOST::META::is_valid_to_subtract_assign_v<IT&, const difference_type&>)>
      ReverseIterator& operator+=(difference_type d)
      {
        iterator_ -= d;
        return *this;
      }

      template<class IT = IteratorT,
        ACCBOOST_REQUIRES(ACCBOOST::META::is_valid_to_add_assign_v<IT&, const difference_type&>)>
      ReverseIterator& operator-=(difference_type d)
      {
        iterator_ += d;
        return *this;
      }

      template<class RI = ReverseIterator, class IT = IteratorT,
        ACCBOOST_REQUIRES(std::is_copy_constructible_v<RI>),
        ACCBOOST_REQUIRES(ACCBOOST::META::is_valid_to_post_declement_v<IT&>)>
      ReverseIterator operator++(int)
      {
        return ReverseIterator(iterator_--);
      }

      template<class RI = ReverseIterator, class IT = IteratorT,
        ACCBOOST_REQUIRES(std::is_copy_constructible_v<RI>),
        ACCBOOST_REQUIRES(ACCBOOST::META::is_valid_to_post_inclement_v<IT&>)>
      ReverseIterator operator--(int)
      {
        return ReverseIterator(iterator_--);
      }

    };

  } // _make_reverseed_iterator

  template<class IteratorT>
  decltype(auto) make_reverse_iterator(IteratorT&& iterator)
  {
    return ACCBOOST::_make_reverse_iterator::ReverseIterator<std::remove_cv_t<std::remove_reference_t<IteratorT>>>(std::forward<IteratorT>(iterator));
  }

}


#endif
