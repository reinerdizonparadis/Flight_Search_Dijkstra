CC		= g++ -Wall -pedantic -std=c++11 -g
OBJS	= travel.o airlineRouter.o graphAlgorithms.o hashTable.o
DEPS	= airlineRouter.h graphAlgorithms.h hashTable.h priorityQueue.h
DEPS1	= priorityQueue.h hashTable.h
DEPS2	= graphAlgorithms.h priorityQueue.h hashTable.h

all: travel
	
	
hashTable.o: hashTable.cpp
	$(CC) -c hashTable.cpp
	
graphAlgorithms.o: graphAlgorithms.cpp $(DEPS1)
	$(CC) -c graphAlgorithms.cpp 
	
airlineRouter.o: airlineRouter.cpp $(DEPS2)
	$(CC) -c airlineRouter.cpp 
	
travel.o: travel.cpp $(DEPS)
	$(CC) -c travel.cpp 
	
travel: $(OBJS) $(DEPS)
	$(CC) -o travel $(OBJS)
	

clean:
	rm	$(OBJS)