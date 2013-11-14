# `std::vector`

A `vector` is a dynamically allocated array. It has the following properties:

- Random access
- Contiguous
- Unordered

# Basic Usage

```C++
#include <vector>

typedef std::vector<int> IntVec;
typedef IntVec::iterator IntIter;

int main()
{
    std::vector<int> numbers;
    
    numbers.reserve(10); // Pre-allocates room for 10 elements.
    
    // numbers == {}
    
    for (int i=0; i<10; ++i)
    {
        numbers.push_back(i);
    }
    
    // numbers == {0,1,2,3,4,5,6,7,8,9}
    
    numbers[7] = 42;
    
    // numbers == {0,1,2,3,4,5,6,42,8,9}
    
    for (IntIter iter=numbers.begin(); iter!=numbers.end(); ++iter)
    {
        *iter *= 2;
    }
    
    // numbers == {0,2,4,6,8,10,12,84,16,18}
    
    numbers.erase(numbers.end()-4, numbers.end());
    
    // numbers == {0,2,4,6,8,10}
    
    int i = numbers.back(); // i == 10
    
    // numbers == {0,2,4,6,8,10}
    
    numbers.pop_back();
    
    // numbers == {0,2,4,6,8}
}
```

