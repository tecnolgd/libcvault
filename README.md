<h1 align = "center" style = "font-family: Roboto;">libcvault</h1>

<div align = "center">

<a href = "LICENSE.md"><img src = "https://img.shields.io/github/license/tecnolgd/libcvault?color=1a1a1a&style=flat-square" alt = "MIT License"></a>
<a href="https://ftp.gnu.org/gnu/gcc/"><img src="https://img.shields.io/badge/g++-13.3.0%2B-1a1a1a?style=flat-square" alt="g++ 13.3.0+"></a>
<a href="https://github.com/tecnolgd/libcvault/releases"><img src="https://img.shields.io/github/v/release/tecnolgd/libcvault?include_prereleases&color=1a1a1a&style=flat-square?" alt="Release"></a>

</div>

<p align = "center">libcvault is a C++ library for static file metadata analysis. It is intended to provide reusable functions for another C++ program(as of now) rather than operate as a standalone executable.
</p>
<hr>


<div align = "center">

  <a href = "#quick-run">Quick Run</a> •
  <a href = "./docs/reference.md#libcvault-library-reference"> Library Reference</a> •
  <a href = "#support-this-project"> Support this project</a>
  
</div>


> [!WARNING]
> libcvault is currently undergoing active refactor and API updates. Please make sure to use the v2.1.0-beta version for required applications.

## API Summary

- `populateData()` — scan a directory and load regular file metadata
- `getTotalBytes()` — compute the total byte size of loaded files
- `getFileCount()` — return the number of loaded files
- `sortFileOnByte()` — sort files by size
- `maxFile()` - return the largest file size 
- `sortFileOnName()`— sort files by name
- `searchFile()` - search by filename
- `lineCount()` — count lines in a text file
- `getFileName()` - returns the name of the file present at a given index
- `getFileSize()` - returns the size(bytes) of the file present at a given index
- `getFiles()` - returns a raw pointer to the internal memory buffer of the file list


## Quick Run

### Prerequisites

- C++17-compatible compiler
- Standard library support for `<filesystem>`


### Build Instructions

```bash
git clone https://github.com/tecnolgd/libcvault
```
```bash
cd libcvault
```

- **Manual Build**

Create the object file(`libcvault.o`)
```bash
g++ -std=c++17 -c main.cpp -o libcvault.o
```

Link with the source code(`my_app.cpp`)
```bash
g++ -std=c++17 my_app.cpp libcvault.o -o my_app
```

### Running the application

After building, run the application
```bash
./my_app
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

## Output

```txt
Files found: 233
Total bytes: 585441
Lines in head.hpp: 38
```

## Documentation
- [Library reference](docs/reference.md)

## Support This Project

If libcvault has positively impacted your workflow, consider:
- Starring this repository
- Forking the project
- Sharing feedback and suggestions
- [Contributing](CONTRIBUTING.md) to the codebase

## License
MIT
