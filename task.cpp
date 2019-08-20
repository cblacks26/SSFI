#include <string>
#include <iostream>
#include <fstream>
#include "stats.h"

using std::string;
using std::ifstream;
using std::cerr;
using std::endl;
using std::cout;

// Expects a line string to be passed, can contain multiple words
void static evaluateString(std::shared_ptr<stats> fileStats, const string& str){
    if(str.length()==0) return;
    else if(str.length()==1){
        // add word if is alnum and return --- example( "A" )
        if(isalnum(str[0])) {
            fileStats->addWord(str);
        }
        return;
    } 
    // Has more than 1 character, must check if their are multiple words
    int startIndex = 0;
    for(unsigned int i = 1; i < str.length(); i++){
        if(i == str.length()-1){
            string word = str.substr(startIndex,i+1);
            fileStats->addWord(word);
        }
        // Found a word separator
        else if(!isalnum(str[i])){
            // get word and add to stats and shift startIndex
            string sub = str.substr(startIndex,i);
            fileStats->addWord(sub);
            startIndex = i+1;
        }
    }
}

void static readFile(std::shared_ptr<stats> programStats, const string& path){
    std::shared_ptr<stats> fileStats(new stats);
    ifstream ifstr(path);
    string str;
    // Readlines while available and call evaluateString to examine
	while(ifstr >> str){
        evaluateString(fileStats, str);
	}
    // Check if reading failed, otherwise add to final word count
	if(ifstr.fail()&&!ifstr.eof()){
        cerr << "Failure reading file" << endl;;
    }else{
        programStats->addStats(fileStats);
    }
}

/* this is a test to make sure task and stats works correctly
int main(int argc, char* args[]){
    if(argc < 2) return -1;
    std::shared_ptr<stats> programStats(new stats);
    string path(args[1]);
    readFile(programStats, path);
    readFile(programStats, path);
    programStats->printStats();
}*/