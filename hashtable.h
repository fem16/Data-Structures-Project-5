#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <iostream>
#include <utility>
#include <algorithm>
#include <vector>
#include <list>
// max_prime is used by the helpful functions provided
// to you.
static const unsigned int max_prime = 1301081;
// the default_capacity is used if the initial capacity 
// of the underlying vector of the hash table is zero. 
static const unsigned int default_capacity = 11;

namespace cop4530{
	
		template <typename K, typename V>
			class HashTable<K, V>
			{
				private:
					void makeEmpty(); ///delete all elements in the hash table. The public interface clear() will call this function
					void rehash(); //Rehash function. Called when the number of elements in the hash table is greater than the size of the vector.
					size_t myhash(const K &k); //return the index of the vector entry where k should be stored.
					unsigned long prime_below (unsigned long); //Helper to determine prime numbers
					void setPrimes(vector<unsigned long>&);
					
					int size;
					std::vector<std::list<std::pair<K,V>> theTable;
					
					
				public:
					HashTable(size_t theSize = 101);//Constructor
					~HashTable(); //Destructor
					bool contains(const K & k); //Check if key is in hashtable
					bool match(const std::pair<K, V> &kv) const; //Ckeck if pair is in hash table
					bool insert(const std::pair<K, V> & kv); //Add key-value pair into hash table
					bool insert (std::pair<K, V> && kv); //Move version of insert
					bool remove(const K & k);	//Delete k and value from hash table
					void clear(); //Delete all elements in hash table
					bool load(const char *filename); //Load the content of the file into hash table
					void dump(); //Display all entries in the hash table
					size_t size(); //Return the number of elements in the hash table
					bool write_to_file(const char *filename); //Write all elements in the hash table into file with filename
										
			};//end of class
			
			#include "hashtable.hpp"
}
			
			
					
 
#endif
