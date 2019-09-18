#ifndef ACCBOOST_UTILITY_ITERATOR_MAKE_CHAIN_ITERATOR_HPP_
#define ACCBOOST_UTILITY_ITERATOR_MAKE_CHAIN_ITERATOR_HPP_


#include "../misc.hpp"
#include "make_arrow_wrapper.hpp"
#include "is_iterator.hpp"
#include <optional>


namespace ACCBOOST
{

  namespace _make_chain_iterator
  {

    using std::begin;
    using std::end;

    template<class IteratorT, class LastIteratorT, class SubIteratorT, class LastSubIteratorT>
    class LastChainedIterator;

    template<class IteratorT, class LastIteratorT, class SubIteratorT, class LastSubIteratorT>
    class ChainedIterator
    {
    public:

      using iterator_category = std::forward_iterator_tag;
      using difference_type = std::ptrdiff_t;
      using value_type = typename SubIteratorT::value_type;
      using reference = typename SubIteratorT::reference;
      using pointer =  decltype(ACCBOOST::make_arrow_wrapper(std::declval<reference&&>()));

    private:

      using sub_range_reference = decltype(*std::declval<const IteratorT&>()); // note: 参照型とは限らない．

      struct Sub
      {
        ACCBOOST::capture_of<sub_range_reference&&> range_;
        SubIteratorT first_;
        LastSubIteratorT last_;

        Sub() = default;
        Sub(Sub&&) = default;
        Sub(const Sub&) = default;
        explicit Sub(sub_range_reference&& range):
          range_(std::forward<sub_range_reference>(range)), first_(begin(range_)), last_(end(range_))
        {}

      };

      IteratorT first_;
      LastIteratorT last_;
      std::optional<Sub> sub_;

    public:

      ChainedIterator() = default;
      ChainedIterator(ChainedIterator&&) = default;
      ChainedIterator(const ChainedIterator&) = default;

      /// current == first または current == last であること．
      template<class T, class U,
        ACCBOOST_REQUIRES(std::is_constructible_v<IteratorT, T&&>),
        ACCBOOST_REQUIRES(std::is_constructible_v<LastIteratorT, U&&>)>
      ChainedIterator(T&& first, U&& last) noexcept(std::is_nothrow_constructible_v<IteratorT, T&&> && std::is_nothrow_constructible_v<LastIteratorT, U&&>):
        first_(first), last_(last), sub_()
      {
        if(first_ != last_){
          sub_.emplace(*first_);
          while(sub_->first_ == sub_->last_){
            sub_.reset();
            ++first_;
            if(first_ == last_) break;
            sub_.emplace(*first_);
          }
        }
      }

      ChainedIterator& operator=(ChainedIterator&&) = default;

      ChainedIterator& operator=(const ChainedIterator&) = default;

      bool operator==(const ChainedIterator& rhs) const
      {
        return first_ == rhs.first_ &&
               ((!sub_.has_value() && !rhs.sub_.has_value()) ||
                (sub_.has_value() && rhs.sub_.has_value() && sub_->first_ == rhs.sub_.first_));
      }

      bool operator!=(const ChainedIterator& rhs) const
      {
        return !operator==(rhs);
      }

      bool operator==(const LastChainedIterator<IteratorT, LastIteratorT, SubIteratorT, LastSubIteratorT>&) const noexcept
      {
        return first_ == last_;
      }

      bool operator!=(const LastChainedIterator<IteratorT, LastIteratorT, SubIteratorT, LastSubIteratorT>&) const noexcept
      {
        return first_ != last_;
      }

      reference operator*() const
      {
        assert(sub_.has_value());
        return *(sub_->first_);
      }

      pointer operator->() const
      {
        return ACCBOOST::make_arrow_wrapper(operator*());
      }

      ChainedIterator& operator++()
      {
        assert(first_ != last_);
        assert(sub_.has_value());
        assert(sub_->first_ != sub_->last_);
        ++(sub_->first_);
        while(1){
          if(sub_->first_ != sub_->last_) break;
          sub_.reset();
          ++first_;
          if(first_ == last_) break;
          sub_.emplace(*first_);
        }
        return *this;
      }

      template<class This = ChainedIterator,
        ACCBOOST_REQUIRES(std::is_copy_constructible_v<This&>)>
      ChainedIterator operator++(int)
      {
        auto tmp(*this);
        ++(*this);
        return tmp;
      }

    };

    template<class IteratorT, class LastIteratorT, class SubIteratorT, class LastSubIteratorT>
    class LastChainedIterator
    {
    public:

      using iterator_category = std::forward_iterator_tag;
      using difference_type = std::ptrdiff_t;
      using value_type = typename SubIteratorT::value_type;
      using reference = typename SubIteratorT::reference;
      using pointer =  decltype(ACCBOOST::make_arrow_wrapper(std::declval<reference&&>()));

      bool operator==(const ChainedIterator<IteratorT, LastIteratorT, SubIteratorT, LastSubIteratorT>& rhs) const noexcept
      {
        return rhs == *this;
      }

      bool operator!=(const ChainedIterator<IteratorT, LastIteratorT, SubIteratorT, LastSubIteratorT>& rhs) const noexcept
      {
        return rhs != *this;
      }

    };

  }

  template<class IteratorT, class LastIteratorT>
  decltype(auto) make_chain_iterator(IteratorT&& first, LastIteratorT&& last)
  {
    using std::begin;
    using std::end;
    using iterator_t = std::remove_cv_t<std::remove_reference_t<IteratorT>>;
    using last_iterator_t = std::remove_cv_t<std::remove_reference_t<LastIteratorT>>;    
    using range_t = std::remove_cv_t<std::remove_reference_t<decltype(*std::declval<const iterator_t&>())>>;
    using sub_iterator_t = std::remove_cv_t<std::remove_reference_t<decltype(begin(std::declval<const range_t&>()))>>;
    using last_sub_iterator_t = std::remove_cv_t<std::remove_reference_t<decltype(end(std::declval<const range_t&>()))>>;
    using chain_iterator_t = _make_chain_iterator::ChainedIterator<iterator_t, last_iterator_t, sub_iterator_t, last_sub_iterator_t>;
    return chain_iterator_t(std::forward<IteratorT>(first), std::forward<LastIteratorT>(last));
  }

  template<class IteratorT, class LastIteratorT>
  decltype(auto) make_last_chain_iterator(IteratorT&&, LastIteratorT&&)
  {
    using std::begin;
    using std::end;
    using iterator_t = std::remove_cv_t<std::remove_reference_t<IteratorT>>;
    using last_iterator_t = std::remove_cv_t<std::remove_reference_t<LastIteratorT>>;    
    using range_t = std::remove_cv_t<std::remove_reference_t<decltype(*std::declval<const iterator_t&>())>>;
    using sub_iterator_t = std::remove_cv_t<std::remove_reference_t<decltype(begin(std::declval<const range_t&>()))>>;
    using last_sub_iterator_t = std::remove_cv_t<std::remove_reference_t<decltype(end(std::declval<const range_t&>()))>>;
    using last_chain_iterator_t = _make_chain_iterator::LastChainedIterator<iterator_t, last_iterator_t, sub_iterator_t, last_sub_iterator_t>;
    return last_chain_iterator_t();
  }

}



#endif
