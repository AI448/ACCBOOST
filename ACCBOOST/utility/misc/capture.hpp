#ifndef ACCBOOST_UTILITY_MISC_CAPTURE_HPP_
#define ACCBOOST_UTILITY_MISC_CAPTURE_HPP_


#include <tuple>
#include <type_traits>
#include <utility>


namespace ACCBOOST{


  namespace _capture
  {
    template<class T>
    struct impl
    {
      static_assert(std::is_reference<T>::value, "T should be reference.");
      using type = std::conditional_t<std::is_lvalue_reference<T>::value, T, std::remove_cv_t<std::remove_reference_t<T>>>;
    };
  }

  /// T が右辺値参照であれば，参照と const, volatile 修飾子を外した型を返すメタ関数．
  /**
   * T は参照型であること．
   */
  template<class T>
  using capture_of = typename ACCBOOST::_capture::impl<T>::type;

  /// x の型が左辺値参照であれば左辺値参照型の値， 右辺値参照であれば，参照と const, volatile 修飾子を外した値を返す関数．
  template<class X>
  ACCBOOST::capture_of<X&&> capture(X&& x) noexcept(std::is_nothrow_constructible_v<ACCBOOST::capture_of<X&&>, X&&>)
  {
    return ACCBOOST::capture_of<X&&>(std::forward<X>(x));
  }

  /// capture の複数引数版．タプルを返す．
  template<class... X>
  std::tuple<ACCBOOST::capture_of<X&&>...> capture_as_tuple(X&&... x) noexcept(( ... && std::is_nothrow_constructible_v<ACCBOOST::capture_of<X&&>, X&&>))
  {
    return std::tuple<ACCBOOST::capture_of<X&&>...>(std::forward<X>(x)...);
  }

}


#endif
