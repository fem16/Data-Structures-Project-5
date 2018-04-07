#include "passserver.h"

PassServer::PassServer(size_t size)//Constructor
{
	ht = new HashTable(size);
}

~PassServer() //Destructor
{
	ht -> clear();
	delete ht;
}

bool load(const char *filename) //Load a password f
{
	ht -> load(filename);
}

bool addUser(std::pair<string, string> & kv) //Add new username and password
{
	if(!ht -> insert(kv))
		cout << "User already Exists!"
	else 
		return true;
}

bool addUser(std::pair<string, string> && kv) //move version of addUser
{
	if(!ht -> insert(std::move(kv)))
		cout << "User already Exists!"
	else 
		return true;
}
bool removeUser(const string & k) //Delete an existing user with username k
{
	if(!ht -> remove(k))
		cout << "User does not exist";
	else 
		return true;
}	

	
//Change an existing password
bool changePassword(const pair<string, string> &p, const string & newpassword)
{
	
				
bool find(const string & user); //Check if user exists
void dump(); //Show structure and content of hashtable
size_t size(); //Return size of hashtable
bool write_to_file(const char *filename); //Save the username and password into file
				
				
string encrypt(const string & str);