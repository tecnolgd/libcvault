//working correctly ,error checks required for beta release . this file is the command line interface way i.e., using one command at a time.
#include "head.hpp" //to inculde main.cpp functionalities as class analyzer.

void printBanner() { //tool logo
    std::cout<<"\t              ####    ####"<<std::endl;
    std::cout<<"\t                ####    ####"<<std::endl;
    std::cout<<"\t                  ####    ####"<<std::endl;
    std::cout<<"\tCode Vault(beta)    ####    ####"<<std::endl;
    std::cout<<"\t                  ####    ####"<<std::endl;
    std::cout<<"\t                ####    ####"<<std::endl;
    std::cout<<"\t              ####    #### "<<std::endl;
}

int main(int argc, char* argv[]){ //to get the number of words used in the command entered to interpret the literal command given by the user.
    analyzer a; //object of class analyser
    cliManager cli; //object of class cliManager
    printBanner();
    
    if(argc<2){ //error check
        std::cout<<"\nStarting interactive mode ...\n";
        cli.runterminal(a); //passing address of class analyser object 'a' to function 'runterminal' 
        return 0;
    }
    std::string command = argv[1];
        
//Commands that take a directory/path as 2nd arg
    if (command == "populate" || command == "report" || command == "fsortbyte" || command == "fmaxbyte") {
        std::string path = (argc >= 3) ? argv[2] : ".";
        a.populate_data(path);
        std::cout<<"-----------------------\n";
        std::cout << "Executable argv[0]: " << (argc>0 ? argv[0] : "<none>") << "\n"; //executable used e.g., analyzer <command> / here "analyzer"= execuatble
        std::cout << "Current working directory: " << std::filesystem::current_path() << "\n";

        if (command == "report") {
            a.reportData();
        } else if (command == "fsortbyte") {
            a.sortFileOnByte(0);
        } else if (command == "maxbyte") {
            a.minMax();
        }
        return 0;
    }
// Commands that take a filename as 2nd arg (or prompt if missing)
    else if (command == "flcount") {
        if (argc >= 3) {
            a.lineCount(argv[2]);
        } else {
            // prompt interactive-style if no filename provided
            a.lineCount();
        }
        return 0;
    }
    else if (command == "fsearch") {
        a.populate_data("."); // load files from current dir
        if (argc >= 3) {
            a.searchfile(argv[2]);
        } else {
            a.searchfile(); // interactive prompt
        }
        return 0;
    }
    else if(command == "creds"){//credits and author details.
            printf("\n\tCredits :\nAuthor: tecnolgd\nDocumentation at https://c.com\n");
    }
    else if (command == "help") {//command reference
        std::cout << "\nAvailable commands:\n"
                  << "populate [path]       - Load files from directory\n"
                  << "report [path]         - Show analysis report\n"
                  << "fsortbyte [path]      - Sort files by size and display\n"
                  << "fmaxbyte [path]       - Show largest file\n"
                  << "fsearch [file name]   - Search for a file (or prompt)\n"
                  << "flcount [file name]   - Count lines in a file (or prompt)\n"
                  << "creds                 - Credits and documentation\n"
                  << "help                  - Show this help message\n";
        return 0;
    }
    else{
        std::cout << "Unknown command: " << command << "\nUse 'help' to see available commands\n";
        return 1;
    }
}  
