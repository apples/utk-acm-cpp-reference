# `std::set`

A `set` is an associative container. It has the following properties:

- Bidirectional
- Semi-stable
- Ordered
- Unique elements

# Example Usage

```C++
#include <set>

typedef std::set<int>    IntSet;
typedef IntSet::iterator IntIter;

int main()
{
	IntSet numbers;
	
	for (int i=0; i<10; ++i)
	{
		int j = i;
		if (j%2 != 0) j /= 2;
		
		if (numbers.insert( j ).second)
		{
			/* Collision! */
		}
	}
	
	// Tried to insert: {0,0,2,1,4,2,6,3,8,4}
	// Collisions at:      ^       ^       ^
	// numbers == {0,1,2,3,4,6,8}
	
	IntIter iter = numbers.find(6);
	numbers.erase( iter );
	
	// numbers == {0,1,2,3,4,8}
}
```

# Notable Methods

`.insert( value )`

- Returns a `std::pair< iterator, bool >`.
  - The first part is an iterator to the inserted or existing element.
  - The second part is a flag indicating if there was no collision.
