layout: true
class: typo, typo-selection

---

count: false
class: nord-dark, center, middle

# Lecture 2: Basic Data Types, Function and Class

---

## Define function in Python

```python
# file: low_discr_seq.py

def vdc(k, base):
    """Van der Corput sequence generator"""
    vdc = 0.0
    denom = 1.0
    while k != 0:
        remainder = k % base
        denom *= base
        k //= base  # integer div
        vdc += remainder / denom
    return vdc


if __name__ == '__main__':
*   for k in range(1, 11):
        print("{}", vdc(k, 2))
```

---

## C++ equivalence

```cpp
/* Van der Corput sequence generator */
inline
auto vdc(size_t k, size_t base) -> double {
    auto vdc = 0.0;
    auto denom = 1.0;
    while (k != 0) {
        const auto remainder = k % base;
        denom *= base;
        k /= base;
        vdc += double(remainder) / denom;
    }
    return vdc;
}

int main() {
    for (auto k=1U; k != 11U; ++k) 
       fmt::print("{}\n", vdc(k, 2));
}
```

---

## Rust 🦀 equivalence

```rust
fn vdc(mut k: u32, base: u32) -> f64 {
    let mut vdc = 0.0;
    let mut denom = 1.0;
    while k != 0 {
        let remainder = k % base;
        denom *= base as f64;
        k /= base;
        vdc += (remainder as f64) / denom;
    }
    vdc  // <- note!
}

fn main() {
    for k in 1..11 { 
        println!("{}", vdc(k, 2));
    }
}
```

---

## Type checking in Python with `MyPy`

```python
# Check with mypy:
#  $ pip install mypy
#  $ mypy low_discr_seq.py

*def vdc(k: int, base: int) -> float:
    vdc = 0.0
    denom = 1.0
    while k != 0:
        remainder = k % base
        denom *= base
*       k /= base  # Oop!!! error!!!
        vdc += remainder / denom
    return vdc
```

---

## `Vdcorput` (Python 🐍)

```python
class Vdcorput:
    def __init__(self, base: int = 2):
        """Constructor"""
        self.count: int = 0
        self.base: int = base

    def pop(self) -> float:
        """make object callable"""
        self.count += 1
        return vdc(self.count, self.base)

if __name__ == '__main__':
    vdc = Vdcorput(3)
    for _ in range(10):
        print(vdc.pop())
```

---

## `Vdcorput` (C++)

```cpp
class Vdcorput {
* private:
    size_t _base, _count;

* public:
    // Use explicit to avoid implicit conversion
    explicit Vdcorput(size_t base = 2)
        : _base{base} , _count{0} { }

    auto pop() -> double {
        this->_count += 1;
        return vdc(this->_count, this->_base); }
};
int main() {
    auto vdc = Vdcorput(3);
    for (auto i=0U; i != 10; ++i) 
        fmt::print("{}\n", vdc.pop());
}
```

---

## Circle (Python 🐍)

```python
from math import pi, sin, cos, sqrt
from typing import List 

TWO_PI = 2.0 * pi

class Circle:
    def __init__(self, base: int = 2):
        self.vdc = vdcorput(base)

*   def pop(self) -> List[float]:
        theta = self.vdc.pop() * TWO_PI
        return [sin(theta), cos(theta)]
```

Note: return a list

---

## Circle (C++)

```cpp
#include <cmath> // for sin(), cos(), acos()
#include <vector>  // for vector
using namespace std;
static const auto TWO_PI = 2.0 * acos(-1.);

class Circle {
    ...

    // Compilers will optimize the return
    // value (RVO) so that no copying is needed 
*   auto pop() -> std::array<double, 2> {
	    const auto theta = this->_vdc() * twoPI;
        return {sin(theta), cos(theta)};
    }
};
```

---

## Halton (Python 🐍)

```python
from typing import List

class Halton:
    """Generate Halton sequence"""

*   def __init__(self, base: List[int]):
        self.vdc0 = Vdcorput(base[0])
        self.vdc1 = Vdcorput(base[1])

    def pop(self) -> List[float]:
        return [self.vdc0.pop(), self.vdc1.pop()]

    def reseed(self, seed: int):
        self.vdc0.reseed(seed)
        self.vdc1.reseed(seed)
```

---

## Halton (C++)

```cpp
class Halton {
  private:
    vdcorput _vdc0, _vdc1;

  public:
*   explicit halton(const size_t* base)
        : _vdc0(base[0]), _vdc1(base[1]) { }

    auto pop() -> std::array<double, 2> {
        return {this->_vdc0.pop(), this->_vdc1.pop()}; }

    auto reseed(size_t seed) -> void { 
        this->_vdc0.reseed(seed);
        this->_vdc1.reseed(seed);
    } // why not const?
};
```

---

## Sphere (Python 🐍)

```python
class Sphere:
    def __init__(self, base: List[int]):
        self.vdc = Vdcorput(base[0])
        self.cirgen = Circle(base[1])

    def pop(self) -> List[float]:
        cphi = 2.0 * self.vdc.pop() - 1.0
        sphi = sqrt(1.0 - cphi * cphi)
        [c, s] = self.cirgen.pop()
        return [sphi * c, sphi * s, cphi]

    def reseed(self, seed: int):
        self.cirgen.reseed(seed)
        self.vdc.reseed(seed)
```

---

## Sphere (C++)

```cpp
class Sphere {
  private:
    Vdcorput _vdc;
    Circle _cirgen;

  public:
    explicit Sphere(const size_t* base)
        : _vdc(base[0]), _cirgen(base[1]) {}

    auto pop() -> std::array<double, 3> {
        const auto cphi = 2.0 * this->_vdc.pop() - 1.0;
        const auto sphi = sqrt(1.0 - cphi*cphi);
        const auto [c, s] = this->_cirgen.pop();
        return {sphi * c, sphi * s, cphi};
    }
};
```

---

## Find roots (Python 🐍)

```python
from math import sqrt
from typing import Optional, Tuple

def find_roots(
    a: float, b: float, c: float
) -> Optional[Tuple[float, float]]:
    assert a != 0.0
    b /= a
    c /= a
    hb = b / 2.0
    d = hb * hb - c
*   if d < 0.0: return None
    x1 = -hb + (sqrt(d) if hb < 0.0 else -sqrt(d))
    x2 = c / x1
    return x1, x2
```

---

## Find roots (C++)

```cpp
#include <optional>
...
template <typename T>
auto find_roots(const T& a, T b, T c) -> optional<pair<T, T>> {
    assert(a != 0.0);
    b /= a;
    c /= a;
    auto hb = b / 2.0;
    auto d = hb * hb - c;
*   if (d < 0.0) return {}; // C++17
    auto x1 = -hb + (hb < 0.0 ? sqrt(d) : -sqrt(d));
    auto x2 = c / x1;
    return { { x1, x2 } };
}
```

---

## Conclusion

- Return Value Optimization (RVO)
- Python 🐍 changes the way I write C++.
- Type-checking is your friend.
- `const` is useful. But don't over-constraint the callers.
- Prefer composition rather than inheritance.

---

## Source code

Python 🐍:

```bash
$ wget https://github.com/luk036/pylds/blob/master/src/pylds/low_discr_seq.py
```

C++:

```bash
$ wget https://github.com/luk036/low_discr_seq/blob/master/lib/include/lds/low_discr_seq.hpp
```

---

class: nord-dark, center, middle

# Q & A 🙋️
