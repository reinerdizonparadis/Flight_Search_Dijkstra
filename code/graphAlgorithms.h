#ifndef GRAPHALGORITHMS_H
#define GRAPHALGORITHMS_H
#include "hashTable.h"
using namespace std;

struct flightInfo{
	unsigned int origAirport;	// origin airport
	unsigned int destAirport;	// destination airport
	string flightNum;			// flight number
	int departTime;				// departure time
	int arrivalTime;			// arrival time
	flightInfo *link;			// link to another flight
								// from the origin airport
};

class graphAlgorithms{
public:
	graphAlgorithms();
	// This is the default constructor for graphAlgorithms class
	// which will initialize the member variables as appropriate.
	
	~graphAlgorithms();
	// This is the destructor for graphAlgorithms class
	// which will call the destroyGraph() function to deallocate memory
	// and will reset all member variables as appropriate.
	
	void newGraph(int);
	// The function will allocate & initialize the adjacency list to 0's
	// after calling destroyGraph() function to prevent memory leaks.
	
	int getVertexCount() const;
	// The function will return current vertex count.
	
	int getFlightsCount() const;
	// The function will return current flights count.
	
	int getAirportsCount() const;
	// The function will return current airports count.
	
	bool loadAirports(const string);
	// The function will load all airports from the given file
	// onto the hash table.
	
	bool checkAirport(const string);
	// The function will return true if the passed airport code exists.
	
	void printFlightPath(const string, const string);
	// The function will print the flight itinerary from origin airport
	// to destination airport.
	
	void addFlight(string, string, int, int, string);
	// The function will add a flight to the adjacency list.
	
	void dijkstraSP(string, int);
	// The function will find the shortest path from source node
	// to every other node in the graph using the Dijkstra algorithm.
		
private:
	int vertexCount;		// number of vertex in graph
	int edgeCount;			// number of edge in graph
	hashTable airports;		// airports hash table
	flightInfo **flights;	// adjacency list
	int *originAirport;		// origin airport array
	int *arrTimes;			// arrival times array
	flightInfo *prevFlight;	// previous flights array
	
	void showPath(const int) const;
	// The function will recursively print the path
	// from source node to the given destination node.
	
	void destroyGraph();
	// The function will deallocate all memories & reset all variables.
};
#endif