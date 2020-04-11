#ifndef ACCBOOST_META_LIST_HPP_
#define ACCBOOST_META_LIST_HPP_


#include <type_traits>
#include <cstdint>


namespace ACCBOOST::META
{

  /// 型リスト．
  template<class... T>
  struct list {};

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

  /// list の T に合致する要素のインデックスを返すメタ関数
  template<class T, class List>
  struct find;

  template<class T>
  struct find<T, META::list<>>: std::integral_constant<std::size_t, 0>
  {};

  template<class T, class U1, class... U2>
  struct find<T, META::list<U1, U2...>>: std::integral_constant<std::size_t, std::is_same_v<T, U1> ? 0 : 1 + META::find<T, META::list<U2...>>::value>
  {};

  template<class T, class List>
  constexpr std::size_t find_v = META::find<T, List>::value;

  /// list が T を含むなら true を返すメタ関数
  template<class T, class List>
  struct in;

  template<class T>
  struct in<T, META::list<>>: std::bool_constant<false>
  {};

  template<class T, class U1, class... U2>
  struct in<T, META::list<U1, U2...>>: std::bool_constant<std::is_same_v<T, U1> || META::in<T, META::list<U2...>>::value>
  {};

  template<class T, class List>
  constexpr std::size_t in_v = META::in<T, List>::value;

  /// list の要素に重複が存在すれば true_type そうでなければ false_type から派生する。
  template<class List>
  struct exists_duplicates;

  template<>
  struct exists_duplicates<META::list<>>: std::bool_constant<false> {};

  template<class T, class... U>
  struct exists_duplicates<META::list<T, U...>>: std::bool_constant<!META::in<T, META::list<U...>>() && META::exists_duplicates<META::list<U...>>()> {};

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

  namespace _drop_duplicates
  {

    template<class List>
    struct impl;

    template<>
    struct impl<META::list<>>
    {
      using type = META::list<>;
    };

    template<class T, class... U>
    struct impl<META::list<T, U...>>
    {
      using type = std::conditional_t<
        META::in<T, META::list<U...>>::value,
        typename META::_drop_duplicates::impl<META::list<U...>>::type,
        META::chain<META::list<T>, typename META::_drop_duplicates::impl<META::list<U...>>::type>>;
    };

  }

  /// List の重複要素を削除するメタ関数
  template<class List>
  using drop_duplicates = META::reverse<typename META::_drop_duplicates::impl<META::reverse<List>>::type>;


  namespace _filter
  {

    template<template<class> class F, class List>
    struct impl;

    template<template<class> class F>
    struct impl<F, META::list<>>
    {
      using type = META::list<>;
    };

    template<template<class> class F, class T, class... U>
    struct impl<F, META::list<T, U...>>
    {
      using type = META::chain<
        std::conditional_t<F<T>::value, META::list<T>, META::list<>>,
        typename META::_filter::impl<F, META::list<U...>>::type>;
    };

  }

  template<template<class> class F, class List>
  using filter = typename META::_filter::impl<F, List>::type;


  namespace _apply
  {

    template<template<class...> class F, class List>
    struct impl;

    template<template<class...> class F, class... T>
    struct impl<F, META::list<T...>>
    {
      using type = F<T...>;
    };

  }

  template<template<class...> class F, class List>
  using apply = typename META::_apply::impl<F, List>::type;


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



  namespace _product
  {

    template<class T, class ListList>
    struct chain_for;

    template<class T, class... Lists>
    struct chain_for<T, META::list<Lists...>>
    {
      using type = META::list<META::chain<META::list<T>, Lists>...>;
    };

    template<class... Lists>
    struct impl;

    template<>
    struct impl<>
    {
      using type = META::list<META::list<>>;
    };

    template<class... T, class... Lists>
    struct impl<META::list<T...>, Lists...>
    {
      using type = META::chain<typename META::_product::chain_for<T, typename META::_product::impl<Lists...>::type>::type...>;
    };

  }

  template<class... Lists>
  using product = typename META::_product::impl<Lists...>::type;

/*
  template<template<class...> class F>
  struct negative
  {
    template<class... T>
    using function = std::bool_constant<!F<T...>()>;
  };
*/

  template<class T>
  struct is_same_to
  {
    template<class U>
    using function = std::is_same<T, U>;
  };

  template<class T>
  struct is_not_same_to
  {
    template<class U>
    using function = std::bool_constant<!std::is_same<T, U>()>;
  };
  
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

