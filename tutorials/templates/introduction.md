# Introduction to Templates

Templates are a generic programming feature found in very few languages.
Most languages rely on type erasure or similar techniques,
but those are usually run-time techniques that are error-prone.

C++ templates are evaluated at compile-time, similar to C's macros.

# Basic Syntax

There are two types of templates in C++03:
function templates and class templates.

In both cases, the template declaration consists of a normal function or class
declaration preceded by `template <args>`, where `args` is a list of
template arguments.

Template arguments can either be a `typename`, an integer literal,
a character string, a function, or another template.

Template parameters for functions are subject to "template argument deduction".
Template argument deduction is a mechanism by which `typename` template
parameters are automagically inferred from the function arguments.

## Function Templates

```C++
template <typename T>
T square(T a)
{
    return a*a;
}

// ...

{
    int i = square(7);
    double j = 7.5;
    j = square(j);
}
```

This function uses template argument deducation to infer the type `T`
from the function argument `a`.

For example, calling `square(7)` will infer that `T` is `int`,
and calling `square(7.5)` will infer that `T` is `double`.

## Class Templates

```C++
template <typename T, typename U>
struct Pair
{
    T first;
    U second;
};

// ...

{
    Pair<int,double> ij;
    ij.first = 7;
    ij.second = 6.8;
}
```

Class templates have no mechanism for argument deduction.
Therefore, it is often useful to have an accompanying "generator" function.

```C++
template <typename T, typename U>
Pair<T,U> MakePair(const T& t, const U& u)
{
    return Pair<T,U>(t,u);
}
```

You may have noticed that this is a naive implementation of `std::pair<>`
and `std::make_pair()`.

# Details on Template Argument Deduction

Template argument deduction is very powerful.
It is a simple pattern-matching system that tries to bind the
type of a function argument to the template arguments.

Argument deduction can also deduce the template parameters
of a type and array sizes.

```C++
template <typename T, int N>
vector<T> array_to_vector(T (&arr)[N])
{
    return vector<T>(&arr[0], &arr[0] + N);
}
```

```C++
template <typename T>
list<T> vector_to_list(const vector<T>& vec)
{
    return list<T>(vec.begin(), vec.end());
}
```

```C++
template <typename T, typename U>
T container_cast(const U& u)
{
    return T(u.begin(), u.end());
}
```

# Deduced Type Properties

Deduced types will be cv-unqualified non-reference types.

For example, a templated function that expects a `const&` must explicitly
request it.

```C++
template <typename T>
void func( const T& t)
{
    // ...
}
```

# Inline

Template functions are implicitly declared with `inline` linkage.
This means that they are to be implemented in a header,
and it is not possible to only declare a function in a header
and implement it elsewhere.
