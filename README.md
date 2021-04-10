# ThingsToRememberAboutConst

Personally, I am a vigorous user of `const` in c++.
So much so that I've gone a bit over the edge and
started to (or have tried) to use it in places
where it is actually trouble some.

Before I continue I must make a quick aside and stay
that I am not using `const` for performance. `const`
might allow the compiler to do some amazing things,
but that's not even a good justification. Instead, I
use `const` for the maintainability and reliability
benifits.

### Why does this repository exist
This repository exists as an excersie for myself to
document cases where I've gone overboard. Hopefully
the sheer act of documenting will be enough, but if
not then this will also serve as a reference for my
self in the future.


# Documented over zealous attempts

This section is my personal wall of shame when it
comes to `const`. Hopefully with additional context
to explain what I should do instead.

----------------------------------------------------

### const types with standard containers

Recently I found myself in a situation where I
wanted to have a matrix, a.k.a a 2-dimensional array,
with a size I knew at code writing time. I wanted that
matrix to be populated during runtime by user provided
values.

Here's what that looked like

```cpp
std::array<std::array<int, 9>, 9> matrix;
```

Then later on in that program I had wanted to have
`const` copies of that array. This is what I thought
a constant version was like.

```cpp
const std::array<const std::array<int, 9>, 9> matrix;
```

I arrived at this because if I have an array of
`std::array<int, 9>` that I want to be constant then I
just slap `const` right in front of it to get
`const std::array<int, 9>`. From here, I came to the
version above by just repeating this process twice for
the second dimension.

There's one thing that should've served as a warning
that I was going down a path that wasn't well justifed.
This was the fact that I've never, in any other project,
seen the templated code that I had to create to make
non-`const` and `const` versions easily compatibile with
each other. The compiler errors would've made some type
of compatibility code necessary. So why didn't other
projects have it anywhere?

In the case of the project where this question originated,
I continued on ward with creating the compatibility code
for the `non-const` and `const` types. I did this as a
learning exercise in template meta programming features
I hadn't used much, specifically SFINAE and parameter
pack/unpacking.

Now, there was one other more obvious thing that should've
made it clear something was wrong. That thing was there
was no `const` next to the `int` but if you try the
following:

```
const std::array<int, 2> array{0,1};
int & pos0 = array[0];
```

Then you'll get a compilation error. This compilation error
would've lead me to the documentation that I needed to see
to know what was going on. In fact, as I wrote this code
I believed it would not work because part of the benifit of
`const` on standard containers is that the values returned
from inside them should also be `const`.

If we check out the documentation for `std::array::operator[]`
on [cppreference](https://en.cppreference.com/w/cpp/container/array/operator_at) then we'll see that for `const std::array`s we'll access
a `const_reference`. A `const_reference` is a type alias
for `const value_type &` which means that for `std::array`
a single const is enough to specify all levels are constant.
Thus the simpilest solution would've been simply:

```cpp
const std::array<std::array<int, 9>, 9> matrix;
```
