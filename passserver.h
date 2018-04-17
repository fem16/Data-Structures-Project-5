#ifndef PASSSERVER_H
#define PASSSERVER_H

#include "hashtable.h"
#include <iostream>
#include <fstream>
#include <string>
#include <crypt.h>
#include <unistd.h>


using namespace cop4530;
using namespace std;

class PassServer
{
	public:
		PassServer(size_t size = 101); //Constructor
		~PassServer();	//Destructor
		bool load(const char *filename); //Load a password file into hashtable
		bool addUser(std::pair<string, string> & kv); //Add new username and password
		bool addUser(std::pair<string, string> && kv); //move version of addUser
		bool removeUser(const string & k); //Delete an existing user with username k
		
		//Change an existing password
		bool changePassword(const pair<string, string> &p, const string & newpassword);
		
		bool find(const string & user); //Check if user exists
		void dump(); //Show structure and content of hashtable
		size_t size(); //Return size of hashtable
		bool write_to_file(const char *filename); //Save the username and password into file
		
		
	private:
		string encrypt(const string & str);
		cop4530::HashTable<string, string> * ht;
};
#endif

