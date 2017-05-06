#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

/* heapNode struct definition */
template <class myType>
struct heapNode{
	unsigned long long priority;	// priority
	myType item;					// item
};

/* priorityQueue class specification */
template <class myType>
class priorityQueue{
public:
	priorityQueue(int=6000);
	// This is the default constructor for priorityQueue class
	// which will set member variables count to 0 
	// & heapSize to given parameter or to 6000 
	// if no parameters are passed or if the parameter < 6000.
	// The array myHeap is dynamically allocated to the heapSize.
	
	~priorityQueue();
	// This is the destructor for priorityQueue class
	// which will reset both member variables count & heapSize.
	// The pointer myHeap is deallocated and set to NULL.
	
	int entries() const;
	// The function will return the number of entries in the heap.
	
	void insert(const myType, const unsigned long long);
	// The function will insert an element onto the heap (single insertion)
	
	bool deleteMin(myType &, unsigned long long &);
	// The function will delete the top of the heap,
	// orphans the last placed element of the heap to the top,
	// & calls reheapDown to maintain order property.
	
	bool isEmpty() const;
	// The function will return true if the heap is empty.
	
private:
	int count;					// number of entries in the heap
	int heapSize;				// max size of the heap
	heapNode<myType> *myHeap;	// heap
	
	void reheapUp(int);
	// The function will reheap an element by traversing up the tree.
	
	void reheapDown(int);
	// The function will reheap an element by traversing down the tree.
	
	void buildHeap();
	// The function will order the elements according to the order property.
	
	void resize();
	// The function will resize the heap once it reaches its full capacity.
};

/* priorityQueue class implementation */
template <class myType>
priorityQueue<myType>::priorityQueue(int size){
	// initialize class variables
	count = 0;
	heapSize = (size<5000) ? 5000 : size;
	
	// create min heap
	myHeap = new heapNode<myType>[heapSize];
}

template <class myType>
priorityQueue<myType>::~priorityQueue(){
	// delete all allocated memory
	if(myHeap != NULL){
		delete [] myHeap;
		myHeap = NULL;
	}
	
	// reset class variables
	count = 0;
	heapSize = 5000;
}

template <class myType>
int priorityQueue<myType>::entries() const{
	// return number of entries from the heap
	return count;
}

template <class myType>
void priorityQueue<myType>::insert(const myType newItem, const unsigned long long newPriority){
	// increment count
	count++;
	
	// resize if heap is full
	if(count > heapSize-1)
		resize();
	
	// insert data
	myHeap[count] = {newPriority, newItem};
	
	// reheap up to maintain order property
	reheapUp(count);
}

template <class myType>
bool priorityQueue<myType>::deleteMin(myType &retItem, unsigned long long &retPriority){
	// check if heap is empty
	if(isEmpty())
		return false;
	
	// return item & priority by reference
	retItem = myHeap[1].item;
	retPriority = myHeap[1].priority;
	
	// orphan last entry to root
	myHeap[1] = {myHeap[count].priority, myHeap[count].item};
	count--;
	
	// reheap root down
	reheapDown(1);
	return true;
}

template <class myType>
bool priorityQueue<myType>::isEmpty() const{
	// check if heap is empty
	return (count == 0);
}

// private functions
template <class myType>
void priorityQueue<myType>::reheapUp(int index){
	// variable declarations
	int parent;
	heapNode<myType> temp;
	
	// reheap index up
	if(index > 1){
		parent = index / 2;
		if(myHeap[index].priority < myHeap[parent].priority){
			// swap parent & child
			temp = myHeap[index];
			myHeap[index] = myHeap[parent];
			myHeap[parent] = temp;
			reheapUp(parent);
		}
	}
}

template <class myType>
void priorityQueue<myType>::reheapDown(int index){
	// variable declarations
	int child;
	heapNode<myType> temp;
	
	// reheap index down
	if(index <= count/2){
		if(myHeap[index*2].priority <= myHeap[index*2+1].priority)
			child = index*2;	// left child
		else
			child = index*2+1;	// right child
		
		if(myHeap[index].priority > myHeap[child].priority){
			temp = myHeap[index];
			myHeap[index] = myHeap[child];
			myHeap[child] = temp;
			reheapDown(child);
		}
	}
}

template <class myType>
void priorityQueue<myType>::buildHeap(){
	// variable declarations
	int index = count/2;
	
	// reheap down from last non-leaf tree element up
	while(index >= 1)
		reheapDown(index--);
}

template <class myType>
void priorityQueue<myType>::resize(){
	// variable declarations
	int oldSize = heapSize;
	heapNode<myType> *oldHeap = myHeap;
	
	// create a new heap twice the size
	heapSize *= 2;
	myHeap = new heapNode<myType>[heapSize];
	
	// reenter heap entries into new heap
	for(int i = 0; i < oldSize; i++)
		myHeap[i] = {oldHeap[i].priority, oldHeap[i].item};
	
	// delete the old heap
	delete [] oldHeap;
	oldHeap = NULL;
}

#endif