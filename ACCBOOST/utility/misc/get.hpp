#ifndef ACCBOOST_UTILITY_MISC_GET_HPP_
#define ACCBOOST_UTILITY_MISC_GET_HPP_


#include <array>
#include <tuple>
#include <type_traits>


namespace ACCBOOST
{

  /// std::tuple, std::arary または配列の I 番目の要素を取得する．
  /**
   * 引数が std::tuple の左辺値参照かつ I 番目の要素が右辺値参照型である場合に，右辺値参照型を返すことを除き，
   * 標準ライブラリの std::get と同じ．(std::get は左辺値参照型を返す．)
   */
  template<std::size_t I, class T,
    std::remove_reference_t<decltype(std::get<I>(std::declval<T&&>()))>* = nullptr>
  decltype(auto) get(T&& tuple)
  {
    static_assert(I < std::tuple_size_v<std::remove_reference_t<T>>, "");
    using element_type = std::tuple_element_t<I, std::remove_reference_t<T>>;
    using result_type = std::conditional_t<std::is_reference_v<element_type>, element_type, decltype(std::get<I>(std::forward<T>(tuple)))>;
    return static_cast<result_type>(std::get<I>(std::forward<T>(tuple)));
  }

  template<std::size_t I, class T, std::size_t N>
  T&& get(T (&&array)[N])
  {
    return std::move(array[I]);
  }

  template<std::size_t I, class T, std::size_t N>
  T& get(T (&array)[N])
  {
    return array[I];
  }

  /// std::array または配列に ACCBOOST::get を適用した際の戻り値の型を返すメタ関数．
  template<class T>
  struct result_type_of_get_from_array
  {
    static_assert(!std::is_same_v<T, T>, "Template parameter of result_type_of_get_from_array should be reference type of std::array.");
  };

  template<class T, std::size_t N>
  struct result_type_of_get_from_array<T(&)[N]>
  {
    using type = T&;
  };

  template<class T, std::size_t N>
  struct result_type_of_get_from_array<T(&&)[N]>
  {
    using type = T&&;
  };

  template<class T, std::size_t N>
  struct result_type_of_get_from_array<std::array<T, N>&&>
  {
    using type = T&&;
  };

  template<class T, std::size_t N>
  struct result_type_of_get_from_array<const std::array<T, N>&&>
  {
    using type = const T&&;
  };

  template<class T, std::size_t N>
  struct result_type_of_get_from_array<std::array<T, N>&>
  {
    using type = T&;
  };

  template<class T, std::size_t N>
  struct result_type_of_get_from_array<const std::array<T, N>&>
  {
    using type = const T&;
  };

  /// std::array または配列に ACCBOOST::get を適用した際の戻り値の型．
  template<class T>
  using result_type_of_get_from_array_t = typename ACCBOOST::result_type_of_get_from_array<T>::type;

}

#endif
