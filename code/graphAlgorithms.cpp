#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
#include "graphAlgorithms.h"
#include "priorityQueue.h"
#include "hashTable.h"
using namespace std;

graphAlgorithms::graphAlgorithms(){
	// initialize class variables
	flights = NULL;
	originAirport = NULL;
	arrTimes = NULL;
	prevFlight = NULL;
	vertexCount = 0;
	edgeCount = 0;
}

graphAlgorithms::~graphAlgorithms(){
	// delete dynamically allocated memory
	destroyGraph();
	
	// reset all variables
	flights = NULL;
	originAirport = NULL;
	arrTimes = NULL;
	prevFlight = NULL;
	vertexCount = 0;
	edgeCount = 0;
}

void graphAlgorithms::newGraph(int size){
	// deallocate all memories to avoid memory leaks
	destroyGraph();
	
	// initialize adjancency list
	vertexCount = size;
	flights = new flightInfo*[vertexCount];
	for(int i = 0; i < vertexCount; i++)
		flights[i] = NULL;
}

int graphAlgorithms::getVertexCount() const{
	// return current vertex count
	return vertexCount;
}

int graphAlgorithms::getFlightsCount() const{
	// return current flights count
	return edgeCount;
}

int graphAlgorithms::getAirportsCount() const{
	// return current flights count
	return airports.getEntries();
}

bool graphAlgorithms::loadAirports(const string filename){
	// variable declarations
	string temp, name, code;
	stringstream ss;
	ifstream infile;
	
	// check for open file error
	infile.open(filename.c_str());
	if(!infile.is_open())
		return false;
	
	getline(infile, temp);
	while(infile){
		name = temp.substr(0, 55);
		ss.clear();
		ss.str("");
		ss << temp;
		ss.ignore(109);
		ss >> code;
		
		airports.insert(code, name);
		getline(infile, temp);
	}
	infile.close();
	newGraph(airports.getHashSize());
	return true;
}

bool graphAlgorithms::checkAirport(const string code){
	string temp;
	unsigned int temp1;
	return airports.lookup(code, temp, temp1);
}

void graphAlgorithms::printFlightPath(const string origAirport, const string destAirport){
	// variable & constant declarations
	const int INF = std::numeric_limits<int>::max();
	string nameO, nameD;
	string temp1, dashes;
	unsigned int destNode, origNode, temp;
	dashes.append(44, '-');
	
	if(flights==NULL || !airports.lookup(destAirport, temp1, destNode))
		return;
	
	if(!airports.lookup(origAirport, temp1, origNode))
		return;
	
	cout << endl;
	if(flights[origNode] == NULL){
		cout << "No flights from " << origAirport << endl << endl;
		return;
	}
	
	if(!airports.lookup(origAirport, nameO, temp))
		return;
	
	if(!airports.lookup(destAirport, nameD, temp))
		return;
	
	// print header
	cout << dashes << "\nFrom / To" << endl;
	cout << "  " << origAirport << " - " << nameO << endl;
	cout << "  " << destAirport << " - " << nameD << endl;
	
	if(arrTimes[destNode] == INF){
		cout << "\n  " << destAirport << " is not reachable from " << origAirport << "." << endl << endl;
		return;
	}
	
	// print path
	cout << endl;
	showPath((int)destNode);
	
	if(originAirport != NULL){
		delete [] originAirport;
		originAirport = NULL;
	}
	
	if(arrTimes != NULL){
		delete [] arrTimes;
		arrTimes = NULL;
	}
	
	if(prevFlight != NULL){
		delete [] prevFlight;
		prevFlight = NULL;
	}
}

void graphAlgorithms::addFlight(string origAirport, string destAirport, int depTime, int arrTime, string flight_num){
	// variable declarations
	unsigned int origAir, destAir;
	string temp;
	
	// check if airports are valid
	if(!airports.lookup(origAirport, temp, origAir) || !airports.lookup(destAirport, temp, destAir))
		return;
	
	// check if airports are same
	if(origAir == destAir)
		return;
	
	flightInfo *newFlight = new flightInfo;
	newFlight->origAirport = origAir;
	newFlight->destAirport = destAir;
	newFlight->flightNum = flight_num;
	newFlight->departTime = depTime;
	newFlight->arrivalTime = arrTime;
	newFlight->link = NULL;
	
	if(flights[origAir] == NULL)
		flights[origAir] = newFlight;
	else{
		newFlight->link = flights[origAir];
		flights[origAir] = newFlight;
	}
	edgeCount++;
}

void graphAlgorithms::dijkstraSP(string origAirport, int startTime){
	unsigned int origAir;
	string temp;
	if(flights == NULL || !airports.lookup(origAirport, temp, origAir))
		return;
	
	// constants & variables declarations
	const int INF = std::numeric_limits<int>::max();
	priorityQueue<unsigned int> pq;
	unsigned int u, v, arrTime, depTime;
	unsigned long long tempTime;
	flightInfo *tempFlight;
	
	// arrival times & previous flight arrays
	arrTimes = new int[vertexCount];
	originAirport = new int[vertexCount];
	prevFlight = new flightInfo[vertexCount];
	for(int i = 0; i < vertexCount; i++){
		arrTimes[i] = INF;
		originAirport[i] = -1;
		prevFlight[i] = {INF, INF, "", -1, INF, NULL};
	}
	
	// insert empty node
	pq.insert(origAir, startTime);
	arrTimes[origAir] = startTime;
	prevFlight[origAir].arrivalTime = startTime - 30;
	prevFlight[origAir].departTime = 0;
	prevFlight[origAir].origAirport = origAir;
	
	// loop to check paths
	while(!pq.isEmpty()){
		if(!pq.deleteMin(u, tempTime))
			cout << "Error!" << endl;
		tempFlight = flights[u];
		while(tempFlight != NULL){
			v = tempFlight->destAirport;
			arrTime = tempFlight->arrivalTime;
			depTime = tempFlight->departTime;
			
			if(tempTime < depTime && depTime < arrTime && (int)arrTime < arrTimes[v]){
				arrTimes[v] = arrTime;
				originAirport[v] = u;
				arrTime += 30;
				prevFlight[v].origAirport = tempFlight->origAirport;
				prevFlight[v].destAirport = tempFlight->destAirport;
				prevFlight[v].flightNum = tempFlight->flightNum;
				prevFlight[v].departTime = tempFlight->departTime;
				prevFlight[v].arrivalTime = tempFlight->arrivalTime;
				if(arrTime % 100 > 60)
					arrTime += 40;
				pq.insert(v, arrTime);
			}
			tempFlight = tempFlight->link;
		}
	}
}

// private functions
void graphAlgorithms::showPath(const int destNode) const{
	string name, code1, code2;
	if(!airports.lookup(destNode, name, code1) || originAirport[destNode] == -1)
		return;
	else{
		showPath(originAirport[destNode]);
		if(!airports.lookup(prevFlight[destNode].origAirport, name, code2))
			return;
		
		cout << "Flight:" << endl;
		cout << "  " << code2 << "-" << code1 << " :: ";
		cout << "DeptTime: " << prevFlight[destNode].departTime;
		cout << "   ArrvTime: " << prevFlight[destNode].arrivalTime;
		cout << "   " << endl;
		cout << "  Flight Number: " << prevFlight[destNode].flightNum << endl << endl;
	}
}

void graphAlgorithms::destroyGraph(){
	// deallocate all memories
	if(flights != NULL){
		delete [] flights;
		flights = NULL;
	}
	
	if(originAirport != NULL){
		delete [] originAirport;
		originAirport = NULL;
	}
	
	if(arrTimes != NULL){
		delete [] arrTimes;
		arrTimes = NULL;
	}
	
	if(prevFlight != NULL){
		delete [] prevFlight;
		prevFlight = NULL;
	}
	
	// reinitialize class variables
	vertexCount = 0;
	edgeCount = 0;
}