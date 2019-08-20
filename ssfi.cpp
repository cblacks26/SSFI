#include <iostream>
#include <boost/filesystem.hpp>
#include "threadpool.h"

using std::cout;
using std::endl;
using std::cerr;
using std::string;
using std::ifstream;

boost::filesystem::path txt(".txt");

// if file is a textfile submit a new task for completion
void isTextFile(std::shared_ptr<threadpool> pool, 
    std::shared_ptr<stats> programStats, const string& p){
    boost::filesystem::path pat(p);
    boost::filesystem::path ext = pat.extension();

    if(txt.compare(ext)==0){
        pool->addTask(programStats,p);
    };
}
// recursive search through directory for files
void searchDirectory(std::shared_ptr<threadpool> pool, 
    std::shared_ptr<stats> programStats, string& path){
    if(boost::filesystem::exists(path)){
        if (boost::filesystem::is_regular_file(path)) {
            isTextFile(pool,programStats,path);
        }else if (boost::filesystem::is_directory(path)) {
            for(auto &entry : boost::filesystem::directory_iterator(path)){
                string s = entry.path().string();
                searchDirectory(pool, programStats, s);
            }
        }else
            cout << path << " exists, but is not a regular file or directory" << endl;
    }
}

int main(int argc, char* args[]){
    int N = 4;
    string pathString;
    boost::filesystem::path p;
    // check for correct number of arguments
    if( argc < 2 || argc % 2 !=0 ){
        cerr << "Invalid number of arguments" << endl;
        cerr << "Must include path to file or directory" << endl;
        cerr << "./ssfi path/to/directory-or-file -t 3" << endl;
        return -1;
    }
    // search for options and arguments
    for(int i = 1; i < argc; i++){
        string arg = string(args[i]);
        // Check if there is an option included
        if(arg[0]=='-'){
            if(arg[1]=='t'){
                try{
                    if(i+1<argc){
                        N = std::stoi(string(args[i+1]));
                        i++;
                        cout << "Using " << N << " Worker Threads" << endl;
                    }
                }catch(std::invalid_argument& e){
                    cerr << "Unable to parse Number of threads" << endl;
                }
            }
        }else{
            pathString = string(args[i]);
            p = boost::filesystem::path(args[i]);
        }
    }
    std::shared_ptr<threadpool> pool(new threadpool(N));
    std::shared_ptr<stats> programStats(new stats);
    // Begin searching directory
    boost::thread threadSearch{boost::bind(&searchDirectory, pool, programStats, pathString)};
    threadSearch.join();
    // Wait for worker threads to finish execution 
    pool->closePool();
    // print the statistics
    programStats->printStats();
    return 0;
}