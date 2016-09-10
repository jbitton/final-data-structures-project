#ifndef CLIENT_ADDRESS_BOOK
#define CLIENT_ADDRESS_BOOK

#include <iostream>
#include <iomanip>
#include <string>
#include "client_info.h"
using namespace std;

class Client_Address_Book
{
	public:
		 //default constructor - will read data from input file "client_address_data.txt".
		Client_Address_Book();
		//copy constructor
		Client_Address_Book(const Client_Address_Book &);
		//destructor
		~Client_Address_Book();
		//insert record
		void Insert(const string & s);
		//remove record
		void Remove(const string & s);
		//update record
		void Update(const string & s);
		//print function - bst
		void Print_BST(const string & s);
		//print function - hash table (screen)
		void Print_Hash_Table();
		///print function - hash table (output file)
		void Print_Hash_Table_to_File(const string & filename);                                                                                                                                                                              
		//search function
		BST_Node * Search(const string & s);
		//hash function
		unsigned int Hash_Function(const string & s);
		//counts nodes
		int countInts(const string &s);

  private:
      int capacity;  //SET THIS VALUE EQUAL TO 27  YOUR DEFAULT CONSTRUCTOR
	  Clients_Info_BST *hash_table; // USING 1 THROUGH 26 or whatever you like
};

#endif
