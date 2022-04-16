layout: true
class: typo, typo-selection

---

count: false
class: nord-dark, center, middle

# Lecture 3a: Build System

---

## Cargo (Rust 🦀)

```bash
$ cargo new/init
$ cargo build 
$ cargo check     # check without build
$ cargo run       # run
$ cargo test      # run unit test
$ cargo fmt       # formatting
$ cargo clippy    # static analysis
$ cargo doc
$ cargo install --path .
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

## xmake (C++)

```bash
$ xmake create -l c++ -t static foo  # create a c++ project foo
$ xmake f -m release     # configure the project w/ release mode
$ xmake                  # compile
$ xmake run console      # run the target console
$ xmake clean
$ xmake project -k cmakelists
```

---

## xrepo (C++)

```bash
$ xrepo search fmt
$ xrepo install fmt
$ xrepo scan
```
---

## `xmake.lua`

```lua
add_rules("mode.debug", "mode.release", "mode.coverage")
add_requires("fmt", {alias = "fmt"})
add_requires("conan::doctest/2.4.8", {alias = "doctest"})

target("foo")
    set_kind("static")
    add_includedirs("include", {public = true})
    add_files("src/*.cpp")

target("test")
    set_kind("binary")
    add_deps("foo")
    add_includedirs("include", {public = true})
    add_files("tests/*.cpp")
    add_packages("fmt", "doctest")
```

---

## Add multi-threading support

```lua
target("foo")
    if is_plat("linux") then
        -- add system link libraries
        add_syslinks("pthread")
        -- add compilation and link flags
        add_ldflags("-lpthread", {force = true})
    elseif is_plat("windows") then
        if is_mode("release") then
            add_cxflags("-MT")
        elseif is_mode("debug") then
            add_cxflags("-MTd")
        end
        add_ldflags("-nodefaultlib:msvcrt.lib")
    end
```

---

## trunk.io

```bash
$ trunk init
$ trunk fmt
$ trunk check
```

---

class: nord-dark, center, middle

# Q & A 🗣️
