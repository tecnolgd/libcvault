## Contributing to libcvault

Thank you for your interest in contributing to libcvault!

Whether you’re fixing a bug, adding a new API, or optimizing data structures used, your help is welcome.

### Development Setup

To set up your local development environment and build the project, please follow the Installation Instructions in the [README.md](README.md#build-instructions).

> [!NOTE]     
> - Ensure you have a C++17 compiler, `cmake`, and a build tool such as `make` installed.*
> - [GoogleTest](https://github.com/google/googletest) is used for the automated test suite. The CMake configuration ([CMakeLists.txt](/home/chief/projects/libcvault/CMakeLists.txt)) first looks for a system-installed GoogleTest; if none is found, it automatically fetches and builds GoogleTest (v1.14.0) in the local build directory via CMake `FetchContent` on the first configure, so a system-wide GoogleTest installation is not required.

### Development Workflow

- **Code Style:** Keep it clean and readable. Use standard C++17 practices.

- **Performance:** libcvault’s core goal is low overhead. Any new feature should have a minimal footprint on system resources.

- **Testing:** If you add a new API or change behavior, add or update tests so the change is covered. New tests should be modular and must not break existing coverage.

### Building and Testing

The project uses a single root [CMake](https://cmake.org/) configuration and a root [Makefile](/home/chief/projects/libcvault/Makefile) for building the library and running the [GoogleTest](https://github.com/google/googletest)-based test suite in [`tests/`](tests/).

#### Structure

- `CMakeLists.txt` — top-level build configuration (library target, test target, and GoogleTest discovery/fetch).
- `Makefile` — convenience targets that configure/build/test via CMake (`make test`).
- `tests/test_*.cpp` — test files grouped by API/behavior (for example, `test_populate_data.cpp`, `test_sorting.cpp`, `test_search.cpp`, `test_line_count.cpp`, `test_accessors.cpp`).
- `tests/test_helpers.hpp` — shared helpers for creating temporary directories/files and other fixtures.

#### Configure, build, and run

From the repository root, the simplest workflow is:

```bash
make test
```

This configures the project in `build/` (fetching/building GoogleTest locally on first run if needed), builds the library and tests, and runs the full suite via CTest.

Other useful commands:

```bash
make            # configure and build
make clean      # remove the local build directory
cmake --build build --target libcvault_tests   # build only the test executable
ctest --test-dir build --output-on-failure  # run tests after a build
./build/libcvault_tests --gtest_filter=PopulateData.*  # run specific tests
./build/libcvault_tests --gtest_list_tests            # list available tests
```

You can also drive CMake directly:

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

#### Adding new tests

1. Create a new file such as `tests/test_<feature>.cpp`, or add cases to an existing `tests/test_*.cpp` file if they belong to the same API area.
2. Include the headers you need:

   ```cpp
   #include <gtest/gtest.h>

   #include "head.hpp"
   #include "test_helpers.hpp"
   ```

3. Write tests with standard GoogleTest macros, for example:

   ```cpp
   TEST(MyFeature, DescriptiveCaseName) {
       libcvault_test::TempDir tmp;
       libcvault_test::write_bytes_file(tmp.path / "example.bin", 4);

       ASSERT_EQ(populateData(tmp.path.string().c_str()), 0);
       EXPECT_EQ(getFileCount(), 1);
   }
   ```

4. Run `make test` (or rebuild via CMake). The CMake configuration discovers `tests/test_*.cpp` automatically, so adding a new test file usually only requires rebuilding (reconfigure if your generator does not pick up the new file automatically).
5. Keep tests isolated and deterministic: use temporary fixtures/helpers instead of depending on repository contents or shared mutable state.


## The Required Contribution Workflow

To keep the codebase stable and ensure your time isn't wasted, all contributors **must** follow this exact workflow. Pull Requests that skip these steps will be closed without code review.

### 1. Find or Open an Issue First

* Do not write code or open a Pull Request out of nowhere. 
* Look at our [Open Issues](https://github.com/tecnolgd/libcvault/issues) tab. If you find a bug or a feature you want to tackle, comment on that specific issue stating your intent to fix it.
* If you have a new idea, open a new issue first to discuss the architectural impact with the maintainers.

### 2. Wait to be Officially Assigned

* **Do not start working until a maintainer officially assigns the issue to you.**
* We will not accept PRs from unassigned contributors(Such PRs would be closed automatically). This prevents multiple people from accidentally working on the exact same file at the same time.

### 3. One Branch, One Pull Request

* When you are ready to submit, use standard keywords in your PR description to link your work (e.g., `Closes #30` or `Fixes #30`).
* **Do not open duplicate Pull Requests.** If you need to fix your code, update your existing branch and push the new commits to your fork. The original Pull Request thread will update automatically.

### 4. Code and Communication Standards

* **Language:** All source code, terminal logs, pull request descriptions, and in-line code comments **must be written in English**. 
* Keep pull request descriptions clean, formatted, and focused entirely on the issue layout.


### Current Priorities

Looking for a place to start?
Check     
- [Open Issues](https://github.com/tecnolgd/libcvault/issues) to find bugs and features you can contribute to
