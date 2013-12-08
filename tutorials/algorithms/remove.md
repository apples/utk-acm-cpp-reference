# `std::remove`

- `remove    ( begin, end, value )`
- `remove_if ( begin, end, predicate )`

The `remove` algorithm is one of the more commonly used algorithms.
As its name implies, it removes all occurences of a value
(or values for which the predicate returns true) from the range.
However, it does not erase the elements from the container.
All algorithms are unaware of containers, they only operate on ranges.

The return value is an iterator to the end of the new range.

Note that the order of the remaining elements is preserved.
The elements after the end of the new range should be erased immediately.

# Example

```C++
#include <algorithm>
#include <vector>

typedef std::vector<int> Container;
typedef Container::iterator Iterator;
using std::remove;
using std::remove_if;

bool is_even(int i)
{
    return (i%2 == 0);
}

int main()
{
    Container numbers;
    
    // numbers == {}
    
    for (int i=0; i<10; ++i)
    {
        numbers.push_back(i);
    }
    
    // numbers == {0,1,2,3,4,5,6,7,8,9}
    
    Iterator new_end = remove_if( numbers.begin(), numbers.end(), is_even );
    
    // numbers == {1,3,5,7,9,5,6,7,8,9}
    // new_end ==           ^
    
    numbers.erase( new_end, numbers.end() );
    
    // numbers == {1,3,5,7,9}
    
    numbers[0] = 5;
    numbers[4] = 5;
    
    // numbers == {5,3,5,7,5}
    
    numbers.erase( remove( numbers.begin(), numbers.end(), 5 ), numbers.end() );
    
    // numbers == {3,7}
}
```
