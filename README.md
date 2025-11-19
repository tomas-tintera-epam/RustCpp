# RustCpp

[![CI](https://github.com/tomas-tintera-epam/RustCpp/actions/workflows/ci.yml/badge.svg)](https://github.com/tomas-tintera-epam/RustCpp/actions)

Small C++ project with a C ABI wrapper and tests. The CI workflow builds the project and runs the C tests (including an external C consumer that links against `libtask_c.a`).

## Build & Test (local)

```bash
cmake -S . -B build -DBUILD_TESTING=ON
cmake --build build -j$(nproc)
ctest --test-dir build --output-on-failure
```

## C API

The public C API is defined in `task_c.h`. Link against the static library `libtask_c.a` and add `-lstdc++` when linking from C.
