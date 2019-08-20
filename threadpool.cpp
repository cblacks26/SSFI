#include "threadpool.h"


// Submit a new task for completion, through the ioService
void threadpool::addTask(std::shared_ptr<stats> programStats, const string& path){
    boost::asio::post(threads,boost::bind(&readFile,programStats,path));
}
// Wait for tasks to be completed then close the thread pool
void threadpool::closePool(){
    threads.join();
}