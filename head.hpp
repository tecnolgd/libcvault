//head file 
#ifndef HEAD_HPP
#define HEAD_HPP

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include <algorithm> 

// 1. DATA STRUCTURES
struct fileStructure {
  std::string name;
  long long byte_size;
};

// -----------------------------------------------------------------
// 2. CLASS DECLARATIONS (Interface Only)
// -----------------------------------------------------------------

class analyzer {
  private:
    std::vector<fileStructure> files;

  public:
    // Core Data Management
    void populate_data(const std::string& path = ".");
    void reportData();
    
    // Analysis and Manipulation
    long long sortFileOnByte(bool x); // Note: Should probably return void, or the max byte size.
    void minMax();
    void sortFileOnName();
    void searchfile(const std::string& fname);
    void searchfile(); // Interactive wrapper
    
    // Utility
    void lineCount(const std::string& filepath);
    void lineCount(); // Interactive wrapper
};


class cliManager {
  public:
    /**
     * @brief Runs the continuous interactive loop.
     * @param a Reference to the analyzer object to execute commands on.
     */
    void runterminal(analyzer &a);
};

// -----------------------------------------------------------------
// 3. UTILITY FUNCTION DECLARATIONS
// -----------------------------------------------------------------

/**
 * @brief Prints the tool's main banner/header.
 */
void printBanner();

#endif // HEAD_HPP
