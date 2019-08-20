#include <boost/asio/io_service.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "task.cpp"
#include <queue>

class threadpool{
    private:
        boost::asio::thread_pool threads;

    public:
        threadpool(int N){
            boost::asio::thread_pool threads(N);
        }
        void addTask(std::shared_ptr<stats> programStats, const string& path);
        void closePool();
};