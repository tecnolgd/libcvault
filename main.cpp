//function defination file

#include "head.hpp"
#include <cstddef>
#include <filesystem>
#include <algorithm> //for stl based algo usage
#include <unordered_map> //for hash map usage
 

std::vector<fileStructure> files;

std::unordered_map<std::string, long long int> fileMap; //to store file_name-byte_size map

extern "C"{

    int populateData( const char* path) { 
        files.clear(); //clear any garbage data
        fileMap.clear(); //clear stale search index
        std::filesystem::path p(path);

        try {                                   // check for probable errors
            if (!std::filesystem::exists(p)) {
                return -1;
            }
            if (!std::filesystem::is_directory(p)) {
                return -2;
             }
            
            auto options = std::filesystem::directory_options::skip_permission_denied; //skips protected folders to avoid crashes while scanning protected folders

            for (const auto& entry : std::filesystem::recursive_directory_iterator(p, options)) { //for-each loop
                if (entry.is_regular_file()) {
                    fileStructure file;
                    
                    file.name = std::filesystem::relative(entry.path(), p).string(); //saves relative or full path (e.g., "src/main.cpp") as the file name

                    file.byte_size = std::filesystem::file_size(entry.path());
                    files.push_back(file); //stack push operation
                
                    fileMap[file.name] = file.byte_size; //populate 'fileMap' hashmap
                }
            }
        }
        catch (const std::filesystem::filesystem_error& e) { //error detection and display
            return -3;
        }
        catch(...) { //for unknown errors
            return -4;
        }
        return 0;
    }

            
    long long int getTotalBytes() { //returns total bytes
        if (files.empty()) return 0;
        
        long long totalSizeBytes = 0;
        for (const auto& file : files) {
            totalSizeBytes += file.byte_size;
        }
        return totalSizeBytes;
    }

 
    int getFileCount() { //returns file count
        return static_cast<int>(files.size());
    }
    
    const char* getFileName(int index) { //returns file name 
        return files[index].name.c_str(); 
    }
    
    long long int getFileSize(int index) { //returns file size
        return files[index].byte_size; 
    }

    void sortFileOnByte(){ 

        if(files.empty()){
            return;
        }

        std::sort(files.begin(), files.end(), [](const fileStructure& a, const fileStructure& b){
            return a.byte_size <b.byte_size; //ascending order
        });
    }

        
    long long int maxFile(){

        if(files.empty()){
            return -1;
        }

        auto max_it = std::max_element(files.begin(), files.end(), [](const fileStructure& a, const fileStructure& b){
            return a.byte_size < b.byte_size; //'<' is default in cpp for comparisions
        });

        return max_it->byte_size; 
    }


    //sort file for search functionality
    void sortFileOnName() {
        if (files.size() < 2) {
             return;
        }
       
        std::sort(files.begin(), files.end(), [](const fileStructure& a, const fileStructure& b){
            return a.name < b.name;
        });
    }

    
    long long int searchFile(const char* fname){ //to search the files using hashmap 'fileMap'
        
        if(!fname){
            return -3;
        }

        auto it = fileMap.find(fname); 
        
        if(it != fileMap.end()){
            return it->second;
        }

        return -3;
    }
            
        
    long int lineCount(const char* filepath){   //function to count lines of code in a desired file (any file in the system)

        std::ifstream file(filepath); //open file for reading

        if(! file.is_open()){ //to check whether the file exists
            return -1;
        }

        long int flCount=0; //line counter
         std::string line; //string to store lines

         while(std::getline(file,line)){ //lines include tab spaces and goes until new line is encountered.
            flCount++; //increment the lCount when new line is encountered.
        }
        file.close();

        if (flCount > 0) { //to check whether file is empty and block any other possible errors.
            return flCount;
        }   
         return 0;
    }



    // returns pointer to the populated file list/array
    const fileStructure* getFiles(size_t* out_count){
        if(out_count){
            *out_count = files.size();
        }

        return files.empty() ? nullptr: files.data();
    }

}    
    //Future Expansion Point: This is where advanced features will go.
