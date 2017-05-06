#include <iostream>
#include <sstream>
#include <string>
#include "hashTable.h"
using namespace std;

hashTable::hashTable(){
	// initialize class variables
	hashSize = initialHashSize;
	entries = 0;
	airportsHash = new string*[hashSize];
	for(unsigned int i = 0; i < hashSize; i++){
		airportsHash[i] = new string[2];
		airportsHash[i][0] = "";
	}
}

hashTable::~hashTable(){
	// delete dynamically allocated memory
	if(airportsHash != NULL){
		delete [] airportsHash;
		airportsHash = NULL;
	}
	
	// reset all variables
	hashSize = initialHashSize;
	entries = 0;
}

bool hashTable::insert(const string newCode, const string newName){
	unsigned int newHash = hash(newCode);
	// variable declarations
	string temp1;
	unsigned int temp2;
	
	// check if key already exists
	if(lookup(newCode, temp1, temp2))
		return false;
	
	// checking for collision
	while(!(airportsHash[newHash][0]=="" || airportsHash[newHash][0]=="*"))
		newHash = (newHash + 1) % hashSize;
	
	// insert data onto table
	airportsHash[newHash][0] = newCode;
	airportsHash[newHash][1] = newName;
	entries++;
	
	// rehash if it reaches load factor
	if(entries * 1.0 / hashSize > loadFactor)
		rehash();
	
	return true;
}

bool hashTable::lookup(const string airCode, string &airName, unsigned int &airElement) const{
	// variable declarations
	unsigned int newHash = hash(airCode);
	
	if(airCode == "PSZ")
		return false;
	while(airportsHash[newHash][0] != ""){
		if(airportsHash[newHash][0] == airCode){
			airName = airportsHash[newHash][1];
			airElement = newHash;
			return true;
		}
		newHash = (newHash + 1) % hashSize;
	}
	return false;
}

bool hashTable::lookup(const unsigned int airVertex, string &airName, string& airCode) const{
	if(airVertex < 0 || airVertex >= hashSize)
		return false;
	airCode = airportsHash[airVertex][0];
	airName = airportsHash[airVertex][1];
	return true;
}

unsigned int hashTable::getHashSize() const{
	// return hash table size
	return hashSize;
}

unsigned int hashTable::getEntries() const{
	// return number of entries on table size
	return entries;
}

// private functions
unsigned int hashTable::hash(string wrd) const{
	// Hash based on Horner's rule
	int hash = 0;
	for(int i = wrd.length()-1; i >= 0; i--)
		hash = (wrd[i] + 128 * hash) % hashSize;
	return hash;
}

void hashTable::rehash(){
	unsigned int oldHashSize = hashSize;
	hashSize *= 2;
	string **oldAddrHash = airportsHash;
	airportsHash = new string*[hashSize];
	entries = 0;
	
	for(unsigned int i = 0; i < hashSize; i++){
		airportsHash[i] = new string[2];
		airportsHash[i][0] = "";
	}
	
	for(unsigned int i = 0; i < oldHashSize; i++){
		if(!(oldAddrHash[i][0]=="" || oldAddrHash[i][0]=="*"))
			if(!insert(oldAddrHash[i][0], oldAddrHash[i][1]))
				cout << "Error, insert fail. (" << oldAddrHash[i][0] << ")" << endl;
	}
	
	delete [] oldAddrHash;
	oldAddrHash = NULL;
}
