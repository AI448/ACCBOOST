#ifndef TESTUTILS_HPP_
#define TESTUTILS_HPP_


#include <string>
#include <cxxabi.h>
#include <stdexcept>
#include <iostream>
#include <tuple>


namespace TEST_UTILS
{

  template<class T,
    typename std::enable_if<!std::is_reference_v<T> && !std::is_const_v<T>>::type* = nullptr>
  static inline std::string demangle()
  {
    std::string result;
    int status = 0;
    char* ptr = abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, &status);
    if(ptr == nullptr){
      if(status == -1) throw std::bad_alloc();
      else if(status == -2) throw std::runtime_error("mangled_name is not a valid name under the C++ ABI mangling rules.");
      else if(status == -3) throw std::runtime_error("One of the arguments is invalid.");
      else throw std::runtime_error(std::string("Unknown error occurred at ") + __FILE__  +  ":" + std::to_string(__LINE__) + ".");
    }
    try{
      result = ptr; // note ここで例外が投げられる可能性がある．
    }catch(...){
      ::free(ptr);
      throw;
    }
    ::free(ptr);
    return result;
  }

  template<class T,
    typename std::enable_if<!std::is_reference_v<T> && std::is_const_v<T>>::type* = nullptr>
  static inline std::string demangle()
  {
    return TEST_UTILS::demangle<std::remove_const_t<T>>() + " const";
  }

  template<class T,
    typename std::enable_if<std::is_lvalue_reference_v<T>>::type* = nullptr>
  static inline std::string demangle()
  {
    return TEST_UTILS::demangle<std::remove_reference_t<T>>() + "&";
  }

  template<class T,
    typename std::enable_if<std::is_rvalue_reference_v<T>>::type* = nullptr>
  static inline std::string demangle()
  {
    return TEST_UTILS::demangle<std::remove_reference_t<T>>() + "&&";
  }

  template<class X>
  void serialize(std::ostream& os, const X& x);

  namespace _test
  {
    template<class X>
    auto can_serialize(X&&) ->decltype(std::declval<std::ostream&>() << std::declval<const X&>(), std::true_type());

    std::false_type can_serialize(...);

    template<class... X>
    std::true_type is_tuple(const std::tuple<X...>&);

    std::false_type is_tuple(...);

    static inline void impl(std::ostream&)
    {}

    template<class X>
    void impl(std::ostream& os, const X& x)
    {
      serialize(os, x);
    }

    template<class X, class Y, class... Z>
    void impl(std::ostream& os, const X& x, const Y& y, const Z&... z)
    {
      serialize(os, x);
      serialize(os, ',');
      _test::impl(os, y, z...);
    }

  }

  template<class X>
  void serialize(std::ostream& os, const X& x)
  {
    if constexpr (decltype(TEST_UTILS::_test::can_serialize(x))::value && !std::is_array_v<X>){
      os << x;
    }else if constexpr (decltype(TEST_UTILS::_test::is_tuple(x))::value){
      os << '(';
      std::apply([&](const auto&... y){TEST_UTILS::_test::impl(os, y...);}, x);
      os << ')';
    }else{
      serialize(os, '[');      
      bool first = true;
      for(auto&& v: x){
        if(first){
          first = false;
        }else{
          serialize(os, ',');
        }
        serialize(os, v);
      }
      serialize(os, ']');
    }
  }

  template<class X>
  void dump(X&& x)
  {
    std::cout << TEST_UTILS::demangle<X&&>() << '\t';
    TEST_UTILS::serialize(std::cout, x);
    std::cout << std::endl;
  }

}

#endif
