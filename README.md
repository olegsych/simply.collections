# simply::collections

A small C++ library for implementing collections suitable for use in high-level object-oriented APIs.
The C++ [iterators](http://en.cppreference.com/w/cpp/concept/Iterator) are a chore to implement and 
represent collections with a low-level, pointer-like abstraction. The proposed C++
[range](https://github.com/ericniebler/range-v3) concept is much closer to what is needed in modern APIs. 
This library is a separate implementation of this concept focused on API readability and ease of implementation.

## use

Add the [simply.collections](http://www.nuget.org/packages/simply.collections) NuGet package to your Visual C++ 
project using the [Package Manager Dialog](http://docs.nuget.org/consume/Package-Manager-Dialog) or 
the [Package Manager Console](http://docs.nuget.org/consume/package-manager-console).
``` PowerShell
Install-Package simply.collections
```

Include the library header and use its namespace.
``` C++
#include <simply/collections.h>
using namespace simply;
```

Implement an `enumerable`, an internal class encapsulating a collection and responsible for creating enumerators.
``` C++
#using <memory>

class answer_enumerable : public enumerable<int>
{
    std::vector<int> answers { 40, 41, 42 };
public:
    std::unique_ptr<enumerator<int>> create_enumerator() override
    {
        return std::make_unique<answer_enumerator>(answers);
    }
};
```

Implement an `enumerator`, an internal class responsible for returning elements of the collection, one by one.
``` C++
#using <vector>

class answer_enumerator : public enumerator<int>
{
    const std::vector<int> answers;
    size_t index = 0;
public:
    answer_enumerator(const std::vector<int> answers) : answers(answers)
    {
    }

    bool get_next(int* element) override
    {
        if (index < answers.size())
        {
            *element = answers[index++];
            return true;
        }

        return false;
    }
};
```

Use the `range` class to expose the collection in your API. Internally, it relies on the 
`enumerable` and `enumerator` to implement `begin` and `end` iterators.
``` C++
#using <memory>

class question
{
public:
    range<int> answers()
    {
        return range<int> { std::make_shared<answer_enumerable>() };
    }
};
```

You can use `range` with the C++ `for each` loop, the STL algorithms or any other code expecting C++ iterators.
``` C++
#include <iostream>
#include <algorithm>

question q;
range<int> answers { q.answers() };

for each(int answer in answers)
    std::cout << answer;

std::for_each(std::begin(answers), std::end(answers), [](int answer) {
    std::cout << answer;
});
```

## build

[![Build status](https://ci.appveyor.com/api/projects/status/github/olegsych/simply.collections?branch=master)](https://ci.appveyor.com/project/olegsych/simply-collections/branch/master)

From [Visual Studio 2015](https://www.visualstudio.com/downloads):
- Open `simply.collections.sln`
- Select _Build Solution_ from the _Build_ menu
- To switch build between `x86` and `x64` platforms, select _Configuration Manager_ from the _Build_ menu and change the _Active Solution Configuration_

From [Developer Command Prompt for VS2015](https://msdn.microsoft.com/en-us/library/ms229859.aspx):
```
msbuild simply.collections.sln /p:Platform=x86
msbuild simply.collections.sln /p:Platform=x64
```

## test

From Visual Studio 2015:
- Select _Run_ / _All Tests_ from the _Test_ menu
- To switch test execution between `x86` and `x64` platform, select _Test Settings_ from the _Test_ menu and change the _Default Processor Architecture_.

From Developer Command Prompt for VS2015:
```
vstest.console bin\Win32\test.dll /Platform:x86
vstest.console bin\x64\test.dll /Platform:x64 /inIsolation
```