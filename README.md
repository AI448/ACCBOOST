# ACCBOOST

 ACCBOOST is set of utility functions like Python built-in functions.

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

### Example for tuples
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

### Example for iterable objects
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

### Example for tuples
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

### Example for iterable objects
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

### Example for tuples
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

### Example for iterable objects
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
