#ifndef HASHTABLE_H
#define HASHTABLE_H
using namespace std;

class hashTable{
public:
	hashTable();
	// This is the default constructor for hashTable class
	// which will set the member variable hashSize to initialHashSize 
	// and all other variables to 0 as well as allocate a 2D array 
	// that has a length of hashSize and width of 2.
	// The first element of each row array is the empty string.
	
	~hashTable();
	// This is the destructor for hashTable class
	// which will deallocate the 2D array,
	// set the addrHash to NULL if addrHash is not NULL,
	// and reset all other member variables.
	
	bool insert(const string, const string);
	// The function will insert the key and two other values
	// by finding an element in the hash table using hash function.
	// If there is a collision, the 
	
	bool lookup(const string, string&, unsigned int&) const;
	// The function will lookup a certain key (airport code)
	// on the hash table and return the city and hash value
	// via reference.
	
	bool lookup(const unsigned int, string&, string&) const;
	// The function will lookup a certain key (vertex or hash value)
	// on the hash table and return the city and code via reference.
	
	unsigned int getHashSize() const;
	// The function will return size of hash table.
	
	unsigned int getEntries() const;
	// The function will return the number of entries.
	
private:
	unsigned int hashSize;			// size of hash table
	unsigned int entries;			// count of nonempty elements of the hash table
	string **airportsHash;			// 2D array to hold the hash table
	
	static constexpr double loadFactor = 0.7;				// max load factor before rehashing
	static constexpr unsigned int initialHashSize = 10000;	// initial hash size
	
	unsigned int hash(string) const;
	// This private function will produce the element 
	// to the hash table using the given hash function(s).
	
	void rehash();
	// This private function will create a new 2D array
	// with twice the original hash size.
	// The elements in the original hash table will need 
	// to be rehashed and inserted to the new hash table.
	// The old hash table is then deleted.
};
#endif