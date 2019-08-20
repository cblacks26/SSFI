# Super Simple File Indexer
This program searches a passed file or directory of files looking for files ending in *.txt*. Once found it will count the number of words for a file. Note it will not take into account apostrophes, etc... As well as it will not stem words into their base form. At the end, the program will print out the top 10 most used words.
### Libraries
This program uses boost 1.66 for multithreading by means of the thread_pool class, as well as boost filesystem for searching the directories, and is compiled using c++11. 

### Steps to run
1. Install boost
2. Checkout the Makefile to see if you need to change the boost include and lib directories.
3. Run the `make` command
4. Run command is `./ssfi <File or Directory>`
5. Specify number of worker threads to use with `-t number_of_threads` by default it will use 4
