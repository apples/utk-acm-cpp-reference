# Copy Stream to Vector

Sometimes, it is useful to easily convert stream contents into a container.

For example, if our stream looks like this:

```
"12 42 75 90 13 7 21"
```

We would want to convert it into a vector:

```
{12, 42, 75, 90, 13, 7, 21}
```

This technique is most useful when the number of elements is known.

It is also possible to copy a container into a stream,
although this is not as fequently useful.

# Key Libraries

`<algorithm>`

- `copy()`
- `copy_n()`

`<iterator>`

- `istream_iterator<>`
- `ostream_iterator<>`
- `back_inserter()`

# Example

Input file `input.in`:

```
12 42 75 90 13 7 21
```

Program:

```C++
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

int main()
{
    ifstream in ("input.in");
    vector<int> numbers;
    
    numbers.reserve(7);
    
    copy_n(istream_iterator<int>(in), 7, back_inserter(numbers));
    
    copy(numbers.begin(), numbers.end(), ostream_iterator<int>(cout, "\n"));
}
```
