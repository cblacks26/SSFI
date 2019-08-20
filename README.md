This program makes use of boost 1.66 for multithreading using the thread_pool utility,
boost filesystem for searching the directories, and is compiled using c++11. 
Be sure to checkout the Makefile to see if you need to change the boost include and lib directories.
When running the program without the thread option -t, the program will use 4 threads 
by default.