# libcvault Library Reference

## 1. Overview

This project is implemented as a C++ library rather than a standalone command-line application. It provides reusable functions that can be linked into another program.

The library includes:

- directory traversal with file metadata collection
- file count and total byte-size computation
- ascending sort by file size
- maximum file size lookup
- filename-based search
- line count for text files


## 2. Build and Integration

### 2.1 Requirements
- **Compiler:** A C++17-compatible compiler
- **Standard library:** Support for `<filesystem>`

### 2.2 Example build

- Compile the implementation file into an object file:
    ```bash
    g++ -std=c++17 -c main.cpp -o libcvault.o
    ```

- Then link it with your application source:
    ```bash
    g++ -std=c++17 my_app.cpp libcvault.o -o my_app
    ```
- To create a static library:
    ```bash
    ar rcs libcvault.a libcvault.o
    ```


## 3. API Reference

Include the header:
```cpp
#include "head.hpp"
```

- `int populateData(const char* path);`      
Loads file names and sizes from the given directory into the library's internal list.

    Return values:
    - `0` - success
    - `-1` - path does not exist
    - `-2` - path is not a directory
    - `-3` - filesystem error
    - `-4` - unknown error

- `long long int getTotalBytes();`     
Returns the total byte size of all files loaded by the last successful `populateData` call.

- `int getFileCount();`     
Returns the number of files currently loaded.

- `long long int sortFileOnByte(bool flag);`        
Sorts loaded files in ascending order by size.
If `flag` is `true`, returns the largest file size after sorting. If no files are loaded, returns `-1`.

- `long long int maxFile();`      
Returns the maximum loaded file size, or `-1` if no files are loaded.

- `void sortFileOnName();`      
Sorts the loaded file list alphabetically by file name.

- `long long int searchFile(const char* fname);`       
Searches the loaded file list by filename, returning the file size if found or `-3` if not found.

- `long int lineCount(const char* filepath);`      
Returns the number of lines in the specified file, or `-1` if the file cannot be opened.


## 4. Example Usage

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