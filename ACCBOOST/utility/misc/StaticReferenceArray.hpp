#ifndef ACCBOOST_UTIILTY_MISC_STATICREFERENCEARRAY_HPP_
#define ACCBOOST_UTIILTY_MISC_STATICREFERENCEARRAY_HPP_


#include <array>
#include <cassert>
#include <iterator>
#include <memory>
#include <utility>
#include "REQUIERS.hpp"
#include "tuple_size.hpp"
#include "tuple_element.hpp"
#include "get.hpp"


namespace ACCBOOST
{

  template<class ReferenceType, std::size_t N>
  class StaticReferenceArray;

  template<class T, std::size_t N>
  class tuple_size<ACCBOOST::StaticReferenceArray<T, N>>: public std::integral_constant<std::size_t, N> {};

  template<std::size_t I, class T, std::size_t N>
  class tuple_element<I, ACCBOOST::StaticReferenceArray<T, N>>
  {
    static_assert(I < N);
  public:
    using type = T;
  };

  template<class T, std::size_t N>
  struct result_type_of_get_from_array<ACCBOOST::StaticReferenceArray<T, N>&&>
  {
    using type = T;
  };

  template<class T, std::size_t N>
  struct result_type_of_get_from_array<const ACCBOOST::StaticReferenceArray<T, N>&&>
  {
    using type = T;
  };

  template<class T, std::size_t N>
  struct result_type_of_get_from_array<ACCBOOST::StaticReferenceArray<T, N>&>
  {
    using type = T;
  };

  template<class T, std::size_t N>
  struct result_type_of_get_from_array<const ACCBOOST::StaticReferenceArray<T, N>&>
  {
    using type = T;
  };

  template<std::size_t I, class T, std::size_t N>
  constexpr T get(const ACCBOOST::StaticReferenceArray<T, N>& array) noexcept
  {
    // note 戻り値の型は常に T なので const 参照型以外のオーバーロードは必要ない
    static_assert(I < N);
    static_assert(std::is_reference_v<T>);
    return array[I];
  }

}

#include "apply.hpp"

namespace ACCBOOST
{

  template<class ReferenceType, std::size_t N>
  class StaticReferenceArray
  {
    static_assert(std::is_reference_v<ReferenceType>);
  public:

    using value_type = ReferenceType;
    
  private:

    using pointer_type = std::remove_reference_t<ReferenceType>*;

    class Iterator
    {
    public:

      using iterator_category = std::random_access_iterator_tag;

      using difference_type = std::ptrdiff_t;

      using value_type = std::remove_reference_t<ReferenceType>;

      using reference = ReferenceType;

      using pointer = pointer_type;

    private:

      const pointer_type* _ptr;

    public:

      explicit Iterator(const pointer_type* ptr) noexcept:
        _ptr(ptr)
      {}
      
      Iterator() noexcept: _ptr(nullptr) {}
      Iterator(Iterator&&) = default;
      Iterator(const Iterator&) = default;      
      Iterator& operator=(Iterator&&) = default;
      Iterator& operator=(const Iterator&) = default;      
      
      ReferenceType operator*() const noexcept
      {
        assert(_ptr != nullptr); assert(*_ptr != nullptr);
        return static_cast<ReferenceType>(**_ptr);
      }

      bool operator==(const Iterator& rhs) const noexcept
      {
        return _ptr == rhs._ptr;
      }

      bool operator!=(const Iterator& rhs) const noexcept
      {
        return !operator==(rhs);
      }

      bool operator<(const Iterator& rhs) const noexcept
      {
        assert(_ptr != nullptr); assert(rhs._ptr != nullptr);
        return _ptr < rhs._ptr;
      }

      bool operator<=(const Iterator& rhs) const noexcept
      {
        assert(_ptr != nullptr); assert(rhs._ptr != nullptr);  
        return _ptr <= rhs._ptr;
      }

      bool operator>(const Iterator& rhs) const noexcept
      {
        assert(_ptr != nullptr); assert(rhs._ptr != nullptr);  
        return _ptr > rhs._ptr;
      }

      bool operator>=(const Iterator& rhs) const noexcept
      {
        assert(_ptr != nullptr); assert(rhs._ptr != nullptr);  
        return _ptr >= rhs._ptr;
      }

      Iterator& operator++() noexcept
      {
        ++_ptr;
        return *this;
      }

      Iterator& operator--() noexcept
      {
        --_ptr;
        return *this;
      }

      Iterator operator++(int) noexcept
      {
        Iterator tmp(*this);
        ++tmp;
        return tmp; 
      }

      Iterator operator--(int) noexcept
      {
        Iterator tmp(*this);
        --tmp;
        return tmp;
      }
      
      Iterator& operator+=(std::ptrdiff_t d) noexcept
      {
        _ptr += d;
        return *this;
      }

      Iterator& operator-=(std::ptrdiff_t d) noexcept
      {
        _ptr -= d;
        return *this;
      }

      Iterator operator+(std::ptrdiff_t d) const noexcept
      {
        Iterator tmp(*this);
        tmp += d;
        return tmp;
      }

      Iterator operator-(std::ptrdiff_t d) const noexcept
      {
        Iterator tmp(*this);
        tmp -= d;
        return tmp;
      }

      std::ptrdiff_t operator-(const Iterator& rhs) const noexcept
      {
        return _ptr - rhs._ptr;
      }

    };
    
    pointer_type _data[N];

  public:

    template<class... T,
      ACCBOOST_REQUIRES(sizeof...(T) == N),
      ACCBOOST_REQUIRES((... && std::is_same_v<std::remove_cv_t<std::remove_reference_t<ReferenceType>>, std::remove_cv_t<std::remove_reference_t<T>>>)),
      ACCBOOST_REQUIRES((... && std::is_convertible_v<ReferenceType, T&&>))>
    StaticReferenceArray(T&&... args):
      _data{std::addressof(std::forward<T>(args))...}
    {}

    StaticReferenceArray(StaticReferenceArray&&) = default;
    StaticReferenceArray(const StaticReferenceArray&) = default;    

/* ???
    StaticReferenceArray(StaticReferenceArray& other) noexcept(std::is_nothrow_copy_constructible_v<StaticReferenceArray>):
      StaticReferenceArray(std::as_const(other))
    {}
*/
/*
    operator std::array<std::remove_cv_t<std::remove_reference_t<ReferenceType>>, N>() const
    {
      return ACCBOOST::apply([](auto&... args){
        return std::array<std::remove_cv_t<std::remove_reference_t<ReferenceType>>, N>{std::forward<decltype(args)>(args)...};
      }, *this);
    }
*/
    std::size_t size() const noexcept
    {
      return N;
    }

    ReferenceType operator[](std::size_t i) const noexcept
    {
      assert(i < N);
      assert(_data[i] != nullptr);
      return static_cast<ReferenceType>(*_data[i]);
    }

    Iterator begin() const noexcept
    {
      return Iterator(_data);
    }

    Iterator end() const noexcept
    {
      return Iterator(_data + N);
    }

  // deleted:

    StaticReferenceArray() = delete;
    StaticReferenceArray& operator=(StaticReferenceArray&&) = delete;
    StaticReferenceArray& operator=(const StaticReferenceArray&) = delete;    

  };

  template<class ReferenceType>
  class StaticReferenceArray<ReferenceType, 0>
  {
  public:

    std::size_t size() const noexcept
    {
      return 0;
    }

    ReferenceType operator[](std::size_t) const noexcept
    {
      assert(false);
      return *std::remove_reference_t<ReferenceType>(nullptr);
    }
    
    std::nullptr_t begin() const noexcept
    {
      return nullptr;
    }

    std::nullptr_t end() const noexcept
    {
      return nullptr;
    }
    
  };

}


#endif
