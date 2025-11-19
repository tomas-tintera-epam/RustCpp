fn main() {
    // Tell cargo/rustc where to find the static library and to link it.
    // The library is produced in the top-level CMake build directory `build/`.
    println!("cargo:rustc-link-search=native={}", "../build");
    println!("cargo:rustc-link-lib=static=task_c");
    // Link the C++ standard library (task_c uses C++ internally)
    println!("cargo:rustc-link-lib=dylib=stdc++");
}
