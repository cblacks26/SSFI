CC = g++ -std=c++11
CFLAGS = -Wall -c
LFLAGS = -Wall
INCLUDE  = -I. 

# INCLUDE BASE DIRECTORY AND BOOST DIRECTORY FOR HEADERS
LDFLAGS = -I/usr/local/include/boost -I.

# INCLUDE BOOST DIRECTORY FOR LIB FILES
LLIBFLAGS = -L/usr/local/lib

# SPECIFIY LINK OPTIONS
LINKFLAGS = -lpthread -lboost_system -lboost_filesystem -lboost_thread

# FINAL FLAGS -- TO BE USED THROUGHOUT
FLAGS = $(LDFLAGS) $(LLIBFLAGS)

all: ssfi.o stats.o task.o threadpool.o
	$(CC) ssfi.o stats.o task.o threadpool.o $(FLAGS) -o ssfi $(LINKFLAGS) 

task: task.o stats.o
	$(CC) task.o stats.o $(FLAGS) -o task $(LINKFLAGS)

task.o: task.cpp stats.h
	$(CC) task.cpp $(LDFLAGS) $(CFLAGS) 

stats.o: stats.cpp stats.h
	$(CC) stats.cpp $(LDFLAGS) $(CFLAGS)

ssfi.o: ssfi.cpp threadpool.h
	$(CC) ssfi.cpp $(CFLAGS) -I.

threadpool.o: threadpool.cpp threadpool.h
	$(CC) threadpool.cpp $(LDFLAGS) $(CFLAGS)

clean :
	-rm *.o ssfi
