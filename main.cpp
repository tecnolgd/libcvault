// interactive mode logic ( menu based with ">>" arrows for each command )
//file contains all function definations

#include "head.hpp"
 
//analyzer class implementation
void analyzer::populate_data( const std::string& path) { 
    files.clear(); //clear any garbage data
    std::filesystem::path p(path);
    try {                                   // check for probable errors
        if (!std::filesystem::exists(p)) {
            std::cout << "Error: path '" << path << "' does not exist.\n";
            return;
        }
        if (!std::filesystem::is_directory(p)) {
            std::cout << "Error: path '" << path << "' is not a directory.\n";
            return;
        }
        std::cout << "Analyzing directory: " << path << "\n";
                
        for (const auto& entry : std::filesystem::directory_iterator(p)) { //for-each loop
            if (entry.is_regular_file()) {
                fileStructure file;
                file.name = entry.path().filename().string(); //needs explanation !!
                file.byte_size = std::filesystem::file_size(entry.path());
                files.push_back(file); //stack push operation
            }
        }
        std::cout << "Found " << files.size() << " files\n";
    } catch (const std::filesystem::filesystem_error& e) { //error detection and display
            std::cout << "Filesystem error: " << e.what() << "\n";
            return;
        }
}
           
fileStructure analyzer::reportData() { //report generation function
        if (files.empty()) { //checks if file is empty or not
            std::cout << "Vector is empty. Run 'populate' first.\n";
            return {};
        }                                                          std::cout << "\n--- CodeVault Directory Report (Summation) ---\n"; //report summary 
        long long totalSizeBytes = 0;
        
        //CORE DSA: Iterating over the entire vector (array).
        for (size_t i=0; i<files.size();i++) { //for loop
            
            totalSizeBytes += files[i].byte_size; //total bytes size
        }

        fileStructure result;
        std::string total_bytes = std::to_string(totalSizeBytes);
        result.name = total_bytes;
        result.byte_size = files.size();
        
        return result;
    }
    long long int analyzer::sortFileOnByte(bool flag){ //bubble sort algorithm
        
        if(files.empty()){
            return 0;
        }

        //function to sort files based on byte size
        for( size_t i=0;i<files.size()-1;i++){
             for(size_t j=0;j<files.size()-1-i;j++){

                if(files[j].byte_size>files[j+1].byte_size){ //to sort bytes
                long long t=files[j].byte_size;
                std::string s=files[j].name;

                files[j].byte_size=files[j+1].byte_size;
                files[j].name=files[j+1].name;

                files[j+1].byte_size=t;
                files[j+1].name=s;
                }
            }
        }
        if(flag){
            size_t size= files.size();
            return files[size-1].byte_size;//return the max bytes since the sort is ascending order
        }
        return 0;
    }
    
long long int analyzer::minMax(){
    // sortFileOnByte(false) sorts and returns the largest byte size
    long long max_size = sortFileOnByte(true); 
    if (max_size > 0) {
        
        return max_size;
        // Note: To show the name, you'd need to loop over the files vector 
        // and find the file matching the max_size, as the sorting only guarantees 
        // the size is at the end, not necessarily the name is still correct 
        // if there are files with the same size. For simplicity, we just output the size.
    }
    return -2;

    }
//sort file for search functionality
void analyzer::sortFileOnName() {
    for (size_t i = 0; i < files.size() - 1; i++) {
        for (size_t j = 0; j < files.size() - 1 - i; j++) {
            // Compare names alphabetically
            if (files[j].name > files[j+1].name) { 
                // Swap the entire fileStructure objects
                fileStructure temp = files[j];
                files[j] = files[j+1];
                files[j+1] = temp;
            }
        }
    }
}
  
long long int analyzer::searchfile(const std::string& fname){ //to search the file vector based on the file name.
        sortFileOnName(); //to sort the vector before binary search.
        int key; //key - for search condition verification
        size_t size = files.size();
        int low=0,high=size-1;
        int mid;
        
        while(low<=high){   //binary search algorithm
            mid=(low+high)/2;
            if(files[mid].name == fname){
                key=1;
                break;
            }
            else {
                if(files[mid].name<fname)
                    low=mid+1;
                else{
                    if(mid==0)
                        break;
                    high = mid-1;
                }
                
            }
        }
        if(key==1){
            return files[mid].byte_size;
            
        }
        else{
            return -5;
        }
    }
    
    
    long int analyzer::lineCount(const std::string& filepath){   //function to count lines of code in a desired file (any file in the system)
        std::ifstream file(filepath); //open file for reading
        if(! file.is_open()){ //to check whether the file exists
            std::cout<<"Error: Could not open file "<<filepath<<" !"<<std::endl;
            return -5;
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
        return -3;
    }

    
             
     //Future Expansion Point: This is where advanced features will go.


    
//Developer notes:
//Flow of the cli.runterminal(&a); ->  object a  address--> passed to runterminal()function as argument --> later derefenced to get data or value from it --> runterminal() is executed with cli i.e., ' cli.runterminal(&a) '
//Basically, class analyzer is the argument for function runterminal() which runs inside class cliManager.
