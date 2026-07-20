<h1 align = "center" style = "font-family: Roboto;">libcvault</h1>

<div align = "center">

<a href = "LICENSE.md"><img src = "https://img.shields.io/github/license/tecnolgd/libcvault?color=1a1a1a&style=flat-square" alt = "MIT License"></a>
<a href="https://ftp.gnu.org/gnu/gcc/"><img src="https://img.shields.io/badge/g++-13.3.0%2B-1a1a1a?style=flat-square" alt="g++ 13.3.0+"></a>
<a href="https://github.com/tecnolgd/libcvault/releases"><img src="https://img.shields.io/github/v/release/tecnolgd/libcvault?include_prereleases&color=1a1a1a&style=flat-square?" alt="Release"></a>
<a href = "#documentation"><img src = "https://img.shields.io/badge/Docs-Available-1a1a1a?style=flat-square" alt = "Docs: Available"></a>

</div>

> **libcvault** is a C++ library for static file metadata analysis. It is intended to provide reusable functions for another C++ program(as of now) rather than operate as a standalone executable.


## API Summary

- `populateData()` — scan a directory and load regular file metadata
- `getTotalBytes()` — compute the total byte size of loaded files
- `getFileCount()` — return the number of loaded files
- `sortFileOnByte()` / `minMax()` — sort files by size and retrieve the largest size
- `sortFileOnName()` / `searchfile()` — sort files by name and search by filename
- `lineCount()` — count lines in a text file

## Requirements

- C++17-compatible compiler
- Standard library support for `<filesystem>`

## Build Example

```bash
git clone https://github.com/tecnolgd/libcvault
cd libcvault
g++ -std=c++17 -c main.cpp -o libcvault.o
g++ -std=c++17 my_app.cpp libcvault.o -o my_app
```

## Example Usage

```cpp
#include "head.hpp"
#include <iostream>

int main() {
    if (populateData(".") != 0) {
        std::cerr << "Directory scan failed\n";
        return 1;
    }

    std::cout << "Files found: " << getFileCount() << "\n";
    std::cout << "Total bytes: " << getTotalBytes() << "\n";
    std::cout << "Lines in head.hpp: " << lineCount("head.hpp") << "\n";

    return 0;
}
```
## Documentation
- [Library reference](docs/reference.md)

## Author & License

- **Author:** tecnolgd   
- **License:** [MIT License](LICENSE.md)