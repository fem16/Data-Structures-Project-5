#include "passserver.h"

PassServer::PassServer(size_t size)//Constructor
{
	ht = new HashTable<string,string>(size);
}

PassServer::~PassServer() //Destructor
{
	ht -> clear();
	delete ht;
}

bool PassServer::load(const char *filename) //Load a password f
{
	
	if(!ht -> load(filename))
	{
		std::cout << "Error: Loading file entry is incorrect\n";
		return false;
	}
	else 
		return ht -> load(filename);
}

bool PassServer::addUser(std::pair<string, string> & kv) //Add new username and password
{
	
	if(find(kv.first))
	{
		cout << "\n*****Error: User already exists. Could not add user.";
		return false;
	}
	else 
	{
		kv.second = encrypt(kv.second);
		std::cout << "\nUser " << kv.first << " added.";
		ht -> insert(kv);
		return true;
	}
}

bool PassServer::addUser(std::pair<string, string> && kv) //move version of addUser
{
	
	if(find(kv.first))
	{
		cout << "\n*****Error: User already exists. Could not add user.";
		return false;
	}
	else 
	{
		kv.second = encrypt(kv.second);
		std::cout << "\nUser " << kv.first << " added.";
		ht -> insert(std::move(kv));
		return true;
	}
}
bool PassServer::removeUser(const string & k) //Delete an existing user with username k
{
	if(find(k))
	{
		
		if(ht -> remove(k))
		{
			std::cout << "\nUser " << k << " deleted."; 
			return true;
		}
	}
	else 
	{
		cout << "*****Error: User not found.  Could not delete user";
		return false;
	} 
}	

	
//Change an existing password
bool PassServer::changePassword(const pair<string, string> &p, const string & newpassword)
{
	string password;
	
	if(!find(p.first))
	{
		std::cout << "*****Error: Could not change user password";
		return false;
	}
	else if(newpassword == p.second)
	{
		std::cout << "*****Error: Could not change user password";
		return false;
	}
	else if(!ht -> match(make_pair(p.first, encrypt(p.second))))
	{
		std::cout << "*****Error: Could not change user password";
		return false;
	}
	else
	{
		password = encrypt(newpassword);
		
		ht -> insert(make_pair(p.first, password));
		
		std::cout << "Password changed for user " << p.first;
		return true;
	}
}
					
bool PassServer::find(const string & user) //Check if user exists
{
	return ht -> contains(user);
}

void PassServer::dump() //Show structure and content of hashtable
{
	ht -> dump();
}

size_t PassServer::size() //Return size of hashtable
{
	return ht -> size();
}

bool PassServer::write_to_file(const char *filename)//Save the username and password into file
{
	return ht -> write_to_file(filename);
}
				
				
string PassServer::encrypt(const string & str)
{
	char salt[] = "$1$########";
	char * pass;
	pass = crypt(str.c_str(),salt);
	string ps(pass);
	size_t found = ps.find_last_of('$');
	ps = ps.substr(found + 1);
	
	return ps;
}
	
