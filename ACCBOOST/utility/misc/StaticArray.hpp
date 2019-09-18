#ifndef ACCBOOST_MISC_STATICARRAY_HPP_
#define ACCBOOST_MISC_STATICARRAY_HPP_


#include "StaticReferenceArray.hpp"


namespace ACCBOOST
{
  /// 参照型にも対応した構造体クラス．
  template<class ValueType, std::size_t N>
  using StaticArray = std::conditional_t<std::is_reference_v<ValueType>, StaticReferenceArray<ValueType, N>, std::array<ValueType, N>>;

}


#endif
