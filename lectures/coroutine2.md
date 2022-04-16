
---

## Python 🐍 code

```python
def BRGC_gen(n: int):
    """Binary Reflected Gray Code
    """
    if n == 1:
        yield 0
        return
    yield from BRGC_gen(n - 1)
    yield n - 1
    yield from BRGC_gen(n - 1)
```

---

## Rust 🦀 code

```rust
use genawaiter::sync::{Gen, GenBoxed};

/// Binary Reflexed Gray Code Generator
pub fn brgc_gen(n: usize) -> GenBoxed<usize> {
    Gen::new_boxed(|co| async move {
        if n < 1 {
            return;
        }
        for i in brgc_gen(n - 1) {
            co.yield_(i).await;
        }
        co.yield_(n - 1).await;
        for i in brgc_gen(n - 1) {
            co.yield_(i).await;
        }
    })
}
```

---

## `Cargo.toml`

```toml
[package]
name = "ecgen-rs"
version = "0.1.0"
edition = "2021"

[dependencies]
genawaiter = { version = "0.99.1", features = ["futures03"] }
```

---

## C++ code

```cpp
#include <cppcoro/coroutine.hpp>  // for cppcoro

namespace ecgen {
    using namespace cppcoro;

    /**
     * @brief Binary Reflexed Gray Code Generator
     */
    auto BRGC_gen(size_t n) -> recursive_generator<size_t> {
        if (n < 1) {
            co_return;
        }
        co_yield BRGC_gen(n - 1);
        co_yield n - 1;
        co_yield BRGC_gen(n - 1);
    }
}  // namespace ecgen
```

---

## `xmake.lua`

```lua
set_languages("c++20")

add_rules("mode.debug", "mode.release", "mode.coverage")
add_requires("conan::fmt/8.1.1", {alias = "fmt"})
add_requires("conan::doctest/2.4.5", {alias = "doctest"})
add_requires("conan::andreasbuhr-cppcoro/cci.20210113", {alias = "cppcoro"})

target("ecgen")
    set_kind("static")
    add_includedirs("include", {public = true})
    add_files("src/*.cpp")
    add_packages("cppcoro")

target("test")
    set_kind("binary")
    add_deps("ecgen")
    add_includedirs("include", {public = true})
    add_files("tests/*.cpp")
    add_packages("fmt", "doctest", "cppcoro")
```
