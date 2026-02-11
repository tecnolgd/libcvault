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
           
void analyzer::reportData() { //report generation function
        if (files.empty()) { //checks if file is empty or not
            std::cout << "Vector is empty. Run 'populate' first.\n";
            return;
        }                                                          std::cout << "\n--- CodeVault Directory Report (Summation) ---\n"; //report summary 
        long long totalSizeBytes = 0;
        
        //CORE DSA: Iterating over the entire vector (array).
        for (size_t i=0; i<files.size();i++) { //for loop
            std::cout << " - File "<<i+1<<": " << files[i].name << " (" << files[i].byte_size << " bytes)\n";
            totalSizeBytes += files[i].byte_size; //total bytes size
        }
        std::cout << "\nTotal Files Stored: " << files.size() << "\n"; //size() function
        std::cout << "Total Codebase Size: " << totalSizeBytes << " bytes\n";
    }
    long long analyzer::sortFileOnByte(bool x){ //bubble sort algorithm
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

        if(x){ //this would work if x is 1 ,i.e when the sortbyte() function is called
            std::cout<<"Sorted files based on number of bytes(file-size) :\n";
            for(size_t i=0;i<files.size();i++){
                std::cout << " - File "<<i+1<<": "<< files[i].name << " (" << files[i].byte_size << " bytes)\n";
            }
        }
        else{
            size_t size= files.size();
            return files[size-1].byte_size;//return the max bytes since the sort is ascending order
        }
        return 0;
    }
    
void analyzer::minMax(){
    // sortFileOnByte(false) sorts and returns the largest byte size
    long long max_size = sortFileOnByte(0); 
    if (max_size > 0) {
        std::cout<<"Largest file size: "<<max_size << " bytes\n"; 
        // Note: To show the name, you'd need to loop over the files vector 
        // and find the file matching the max_size, as the sorting only guarantees 
        // the size is at the end, not necessarily the name is still correct 
        // if there are files with the same size. For simplicity, we just output the size.
    } else {
        std::cout << "No files to analyze for min/max.\n";
    }
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
  
void analyzer::searchfile(const std::string& fname){ //to search the file vector based on the file name.
        sortFileOnName(); //to sort the vector before binary search.
        //sortFileOnByte(0);
        size_t size=files.size();
        int key; //key - for search condition verification
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
            std::cout<<"File found: "<<files[mid].name<<" with "<<files[mid].byte_size<<" bytes"<<std::endl;
        }
        else{
            std::cout<<"File not found. Try with a correct name"<<std::endl;
        }
    }
    void analyzer::searchfile() { //interactive file search wrapper
        std::string fname;
        std::cout << "Enter name of the file to be searched :";
        std::cin >> fname;
        searchfile(fname);
    }
    
    void analyzer::lineCount(const std::string& filepath){   //function to count lines of code in a desired file (any file in the system)
        std::ifstream file(filepath); //open file for reading
        if(! file.is_open()){ //to check whether the file exists
            std::cout<<"Error: Could not open file "<<filepath<<" !"<<std::endl;
            return;
        }
        int flCount=0; //line counter
        std::string line; //string to store lines

        while(std::getline(file,line)){ //lines include tab spaces and goes until new line is encountered.
            flCount++; //increment the lCount when new line is encountered.
        }
        file.close();
        if (flCount > 0) { //to check whether file is empty and block any other possible errors.
            std::cout<<std::endl;
            std::cout << "Analysis Complete." << std::endl;
            std::cout << "File: " <<filepath<< std::endl;
            std::cout << "Total Lines of Code: " <<flCount<< std::endl;
        }   
        else {
            std::cout << "Could not complete analysis. Check the path and file permissions." << std::endl;
        }
    }

    void analyzer::lineCount() { //interactive file line count wrapper
        std::string filepath;
        std::cout << "Enter filename: ";
        std::cin >> filepath;
        lineCount(filepath);
    }
             
     //Future Expansion Point: This is where advanced features will go.


    //cliManager class implementation

    void cliManager::runterminal(analyzer &a){ //function to run the terminal as a whole 
    std::string command;
    std::cout << "\n\tWelcome to CodeVault Basics.\n";
    
    while (true) {
        std::cout << "\n>>>";
        std::cin >> command;
        std::cin.clear();
        if ((command == "exit")||(command=="quit")) {
            std::cout<<"Code Vault interactive-mode terminated."<<std::endl;
            break;
        } else if ((command =="populate") || (command=="report")) {
            a.populate_data();
            if(command=="report"){
                 a.reportData();
            }
        } else if(command =="fsortbyte"){
            a.sortFileOnByte(1);
        } else if(command == "fmaxbyte"){//display the max byte sized file.
            a.minMax();
        } else if(command == "fsearch"){//search for a file and display filename and location.
            a.searchfile();
        }else if(command == "flcount"){//count number of lines in any file in the system.
            a.lineCount();
        }else if(command == "creds"){//credits and author details.
            printf("\n\tCredits :\nAuthor: tecnolgd\nDocumentation at  https://tecnolgd.github.io/Code-Vault-doc\n");
        }else if (command == "help") {//help option 
            std::cout << "\n\t-- Available commands --\n populate  - reading /fetching file names and byte size\n fsortbyte - display the files sorted based on byte size\n report    - summarize key findings regarding file data\n fsearch   - to sreach for a file based on its name\n fmaxbyte  - gives the max byte file\n exit/quit - terminate from the application\n flcount   - display number of lines of code in a desired file\n creds     - tool credits and doc details\n";
        } else {
            std::cout << "Unknown command. Try using 'help'\n";
        }
    }
}
//Developer notes:
//Flow of the cli.runterminal(&a); ->  object a  address--> passed to runterminal()function as argument --> later derefenced to get data or value from it --> runterminal() is executed with cli i.e., ' cli.runterminal(&a) '
//Basically, class analyzer is the argument for function runterminal() which runs inside class cliManager.
