#ifndef ACCBOOST_UTILITY_MISC_INLINE_HPP_
#define ACCBOOST_UTILITY_MISC_INLINE_HPP_


/// インライン展開しない．
#define ACCBOOST_NOINLINE __attribute__((noinline))

/// 強制的にインライン展開する．
#define ACCBOOST_INLINE __attribute__((always_inline))


#endif
