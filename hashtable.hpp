
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
	
	for(auto & list : theTable)
	{
		list.clear();
	}
	
	currSize = 0;
}

//Rehash function. Called when the number of elements in the hash table is greater than the size of the vector.
template <typename K, typename V>
void HashTable<K, V>::rehash()
{
	std::vector<std::list<std::pair<K,V>>>prevList = theTable;
	
	theTable.resize(prime_below(2 * prevList.size ()));
	
	for(auto & list : theTable)
		list.clear();
	
	currSize = 0;
	
	for(auto & list : prevList)
		for(auto & pair : list)
			insert(std::move(pair));
}
//return the index of the vector entry where k should be stored.
template <typename K, typename V>
size_t HashTable<K, V>::myhash(const K &k)
{
	static std::hash<K> hf;
	return hf(k) % theTable.size();
}

//Constructor
template <typename K, typename V>
HashTable<K, V>::HashTable(size_t theSize)
{
	currSize =0;
	if(prime_below(theSize) == 0)
	{
		std::cout << "set to default capacity\n";
		theTable.resize(default_capacity);
	}
	else
		theTable.resize(prime_below(theSize));
	
	std::cout <<  theTable.size();
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
		auto it = std::find_if(begin(list), end(list), [&k](const std::pair<K, V> p)
		{return p.first == k;});
			
		if(it != end(list))
		{
			return true;
		}
	}
	
	return false;
}
 
 //Ckeck if pair is in hash table
template <typename K, typename V>
bool HashTable<K, V>::match(const std::pair<K, V> &kv) const
{
	
	for(auto list: theTable)
	{
		auto it = std::find_if(begin(list), end(list), [&kv](const std::pair<K, V> p)
		{return p.first == kv.first && p.second == kv.second;} );
			
		if(it != end(list))
		{
			
			return true;
		}
	}

	return false;
}

//Add key-value pair into hash table
template <typename K, typename V>
bool HashTable<K, V>::insert(const std::pair<K, V> & kv) 
{
	auto & theList = theTable[myhash(kv.first)];
	
	
	size_t check = currSize +1;
	
	if(match(kv))
		return false;
	
	if(contains(kv.first))
	{
		for(auto & p : theList)
		{
			if(p.first == kv.first)
			{
					p.second = kv.second;
					return false;
			}
				
		}
	}
	else 
		theList.push_back(kv);
	
	currSize++;
	if(check > theTable.size())
		rehash();
	
	return true;
}

//Move version of insert
template <typename K, typename V>
bool HashTable<K, V>::insert(std::pair<K, V> && kv)
{
	auto & theList = theTable[myhash(kv.first)];
	
	size_t check = currSize +1;

	if(match(kv))
		return false;
	
	if(contains(kv.first))
	{
		for(auto & p : theList)
		{
			if(p.first == kv.first)
			{
					p.second = std::move(kv.second);
					return false;
			}
				
		}
	}
	else 
		theList.push_back(std::move(kv));
	
	currSize++;	
	if(check > theTable.size())
		rehash();
	
	return true;
}
//Delete k and value from hash table
template <typename K, typename V>
bool HashTable<K, V>::remove(const K & k)
{
	auto & theList = theTable[myhash(k)];

	auto itr = std::find_if(begin(theList), end(theList), [&k](const std::pair<K, V> p)
		{return p.first == k;} );
	
	if(itr == end(theList))
		return false;
	
	theList.erase(itr);
	--currSize;
	return true;
}

//Delete all elements in hash table
template <typename K, typename V>
void HashTable<K,V>::clear()
{
	makeEmpty();
	
}
//Load the content of the file into hash table
template <typename K, typename V>
bool HashTable<K, V>::load(const char *filename)
{
	K key;
	V value;
	std::string line;
	std::fstream in;
	
	in.open(filename, std::fstream::in);
	
	if(!in)
		return false;
	
	while(in)
	{
			in >> key;
			in >> value;
			in.ignore(1, '\n');
			insert(std::make_pair(key, value));
	}
	
	in.close();
	return true;
}
//Display all entries in the hash table
template <typename K, typename V>
void HashTable<K, V> :: dump()
{
	
	int i	= 0;
	for(auto list : theTable)
	{
		std::cout << "v[" << i << "]: ";
		for(auto pair : list)
		{
			std::cout << pair.first << " " << pair.second;
			
			if(list.size() > 1)
				std::cout << ":";
		}
		
		std::cout << "\n";
		i++;
	}
}

template <typename K, typename V>
size_t HashTable<K,V>::size()
{
	return currSize;
}

//Write all elements in the hash table into file with filename
template <typename K, typename V>
bool HashTable<K,V>::write_to_file(const char *filename)
{
	std::ofstream out(filename);
	
	if(!out)
		return false;
	
	for(auto list : theTable)
	{
		for(auto pair: list)
		{
			out << pair.first << "  " << pair.second << "\n";
		}
		
	}
	return true;
	
}
