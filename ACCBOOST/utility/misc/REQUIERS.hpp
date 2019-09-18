

#ifndef ACCBOOST_UTILITY_MISC_REQUIERS_HPP_
#define ACCBOOST_UTILITY_MISC_REQUIERS_HPP_


#include <type_traits>


/// SFINE を使うためのユーティリティ
#define ACCBOOST_REQUIRES(...) typename std::enable_if_t<( __VA_ARGS__)>* = nullptr


#endif
