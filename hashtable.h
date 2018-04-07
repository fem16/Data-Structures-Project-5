#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <iostream>
#include <utility>
#include <pair>
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
			class HashTable
			{
				private:
					void makeEmpty(); ///delete all elements in the hash table. The public interface clear() will call this function
					void rehash(); //Rehash function. Called when the number of elements in the hash table is greater than the size of the vector.
					size_t myhash(const K &k); //return the index of the vector entry where k should be stored.
					unsigned long prime_below (unsigned long);
					void setPrimes(vector<unsigned long>&);
					
					
					
				public:
					HashTable(size_t size = 101);
					~HashTable();
					bool contains(const K & k); 
					bool match(const std::pair<K, V> &kv) const;
					bool insert(const std::pair<K, V> & kv); 
					bool insert (std::pair<K,  V> && kv); 
					bool remove(const K & k);
					void clear(); 
					bool load(const char *filename); 
					void dump(); 
					size_t size(); 
					bool write_to_file(const char *filename);
										
			};//end of class
			
			#include "hashtable.hpp"
}
			
			
					
 
#endif
