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
	ht -> load(filename);
}

bool PassServer::addUser(std::pair<string, string> & kv) //Add new username and password
{
	if(!ht -> insert(kv))
		cout << "User already Exists!";
	else 
	{
		ht -> insert(kv);
		return true;
	}
}

bool PassServer::addUser(std::pair<string, string> && kv) //move version of addUser
{
	if(!ht -> insert(std::move(kv)))
		cout << "User already Exists!";
	else 
	{
		ht -> insert(std::move(kv));
		return true;
	}
}
bool PassServer::removeUser(const string & k) //Delete an existing user with username k
{
	if(!ht -> remove(k))
		cout << "User does not exist";
	else 
	{
		ht -> remove(k);
		return true;
	} 
}	

	
//Change an existing password
bool PassServer::changePassword(const pair<string, string> &p, const string & newpassword)
{
	string password;
	
	if(!ht -> match(p))
		return false;
	else if(newpassword == p.second)
		return false;
	else
	{
		password = encrypt(newpassword);
		
		ht -> insert(make_pair(p.first, password));
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
	
