layout: true
class: typo, typo-selection

---

count: false
class: nord-dark, center, middle

# Iterators

## C

```c
int lst[] = {2, 3, 5, 7};
size_t N = sizeof(lst); 
for (size_t i = 0; i != N; ++i) {
    printf("%d\n", lst[i]);
}
for (size_t i = 0; i != N; ++i) {
    lst[i] += weight;
}
```

---

## C++11

```cpp
auto lst = std::array{2, 3, 5, 7};
for (auto it = lst.cbegin(); it != lst.cend(); ++it) {
    fmt::print("{}\n", *it);
}
for (auto it = lst.begin(); it != lst.end(); ++it) {
    *it += weight;
}
auto it2 = lst.begin(); // *it == 2
++it2; // *it == 3
++it2; // *it == 5
++it2; // *it == 7
++it2; // *it == lst.end()
```

---

## C++14

- Prefer range-based for loop

```cpp
auto lst = std::array{2, 3, 5, 7};
for (auto&& item : lst) {
    fmt::print("{}\n", item);
}
for (auto& item : lst) {
    item += weight;
}
auto rng = ranges::view(lst); // C++20
```

---

## Python

- Only range-based for loop

```python
lst = [2, 3, 5, 7]
for item in lst:
    print("{}".format(item))
    
for i in range(len(lst)):
    lst[i] += weight 

iter2 = iter(lst)
p = next(iter2) # 2
p = next(iter2) # 3
p = next(iter2) # 5
p = next(iter2) # 7
p = next(iter2) # raise StopIteration
```

---

## Rust

- Only range-based for loop
- No function overloading

- Three types:
  - iter()
  - iter_mut()
  - into_iter()

---

## Rust

```rust
let mut lst = [2, 3, 5, 7];
for item in lst.iter() {
    println!("{}", item);
}
for item in lst.iter_mut() {
    item += weight;
}
let iter2 = lst.into_iter();
let p = iter2.next(); // Some(2)
let p = iter2.next(); // Some(3)
let p = iter2.next(); // Some(5)
let p = iter2.next(); // Some(7)
let p = iter2.next(); // None
```

---

# step by

## C

```c
int lst[] = {2, 3, 5, 7};
size_t N = sizeof(lst); 
for (size_t i = 0; i != N; i += 2) {
    printf("%d\n", lst[i]);
}
```

---

## C++

```cpp
auto lst = std::array{2, 3, 5, 7};
for (auto&& item : ranges::view(lst) | stride(1)) { // ???
    fmt::print("{}\n", item);
}
```

---

## Python

```python
lst = [2, 3, 5, 7]
for i in range(0, len(lst), 2):
    print("{}".format(lst[i]))
```

---

## Rust

```rust
let mut lst = [2, 3, 5, 7];
for item in lst.iter().step_by(2) {
    println!("{}", item);
}
```

---

# drop/skip

## C

```c
int lst[] = {2, 3, 5, 7};
size_t N = sizeof(lst); 
for (size_t i = 1; i != N; ++i) {
    printf("%d\n", lst[i]);
}
```

## C++

```cpp
auto lst = std::array{2, 3, 5, 7};
for (auto&& item : ranges::view(lst) | drop(1)) { // ???
    fmt::print("{}\n", item);
}
```

---

## Python

```python
lst = [2, 3, 5, 7]
for i in range(1, len(lst)):
    print("{}".format(lst[i]))
```

---

## Rust

```rust
let mut lst = [2, 3, 5, 7];
for item in lst.iter().skip(1) {
    println!("{}", item);
}
```

---

# filter

## C

```c
int lst[] = {2, 3, 5, 7};
size_t N = sizeof(lst); 
for (size_t i = 0; i != N; ++i) {
    if (lst[i] == k) {
        continue;
    }
    printf("%d\n", lst[i]);
}
```

## C++

```cpp
auto lst = std::array{2, 3, 5, 7};
for (auto&& item : ranges::view(lst) | 
          filter([&](auto x) { return x != k; } )) { 
    fmt::print("{}\n", item);
}
```

---

## Python

```python
from itertools import filter

lst = [2, 3, 5, 7]
for i in filter(lambda x: x != k, range(len(lst))):
    print("{}".format(lst[i]))
```

---

## Rust

```rust
let mut lst = [2, 3, 5, 7];
for item in lst.iter().filter(|x| x != k) {
    println!("{}", item);
}
```

---

# Implementation

## C++

```cpp
class Foo {
public:
    using iterator = FooIterator;
    auto begin() -> FooIterator;
    auto end() -> FooIterator;
};

class FooIterator {
public:
    typename value_type;
    auto operator++() -> value_type&;
    auto operator*();
};
```

---

## Python

```python
class Foo:
    def __iter__(): ...

class FooIterator:
    def __next__():
```

---

## Rust

```rust
pub trait Iterator {
    type Item;
    fn next(&mut self) -> Option<Self::Item>;
}

impl Iterator for Foo {

}

```

---

class: nord-dark, center, middle

# Q & A 🗣️
