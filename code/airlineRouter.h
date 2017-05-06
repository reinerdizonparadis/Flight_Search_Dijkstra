#ifndef AIRLINEROUTER_H
#define AIRLINEROUTER_H
#include "graphAlgorithms.h"
using namespace std;

class airlineRouter{
public:
	airlineRouter();
	// This is the default constructor for airlineRouter class
	// which will initialize the member variables to 0.
	
	~airlineRouter();
	// This is the destructor for airlineRouter class
	// which will reset all member variables to 0.
	
	bool readAirports(const string);
	// The function will read airports data file onto the hash table.
	
	bool readFlights(const string);
	// The function will read flights data file onto adjacency list.
	
	void showGraphStats();
	// The function will display the graph statistics: airports & flights count.
	
	void findFlights(string, string, int);
	// The function will perform Dijkstra's shortest path algorithm
	// to find the shortest flight by earliest arrival time
	// from the passed origin airport to the destination airport,
	
	bool checkAirportCode(const string);
	// The function will return true if the airport code is valid.
	
	
private:
	graphAlgorithms flights;	// flights graph (w/ airport hash table)
	int flightsCnt;				// number of flights
	int airportsCnt;			// number of airports
};

#endif