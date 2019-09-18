#ifndef ACCBOOST_UTILITY_ITERATOR_MAKE_RANDOM_ACCESS_ZIP_ITERATOR_HPP_
#define ACCBOOST_UTILITY_ITERATOR_MAKE_RANDOM_ACCESS_ZIP_ITERATOR_HPP_


#include "../misc.hpp"
#include "make_arrow_wrapper.hpp"
#include "is_iterator.hpp"


namespace ACCBOOST
{

  namespace _make_random_access_zip_iterator
  {

    /// RnadomAccessIterator の zip, enumerate の高速な実装のためのクラス
    template<bool Indexing, class... IteratorsT>
    class Impl
    {
      static_assert((... && !std::is_reference_v<IteratorsT>));
      static_assert((... && ACCBOOST::is_random_access_iterator_v<IteratorsT>));

      template<bool, class...>
      friend class Impl;

    public:

      using iterator_category = std::random_access_iterator_tag;

      using difference_type = std::ptrdiff_t;

      using value_type = std::conditional_t<
          (... || std::is_void_v<typename std::iterator_traits<IteratorsT>::value_type>),
          void,
          std::conditional_t<
            Indexing,
            std::tuple<std::size_t, typename std::iterator_traits<IteratorsT>::value_type...>,
            std::tuple<typename std::iterator_traits<IteratorsT>::value_type...>>>;

      using reference =
        std::conditional_t<
          Indexing,
          std::tuple<std::size_t, typename std::iterator_traits<IteratorsT>::reference...>,
          std::tuple<typename std::iterator_traits<IteratorsT>::reference...>>;

      using pointer = decltype(ACCBOOST::make_arrow_wrapper(std::declval<reference&&>()));

    private:

      difference_type position_;

      std::tuple<IteratorsT...> iterators_;

    public:

      template<class... I,
        ACCBOOST_REQUIRES(sizeof...(I) == sizeof...(IteratorsT))>
      Impl(difference_type position, I&&... iterators):
        position_(position), iterators_(std::forward<I>(iterators)...)
      {}

      Impl() = default;
      Impl(Impl&&) = default;
      Impl(const Impl&) = default;
      Impl& operator=(Impl&&) = default;
      Impl& operator=(const Impl&) = default;

      template<class... I,
        ACCBOOST_REQUIRES(sizeof...(I) == sizeof...(IteratorsT)),   
        ACCBOOST_REQUIRES(ACCBOOST::META::all_v<
          ACCBOOST::META::map<
            ACCBOOST::META::is_valid_to_equal,
            ACCBOOST::META::zip<ACCBOOST::META::list<const IteratorsT&...>, ACCBOOST::META::list<const I&...>>>>)>
      bool operator==(const Impl<Indexing, I...>& other) const
      {
        return position_ == other.position_;
      }

      template<class... I,
        ACCBOOST_REQUIRES(sizeof...(I) == sizeof...(IteratorsT)),   
        ACCBOOST_REQUIRES(ACCBOOST::META::all_v<ACCBOOST::META::map<ACCBOOST::META::is_valid_to_inequal, ACCBOOST::META::zip<ACCBOOST::META::list<const IteratorsT&...>, ACCBOOST::META::list<const I&...>>>>)>      
      bool operator!=(const Impl<Indexing, I...>& other) const
      {
        return position_ != other.position_;
      }

      template<class... I,
        ACCBOOST_REQUIRES(sizeof...(I) == sizeof...(IteratorsT)),   
        ACCBOOST_REQUIRES(ACCBOOST::META::all_v<ACCBOOST::META::map<ACCBOOST::META::is_valid_to_less, ACCBOOST::META::zip<ACCBOOST::META::list<const IteratorsT&...>, ACCBOOST::META::list<const I&...>>>>)>      
      bool operator<(const Impl<Indexing, I...>& other) const
      {
        return position_ < other.position_;
      }

      template<class... I,
        ACCBOOST_REQUIRES(sizeof...(I) == sizeof...(IteratorsT)),   
        ACCBOOST_REQUIRES(ACCBOOST::META::all_v<ACCBOOST::META::map<ACCBOOST::META::is_valid_to_greater, ACCBOOST::META::zip<ACCBOOST::META::list<const IteratorsT&...>, ACCBOOST::META::list<const I&...>>>>)>      
      bool operator>(const Impl<Indexing, I...>& other) const
      {
        return position_ > other.position_;
      }

      template<class... I,
        ACCBOOST_REQUIRES(sizeof...(I) == sizeof...(IteratorsT)),   
        ACCBOOST_REQUIRES(ACCBOOST::META::all_v<ACCBOOST::META::map<ACCBOOST::META::is_valid_to_less_equal, ACCBOOST::META::zip<ACCBOOST::META::list<const IteratorsT&...>, ACCBOOST::META::list<const I&...>>>>)>      
      bool operator<=(const Impl<Indexing, I...>& other) const
      {
        return position_ <= other.position_;
      }

      template<class... I,
        ACCBOOST_REQUIRES(sizeof...(I) == sizeof...(IteratorsT)),   
        ACCBOOST_REQUIRES(ACCBOOST::META::all_v<ACCBOOST::META::map<ACCBOOST::META::is_valid_to_greater_equal, ACCBOOST::META::zip<ACCBOOST::META::list<const IteratorsT&...>, ACCBOOST::META::list<const I&...>>>>)>      
      bool operator>=(const Impl<Indexing, I...>& other) const
      {
        return position_ >= other.position_;
      }

      template<class... I,
        ACCBOOST_REQUIRES(sizeof...(I) == sizeof...(IteratorsT)),   
        ACCBOOST_REQUIRES(ACCBOOST::META::all_v<ACCBOOST::META::map<ACCBOOST::META::is_valid_to_subtract, ACCBOOST::META::zip<ACCBOOST::META::list<const IteratorsT&...>, ACCBOOST::META::list<const I&...>>>>)>      
      difference_type operator-(const Impl<Indexing, I...>& other) const
      {
        return position_ - other.position_;
      }

      template<class X = ACCBOOST::META::list<const IteratorsT&...>,
        ACCBOOST_REQUIRES(ACCBOOST::META::all_v<ACCBOOST::META::map<ACCBOOST::META::is_valid_to_indirect, X>>)>
      reference operator*() const
      {
        static_assert((... && ACCBOOST::META::is_valid_to_subscript_v<const IteratorsT&, const difference_type&>));
        assert(position_ >= 0);
        return ACCBOOST::apply([p = position_](const auto&... i) ->decltype(auto)
        {
          if constexpr(Indexing){
            return reference(static_cast<std::size_t>(p), i[p]...);
          }else{
            return reference(i[p]...);
          }
        }, iterators_);
      }

      template<class X = ACCBOOST::META::list<ACCBOOST::META::list<const IteratorsT&, const difference_type&>...>,
        ACCBOOST_REQUIRES(ACCBOOST::META::all_v<ACCBOOST::META::map<ACCBOOST::META::is_valid_to_subscript, X>>)>
      reference operator[](difference_type d) const
      {
        assert(position_  + d >= 0);
        return ACCBOOST::apply([p = position_ + d](const auto&... i) ->decltype(auto)
        {
          if constexpr(Indexing){
            return reference(static_cast<std::size_t>(p), i[p]...);
          }else{
            return reference(i[p]...);
          }
        }, iterators_);
      }

      template<class X = ACCBOOST::META::list<const IteratorsT&...>,
        ACCBOOST_REQUIRES(ACCBOOST::META::all_v<ACCBOOST::META::map<ACCBOOST::META::is_valid_to_indirect, X>>)>
      pointer operator->() const
      {
        return ACCBOOST::make_arrow_wrapper(operator*());
      }

      template<class X = ACCBOOST::META::list<ACCBOOST::META::list<const IteratorsT&, const difference_type&>...>,
        ACCBOOST_REQUIRES(ACCBOOST::META::all_v<ACCBOOST::META::map<ACCBOOST::META::is_valid_to_add, X>>)>
      Impl operator+(difference_type d) const
      {
        static_assert((... && std::is_copy_constructible_v<IteratorsT>));
        return ACCBOOST::apply([p = position_ + d](const auto&... i) ->decltype(auto)
        {
          return Impl(p, i...);
        }, iterators_);
      }

      template<class X = ACCBOOST::META::list<ACCBOOST::META::list<const IteratorsT&, const difference_type&>...>,
        ACCBOOST_REQUIRES(ACCBOOST::META::all_v<ACCBOOST::META::map<ACCBOOST::META::is_valid_to_subtract, X>>)>
      Impl operator-(difference_type d) const
      {
        static_assert((... && std::is_copy_constructible_v<IteratorsT>));
        return ACCBOOST::apply([p = position_ - d](const auto&... i) ->decltype(auto)
        {
          return Impl(p, i...);
        }, iterators_);        
      }

      template<class X = ACCBOOST::META::list<IteratorsT&...>,
        ACCBOOST_REQUIRES(ACCBOOST::META::all_v<ACCBOOST::META::map<ACCBOOST::META::is_valid_to_pre_inclement, X>>)>
      Impl& operator++()
      {
        ++position_;
        return *this;
      }

      template<class X = ACCBOOST::META::list<IteratorsT&...>,
        ACCBOOST_REQUIRES(ACCBOOST::META::all_v<ACCBOOST::META::map<ACCBOOST::META::is_valid_to_pre_declement, X>>)>
      Impl& operator--()
      {
        --position_;
        return *this;
      }

      template<class X = ACCBOOST::META::list<IteratorsT&...>,
        ACCBOOST_REQUIRES(ACCBOOST::META::all_v<ACCBOOST::META::map<ACCBOOST::META::is_valid_to_add_assign, X>>)>
      Impl& operator+=(difference_type d)
      {
        position_ += d;
        return *this;
      }

      template<class X = ACCBOOST::META::list<IteratorsT&...>,
        ACCBOOST_REQUIRES(ACCBOOST::META::all_v<ACCBOOST::META::map<ACCBOOST::META::is_valid_to_subtract_assign, X>>)>
      Impl& operator-=(difference_type d)
      {
        position_ -= d;
        return *this;
      }

      template<class X = ACCBOOST::META::list<IteratorsT&...>,
        ACCBOOST_REQUIRES(ACCBOOST::META::all_v<ACCBOOST::META::map<ACCBOOST::META::is_valid_to_post_inclement, X>>)>
      Impl operator++(int)
      {
        static_assert((... && std::is_copy_constructible_v<IteratorsT>));
        return ACCBOOST::apply([p = position_++](const auto&... i) ->decltype(auto)
        {
          return Impl(p, i...);
        }, iterators_);
      }

      template<class X = ACCBOOST::META::list<IteratorsT&...>,
        ACCBOOST_REQUIRES(ACCBOOST::META::all_v<ACCBOOST::META::map<ACCBOOST::META::is_valid_to_post_declement, X>>)>
      Impl operator--(int)
      {
        static_assert((... && std::is_copy_constructible_v<IteratorsT>));        
        return ACCBOOST::apply([p = position_--](const auto&... i)->decltype(auto)
        {
          return Impl(p, i...);
        }, iterators_);
      }

     };

    template<class... IteratorsT>
    using RandomAccessZipIterator = ACCBOOST::_make_random_access_zip_iterator::Impl<false, IteratorsT...>;

    template<class... IteratorsT>
    using RandomAccessEnumeratedIterator = ACCBOOST::_make_random_access_zip_iterator::Impl<true, IteratorsT...>;

  } // _make_random_access_zip_iterator

  template<class IntegerT, class... IteratorsT>
  decltype(auto) make_random_access_zip_iterator(IntegerT&& integer, IteratorsT&&... iterators)
  {
    using zip_iterator_t = ACCBOOST::_make_random_access_zip_iterator::RandomAccessZipIterator<std::remove_cv_t<std::remove_reference_t<IteratorsT>>...>;
    return zip_iterator_t(static_cast<std::ptrdiff_t>(std::forward<IntegerT>(integer)), std::forward<IteratorsT>(iterators)...);
  }

  template<class IntegerT, class... IteratorsT>
  decltype(auto) make_random_access_enumerated_iterator(IntegerT&& integer, IteratorsT&&... iterators)
  {
    using enumerate_iterator_t = ACCBOOST::_make_random_access_zip_iterator::RandomAccessEnumeratedIterator<std::remove_cv_t<std::remove_reference_t<IteratorsT>>...>;
    return enumerate_iterator_t(static_cast<std::ptrdiff_t>(std::forward<IntegerT>(integer)), std::forward<IteratorsT>(iterators)...);
  }

}


#endif
