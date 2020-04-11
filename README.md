

# ACCBOOST

 ACCBOOST is set of utility functions for c++17 like Python built-in functions.

- [Requirements](#requirements)
- [Examples](#examples)
    - [range](#range)
    - [zip for iterables](#zip-for-iterables)
    - [zip for tuples](#zip-for-tuples)
    - [enumerate for iterables](#enumerate-for-iterables)
    - [enumerate for tuples](#enumerate-for-tuples)
    - [map for iterables](#map-for-iterables)
    - [map for tuples](#map-for-tuples)
    - [reverse for iterables](#reverse-for-iterables)
    - [reverse for tuples](#reverse-for-tuples)
    - [in for initializer list](#in-for-initializer-list)
    - [in for iterable](#in-for-iterable)
    - [in for tuple](#in-for-tuple)
    - [all any for initializer list](#all-any-for-initializer-list)
    - [all any for iterables](#all-any-for-iterables)
    - [all any for tuples](#all-any-for-tuples)
    - [filter for iterables](#filter-for-iterables)
    - [chain for iterable](#chain-for-iterable)

## Requirements

* g++ -std=c++17
* clang++ -std=c++17
* icl /std:c++17


## Examples
### range
Code
```cpp
#include <iostream>
#include "ACCBOOST/utility.hpp"
using namespace ACCBOOST;
int main()
{
  for(auto&& i: range(3)){
    std::cout << i << std::endl;
  }
  for(auto&& i: range(10, 13)){
    std::cout << i << std::endl;
  }
}
```
Result
```
0
1
2
10
11
12
```
### zip for iterables
Code
```cpp
#include <iostream>
#include <vector>
#include <list>
#include "ACCBOOST/utility.hpp"
using namespace ACCBOOST;
int main()
{
  std::vector<int> a = {1, 2, 3};
  std::list<double> b = {0.1, 0.2, 0.3};
  for(auto&& [x, y]: zip(a, b)){
    std::cout << x << ' ' << y << std::endl;
  }
}
```
Result
```
1 0.1
2 0.2
3 0.3
```
### zip for tuples
Code
```cpp
#include <iostream>
#include <tuple>
#include "ACCBOOST/utility.hpp"
using namespace ACCBOOST;
int main()
{
  std::tuple<int, double> a = {1, 0.1};
  std::tuple<double, char> b = {0.2, 'A'};
  auto c = zip(a, b);
  std::cout << std::get<0>(std::get<0>(c)) << ' ' << std::get<0>(std::get<1>(c)) << std::endl;
  std::cout << std::get<1>(std::get<0>(c)) << ' ' << std::get<1>(std::get<1>(c)) << std::endl;
}
```
Result
```
1 0.1
0.2 A
```
### enumerate for iterables
Code
```cpp
#include <iostream>
#include <vector>
#include "ACCBOOST/utility.hpp"
using namespace ACCBOOST;
int main()
{
  std::vector<std::string> a = {"A", "B", "C"};
  std::vector<int> b = {20, 31, 42};
  for(auto&& [i, x, y]: enumerate(a, b)){
  std::cout << i << ' ' << x << ' ' << y << std::endl;
  }
  return 0;
}
```
Result
```
0 A 20
1 B 31
2 C 42
```
### enumerate for tuples
Code
```cpp
#include <iostream>
#include <tuple>
#include "ACCBOOST/utility.hpp"
using namespace ACCBOOST;
int main()
{
  std::tuple<std::string, double> a = {"A", 0.1};
  auto b = enumerate(a);
  std::cout << std::get<0>(std::get<0>(b)) << ' ' << std::get<1>(std::get<0>(b)) << std::endl;
  std::cout << std::get<0>(std::get<1>(b)) << ' ' << std::get<1>(std::get<1>(b)) << std::endl;
}
```
Result
```
0 A
1 0.1
```
### map for iterables
Code
```cpp
#include <iostream>
#include <vector>
#include <list>
#include "ACCBOOST/utility.hpp"
using namespace ACCBOOST;
int main()
{
  std::vector<int> a = {1, 2, 3};
  std::list<double> b = {0.1, 0.2, 0.3};
  for(auto&& z: map([](auto&& x, auto&& y){return x + y;}, a, b)){
  std::cout << z << std::endl;
  }
  return 0;
}
```
Result
```
1.1
2.2
3.3
```
### map for tuples
Code
```cpp
#include <iostream>
#include <tuple>
#include "ACCBOOST/utility.hpp"
using namespace ACCBOOST;
int main()
{
  std::tuple<int, std::string> a = {1, "Hello"};
  std::tuple<double, std::string> b = {0.1, "World"};
  auto c = map([](auto&& x, auto&& y){return x + y;}, a, b);
  std::cout << std::get<0>(c) << std::endl;
  std::cout << std::get<1>(c) << std::endl;
  return 0;
}
```
Result
```
1.1
HelloWorld
```
### reverse for iterables
Code
```cpp
#include <iostream>
#include <vector>
#include "ACCBOOST/utility.hpp"
using namespace ACCBOOST;
int main()
{
  std::vector<int> a = {1, 2, 3, 4};
  for(auto&& x: reverse(a)){
    std::cout << x << std::endl;
  }
}
```
Result
```
4
3
2
1
```
### reverse for tuples
Code
```cpp
#include <iostream>
#include <tuple>
#include "ACCBOOST/utility.hpp"
using namespace ACCBOOST;
int main()
{
  std::tuple<std::string, double> a = {"A", 0.1};
  auto b = reverse(a);
  std::cout << std::get<0>(b) << std::endl;
  std::cout << std::get<1>(b) << std::endl;
}
```
Result
```
0.1
A
```
### in for initializer list
Code
```cpp
#include <iostream>
#include <vector>
#include "ACCBOOST/utility.hpp"
using namespace ACCBOOST;
int main()
{
  std::cout << in(2, {1, 2, 3}) << std::endl;
  std::cout << in(0, {1, 2, 3}) << std::endl;
}
```
Result
```
1
0
```
### in for iterable
Code
```cpp
#include <iostream>
#include <vector>
#include "ACCBOOST/utility.hpp"
using namespace ACCBOOST;
int main()
{
  std::vector<double> a = {1, 1e-2, 0};
  std::cout << in(1e-2, a) << std::endl;
  std::cout << in(3, a) << std::endl;
}

```
Result
```
1
0
```
### in for tuple
Code
```cpp
#include <iostream>
#include <tuple>
#include "ACCBOOST/utility.hpp"
using namespace ACCBOOST;
int main()
{
  std::tuple<int, double, double> a = {1, 1e-2, 0};
  std::tuple<int, double, double> b = {2, 1e-2, -1e-1};
  std::cout << in(0, a) << std::endl;
  std::cout << in(0, b) << std::endl;  
}
```
Result
```
1
0
```
### all any for initializer list
Code
```cpp
#include <iostream>
#include <vector>
#include "ACCBOOST/utility.hpp"
using namespace ACCBOOST;
int main()
{
  std::cout << all([](auto&& x){return x % 2 == 0;}, {1, 2, 3, 4}) << std::endl;
  std::cout << all([](auto&& x){return x % 2 == 0;}, {2, 4}) << std::endl;
  std::cout << all([](auto&& x){return x % 2 == 0;}, {1, 3, 5}) << std::endl;    
  std::cout << any([](auto&& x){return x % 2 == 0;}, {1, 2, 3, 4}) << std::endl;
  std::cout << any([](auto&& x){return x % 2 == 0;}, {2, 4}) << std::endl;
  std::cout << any([](auto&& x){return x % 2 == 0;}, {1, 3, 5}) << std::endl;
}
```
Result
```
0
1
0
1
1
0
```
### all any for iterables
Code
```cpp
#include <iostream>
#include <vector>
#include "ACCBOOST/utility.hpp"
using namespace ACCBOOST;
int main()
{
  std::vector<int> a = {1, 2, 3, 4};
  std::vector<int> b = {2, 4};
  std::vector<int> c = {1, 3, 5};
  std::cout << all([](auto&& x){return x % 2 == 0;}, a) << std::endl;
  std::cout << all([](auto&& x){return x % 2 == 0;}, b) << std::endl;
  std::cout << all([](auto&& x){return x % 2 == 0;}, c) << std::endl;    
  std::cout << any([](auto&& x){return x % 2 == 0;}, a) << std::endl;
  std::cout << any([](auto&& x){return x % 2 == 0;}, b) << std::endl;
  std::cout << any([](auto&& x){return x % 2 == 0;}, c) << std::endl;
}
```
Result
```
0
1
0
1
1
0
```
### all any for tuples
Code
```cpp
#include <iostream>
#include <tuple>
#include "ACCBOOST/utility.hpp"
using namespace ACCBOOST;
int main()
{
  std::tuple<int, double, char> a = {1, 1e-2, 0};
  std::tuple<int, double, char> b = {0, 0.0, 0};  
  std::cout << all([](auto&& x){return x == 0;}, a) << std::endl;
  std::cout << all([](auto&& x){return x == 0;}, b) << std::endl;  
  std::cout << any([](auto&& x){return x == 0;}, a) << std::endl;
  std::cout << any([](auto&& x){return x == 0;}, b) << std::endl;
}
```
Result
```
0
1
1
1
```
### filter for iterables
Code
```cpp
#include <iostream>
#include <vector>
#include "ACCBOOST/utility.hpp"
using namespace ACCBOOST;
int main()
{
  std::vector<int> a = {0, 1, 2, 3, 4, 5, 6};
  for(auto&& y: filter([](auto&& x){return x % 3 == 0;}, a)){
    std::cout << y << std::endl;
  }
  return 0;
}
```
Result
```
0
3
6
```
### chain for iterable
Code
```cpp
#include <iostream>
#include <vector>
#include "ACCBOOST/utility.hpp"
using namespace ACCBOOST;
int main()
{
  std::vector<std::vector<int>> a = {{1, 2}, {3, 4}, {5, 6}};
  for(auto&& y: chain_from_iterable(a)){
    std::cout << y << std::endl;
  }
  return 0;
}
```
Result
```
1
2
3
4
5
6
```
