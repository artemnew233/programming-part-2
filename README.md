# Lab 04 — MovieTicket Class with Unit Tests (Variant 12)

## Build & Run
```bash
cmake -S . -B build
cmake --build build
./build/lab04_app
ctest --test-dir build --output-on-failure
```

## Structure
```
lab04/
├── CMakeLists.txt
├── include/
│   └── MovieTicket.hpp
├── src/
│   ├── MovieTicket.cpp
│   └── main.cpp
├── tests/
│   └── test_movieticket.cpp
└── uml/
    └── MovieTicket.puml
```
