#include "passserver.h"

PassServer::PassServer(size_t size)//Constructor
{
	ht(size);
}

PassServer::~PassServer() //Destructor
{
	ht.clear();
	delete ht;
}

bool PassServer::load(const char *filename) //Load a password f
{
	ht -> load(filename);
}

bool PassServer::addUser(std::pair<string, string> & kv) //Add new username and password
{
	if(!ht.insert(kv))
		cout << "User already Exists!"
	else 
	{
		ht.insert(kv);
		return true;
	}
}

bool PassServer::addUser(std::pair<string, string> && kv) //move version of addUser
{
	if(!ht.insert(std::move(kv)))
		cout << "User already Exists!"
	else 
	{
		ht.insert(std::move(kv));
		return true;
	}
}
bool PassServer::removeUser(const string & k) //Delete an existing user with username k
{
	if(!ht.remove(k))
		cout << "User does not exist";
	else 
	{
		ht.remove(k);
		return true;
	} 
}	

	
//Change an existing password
bool PassServer::changePassword(const pair<string, string> &p, const string & newpassword)
{
	if(!ht.contains(p))
		return false;
	else if(newpassword == p.second)
		return false;
	else
	{
		newpassword = encrypt(newpassword);
		
		ht.insert(newpassword);
	}
}
					
bool PassServer::find(const string & user) //Check if user exists
{
	return ht.contains(user);
}

void PassServer::dump() //Show structure and content of hashtable
{
	ht.dump();
}

size_t PassServer::size() //Return size of hashtable
{
	return ht.size();
}

bool write_to_file(const char *filename)//Save the username and password into file
{
	return ht.write_to_file(filename);
}
				
				
string encrypt(const string & str)
{
	char salt[] = "$1$########";
	
	string pass = crypt(str,salt);
	size_t found = pass.find_last_of('$');
	pass = pass.substr(found + 1);
	
	return pass;
}
	