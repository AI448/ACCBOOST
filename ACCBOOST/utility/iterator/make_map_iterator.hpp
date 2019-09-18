#ifndef ACCBOOST_UTILITY_ITERATOR_MAKE_MAP_ITERATOR_HPP_
#define ACCBOOST_UTILITY_ITERATOR_MAKE_MAP_ITERATOR_HPP_


#include "../misc.hpp"
#include "make_arrow_wrapper.hpp"


namespace ACCBOOST
{

  namespace _make_map_iterator
  {

    template<class FunctorT, class IteratorT>
    class MapIterator
    {
      static_assert(!std::is_rvalue_reference_v<FunctorT>);
      static_assert(!std::is_reference_v<IteratorT>);

      template<class, class>
      friend class MapIterator;

    public:

      using iterator_category = typename std::iterator_traits<IteratorT>::iterator_category;

      using difference_type = typename std::iterator_traits<IteratorT>::difference_type;

      using reference = decltype(std::declval<const FunctorT&>()(*std::declval<const IteratorT&>()));

      using value_type = std::conditional_t<
          std::is_reference_v<reference>,
          std::remove_reference_t<reference>,
          void>;

      using pointer = decltype(ACCBOOST::make_arrow_wrapper(std::declval<reference&&>()));

    private:

      FunctorT functor_;

      IteratorT iterator_;

    public:

      template<class I>
      MapIterator(FunctorT&& functor, I&& iterator):
        functor_(std::forward<FunctorT>(functor)), iterator_(std::forward<I>(iterator))
      {}

      MapIterator() = default;
      MapIterator(MapIterator&&) = default;
      MapIterator(const MapIterator&) = default;
      ~MapIterator() = default;
      MapIterator& operator=(MapIterator&&) = default;
      MapIterator& operator=(const MapIterator&) = default;

      template<class I,
        ACCBOOST_REQUIRES(ACCBOOST::META::is_valid_to_equal_v<const IteratorT&, const I&>)>
      bool operator==(const MapIterator<FunctorT, I>& other) const
      {
        return iterator_ == other.iterator_;
      }

      template<class I,
        ACCBOOST_REQUIRES(ACCBOOST::META::is_valid_to_inequal_v<const IteratorT&, const I&>)>
      bool operator!=(const MapIterator<FunctorT, I>& other) const
      {
        return iterator_ != other.iterator_;
      }

      template<class I,
        ACCBOOST_REQUIRES(ACCBOOST::META::is_valid_to_less_v<const IteratorT&, const I&>)>
      bool operator<(const MapIterator<FunctorT, I>& other) const
      {
        return iterator_ < other.iterator_;
      }

      template<class I,
        ACCBOOST_REQUIRES(ACCBOOST::META::is_valid_to_greater_v<const IteratorT&, const I&>)>
      bool operator>(const MapIterator<FunctorT, I>& other) const
      {
        return iterator_ > other.iterator_;
      }

      template<class I,
        ACCBOOST_REQUIRES(ACCBOOST::META::is_valid_to_less_equal_v<const IteratorT&, const I&>)>
      bool operator<=(const MapIterator<FunctorT, I>& other) const
      {
        return iterator_ <= other.iterator_;
      }

      template<class I,
        ACCBOOST_REQUIRES(ACCBOOST::META::is_valid_to_greater_equal_v<const IteratorT&, const I&>)>
      bool operator>=(const MapIterator<FunctorT, I>& other) const
      {
        return iterator_ >= other.iterator_;
      }

      template<class I,
        ACCBOOST_REQUIRES(ACCBOOST::META::is_valid_to_subtract_v<const IteratorT&, const I&>)>
      difference_type operator-(const MapIterator<FunctorT, I>& other) const
      {
        return iterator_ - other.iterator_;
      }

      template<class IT = IteratorT,
        ACCBOOST_REQUIRES(ACCBOOST::META::is_valid_to_indirect_v<const IT&>)>
      reference operator*() const
      {
        return functor_(*iterator_);
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
        return functor_(iterator_[d]);
      }

      template<class ThisT = MapIterator, class IT = IteratorT,
        ACCBOOST_REQUIRES(std::is_copy_constructible_v<ThisT>),
        ACCBOOST_REQUIRES(ACCBOOST::META::is_valid_to_add_v<const IT&, const difference_type&>)>
      MapIterator operator+(difference_type d) const
      {
        return MapIterator(functor_, iterator_ + d);
      }

      template<class ThisT = MapIterator, class IT = IteratorT,
        ACCBOOST_REQUIRES(std::is_copy_constructible_v<ThisT>),
        ACCBOOST_REQUIRES(ACCBOOST::META::is_valid_to_subtract_v<const IT&, const difference_type&>)>
      MapIterator operator-(difference_type d) const
      {
        return MapIterator(functor_, iterator_ - d);        
      }

      template<class IT = IteratorT,
        ACCBOOST_REQUIRES(ACCBOOST::META::is_valid_to_pre_inclement_v<IT&>)>
      MapIterator& operator++()
      {
        ++iterator_;
        return *this;
      }

      template<class IT = IteratorT,
        ACCBOOST_REQUIRES(ACCBOOST::META::is_valid_to_pre_declement_v<IT&>)>
      MapIterator& operator--()
      {
        --iterator_;
        return *this;
      }

      template<class IT = IteratorT,
        ACCBOOST_REQUIRES(ACCBOOST::META::is_valid_to_add_assign_v<IT&, const difference_type&>)>
      MapIterator& operator+=(difference_type d)
      {
        iterator_ += d;
        return *this;
      }

      template<class IT = IteratorT,
        ACCBOOST_REQUIRES(ACCBOOST::META::is_valid_to_subtract_assign_v<IT&, const difference_type&>)>
      MapIterator& operator-=(difference_type d)
      {
        iterator_ -= d;
        return *this;
      }

      template<class ThisT = MapIterator, class IT = IteratorT,
        ACCBOOST_REQUIRES(std::is_copy_constructible_v<ThisT>),
        ACCBOOST_REQUIRES(ACCBOOST::META::is_valid_to_post_inclement_v<IT&>)>
      MapIterator operator++(int)
      {
        return MapIterator(functor_, iterator_++);
      }

      template<class ThisT = MapIterator, class IT = IteratorT,
        ACCBOOST_REQUIRES(std::is_copy_constructible_v<ThisT>),
        ACCBOOST_REQUIRES(ACCBOOST::META::is_valid_to_post_declement_v<IT&>)>
      MapIterator operator--(int)
      {
        return MapIterator(functor_, iterator_--);
      }

    };

    struct None {};

  } // _make_map_iterator


  template<class FunctorT, class IteratorT>
  decltype(auto) make_map_iterator(FunctorT&& f, IteratorT&& i)
  {
    using functor_t = ACCBOOST::capture_of<FunctorT&&>;
    using iterator_t = std::remove_cv_t<std::remove_reference_t<IteratorT>>;
    return ACCBOOST::_make_map_iterator::MapIterator<functor_t, iterator_t>(std::forward<FunctorT>(f), std::forward<IteratorT>(i));
  }

}


#endif
