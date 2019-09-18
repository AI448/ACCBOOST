#ifndef ACCBOOST_META_LIST_HPP_
#define ACCBOOST_META_LIST_HPP_


#include <type_traits>
#include <cstdint>


namespace ACCBOOST::META
{

  /// 型リスト．
  template<class... T>
  struct list;

  /// list の要素数を返すメタ関数．
  template<class List>
  struct len;

  template<>
  struct len<META::list<>>
  {
    static constexpr std::size_t value = 0;
    constexpr operator std::size_t() const noexcept {return value;}
  };

  template<class T1, class... T2>
  struct len<META::list<T1, T2...>>
  {
    static constexpr std::size_t value = 1 + len<list<T2...>>::value;
    constexpr operator std::size_t() const noexcept {return value;}
  };

  template<class List>
  constexpr std::size_t len_v = META::len<List>::value;

  namespace _get
  {

    template<std::size_t I, class List>
    struct impl;

    template<std::size_t I>
    struct impl<I, META::list<>> {};

    template<class T1, class... T2>
    struct impl<0, META::list<T1, T2...>>
    {
      using type = T1;
    };

    template<std::size_t I, class T1, class... T2>
    struct impl<I, META::list<T1, T2...>>
    {
      using type = typename META::_get::impl<I - 1, META::list<T2...>>::type;
    };

  }

  /// list の I 番目の要素を返すメタ関数．
  template<std::size_t I, class List>
  using get = typename META::_get::impl<I, List>::type;

  namespace _chain
  {

    template<class... T>
    struct impl;

    template<>
    struct impl<>
    {
      using type = META::list<>;
    };

    template<class... T>
    struct impl<META::list<T...>>
    {
      using type = META::list<T...>;
    };

    template<class... T1, class... T2, class... T3>
    struct impl<list<T1...>, list<T2...>, T3...>
    {
      using type = typename META::_chain::impl<META::list<T1..., T2...>, T3...>::type;
    };

  } // _chain

  /// list 同士を結合した list を返すメタ関数．
  template<class... Lists>
  using chain = typename META::_chain::impl<Lists...>::type;

  namespace _zip
  {

    template<class List1, class List2>
    struct sub;

    template<>
    struct sub<META::list<>, META::list<>>
    {
      using type = META::list<>;
    };

    template<class T1, class... T2, class T3, class... T4>
    struct sub<META::list<T1, T2...>, META::list<T3, T4...>>
    {
      using type = META::chain<
	      META::list<META::chain<T1, META::list<T3>>>,
	      typename META::_zip::sub<list<T2...>, META::list<T4...>>::type>;
    };

    template<class... T>
    struct impl2;

    template<class... T>
    struct impl2<META::list<T...>>
    {
      using type = META::list<T...>;
    };

    template<class... T1, class... T2, class... T3>
    struct impl2<META::list<T1...>, META::list<T2...>, T3...>
    {
      static_assert(META::len<META::list<T1...>>::value == META::len<META::list<T2...>>::value);
      using type = typename META::_zip::impl2<
	      typename META::_zip::sub<META::list<T1...>, META::list<T2...>>::type, T3...>::type;
    };

    template<class... T>
    struct impl1;

    template<class... T1, class... T2>
    struct impl1<META::list<T1...>, T2...>
    {
      using type = typename META::_zip::impl2<META::list<META::list<T1>...>, T2...>::type;
    };

  }

  /// 複数の list を zip した結果を返すメタ関数．
  template<class... Lists>
  using zip = typename META::_zip::impl1<Lists...>::type;

  namespace _reverse
  {

    template<class>
    struct impl;

    template<>
    struct impl<META::list<>>
    {
      using type = META::list<>;
    };

    template<class T1, class... T2>
    struct impl<META::list<T1, T2...>>
    {
      using type = META::chain<typename META::_reverse::impl<META::list<T2...>>::type, META::list<T1>>;
    };

  } // _reverse

  /// List の要素の並び順を逆転した list を返すメタ関数．
  template<class List>
  using reverse = typename META::_reverse::impl<List>::type;

  namespace _map
  {

    template<template<class...> class F, class T>
    struct impl;

    template<template<class...> class F, class... T>
    struct impl<F, META::list<T...>>
    {
      using type = META::list<F<T>...>;
    };

  }

  /// List の各要素に MetaFunction を適用した結果の list を返すメタ関数．
  template<template<class...> class MetaFunction, class List>
  using map = typename META::_map::impl<MetaFunction, List>::type;

/*
  template<class T>
  struct negative: std::bool_constant<!T::value> {};
*/

  /// List の各要素の value が全て true なら true を返すメタ関数．
  template<class List>
  struct all;

  template<>
  struct all<META::list<>>
  {
    static constexpr bool value = true;
  };

  template<class T, class... U>
  struct all<META::list<T, U...>>
  {
    static constexpr bool value = T::value && META::all<META::list<U...>>::value;
  };

  template<class List>
  constexpr bool all_v = META::all<List>::value;

  /// List の各要素の value のいずれかが true なら true を返すメタ関数．
  template<class List>
  struct any;

  template<>
  struct any<META::list<>>
  {
    static constexpr bool value = false;
  };

  template<class T, class... U>
  struct any<META::list<T, U...>>
  {
    static constexpr bool value = T::value || META::any<META::list<U...>>::value;
  };

  template<class List>
  constexpr bool any_v = META::any<List>::value;

}


#endif

