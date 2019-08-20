#include "stats.h"

void stats::addWord(const string& word){
    
    // Search if word has already been found
    unordered_map<string, int>::iterator it = words.find(word);
    if(it==words.end()){
        // Word hasn't been found, create new word counter pair
        std::pair<std::string,int> pair (word,1);
        words.insert(pair);
    }else{
        // Word already found, increment counter
        it->second++;
    }
}

void stats::addStats(std::shared_ptr<stats> stat){
    // Lock stat object to ensure it isn't changed during execution
    stat->lockStats();
    // Copy over stats from passed stat object
    for ( auto it = stat->words.begin(); it != stat->words.end(); ++it ){
        auto wordsIt = words.find(it->first);
        if(wordsIt==words.end()){
			words.insert({it->first,it->second});
		}else{
			wordsIt->second = it->second + wordsIt->second;
		}
    }
    // Unlock object
    stat->unlockStats();
}

void stats::printStats(){
    std::set<std::pair<int,string>> sortedWords;
    for(auto it = words.begin(); it!=words.end(); ++it){
        sortedWords.insert({it->second,it->first});
    }
    unsigned int count = 0;
    // Print out the top 10 words
    for(auto it = sortedWords.rbegin(); it!=sortedWords.rend()&&count<10; ++it,++count){
        std::cout << it->second << "\t" << it->first << std::endl;
    }
    
}
