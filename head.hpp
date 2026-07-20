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
  fileStructure reportData();
    
    // Analysis and Manipulation
    long long sortFileOnByte(); // Note: Should probably return void, or the max byte size.
    long long int  minMax();
    void sortFileOnName();
    long long int searchfile(const std::string& fname);
    //void searchfile(); // Interactive wrapper
    
    // Utility
    long int lineCount(const std::string& filepath);
    //void lineCount(); // Interactive wrapper
};


void printBanner();

#endif // HEAD_HPP
