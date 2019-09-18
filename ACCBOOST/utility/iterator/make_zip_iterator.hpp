#ifndef ACCBOOST_UTILITY_ITERATOR_MAKE_ZIP_ITERATOR_HPP_
#define ACCBOOST_UTILITY_ITERATOR_MAKE_ZIP_ITERATOR_HPP_


#include "../misc.hpp"
#include "../tuple.hpp"
#include "make_arrow_wrapper.hpp"
#include "make_integer_iterator.hpp"
#include "is_iterator.hpp"


namespace ACCBOOST
{

  namespace _make_zip_iterator
  {

    template<class Comparator, class... Iterators>
    class Impl: protected Comparator
    {
      static_assert(sizeof...(Iterators) > 0);
      static_assert((... && !std::is_reference_v<Iterators>));
      static_assert((... && ACCBOOST::is_iterator_v<Iterators>));

      template<class, class ...>
      friend class Impl;

    public:

      using iterator_category = std::conditional_t<
        (... && ACCBOOST::is_forward_iterator_v<Iterators>),
        std::forward_iterator_tag,
        std::input_iterator_tag>;

      using difference_type = std::ptrdiff_t;

      using value_type = std::conditional_t<
          (... || std::is_void_v<typename std::iterator_traits<Iterators>::value_type>),
          void,
          std::tuple<typename std::iterator_traits<Iterators>::value_type...>>;

      using reference = std::tuple<typename std::iterator_traits<Iterators>::reference...>;

      using pointer = decltype(ACCBOOST::make_arrow_wrapper(std::declval<reference&&>()));

    private:

      std::tuple<Iterators...> iterators_;

    public:

      template<class... I,
        ACCBOOST_REQUIRES(sizeof...(I) == sizeof...(Iterators)),
        ACCBOOST_REQUIRES(ACCBOOST::META::all_v<ACCBOOST::META::map<std::is_constructible, ACCBOOST::META::zip<ACCBOOST::META::list<Iterators...>, ACCBOOST::META::list<I&&...>>>>)>
      explicit Impl(I&&... iterators):
        Comparator(), iterators_(std::forward<I>(iterators)...)
      {}

      Impl() = default;
      Impl(Impl&&) = default;
      Impl(const Impl&) = default;
      Impl& operator=(Impl&&) = default;
      Impl& operator=(const Impl&) = default;

      template<class... I,
        ACCBOOST_REQUIRES(sizeof...(I) == sizeof...(Iterators)),      
        ACCBOOST_REQUIRES(ACCBOOST::META::all_v<ACCBOOST::META::map<ACCBOOST::META::is_valid_to_equal, ACCBOOST::META::zip<ACCBOOST::META::list<const Iterators&...>, ACCBOOST::META::list<const I&...>>>>)>
      bool operator==(const Impl<Comparator, I...>& other) const
      {
        return Comparator::operator()(iterators_, other.iterators_);
      }

      template<class... I,
        ACCBOOST_REQUIRES(sizeof...(I) == sizeof...(Iterators)),
        ACCBOOST_REQUIRES(ACCBOOST::META::all_v<ACCBOOST::META::map<ACCBOOST::META::is_valid_to_inequal, ACCBOOST::META::zip<ACCBOOST::META::list<const Iterators&...>, ACCBOOST::META::list<const I&...>>>>)>        
      bool operator!=(const Impl<Comparator, I...>& other) const
      {
        return !Comparator::operator()(iterators_, other.iterators_);        
      }

      template<class X = ACCBOOST::META::list<const Iterators&...>,
        ACCBOOST_REQUIRES(ACCBOOST::META::all_v<ACCBOOST::META::map<ACCBOOST::META::is_valid_to_indirect, X>>)>
      reference operator*() const
      {
        return ACCBOOST::map([](const auto& i)->decltype(auto) {return *i;}, iterators_);
      }

      template<class X = ACCBOOST::META::list<const Iterators&...>,
        ACCBOOST_REQUIRES(ACCBOOST::META::all_v<ACCBOOST::META::map<ACCBOOST::META::is_valid_to_indirect, X>>)>
      pointer operator->() const
      {
        return ACCBOOST::make_arrow_wrapper(operator*());
      }

      template<class X = ACCBOOST::META::list<Iterators&...>,
        ACCBOOST_REQUIRES(ACCBOOST::META::all_v<ACCBOOST::META::map<ACCBOOST::META::is_valid_to_pre_inclement, X>>)>
      Impl& operator++()
      {
      	ACCBOOST::for_each([](auto& i){++i;}, iterators_);
        return *this;
      }

      template<class X = ACCBOOST::META::list<Iterators&...>,
        ACCBOOST_REQUIRES(ACCBOOST::META::all_v<ACCBOOST::META::map<ACCBOOST::META::is_valid_to_post_inclement, X>>)>
      Impl operator++(int)
      {
        return ACCBOOST::apply([](auto&... i){return Impl(i++...);}, iterators_);
      }

    };

    struct Comparator
    {
      template<class LHS, class RHS>
      bool operator()(const LHS& lhs, const RHS& rhs) const
      {
        return ACCBOOST::apply([](const auto&... pairs)
        {
          return (... || (ACCBOOST::get<0>(pairs) == ACCBOOST::get<1>(pairs)));
        }, ACCBOOST::zip(lhs, rhs));
      }
    };

    struct ComparatorForEnumerate
    {
      template<class LHS, class RHS>
      bool operator()(const LHS& lhs, const RHS& rhs) const
      {
        return ACCBOOST::apply([](const auto&, const auto&... pairs)
        {
          // note 最初の 1 つ (IntegerIterator) は比較しない．
          return (... || (ACCBOOST::get<0>(pairs) == ACCBOOST::get<1>(pairs)));
        }, ACCBOOST::zip(lhs, rhs));
      }
    };

    template<class... Iterators>
    using ZipIterator = ACCBOOST::_make_zip_iterator::Impl<ACCBOOST::_make_zip_iterator::Comparator, Iterators...>;

    template<class... Iterators>
    using EnumeratedIterator = ACCBOOST::_make_zip_iterator::Impl<ACCBOOST::_make_zip_iterator::ComparatorForEnumerate, Iterators...>;

  } // _make_zip_iterator

  template<class... IteratorsT>
  decltype(auto) make_zip_iterator(IteratorsT&&... iterators)
  {
    using zip_iterator_t = ACCBOOST::_make_zip_iterator::ZipIterator<std::remove_cv_t<std::remove_reference_t<IteratorsT>>...>;
    return zip_iterator_t(std::forward<IteratorsT>(iterators)...);
  }

  template<class... IteratorsT>
  decltype(auto) make_enumerated_iterator(std::size_t integer, IteratorsT&&... iterators)
  {
    auto integer_iterator = ACCBOOST::make_integer_iterator(integer);
    using zip_iterator_t = ACCBOOST::_make_zip_iterator::EnumeratedIterator<decltype(integer_iterator), std::remove_cv_t<std::remove_reference_t<IteratorsT>>...>;
    return zip_iterator_t(std::move(integer_iterator), std::forward<IteratorsT>(iterators)...);
  }

} // ACCBOOST


#endif
