#ifndef ACCBOOST_META_EXPRESSION_TRAITS_HPP_
#define ACCBOOST_META_EXPRESSION_TRAITS_HPP_


#include <iterator>
#include "list.hpp"


namespace ACCBOOST::META
{

  namespace _result_of
  {

    struct Invalid {};

  }

  /// result_of_xxx の結果が正当であれば std::true_type から派生する．
  template<class T>
  struct is_valid: std::bool_constant<!std::is_same_v<T, META::_result_of::Invalid>> {};

  /// result_of_xxx の結果が正当であれば true ．
  template<class T>
  constexpr bool is_valid_v = META::is_valid<T>::value;

  // 単項演算の result_of_xxx 用のマクロ
  #define ACCBOOST_META_DEFINE_EXPRESSION_TRAITS_1(name, expr) \
  namespace _result_of_##name \
  { \
    template<class T> auto test(T&&) ->decltype(expr); \
    META::_result_of::Invalid test(...); \
    template<class T> struct Impl \
    { \
      static_assert(std::is_reference_v<T>, "Parameter of expression_traits meta functions should be reference."); \
      using type = decltype(META::_result_of_##name::test(std::declval<T>())); \
    }; \
    template<class T> struct Impl<META::list<T>>: META::_result_of_##name::Impl<T> {}; \
  } \
  template<class T> using result_of_##name = typename META::_result_of_##name::Impl<T>::type; \
  template<class T> struct is_valid_to_##name: META::is_valid<META::result_of_##name<T>> {}; \
  template<class T> struct is_valid_to_##name<META::list<T>>: META::is_valid<META::result_of_##name<T>> {}; \
  template<class T> constexpr bool is_valid_to_##name##_v = META::is_valid_to_##name<T>::value;

  // 単項演算の result_of_xxx 用のマクロ
  #define ACCBOOST_META_DEFINE_EXPRESSION_TRAITS_2(name, expr) \
  namespace _result_of_##name \
  { \
    template<class T, class U> auto test(T&&, U&&) ->decltype(expr); \
    META::_result_of::Invalid test(...); \
    template<class...> struct Impl; \
    template<class T, class U> struct Impl<T, U> \
    { \
      static_assert(std::is_reference_v<T>, "Parameter of expression_traits meta functions should be reference."); \
      static_assert(std::is_reference_v<U>, "Parameter of expression_traits meta functions should be reference."); \
      using type = decltype(META::_result_of_##name::test(std::declval<T>(), std::declval<U>())); \
    }; \
    template<class T, class U> struct Impl<META::list<T, U>>: META::_result_of_##name::Impl<T, U> {}; \
  } \
  template<class... T> using result_of_##name = typename META::_result_of_##name::Impl<T...>::type; \
  template<class... T> struct is_valid_to_##name: META::is_valid<META::result_of_##name<T...>> {}; \
  template<class... T> struct is_valid_to_##name<META::list<T...>>: META::is_valid<META::result_of_##name<T...>> {}; \
  template<class... T> constexpr bool is_valid_to_##name##_v = META::is_valid_to_##name<T...>::value;

  #define ACCBOOST_META_DEFINE_EXPRESSION_TRAITS_N(name, expr) \
  namespace _result_of_##name \
  { \
    template<class T, class... U> auto test(T&&, U&&...) ->decltype(expr); \
    META::_result_of::Invalid test(...); \
    template<class...> struct Impl; \
    template<class T, class... U> struct Impl<T, U...> \
    { \
      static_assert(std::is_reference_v<T>, "Parameter of expression_traits meta functions should be reference."); \
      static_assert((... && std::is_reference_v<U>), "Parameter of expression_traits meta functions should be reference."); \
      using type = decltype(META::_result_of_##name::test(std::declval<T>(), std::declval<U>()...)); \
    }; \
    template<class T, class... U> struct Impl<META::list<T, U...>>: META::_result_of_##name::Impl<T, U...> {}; \
  } \
  template<class... T> using result_of_##name = typename META::_result_of_##name::Impl<T...>::type; \
  template<class... T> struct is_valid_to_##name: META::is_valid<META::result_of_##name<T...>> {}; \
  template<class... T> struct is_valid_to_##name<META::list<T...>>: META::is_valid<META::result_of_##name<T...>> {}; \
  template<class... T> constexpr bool is_valid_to_##name##_v = META::is_valid_to_##name<T...>::value;

  #define X std::declval<T&&>()
  #define Y std::declval<U&&>()

  ACCBOOST_META_DEFINE_EXPRESSION_TRAITS_1(pre_inclement, ++X)
  ACCBOOST_META_DEFINE_EXPRESSION_TRAITS_1(post_inclement, X++)
  ACCBOOST_META_DEFINE_EXPRESSION_TRAITS_1(pre_declement, --X)
  ACCBOOST_META_DEFINE_EXPRESSION_TRAITS_1(post_declement, X--)
  ACCBOOST_META_DEFINE_EXPRESSION_TRAITS_1(unary_plus, +X);
  ACCBOOST_META_DEFINE_EXPRESSION_TRAITS_1(unary_minus, -X);
  ACCBOOST_META_DEFINE_EXPRESSION_TRAITS_1(negate, !X);
  ACCBOOST_META_DEFINE_EXPRESSION_TRAITS_1(complement, ~X);
  ACCBOOST_META_DEFINE_EXPRESSION_TRAITS_1(indirect, *X);
  ACCBOOST_META_DEFINE_EXPRESSION_TRAITS_1(address_of, &X);
  ACCBOOST_META_DEFINE_EXPRESSION_TRAITS_2(add, X + Y);
  ACCBOOST_META_DEFINE_EXPRESSION_TRAITS_2(subtract, X - Y);
  ACCBOOST_META_DEFINE_EXPRESSION_TRAITS_2(multiplies, X * Y);
  ACCBOOST_META_DEFINE_EXPRESSION_TRAITS_2(divides, X / Y);
  ACCBOOST_META_DEFINE_EXPRESSION_TRAITS_2(modulus, X % Y);
  ACCBOOST_META_DEFINE_EXPRESSION_TRAITS_2(equal, X == Y);
  ACCBOOST_META_DEFINE_EXPRESSION_TRAITS_2(inequal, X != Y);
  ACCBOOST_META_DEFINE_EXPRESSION_TRAITS_2(greater, X > Y);
  ACCBOOST_META_DEFINE_EXPRESSION_TRAITS_2(less, X < Y);
  ACCBOOST_META_DEFINE_EXPRESSION_TRAITS_2(greater_equal, X >= Y);
  ACCBOOST_META_DEFINE_EXPRESSION_TRAITS_2(less_equal, X <= Y);
  ACCBOOST_META_DEFINE_EXPRESSION_TRAITS_2(logical_and, X && Y);
  ACCBOOST_META_DEFINE_EXPRESSION_TRAITS_2(logical_or, X || Y);
  ACCBOOST_META_DEFINE_EXPRESSION_TRAITS_2(bitwise_and, X & Y)
  ACCBOOST_META_DEFINE_EXPRESSION_TRAITS_2(bitwise_or, X | Y)
  ACCBOOST_META_DEFINE_EXPRESSION_TRAITS_2(bitwise_xor, X ^ Y)
  ACCBOOST_META_DEFINE_EXPRESSION_TRAITS_2(left_shift, X << Y)
  ACCBOOST_META_DEFINE_EXPRESSION_TRAITS_2(right_shift, X >> Y)
  ACCBOOST_META_DEFINE_EXPRESSION_TRAITS_2(add_assign, X += Y)
  ACCBOOST_META_DEFINE_EXPRESSION_TRAITS_2(subtract_assign, X -= Y)
  ACCBOOST_META_DEFINE_EXPRESSION_TRAITS_2(multiplies_assign, X *= Y)
  ACCBOOST_META_DEFINE_EXPRESSION_TRAITS_2(divides_assign, X /= Y)
  ACCBOOST_META_DEFINE_EXPRESSION_TRAITS_2(modulus_assign, X %= Y)
  ACCBOOST_META_DEFINE_EXPRESSION_TRAITS_2(right_shift_assign, X >>= Y)
  ACCBOOST_META_DEFINE_EXPRESSION_TRAITS_2(left_shift_assign, X <<= Y)
  ACCBOOST_META_DEFINE_EXPRESSION_TRAITS_2(bitwise_and_assign, X &= Y)
  ACCBOOST_META_DEFINE_EXPRESSION_TRAITS_2(bitwise_xor_assign, X ^= Y)
  ACCBOOST_META_DEFINE_EXPRESSION_TRAITS_2(bitwise_or_assign, X |= Y)
  ACCBOOST_META_DEFINE_EXPRESSION_TRAITS_2(assign, X = Y)
  ACCBOOST_META_DEFINE_EXPRESSION_TRAITS_2(subscript, X[Y])
  ACCBOOST_META_DEFINE_EXPRESSION_TRAITS_N(call, X(Y...))

  using std::begin;
  using std::end;
  using std::size;

  ACCBOOST_META_DEFINE_EXPRESSION_TRAITS_1(begin, begin(X))
  ACCBOOST_META_DEFINE_EXPRESSION_TRAITS_1(end, end(X))
  ACCBOOST_META_DEFINE_EXPRESSION_TRAITS_1(size, size(X))

  #undef X
  #undef Y

  #undef ACCBOOST_META_DEFINE_EXPRESSION_TRAITS_1
  #undef ACCBOOST_META_DEFINE_EXPRESSION_TRAITS_2
  #undef ACCBOOST_META_DEFINE_EXPRESSION_TRAITS_N

}

#endif
