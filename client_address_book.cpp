#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include "client_info.h"
#include "client_address_book.h"
using namespace std;

//*************************************************************************************
//Name: Client_Address_Book
//Precondition: The state of the object (private data) has not been initialized
//Postcondition: The private attributes have been initialized to a default value
//Description:  This is the default constructor which will be called automatically when 
//an object is declared.  It will initialize the state of the class
//
//*************************************************************************************
Client_Address_Book::Client_Address_Book()
{
	capacity = 27;

	hash_table = new Clients_Info_BST[capacity];

	string line;

	ifstream myfile;
	myfile.open("client_address_data.txt");

	while (getline(myfile, line))
	{
		Insert(line);
	}

	myfile.close();
}

//*************************************************************************************
//Name: Client_Address_Book
//Precondition: The private data of the new object has not been initialized.
//Postcondition: The private data of an existing object has been copied to a
// new object (by deep copy)
//Description: A copy constructor is a special constructor that creates a new object
//as a copy of an existing object by the form of a deep copy. A deep copy is needed 
//because there is a pointer/dynamic memory in the private attributes of the class.
//
//*************************************************************************************
Client_Address_Book::Client_Address_Book(const Client_Address_Book & original)
{
	capacity = original.capacity;

	hash_table = new Clients_Info_BST[capacity];

	for (int i = 0; i < capacity; i++)
	{
		hash_table[i] = original.hash_table[i];
	}
}

//*************************************************************************************
//Name: ~Client_Address_Book
//Precondition: An object exists with valid private attributes
//Postcondition: The object is destroyed
//Description: The destructor is automatically invoked when an object goes out of 
//scope. There is especially a need for a destructor when you are dealing with a 
//pointer/dynamic memory in the private data of the class because you must avoid
//memory leak.
//
//*************************************************************************************
Client_Address_Book::~Client_Address_Book()
{
	delete [] hash_table;
}

//*************************************************************************************
//Name: Insert
//Precondition: A string is properly initialized
//Postcondition: A new node is added to the BST based on the first letter of
//the last name.
//Description: Adds a node to the BST based on the first letter of the last
//name passed in the string.
//
//*************************************************************************************
void Client_Address_Book::Insert(const string & s)
{
	hash_table[Hash_Function(s)].Insert(s);
}

//*************************************************************************************
//Name: Remove
//Precondition: A string and a Client_Address_Book object is properly initialized
//Postcondition: A node is removed from the BST based on the first letter of the last
//name if found.
//Description: Removes a node from the BST the first letter of the last name in the
//string passed if found.
//
//*************************************************************************************
void Client_Address_Book::Remove(const string & s)
{
	hash_table[Hash_Function(s)].Remove(s);
}

//*************************************************************************************
//Name: Update
//Precondition: A Client_Address_Book function is properly initialized
//Postcondition: A node in one Clients_Info_BST object is altered
//Description: This function updates the information stored inside one BST node 
//depending on what change needs to be made [what number they specify]
//
//*************************************************************************************
void Client_Address_Book::Update(const string & s)
{
	string a = s.substr(0);
	string num, lastname1, firstname1, lastname2, firstname2, address, phone_number;
	int loc = -1;

	num = a.substr(0, 1);
	a = a.substr(2);

	for (unsigned int i = 0; i < a.length(); i++)
	{
		if (a[i] == ' ')
		{
			loc = i;
			break;
		}
	}

	lastname1 = a.substr(0, loc);
	a = a.substr(loc + 1);

	for (unsigned int i = 0; i < a.length(); i++)
	{
		if (a[i] == ' ')
		{
			loc = i;
			break;
		}
	}

	firstname1 = a.substr(0, loc);
	a = a.substr(loc + 1);

	if (num == "5")
	{
		a += " ";
	}

	if (num == "1" || num == "2" || num == "4" || num == "5")
	{
		for (unsigned int i = 0; i < a.length(); i++)
		{
			if (a[i] == ' ')
			{
				loc = i;
				break;
			}
		}

		lastname2 = a.substr(0, loc);
		a = a.substr(loc + 1);

		for (unsigned int i = 0; i < a.length(); i++)
		{
			if (a[i] == ' ')
			{
				loc = i;
				break;
			}
		}

		firstname2 = a.substr(0, loc);
		a = a.substr(loc + 1);

		if (num == "1")
		{
			hash_table[Hash_Function(lastname1)].Remove(lastname1 + " " + firstname1);
			hash_table[Hash_Function(lastname2)].Insert(lastname2 + " " + firstname2 + " " + a.substr(0));
		}
		else if (num == "2")
		{
			BST_Node *p = hash_table[Hash_Function(lastname1)].Search(lastname1 + " " + firstname1);

			if (p != 0)
			{
				phone_number = p->phone_number;

				hash_table[Hash_Function(lastname1)].Remove(lastname1 + " " + firstname1);
				hash_table[Hash_Function(lastname2)].Insert(lastname2 + " " + firstname2 + " " + a.substr(0) + " " + phone_number);
			}
		}
		else if (num == "4")
		{
			BST_Node *p = hash_table[Hash_Function(lastname1)].Search(lastname1 + " " + firstname1);

			if (p != 0)
			{
				address = p->address;

				hash_table[Hash_Function(lastname1)].Remove(lastname1 + " " + firstname1);
				hash_table[Hash_Function(lastname2)].Insert(lastname2 + " " + firstname2 + " " + address + " " + a.substr(0));
			}
		}
		else if (num == "5")
		{
			BST_Node *p = hash_table[Hash_Function(lastname1)].Search(lastname1 + " " + firstname1);

			if (p != 0)
			{
				address = p->address;
				phone_number = p->phone_number;

				hash_table[Hash_Function(lastname1)].Remove(lastname1 + " " + firstname1);
				hash_table[Hash_Function(lastname2)].Insert(lastname2 + " " + firstname2 + " " + address + " " + phone_number);
			}
		}
	}
	else if (num == "3" || num == "6" || num == "7")
	{
		hash_table[Hash_Function(lastname1)].Update(s);
	}
}

//*************************************************************************************
//Name: Print_BST
//Precondition: A Clients_Address_Book and Clients_Info_BST object are declared and
//initialized properly.
//Postcondition: One index of a Client_Address_Book object is printed.
//Description: Prints a Clients_Info_BST object.
//
//*************************************************************************************
void Client_Address_Book::Print_BST(const string & s)
{
	cout << "Last Name      First Name     Address                   Phone Number" << endl;
	cout << "--------------------------------------------------------------------" << endl;

	hash_table[Hash_Function(s)].Print();
}

//*************************************************************************************
//Name: Print_Hash_Table
//Precondition: A Client_Address_Book object is declared and initialized properly.
//Postcondition: The entire Client_Address_Book object is printed.
//Description: Prints a Client_Address_Book object.
//
//*************************************************************************************
void Client_Address_Book::Print_Hash_Table()
{
	cout << "Printing out entire hash table..." << endl;

	cout << "Last Name      First Name     Address                   Phone Number" << endl;
	cout << "--------------------------------------------------------------------" << endl;

	for (int i = 0; i < capacity; i++)
	{
		hash_table[i].Print();
	}

	cout << endl << endl;
}

//*************************************************************************************
//Name: Print_Hash_Table_to_File
//Precondition: A Client_Address_Book object is declared and initialized properly.
//Postcondition: The entire Client_Address_Book object is printed to a file.
//Description: Prints a Client_Address_Book object to a file.
//
//*************************************************************************************
void Client_Address_Book::Print_Hash_Table_to_File(const string & filename)     
{
	ofstream myfile;
	myfile.open(filename);

	myfile << "Last Name      First Name     Address                   Phone Number" << endl;
	myfile << "--------------------------------------------------------------------" << endl;

	for (int i = 0; i < capacity; i++)
	{
		hash_table[i].Print_to_File(myfile);
	}

	myfile.close();
}

//*************************************************************************************
//Name: Search
//Precondition: A Client_Address_Book object and a string are properly initialized
//Postcondition: No change to the object is made. The function returns the location of
//the item within the BST. If not found, the function returns -1.
//Description: This function traverses the BST in order to find a certain node and
//returns the location in which it is found. If not found, the function returns -1.
//
//*************************************************************************************
BST_Node * Client_Address_Book::Search(const string & s)
{
	cout << "Inside Client_Address_Book Search\n";
	return hash_table[Hash_Function(s)].Search(s);
}

//*************************************************************************************
//Name: Hash_Function
//Precondition: A Client_Address_Book object and a string are properly initialized
//Postcondition: No change to the object is made. The function returns the index of
//the hash table that should be used
//Description: This function returns which index of the BST should be used for the
//specified string
//
//*************************************************************************************
unsigned int Client_Address_Book::Hash_Function(const string & s)
{
	return s[0] - 64;
}

int Client_Address_Book::countInts(const string & s)
{
	return hash_table[Hash_Function(s)].countInt();
}
