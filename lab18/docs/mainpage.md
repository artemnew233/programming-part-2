# Lab 18 — Delivery Route (Variant 12)

## Summary
A C++ library that models an ordered delivery route as a sequence of waypoints.
Provides total route length, longest-segment detection, and empty-route checks.

## Public API
- `lab18::Point` — a named waypoint with x/y coordinates.
- `lab18::Route` — manages the waypoint list; computes geometry.

## Build
```bash
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build
ctest --test-dir build --output-on-failure
```
