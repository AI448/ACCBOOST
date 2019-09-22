#ifndef ACCBOOST_UTILITY_ITERATOR_MAKE_ARROW_WRAPPER_HPP_
#define ACCBOOST_UTILITY_ITERATOR_MAKE_ARROW_WRAPPER_HPP_


#include "../misc.hpp"


namespace ACCBOOST
{

  namespace _make_arrow_wrapper{
      
    template<class ValueT>
    class ArrowWrapper
    {
      static_assert(!std::is_reference_v<ValueT>);

    private:

      ValueT value_;

    public:

      explicit ArrowWrapper(ValueT&& value) noexcept:
        value_(std::move(value))
      {}

      ArrowWrapper(ArrowWrapper&&) = default;

      decltype(auto) operator->() const noexcept
      {
        return std::addressof(value_); // note: 戻り値は const pointer となる．
      }

    // deleted:

      ArrowWrapper() = delete;
      ArrowWrapper(const ArrowWrapper&) = delete;
      ArrowWrapper& operator=(ArrowWrapper&&) = delete;
      ArrowWrapper& operator=(const ArrowWrapper&) = delete;
    };

  } // _make_arrow_wrapper

  template<class X>
  decltype(auto) make_arrow_wrapper(X&& x)
  {
    if constexpr (std::is_lvalue_reference_v<X>){
      return std::addressof(x);
    }else{
      return ACCBOOST::_make_arrow_wrapper::ArrowWrapper<X>(std::move(x));
    }
  }

}


#endif
