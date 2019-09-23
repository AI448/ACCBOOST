# ACCBOOST

 ACCBOOST is set of utility functions like Python built-in functions.

* [range](#range)
* [zip](#zip)
* [enumerate](#enumerate)
* [map](#map)
* [reverse](#reverse)
* [in](#in)
* [all, any](#allany)
* [filter](#filter)
* [chain_from_iterable](#chain_from_iterable)

## range

### Example
Code
```cpp
#include <iostream>
#include "ACCBOOST/utility.hpp"
using namespace ACCBOOST;
int main()
{
  for(auto&& i: range(5)){
    std::cout << i << std::endl;
  }
}
```
Result
```
0
1
2
3
4
```

 This function support only 1 argument.

## zip

### Example of tuples
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

### Example of iterable objects
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

## enumerate

### Example of tuples
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

### Example of iterable objects
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

## map

### Example of tuples
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

### Example of iterable objects
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
## reverse

### Example of tuple
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

### Example of iterable objects
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

## in

## Example of tuples
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

## Example of iterable objects
Code
```
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

## all,any

## Example of tuples
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

### Example of iterable objects
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

## filter

### Example of iterable objects
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

## chain_from_iterable

### Example of iterable objects
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
