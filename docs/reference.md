# Code Vault Documentation

**A CLI-based static file analyzer for codebase analysis.** Made from **pure C++** with object-oriented methodology. Easy to use and blazing fast response.

---

## 1. Project Overview
The project supports two main operational modes:
* **Interactive Mode:** For continuous exploration and analysis.
* **Command Line Mode (CLI):** For quick, one-off commands and scripting.

---

## 2. Installation & Setup

### 2.1 Prerequisites
* **Compiler:** GCC MinGW (x32/64) ver 14.2.0 (Recommended)
* **Terminal:** CMD (Windows)
* **Libraries:** No external dependencies required (clone and run the damn code 💀)
* **Runtime Environment:** Windows 11 and above (Recommended)

### 2.2 Compilation / Build
Use the following commands to build the executable:

**Makefile Build (Recommended):**
```bash
mingw32-make
```
**Manual Build:**
```bash
g++ main.cpp cmd.cpp -o cvault
```
**Running the Application:**
- **Windows:** <code>cvault.exe</code> or simply <code>cvault</code>
- **Linux/macOS:** <code>./cvault</code>

## 3. Feature Reference (Command-line Mode)

### 3.1 <code>cvault populate <path></code>
    Used to scan a directory for files. If the path is not specified, it scans the current working directory.
    ```bash
    cvault populate .
    ```
### 3.2 <code>cvault report <path></code>
    Displays all files in the scanned directory. Defaults to the current directory unless specified otherwise.
    ```bash
    cvault report .
    ```
### 3.3 <code>cvault fsearch <filename></code>
    Searches for a specific file in the populated directory based on the name.
    *Note:* This functionality does not work for executables or object files.
    ```bash
    cvault fsearch filename
    ```
### 3.4 <code> cvault fsortbyte <path></code>
    Sorts files (including executables and object files) in increasing order based on the file size (number of bytes).
    ```bash
    cvault fsortbyte .
    ```

## 4.Interactive Mode Commands
    When launched without arguments, Code Vault enters an interactive shell. Available commands include:

    | Command | Description |
    |---|---|
    | populate | Populate / scan the directory |
    | report | Display the scanned directory report |
    | fsortbyte | Sort files based on file size |
    | fsearch | Search for a specific file in the directory |
    | fmaxbyte | Find the largest file in the directory |
    | creds | Display credits and documentation links |
    | help | Display commands and their meanings |
    | exit / quit | Exit the application |

### Links & Support     
- GitHub Repository: tecnolgd/Code-Vault
- Report Issues: Open an Issue

© 2026 Code Vault Documentation