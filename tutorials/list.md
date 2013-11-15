# `std::list`

A `list` is a doubly linked list. It has the following properties:

- Bidirectional
- Stable
- Unordered

# Example Usage

```C++
#include <list>

typedef std::list<int>    IntList;
typedef IntList::iterator IntIter;

int main()
{
	IntList numbers;
	
	// numbers == {}
	
	for (int i=0; i<10; ++i)
	{
		numbers.push_back(i);
	}
	
	// numbers == {0,1,2,3,4,5,6,7,8,9}
	
	for (IntIter iter=numbers.begin(); iter!=numbers.end(); ++iter)
	{
		if ((*iter)%2 == 0) *iter += 5;
	}
	
	// numbers == {5,1,7,3,9,5,11,7,13,9}
	
	numbers.sort();
	
	// numbers == {1,3,5,5,7,7,9,9,11,13}
	
	numbers.unique();
	
	// numbers == {1,3,5,7,9,11,13}
	
	while (numbers.back() >= 10)
	{
		numbers.pop_back();
	}
	
	// numbers == {1,3,5,7,9}
}
```

# Notable Methods

`.merge( list )`

- Merges the given list into this list.
  - Both lists must be sorted.
- The other list is moved, not copied.
  - It will be empty after the merge.

`.splice( iterator, list )`

- Moves all elements from the given list into this list
  at the given position.
- Other list will be empty after the splice.

`.remove( value/predicate )`

- Removes all elements matching the value or predicate.

`.reverse()`

- Reverses the list.

`.unique()`

- Removes duplicate elements.

`.sort()`

- Sorts the list.
