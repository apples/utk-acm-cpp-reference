# 1 - Program Structure

Most ICPC problems have a similar input and output format.

Source file is `problem.cpp`, input is `problem.in`, output is `STDOUT`.

Input usually comes in multiple sets.

First line is parameters, following lines are data.

Example: Mid-Central 2013 - F - Digit Sum

Examine the input specification:

- "Each problem is described on a single line."
  - This is actually not useful, as we will see.
- "The line begins with an integer N, such that 2 ≤ N ≤ 14, ..."
  - `int N;`.
  - The code that reads in the input usualy does not care about bounds.
- "... designating the number of numerals included in the problem."
- "Following that are those N numerals."
  - `vector<int> data;`
- "There will always be at least 2 numerals that are nonzero."
  - Don't care.
- "The end of the input is designated by a line containing only the value 0."
  - End program when `N==0`.

So what does the code look like?

```C++
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main()
{
	ifstream input ("problem.in");
	int N;
	vector<int> data;
	
	while (input >> N, N!=0)
	{
		data.clear();
		data.reserve(N);
		
		for (int i=0; i<N; ++i)
		{
			int x;
			input >> x;
			data.push_back(x);
		}
		
		/* ALGORITHM */
	}
}
```

Why is this eloquent?

- Vector overhead approaches zero very quickly.
- Simple code is easy for the compiler to optimize.
- No time wasted parsing input.
- Very expressive, no room for doubt (doubt brings errors)

# 2 - Efficient Algoithms and Containers

## 2.1 - Containers

There are 5 main containers:

### 2.1.1 - `vector<Value>`

- The "default" container.
- It's just an array.
- Random access.
  - `my_vec[7] = 42`
  - `*(my_vec.begin()+7) = 42`
- Efficient back operations.
  - `my_vec.push_back(42)`
  - `my_vec.pop_back()`
- Efficient iteration.
- Slow insertion and removal (except back).
- Iterators are invalidated in some operations.

### 2.1.2 - `list<Value>`

- The "efficient" container.
- Linked list; no random access.
- Slow iteration.
- Efficient insertion and removal.
- Terrible for small datatypes, great for large structs and classes.
- Iterators are rarely invalidated.

### 2.1.3 - `deque<Value>`

- The "stable" container.
- Very similar to `vector<Value>`.
  - Faster front and back operations.
- Iterators are usually invalidated.
  - But references to elements are not! (Spooky!)

### 2.1.4 - `set<Value>`

- The "sorted" container.
- Elements are stored in sorted order.
- All elements are unique (no duplicates).
- Probably a balanced binary tree.
- No random access.
- Slow iteration.
- Efficient insertion and removal (`O(N*log(N)` worst-case).
- Iterators always invalidated.

### 2.1.5 - `map<Key, Value>`

- The "associative" container.
- Acts very much like a set.
- Elements are stored as (Key, Value) pairs.
- Elements are sorted by their Key, unaffected by Value.
- All Keys must be unique, but Values need not be.
- Convenient syntax.
  - `my_map[some_key] = some_value;`
  - If a non-existent Value is accessed via `[]`, it will be created.
- Iterators give access to both the Key and Value of each element.

### 2.1.6 - `multiset<Value>`

- Same as `set<Value>`, but allows duplicates.

### 2.1.7 - `multimap<Key, Value>`

- Same as `map<Key, Value>`, but allows duplicates.
- The convenient subscript `[]` syntax is unavailable.

In general, always start with a `vector` unless you know you need
a different container.

So how do you know which container to use?

- `vector`
  - Default, use if unsure
  - Unstable
- `list`
  - Stable for iterators and references
  - Large objects
- `deque`
  - Stable for references only
  - Queues and stacks
- `set`
  - Implicit sorting
  - Unique
- `map`
  - Implicit sorting on keys
  - Efficient lookup
  - Automatic construction
  - Unique keys

What is "stability"?

The following code is incorrect:

```C++
Item& func(vector<Item>& container)
{
	Item& rval = container.front();
	container.push_back(7);
	return rval;
}
```

The code is incorrect because `vector` is an unstable container.

Let's just change `vector` to `list`:

```C++
Item& func(list<Item>& container)
{
	Item& rval = container.front();
	container.push_back(7);
	return rval;
}
```

The code is now correct, and we only changed one line!

Most containers, especially `vector` and `list`,
share a common interface.

| Member          | `vector` | `list` | `deque` | `set` | `map` | Description
|:----------------|:--------:|:------:|:-------:|:-----:|:-----:|:--
| `.begin()`      | Yes      | Yes    | Yes     | Yes   | Yes   | Begin iterator
| `.end()`        | Yes      | Yes    | Yes     | Yes   | Yes   | End iterator
| `.empty()`      | Yes      | Yes    | Yes     | Yes   | Yes   | Check empty
| `.size()`       | Yes      | Yes    | Yes     | Yes   | Yes   | Get size
| `.insert()`     | Yes      | Yes    | Yes     | Yes   | Yes   | Insert element
| `.erase()`      | Yes      | Yes    | Yes     | Yes   | Yes   | Erase element
| `.push_front()` | No       | Yes    | Yes     | No    | No    | Insert first element
| `.pop_front()`  | No       | Yes    | Yes     | No    | No    | Remove first element
| `.push_back()`  | Yes      | Yes    | Yes     | No    | No    | Insert last element
| `.pop_back()`   | Yes      | Yes    | Yes     | No    | No    | Remove last element
| `.front()`      | Yes      | Yes    | Yes     | No    | No    | First element
| `.back()`       | Yes      | Yes    | Yes     | No    | No    | Last element

Notice a common trend?

All container share a common interfece, except `set` and `map`.

This creates two conceptual categories of containers:

- Sequence containers
  - Access is either `O(1)` via indexing, or `O(N)` through iteration
  - Each iteration is `O(N)`
  - Have the full common subset
- Associative containers
  - Access is `O(log(N))`
  - Each iteration is `O(log(N))`
  - Complex insertion and deletion
  - Lack access to front and back

## 2.2 - Container Adaptors

Container adaptors are wrappers around containers that
simplify the interface of the underlying container.

- `stack`
  - Adapts `vector`, `list`, or `deque`
  - Default `vector`
  - First in, last out (FILO or LIFO)
- `queue`
  - Adapts `list` or `deque`
  - Default `deque`
  - First in, first out (FIFO)
- `priority_queue`
  - Adapts `vector` or `deque`
  - Default `vector`
  - Push any, pop smallest (heap-based)

Let's take a quick look at what `stack` provides:

| Member    | Description
|:----------|:--
| `.push()` | Push the item onto the stack
| `.top()`  | Access the top element
| `.pop()`  | Remove the top element

Just a quick syntax overview:

```C++
{
    stack<int, vector<int> > myStack;
    for (int i=0; i<10; ++i) myStack.push(i);
    while (!myStack.empty())
    {
        cout << myStack.top() << endl;
        myStack.pop();
    }
}
```

## 2.3 - Algorithms

Get your wizard hat, it's time for some magic!

Note: C++11 yielded massive improvements to the algorithm library;
the new algorithms will *not* be covered in this material.

Most algorithms have a signature similar to: `algo(begin, end, ...)`.

Several algorithms have suffixes that change their behavior.
For example, `find` looks for a value, `find_if` applies a predicate,
and `find_if_not` applies an inverted predicate.

### 2.3.1 - Non-modifying Sequence Operations (Searching and Counting)

- `for-each`
  - Applies a function to the range
- `count`
  - Returns the number elements that match a value or predicate
- `find`
  - Returns a pointer to the first element that matches value or predicate
- `search`
  - Similar to `find`, but searches for an entire subrange

### 2.3.2 - Modifying Sequence Operations (Transforming and Copying)

- `copy`
  - Copies a range to another (usually not the best solution)
- `fill`
  - Fills a range with a value
- `generate`
  - Fills a range with values generated by a function
- `transform`
  - Transforms values in the range
- `remove`
  - Removes values from a range based on value or predicate
- `replace`
  - Replaces values in a range that match criteria with another value
- `reverse`
  - Reverse order of a range
- `unique`
  - Removes duplicate elements from a range

### 2.3.3 - Partitioning and Sorting

- `partition`
  - Divides a range into two groups based on a predicate
- `sort`
  - Sort a range
- `stable_partition` and `stable_sort`
  - Same as the basic versions, but preserves order of equal elements

### 2.3.4 - Searching and Set Operations

Note: These algorithms only work on sorted ranges.
Also, many containers provide their own versions of these algorithms.
For example, it is better to use `set.lower_bound` than the global
version.

- `lower_bound`
  - Returns a pointer to the beginning of the subrange of equal elements
- `upper_bound`
  - Returns a pointer to the end of the subrange of equal elements
- `equal_range`
  - Performs `lower_bound` and `upper_bound` simultaneously
- `binary_search`
  - Determines if the value exists in the range (boolean)
- `merge`
  - Merges two sorted ranges into a larger sorted range
- `set_difference`, `set_intersection`, and `set_union`
  - Useful set operations

### 2.3.5 - Heap Operations

These are the algorithms that `priority_queue` uses under the hood.
These are very tricky to use, and I do not have enough room
to explain it here.

- `make_heap`
  - Heapifies a range
- `push_heap`
  - Pushes a value onto the heap
- `pop_heap`
  - Removes the largest value form the heap
- `sort_heap`
  - Un-heapify the range; results in a sorted range

### 2.3.6 - Lexicographical Operations

- `min` and `max`
  - Returns the smallest or largest value of two values or a range
- `lexicographical_compare`
  - Compares two ranges lexicographically
- `next_permutation` and `prev_permutation`
  - Transform the range into the next or previous permutation
  - Detects "overflow"

### 2.3.7 - Numerical Operations

- `accumlate`
  - Summation
- `inner_product`
  - Dot product
- `adjacent_difference`
  - Derivative
- `partial_sum`
  - Integration

# 3 - Container/Algorithm Synergy

## 3.1 - Iterators

Iterators (aka pointers) are what allow algorithms to operate on
ranges within containers. Containers and algorithms are completely
separate otherwise.

Most containers support the common methods `.begin()` and `.end()`,
which are iterators to the begin and end of the container.
The end iterator does not point to a valid element of the container.

There are 5 basic categories of iterators:

- `InputIterator`
  - Supports `++`
  - Invalidated after incrementing
  - Read only
- `ForwardIterator`
  - Is an `InputIterator`
  - Not invalidated after incrementing
- `BidirectionalIterator`
  - Is a `ForwardIterator`
  - Also supports `--`
- `RandomAccessIterator`
  - Is a `BidirectionalIterator`
  - Also supports `+N`
- `OutputIterator`
  - Supports `++`
  - Write only

Each algoirthm will require different categories of iterators.
For example, the `sort` algorithm requires `RandomAccessIterator`,
so it cannot work on `list::iterator`, because `list` does not support
random access.

## 3.2 - Reverse Iterators

Many containers also support an imaginary catergory of iterators.

```C++
void print_reverse(vector<int>& int)
{
    typedef vector<int>::reverse_iterator RIter;
    for (RIter i=vec.begin(); i!=vec.end(); ++i)
    {
        cout << *i;
    }
    cout << endl;
}
```

## 3.3 - Using Predicates

Many algorithms and containers accept predicates.

A binary predicate accepts two values, and a unary predicate accepts one.
Both usually return a `bool`.

Algorithms that require comparison accept a binary predicate:

```C++
bool str_size_comp(const string& a, const string& b)
{
    return (a.size() < b.size());
}

void sort_by_size(vector<string>& vec)
{
    sort(vec.begin(), vec.end(), str_size_comp);
}
```

Algorithms that require a condition accept a boolean unary predicate:

```C++
bool is_even(int i)
{
    return (i%2 == 0);
}

vector<int>::iterator separate_even(vector<int>& vec)
{
    return partition(vec.begin(), vec.end(), is_even);
}
```

Transformation algorithms accept a non-boolean unary predicate:

```C++
int square(int i)
{
    return i*i;
}

void square_vec(vector<int>& vec)
{
    transform(vec.begin(), vec.end(), vec.begin(), square);
}
```

## 3.4 - Efficiency

- Don't be afraid of `vector`
  - Use `.reserve()` if you know the size
- Avoid `list` for small datatypes
  - Cannot make use of cache
- Consider using `vector` with `sort` rather than `set`
  - `set` is better for guaranteeing unique values
  - Same advice for `map`
  - Iterating over `set` and `map` is very expensive

## 3.5 - Strings

The `string` type is a special container that acts mch like a
`vector<char>`. It has several built-in algorithms that should
be preferred over the generic algorithms.

# 4 - Final Tips

- Prefer `vector` as a general container.
- The standard algorithms are *very* efficient.
- Check the container for member algorithms before using generic.
