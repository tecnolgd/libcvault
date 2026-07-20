
#ifndef HEAD_HPP
#define HEAD_HPP

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include <algorithm> 

//file structure to store file name and its size(in bytes)
struct fileStructure {
  std::string name;
  long long byte_size;
};

extern "C"{

  // Core Data Management
  int populate_data(const char* path = ".");
  fileStructure reportData();
      
  // Analysis and Manipulation
  long long int sortFileOnByte(bool flag); // Note: Should probably return void, or the max byte size.
  long long int  minMax();
  void sortFileOnName(); //for file search operation
  long long int searchfile(const char* fname);
    
  // Utility
  long int lineCount(const char* filepath);
}
#endif
