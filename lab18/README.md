# Lab 18 — Delivery Route (Variant 12)

## Local build
```bash
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build
ctest --test-dir build --output-on-failure
```

## Sanitizer build
```bash
cmake -S . -B build-asan -G Ninja \
  -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_CXX_COMPILER=clang++ \
  -DENABLE_SANITIZERS=ON
cmake --build build-asan
ctest --test-dir build-asan --output-on-failure
```

## Format check
```bash
find include src tests -type f \( -name '*.hpp' -o -name '*.cpp' \) \
  -print0 | xargs -0 -r clang-format --dry-run --Werror
```

## Static analysis
```bash
cmake -S . -B build-tidy -G Ninja -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
find src tests -type f -name '*.cpp' \
  -print0 | xargs -0 -r clang-tidy -p build-tidy
```

## Documentation
```bash
doxygen Doxyfile
```
