
---

## Python code

```python
def aberth(pa: List, zs: List, options: Options = Options()):
    M = len(zs)
    N = len(pa) - 1
    for niter in range(options.max_iter):
        tol = 0
        for i in filter(lambda i: converged[i] is False, range(M)):  # exclude converged
            pb = pa.copy()
            P = horner_eval(pb, N, zs[i])
            tol_i = abs(P)
            if tol_i < options.tol_ind:
                converged[i] = True
                continue
            P1 = horner_eval(pb, N - 1, zs[i])
            tol = max(tol_i, tol)
            for j in filter(lambda j: j != i, range(M)):  # exclude i
                P1 -= P / (zs[i] - zs[j])
            zs[i] -= P / P1
        if tol < options.tol:
            return zs, niter, True
    return zs, option.max_iter, False
```

---

## Rust code

```rust
pub fn aberth_th(pa: &[f64], zs: &mut Vec<Complex<f64>>, options: &Options) -> (usize, bool) {
    use std::sync::mpsc::channel;
    use std::sync::Arc;
    use threadpool::ThreadPool;

    let n_workers = 4; // assume 4 cores

    let m = zs.len();
    let n = pa.len() - 1; // degree, assume even
    let mut pb = vec![0.0; n];
    let n = pa.len() - 1; // degree, assume even
    for k in 0..n {
        pb[k] = pa[k] * (n - k) as f64;
    }
    let pb = pb; // make imutatable
                 // let mut zsc = zs.clone();
    let pa_share = Arc::new(pa.to_owned());
    let pb_share = Arc::new(pb);
    // let zs_share = Arc::new(Mutex::new(&zs));

    let mut found = false;
    let mut converged = vec![false; m];

    let mut niter: usize = 0;
    while niter < options.max_iter {
        niter += 1;

        let mut tol = 0.0;
        let (tx, rx) = channel();
        let pool = ThreadPool::new(n_workers);
        let mut n_jobs = 0;

        for i in 0..m {
            if converged[i] {
                continue;
            }
            let tx = tx.clone();
            let zsc = zs.clone();
            // let pac = pa.clone();
            // let zi = Complex::<f64>::default();
            let pa_clone = Arc::clone(&pa_share);
            let pb_clone = Arc::clone(&pb_share);
            // let zs_clone = Arc::clone(&zs_share);

            n_jobs += 1;
            pool.execute(move || {
                let zi = zsc[i];
                let pp = horner_eval_c(&pa_clone, &zi);
                let tol_i = pp.l1_norm(); // ???
                if tol_i < 1e-15 {
                    tx.send((None, i))
                        .expect("channel will be there waiting for a pool");
                } else {
                    let mut pp1 = horner_eval_c(&pb_clone, &zi);
                    for (j, zj) in zsc.iter().enumerate() {
                        // exclude i
                        if j == i {
                            continue;
                        }
                        pp1 -= pp / (zi - zj);
                    }
                    let dt = pp / pp1; // Gauss-Seidel fashion
                    tx.send((Some((tol_i, dt)), i))
                        .expect("channel will be there waiting for a pool");
                }
            });
        }
        // let mut zsw = zs_share.lock().unwrap();
        for (res, i) in rx.iter().take(n_jobs) {
            if let Some(result) = res {
                let (toli, dt) = result;
                if tol < toli {
                    tol = toli;
                }
                zs[i] -= dt;
            } else {
                converged[i] = true;
            }
        }
        if tol < options.tol {
            found = true;
            break;
        }
    }
    (niter, found)
}
```

---

## `Cargo.toml`

```toml
[package]
name = "bairstow-rs"
version = "0.1.0"
edition = "2021"

[dependencies]
threadpool = { version = "1.8.1" }
num = { version = "0.4.0" }
num-traits = { version = "0.2.14" }
```

---

## C++ code

```cpp
auto aberth(const std::vector<double>& pa, std::vector<std::complex<double>>& zs,
            const Options& options = Options()) -> std::pair<unsigned int, bool> {
    const auto M = zs.size();
    const auto N = int(pa.size()) - 1;  // degree, assume even
    auto found = false;
    auto converged = std::vector<bool>(M, false);
    auto pb = std::vector<double>(N);
    for (auto i = 0; i < N; ++i) {
        pb[i] = (N - i) * pa[i];
    }
    auto niter = 1U;
    ThreadPool pool(std::thread::hardware_concurrency());

    for (; niter != options.max_iter; ++niter) {
        auto tol = 0.0;
        std::vector<std::future<double>> results;

        for (auto i = 0U; i != M; ++i) {
            if (converged[i]) {
                continue;
            }
            results.emplace_back(pool.enqueue([&, i]() {
                const auto& zi = zs[i];
                const auto P = horner_eval_g(pa, zi);
                const auto tol_i = std::abs(P);
                if (tol_i < 1e-15) {
                    converged[i] = true;
                    return tol_i;
                }
                auto P1 = horner_eval_g(pb, zi);
                for (auto j = 0U; j != M; ++j) {  // exclude i
                    if (j == i) {
                        continue;
                    }
                    const auto zj = zs[j];  // make a copy, don't reference!
                    P1 -= P / (zi - zj);
                }
                zs[i] -= P / P1;  // Gauss-Seidel fashion
                return tol_i;
            }));
        }
        for (auto&& result : results) {
            auto&& res = result.get();
            if (tol < res) {
                tol = res;
            }
        }
        if (tol < options.tol) {
            found = true;
            break;
        }
    }
    return {niter, found};
}
```

---

## `xmake.lua`

```lua
target("bairstow")
    set_kind("static")
    add_includedirs("include", {public = true})
    add_files("src/*.cpp")
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
    add_packages("ms-gsl")
```
