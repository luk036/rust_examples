layout: true
class: typo, typo-selection

---

count: false
class: nord-dark, center, middle

# Unit Testing 

---


## Unit Testing (Python)

```python
*from pytest import approx
...
def test_euclid():
    a1 = pg_point([3., -5., 2.])
    a2 = pg_point([6., 2., 2.])
    a3 = pg_point([5., -4., 3.])
    triangle = [a1, a2, a3]
    trilateral = tri_dual(triangle)
    l1, l2, l3 = trilateral
    t1, t2, t3 = tri_altitude(triangle)
*   assert spread(t1, l1) == approx(1, abs=0.01)
```

---

## Unit Testing (C++)

```cpp
*#include <doctest.h>
...
TEST_CASE("Euclid plane (floating point)") {
    auto a1 = pg_point {1., 3., 1.};
    auto a2 = pg_point {4., 2., 1.};
    auto a3 = pg_point {4., -3., 1.};
    auto triangle = std::tuple {a1, a2, a3};
    auto trilateral = tri_dual(triangle);
    const auto& [l1, l2, l3] = trilateral;
    auto [t1, t2, t3] = tri_altitude(triangle);
*   CHECK(spread(t1, l1) == doctest::Approx(1).epsilon(0.01));
}
```

---

## Environment Setup 🔧

- Lubuntu 20.04 LTS:
    - pip install pytest pytest-cov
    - sudo apt install libboost-dev libfmt-dev
    - sudo apt install cmake ninja git gh
- Android termux:
    - pip install pytest pytest-cov
    - pkg install boost fmt
    - pkg install cmake ninja git gh

---

## Setup (Python) 🔧

```bash
$ gh repo clone luk036/physdespy
$ cd physdespy
$ pip install -r requirements.txt
$ python setup.py develop
$ python setup.py test
```

---

## Setup (C++) 🔧

```bash
$ gh repo clone luk036/physdes
$ cd physdes/external
$ git submodule update --init # for doctest
$ cd ..
$ mkdir build; cd build
$ cmake .. -DCMAKE_BUILD_TYPE=Release
$ cmake --build .
$ ctest
```

---

class: nord-dark, center, middle

# Q & A 🗣️
