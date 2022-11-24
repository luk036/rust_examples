layout: true
class: typo, typo-selection

---

count: false
class: nord-dark, center, middle

# Lecture 5: : Lambda function and algorithms

---

## min()/max() in python

```python
from .recti import point
# find the bottom-most and top-most points
lst = [(-2, 2), (0, -1), (-5, 1), (-2, 4),
       (0, -4), (-4, 3), (-6, -2), (5, 1)]
lst = [point(x, y) for x, y in lst]
botmost = min(lst, key=lambda a: (a.y, a.x))
topmost = max(lst, key=lambda a: (a.y, a.x))
```

---

## min()/max() in C++

```cpp
#include <algorithm>
#include <vector>
#include "recti.hpp"

// find the bottom-most and top-most points
auto lst = std::vector<point<int>> 
   { {-2, 2}, {0, -1}, {-5, 1}, {-2, 4},
    {0, -4}, {-4, 3}, {-6, -2}, {5, 1} };
auto up = [](const auto& a, const auto& b) {
    return std::tie(a.y(), a.x()) < std::tie(b.y(), b.x());
};
auto first = lst.begin();
auto last = lst.end();
auto botmost = *std::min_element(first, last, up);
auto topmost = *std::max_element(first, last, up);
```

---

## min()/max() in Rust 🦀 

```cpp
let coords = vec![
    (-2, 2), (0, -1), (-5, 1), (-2, 4), (0, -4), (-4, 3), (-6, -2),
    (5, 1), (2, 2), (3, -3), (-3, -3), (3, 3), (-3, -4), (1, 4)
];
let mut pointset = vec![];
for (x, y) in coords.iter() {
    pointset.push(Point::<i32>::new(*x, *y));
}
let topmost = pointset.iter().max_by_key(|&a| (a.y_, a.x_)).unwrap();
let botmost = pointset.iter().min_by_key(|&a| (a.y_, a.x_)).unwrap();
```

---

## partition() in python:

```python
from itertools import filterfalse, tee

def partition(pred, iterable):
    # partition(is_odd, range(10)) -->  1 9 3 5 7 and 0 2 8 4 6 
    t1, t2 = tee(iterable)
    return filter(pred, t1), filterfalse(pred, t2)

[lst1, lst2] = partition(lambda a: a.x < botmost.x, lst)
```

---

## partition() in C++

```cpp
#include <vector>
auto first = lst.begin();
auto last = lst.end();
auto right = [&](const auto& a) { return a.x() < botmost.x()); };
auto middle = std::partition(first, last, right)
```

---

## partition() in rust:

```rust
let (mut lst1, mut lst2): (Vec<Point<T>>, Vec<Point<T>>) = 
    pointset.iter().partition(|&pt| (pt.x_ >= botmost.x_));
```

---

## Sorting in Python 🐍

```python
lst1 = sorted(lst1, key=lambda a: (a.y, a.x))
lst2 = sorted(lst2, key=lambda a: (a.y, a.x), reverse=True)
```

---

## Sorting in C++

```cpp
auto up = [](const auto& a, const auto& b) {
    return std::tie(a.y(), a.x()) < std::tie(b.y(), b.x());
};
auto down = [](const auto& a, const auto& b) {
    return std::tie(a.y(), a.x()) > std::tie(b.y(), b.x());
};
std::sort(first, middle, up);
std::sort(middle, last, down);
```

---

## Sorting in rust

```rust
lst1.sort_by_key(|&a| (a.y_, a.x_));
lst2.sort_by_key(|&a| (a.y_, a.x_));
lst2.reverse();
```

---

## Python 🐍

```python
def create_ymono_polygon(lst):
    topmost = max(lst, key=lambda a: (a.y, a.x))
    botmost = min(lst, key=lambda a: (a.y, a.x))
    d = topmost - botmost
    [lst1, lst2] = partition(lambda a: d.cross(a - botmost) <= 0, lst)
    lst1 = sorted(lst1, key=lambda a: (a.y, a.x))
    lst2 = sorted(lst2, key=lambda a: (a.y, a.x), reverse=True)
    return lst1 + lst2
```

---

## C++14

```cpp
template <typename FwIter>
inline void create_ymono_polygon(FwIter&& first, FwIter&& last) {
    auto up = [](const auto& a, const auto& b) {
        return std::tie(a.y(), a.x()) < std::tie(b.y(), b.x()); };
    auto down = [](const auto& a, const auto& b) {
        return std::tie(a.y(), a.x()) > std::tie(b.y(), b.x()); };
    auto topmost = *std::max_element(first, last, up);
    auto botmost = *std::min_element(first, last, up);
    auto d = topmost - botmost;
    auto r2l = [&](const auto& a) { return d.cross(a - botmost) <= 0; };
    auto middle = std::partition(first, last, std::move(r2l));
    std::sort(first, middle, std::move(up));
    std::sort(middle, last, std::move(down));
}
```

---

# Rust 🦀

```rust
impl<T: Clone + Num + Ord + Copy> Polygon<T> {
    pub fn create_ymono_polygon(pointset: &[Point<T>]) -> Vec<Point<T>> {
        let max_pt = pointset.iter().max_by_key(|&a| (a.y_, a.x_)).unwrap();
        let min_pt = pointset.iter().min_by_key(|&a| (a.y_, a.x_)).unwrap();
        let d = max_pt - min_pt;
        let (mut lst1, mut lst2): (Vec<Point<T>>, Vec<Point<T>>) = pointset
            .iter()
            .partition(|&a| d.cross(&(a - min_pt)) <= Zero::zero());
        lst1.sort_by_key(|&a| (a.y_, a.x_));
        lst2.sort_by_key(|&a| (a.y_, a.x_));
        lst2.reverse();
        lst1.append(&mut lst2);
        lst1
    }
}
```

---

![img](ymono_polygon.svg)

---

class: nord-dark, center, middle

# Q & A 🙋️
