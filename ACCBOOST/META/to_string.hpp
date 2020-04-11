#ifndef ACCBOOST_META_TO_STRING_HPP_
#define ACCBOOST_META_TO_STRING_HPP_


#include <cxxabi.h>
#include <stdexcept>
#include <string>


namespace ACCBOOST::META
{

  template<class T,
    typename std::enable_if<!std::is_reference_v<T> && !std::is_const_v<T>>::type* = nullptr>
  static inline std::string to_string()
  {
#ifdef __GNUC__
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
#else
#error "Not implemented."
#endif
  }

  template<class T,
    typename std::enable_if<!std::is_reference_v<T> && std::is_const_v<T>>::type* = nullptr>
  static inline std::string to_string()
  {
    return META::to_string<std::remove_const_t<T>>() + " const";
  }

  template<class T,
    typename std::enable_if<std::is_lvalue_reference_v<T>>::type* = nullptr>
  static inline std::string to_string()
  {
    return META::to_string<std::remove_reference_t<T>>() + "&";
  }

  template<class T,
    typename std::enable_if<std::is_rvalue_reference_v<T>>::type* = nullptr>
  static inline std::string to_string()
  {
    return META::to_string<std::remove_reference_t<T>>() + "&&";
  }

}

#endif
