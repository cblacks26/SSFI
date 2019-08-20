#include <string>
#include <iostream>
#include <unordered_map>
#include <boost/thread.hpp>

using std::string;
using std::unordered_map;

class stats{
	public :
		void addWord(const string& str);
		void addStats(std::shared_ptr<stats> stat);
		void printStats();
	private :
		// unordered map for word counts
		unordered_map<string, int> words;
		// must lock when adding stats up for synchronization
		boost::mutex mutex;
		
		void lockStats(){
			mutex.lock();
		}

		void unlockStats(){
			mutex.unlock();
		}
};