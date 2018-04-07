// returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n
template <typename K, typename V>
unsigned long HashTable<K, V>::prime_below (unsigned long n)
{
  if (n > max_prime)
    {
      std::cerr << "** input too large for prime_below()\n";
      return 0;
    }
  if (n == max_prime)
    {
      return max_prime;
    }
  if (n <= 1)
    {
		std::cerr << "** input too small \n";
      return 0;
    }

  // now: 2 <= n < max_prime
  std::vector <unsigned long> v (n+1);
  setPrimes(v);
  while (n > 2)
    {
      if (v[n] == 1)
	return n;
      --n;
    }

  return 2;
}

//Sets all prime number indexes to 1. Called by method prime_below(n) 
template <typename K, typename V>
void HashTable<K, V>::setPrimes(std::vector<unsigned long>& vprimes)
{
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.capacity();

  for (i = 2; i < n; ++i)
    vprimes[i] = 1;

  for( i = 2; i*i < n; ++i)
    {
      if (vprimes[i] == 1)
        for(j = i + i ; j < n; j += i)
          vprimes[j] = 0;
    }
}

//delete all elements in the hash table. The public interface clear() will call this function
template <typename K, typename V>
void HashTable<K, V>::makeEmpty() 
{
	clear();
}

//Rehash function. Called when the number of elements in the hash table is greater than the size of the vector.
template <typename K, typename V>
void HashTable<K, V>::rehash()
{
	vector <std::pair<K,V>> prevList = theTable;
	
	theTable.resize(prime_below(2 * prevList.size()));
	
	size = 0;
	
	for(auto &pair : prevList)
		insert(std::move(pair));
}
//return the index of the vector entry where k should be stored.
template <typename K, typename V>
size_t HashTable<K, V>::myhash(const K &k)
{
	return k % theTable.size();
}

//Constructor
template <typename K, typename V>
HashTable<K, V>::HashTable(size_t theSize = 101)
{
	size = prime_below(theSize);
	
}

//Destructor
template <typename K, typename V>
HashTable<K, V>::~HashTable() 
{
	clear();
}

//Check if key is in hashtable
template <typename K, typename V>
bool HashTable<K, V>::contains(const K & k)
{
	for(auto list: theTable)
	{
		if(std::find_if(begin(list), end(list), [](const std::pair<K, V> p)
		{return p.first == kv.first;} ) != end(list));
			return true;
	}
	
	return false;
}
 
 //Ckeck if pair is in hash table
template <typename K, typename V>
bool HashTable<K, V>::match(const std::pair<K, V> &kv) const
{
	for(auto list: theTable)
	{
		if(std::find_if(begin(list), end(list), [](const std::pair<K, V> p)
		{return p.first == kv.first && p.second == kv.second;} ) != end(list));
			return true;
	}
	
	return false;
}

//Add key-value pair into hash table
template <typename K, typename V>
bool HashTable<K, V>::insert(const std::pair<K, V> & kv) 
{
	
	auto & theList = theTable[myhash(kv.first)];
	
	size++;
	
	if(match(kv))
		return false;
	
	if(contains(kv.first))
	{
		for(auto & p : theList)
		{
			if(p.first == kv.first)
			{
					p.second = kv.second;
			}
				
		}
	}
	else 
		theList.push_back(kv);
	
	if(++size > theTable.size())
		rehash();
	
	return true;
}

//Move version of insert
template <typename K, typename V>
bool HashTable<K, V>::insert(std::pair<K, V> && kv)
{
	auto & theList = theTable[myhash(kv.first)];
	size++;
	
	if(match(kv))
		return false;
	
	if(contains(kv.first))
	{
		for(auto & p : theList)
		{
			if(p.first == kv.first)
			{
					p.second = std::move(kv.second);
			}
				
		}
	}
	else 
		theList.push_back(kv);
	
	if(++size > theTable.size())
		rehash();
	
	return true;
}
//Delete k and value from hash table
template <typename K, typename V>
bool HashTable<K, V>::remove(const K & k)
{
	auto theList = theTable[myhash(k)];
	
	auto itr = std::find_if(begin(theList), end(theList), [](const std::pair<K, V> p)
		{return p.first == kv.first && p.second == kv.second;} );
	
	if(itr == end(theList))
		return false;
	
	theList.erase(itr);
	--size;
	return true;
}

//Delete all elements in hash table
template <typename K, typename V>
void clear()
{
	for(auto & list : theTable)
	{
		list.clear();
	}
	
	size = 0;
	
}
bool load(const char *filename); //Load the content of the file into hash table
void dump(); //Display all entries in the hash table
size_t size(); //Return the number of elements in the hash table
bool write_to_file(const char *filename); //Write all elements in the hash table into file with filename

