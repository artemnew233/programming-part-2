# Laboratory Work No. 1 — C++ Projects. CMake

**Course:** Programming (Part 2). C++  
**Student:** Смелянцев Артем    
**Group:** KN-925е  
**Branch:** `lab01`

---

## Topic

Managing the build process of C++ projects and dependencies using CMake, GoogleTest, a modular structure, and vcpkg.

## Objective

To acquire practical skills in creating C++ projects, configuring the build process, connecting custom libraries, organizing a modular structure, integrating tests, and adding external dependencies.

## Duration

90 minutes.

## Expected Results

After completing the lab work, the student should be able to:
1. Create a simple C++ project based on CMake.
2. Manage the C++ standard, build parameters, and project structure.
3. Connect custom libraries through `target_link_libraries()`.
4. Add a modular structure through multiple `CMakeLists.txt` files.
5. Connect GoogleTest through `FetchContent`.
6. Use vcpkg to connect an external library.

---

## 1. Brief Theoretical Background

### Why `make` Alone Is Often Not Enough

`make` is effective for small single-platform projects, but in larger C++ projects it requires maintaining source lists, compiler flags, and dependency paths manually across every rule. It also has no native model for transitive dependencies or include path propagation between targets.

### Purpose of CMake

CMake is a build system generator that:
- describes the project structure declaratively in `CMakeLists.txt`;
- generates build files for any target generator (Ninja, Make, Visual Studio, etc.);
- manages targets and their dependencies with `PRIVATE` / `PUBLIC` / `INTERFACE` visibility modifiers;
- integrates with CTest, CPack, and dependency managers such as vcpkg.

### General CMake Workflow

```bash
cmake -S . -B build    # configure (out-of-source)
cmake --build build    # build ig
```

### Tools Used

| Tool | Purpose |
|------|---------|
| CMake 3.20+ | Build system configuration and generation |
| GCC / Clang / MSVC | C++20 compiler |
| GoogleTest v1.17.0 (via `FetchContent`) | Unit testing framework |
| CTest | Test runner bundled with CMake |
| vcpkg | External C++ package manager |
| fmt | External text-formatting library, connected via vcpkg |

---

## 2. Individual Assignment — Variant 12: Class Schedule

The task was to implement a small library for managing a daily class schedule stored as a `std::vector<std::string>`.

| Function | Behaviour |
|----------|-----------|
| `addClass(schedule, name)` | Appends the subject; ignores empty strings |
| `removeClass(schedule, name)` | Removes the first occurrence; returns `false` if absent |
| `countPeriods(schedule)` | Returns the current number of periods |
| `hasClass(schedule, name)` | Returns `true` if the subject exists |
| `getClassAt(schedule, index)` | Returns subject at `index`; returns `""` on out-of-bounds |

---

## 3. Project Directory Structure

```
lab01_v12/
├── CMakeLists.txt          ← root: FetchContent, vcpkg, subdirectories
├── vcpkg.json              ← declares the fmt dependency
├── lib/
│   ├── CMakeLists.txt      ← builds the schedule static library
│   ├── include/
│   │   └── schedule.hpp
│   └── src/
│       └── schedule.cpp
├── app/
│   ├── CMakeLists.txt      ← builds the executable, links schedule + fmt
│   └── main.cpp
└── tests/
    ├── CMakeLists.txt      ← builds the test executable, links schedule + GTest
    └── test_schedule.cpp
```

---

## 4. Implementation

### Root `CMakeLists.txt`

```cmake
cmake_minimum_required(VERSION 3.20)
project(lab01 LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0
)
FetchContent_MakeAvailable(googletest)

enable_testing()

find_package(fmt CONFIG REQUIRED)

add_subdirectory(lib)
add_subdirectory(app)
add_subdirectory(tests)
```

---

### Library — `lib/`

**`lib/CMakeLists.txt`:**

```cmake
add_library(schedule src/schedule.cpp)
target_include_directories(schedule PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(schedule PUBLIC cxx_std_20)
```

**`lib/include/schedule.hpp`:**

```cpp
#pragma once
#include <string>
#include <vector>

void        addClass(std::vector<std::string>& schedule, const std::string& name);
bool        removeClass(std::vector<std::string>& schedule, const std::string& name);
int         countPeriods(const std::vector<std::string>& schedule);
bool        hasClass(const std::vector<std::string>& schedule, const std::string& name);
std::string getClassAt(const std::vector<std::string>& schedule, int index);
```

**`lib/src/schedule.cpp`:**

```cpp
#include "schedule.hpp"
#include <algorithm>

void addClass(std::vector<std::string>& schedule, const std::string& name) {
    if (!name.empty())
        schedule.push_back(name);
}

bool removeClass(std::vector<std::string>& schedule, const std::string& name) {
    auto it = std::find(schedule.begin(), schedule.end(), name);
    if (it == schedule.end())
        return false;
    schedule.erase(it);
    return true;
}

int countPeriods(const std::vector<std::string>& schedule) {
    return static_cast<int>(schedule.size());
}

bool hasClass(const std::vector<std::string>& schedule, const std::string& name) {
    return std::find(schedule.begin(), schedule.end(), name) != schedule.end();
}

std::string getClassAt(const std::vector<std::string>& schedule, int index) {
    if (index < 0 || index >= static_cast<int>(schedule.size()))
        return "";
    return schedule[index];
}
```

---

### Application — `app/`

**`app/CMakeLists.txt`:**

```cmake
add_executable(app main.cpp)
target_link_libraries(app PRIVATE schedule fmt::fmt)
target_compile_features(app PRIVATE cxx_std_20)
```

**`app/main.cpp`:**

```cpp
#include <fmt/core.h>
#include <vector>
#include <string>
#include "schedule.hpp"

int main() {
    std::vector<std::string> monday;

    addClass(monday, "Math");
    addClass(monday, "Physics");
    addClass(monday, "C++ Programming");
    addClass(monday, "English");
    addClass(monday, "History");

    fmt::print("Class Schedule — Monday\n");
    fmt::print("-----------------------\n");
    fmt::print("Total periods: {}\n\n", countPeriods(monday));

    for (int i = 0; i < countPeriods(monday); ++i)
        fmt::print("Period {}: {}\n", i + 1, getClassAt(monday, i));

    fmt::print("\nHas 'Physics': {}\n", hasClass(monday, "Physics") ? "yes" : "no");
    fmt::print("Has 'Biology': {}\n",  hasClass(monday, "Biology")  ? "yes" : "no");

    removeClass(monday, "History");
    fmt::print("\nAfter removing 'History':\n");
    fmt::print("Total periods: {}\n", countPeriods(monday));

    for (int i = 0; i < countPeriods(monday); ++i)
        fmt::print("Period {}: {}\n", i + 1, getClassAt(monday, i));

    return 0;
}
```

---

### Tests — `tests/`

**`tests/CMakeLists.txt`:**

```cmake
add_executable(schedule_tests test_schedule.cpp)
target_link_libraries(schedule_tests PRIVATE schedule GTest::gtest_main)
target_compile_features(schedule_tests PRIVATE cxx_std_20)
include(GoogleTest)
gtest_discover_tests(schedule_tests)
```

**`tests/test_schedule.cpp`** (9 tests covering all functions):

```cpp
#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "schedule.hpp"

TEST(ScheduleTest, AddClassIncreasesCount) {
    std::vector<std::string> s;
    addClass(s, "Math");
    addClass(s, "Physics");
    EXPECT_EQ(countPeriods(s), 2);
}

TEST(ScheduleTest, EmptyNameIgnored) {
    std::vector<std::string> s;
    addClass(s, "");
    EXPECT_EQ(countPeriods(s), 0);
}

TEST(ScheduleTest, RemoveClassDecreasesCount) {
    std::vector<std::string> s;
    addClass(s, "Math");
    addClass(s, "Physics");
    EXPECT_TRUE(removeClass(s, "Math"));
    EXPECT_EQ(countPeriods(s), 1);
}

TEST(ScheduleTest, RemoveNonExistentReturnsFalse) {
    std::vector<std::string> s;
    addClass(s, "Math");
    EXPECT_FALSE(removeClass(s, "Biology"));
    EXPECT_EQ(countPeriods(s), 1);
}

TEST(ScheduleTest, HasClassFindsExisting) {
    std::vector<std::string> s;
    addClass(s, "C++ Programming");
    EXPECT_TRUE(hasClass(s, "C++ Programming"));
}

TEST(ScheduleTest, HasClassReturnsFalseForMissing) {
    std::vector<std::string> s;
    addClass(s, "Math");
    EXPECT_FALSE(hasClass(s, "Biology"));
}

TEST(ScheduleTest, GetClassAtReturnsCorrectName) {
    std::vector<std::string> s;
    addClass(s, "Math");
    addClass(s, "Physics");
    EXPECT_EQ(getClassAt(s, 0), "Math");
    EXPECT_EQ(getClassAt(s, 1), "Physics");
}

TEST(ScheduleTest, GetClassAtOutOfBoundsReturnsEmpty) {
    std::vector<std::string> s;
    addClass(s, "Math");
    EXPECT_EQ(getClassAt(s, 5),  "");
    EXPECT_EQ(getClassAt(s, -1), "");
}

TEST(ScheduleTest, CountPeriodsOnEmptyIsZero) {
    std::vector<std::string> s;
    EXPECT_EQ(countPeriods(s), 0);
}
```

---

### vcpkg Configuration

**`vcpkg.json`:**

```json
{
  "name": "lab01",
  "version-string": "0.1.0",
  "dependencies": [
    "fmt"
  ]
}
```

The `fmt` library provides `fmt::print` as a modern, type-safe alternative to `printf`. It is declared as a dependency in `vcpkg.json`, found by CMake with `find_package(fmt CONFIG REQUIRED)`, and linked to the app target via `fmt::fmt`.

---

## 5. Build and Run Commands

```bash
# Configure (provide vcpkg toolchain)
cmake -S . -B build \
  -DCMAKE_TOOLCHAIN_FILE=/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake

# Build all targets
cmake --build build

# Run the application
./build/app

# Run tests
ctest --test-dir build --output-on-failure
```

<!-- Insert screenshots here:
1. Project directory structure
2. Root CMakeLists.txt open in editor/terminal
3. cmake -S . -B build configuration output
4. cmake --build build output
5. ./build/app program run
6. ctest output — all 9 tests passed
7. vcpkg install or vcpkg.json in editor
8. GitHub repository page (lab01 branch)
-->

---

## 6. Conclusions

In this laboratory work the following was completed:

- A modular C++ project was organized using CMake with three separate `CMakeLists.txt` files for the library, the application, and the tests.
- The `schedule` library was built as a static library target and linked to both `app` and `schedule_tests` using `target_link_libraries()` with `PRIVATE` visibility.
- The `PUBLIC` keyword in `target_include_directories` on the library automatically propagated the `include/` path to all consumer targets, eliminating manual path duplication.
- GoogleTest was integrated without any manual installation using `FetchContent_Declare` and `FetchContent_MakeAvailable`.
- Nine unit tests were written covering normal behavior, empty-input guarding, and out-of-bounds access.
- The external `fmt` library was added via a `vcpkg.json` manifest and connected with `find_package(fmt CONFIG REQUIRED)`.
- The main difficulty was correctly setting up the vcpkg toolchain path during CMake configuration.

---

## 7. GitHub Repository

Repository: `https://github.com/Bezrukiy/programming-part-2`  
Branch: `lab01`  
Pull request: <!-- link -->
