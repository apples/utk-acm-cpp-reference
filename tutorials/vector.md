# `std::vector`

A `vector` is a dynamically allocated array. It has the following properties:

- Random access
- Contiguous
- Unordered

# Example Usage

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

# Notable Methods

All members that increase the `.size()` of the vector may reallocate
and move the vector.

`.push_back( value )`

- Adds new element to the back of the vector.
- Potentially reallocates and swaps the vector.
  - Can be controlled with `.reserve()`.

`.pop_back()`

- Removes the back element.
- Never reallocates.

`.insert( iterator, value )`

- Moves every element in the range `[ iterator, .end() )`.

`.erase( iterator )`

- Moves every element in the range `( iterator, .end() )`.
- Never reallocates.

`.resize( size, [value] )`

- Creates new elements until `.size() == size`.
- Will fill with default or specified value.
- If `.size() > size`, elements are erased instead.
- If `.size() < size`, existing elements are not modified.

`.reserve( size )`

- Allocates room for `size` elements.
- Does not create any new elements.
- Potentially reallocates.

`.size()`

- Returns the number of valid elements.

`.capacity()`

- Returns the max `.size()` of the vector before reallocation must occur.

