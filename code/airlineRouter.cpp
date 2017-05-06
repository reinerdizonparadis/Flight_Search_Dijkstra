#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "airlineRouter.h"
#include "graphAlgorithms.h"
using namespace std;

airlineRouter::airlineRouter(){
	// initialize class variables
	flightsCnt = 0;
	airportsCnt = 0;
}

airlineRouter::~airlineRouter(){
	// initialize class variables
	flightsCnt = 0;
	airportsCnt = 0;
}

bool airlineRouter::readAirports(const string filename){
	// load airports to hash table
	bool done = flights.loadAirports(filename);
	airportsCnt = flights.getAirportsCount();
	return done;
}

bool airlineRouter::readFlights(const string filename){
	// variable declarations
	string temp, flightNum, orig, dest;
	int arr, dep;
	stringstream ss;
	ifstream infile;
	
	// check if file existss
	infile.open(filename.c_str());
	if(!infile.is_open())
		return false;
	
	// load flights onto adjacency list
	getline(infile, temp);
	while(infile){
		flightNum = temp.substr(0, 6);
		temp = temp.substr(6);
		ss.clear();
		ss.str("");
		ss << temp;
		ss >> orig;
		ss >> dep;
		ss >> dest;
		ss >> arr;
		flights.addFlight(orig, dest, dep, arr, flightNum);
		getline(infile, temp);
	}
	infile.close();
	flightsCnt = flights.getFlightsCount();
	return true;
}

void airlineRouter::showGraphStats(){
	// print graph statistics
	cout << "Graph Statistics:" << endl;
	cout << "   Nodes: " << airportsCnt << endl;
	cout << "   Edges: " << flightsCnt << endl << endl;
}

void airlineRouter::findFlights(string orig, string dest, int startTime){
	// perform Dijsktra's algorithm to find earliest flight by arrival time
	flights.dijkstraSP(orig, startTime);
	flights.printFlightPath(orig, dest);
}

bool airlineRouter::checkAirportCode(const string code){
	// check if airport code exists
	return flights.checkAirport(code);
}
