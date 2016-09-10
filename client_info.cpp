#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include "client_info.h"
using namespace std;

//*************************************************************************************
//Name: Clients_Info_BST
//Precondition: The state of the object (private data) has not been initialized
//Postcondition: The private attributes have been initialized to a default value
//Description:  This is the default constructor which will be called automatically when 
//an object is declared.  It will initialize the state of the class
//
//*************************************************************************************
Clients_Info_BST::Clients_Info_BST() 
{
	root = 0;
}

//*************************************************************************************
//Name: Client_Info_BST
//Precondition: The private data of the new object has not been initialized.
//Postcondition: The private data of an existing object has been copied to a
// new object (by deep copy)
//Description: A copy constructor is a special constructor that creates a new object
//as a copy of an existing object by the form of a deep copy. A deep copy is needed 
//because there is a pointer/dynamic memory in the private attributes of the class.
//
//*************************************************************************************
Clients_Info_BST::Clients_Info_BST(const Clients_Info_BST & key) //Copy Constructor
{
	while(root != 0)
		RemoveForDtor(root);

	Copy(root, key.root);
}

//*************************************************************************************
//Name: ~Clients_Info_BST
//Precondition: An object exists with valid private attributes
//Postcondition: The object is destroyed
//Description: The destructor is automatically invoked when an object goes out of 
//scope. There is especially a need for a destructor when you are dealing with a 
//pointer/dynamic memory in the private data of the class because you must avoid
//memory leak.
//
//*************************************************************************************
Clients_Info_BST::~Clients_Info_BST() //Destructor
{
	while (root != 0)
		RemoveForDtor(root);
}

//*************************************************************************************
//Name: operator =
//Precondition: A Clients_Info_BST object has been declared and initialized properly 
//and the string passed is a valid string.
//Postcondition: A Clients_Info_BST object is a copy of item (copied deeply).
//Description: Copies a Clients_Info_BST object into another Clients_Info_BST object
//through =.
//
//*************************************************************************************
Clients_Info_BST & Clients_Info_BST::operator=(const Clients_Info_BST & item)
{
	while (root != 0)
	{
		Remove(item.root->lastname + " " + item.root->firstname);
	}

	Copy(root, item.root);
	return *this;
}

//*************************************************************************************
//Name: Copy
//Precondition: The private data of the new object has not been initialized.
//Postcondition: The private data of an existing object has been copied to a
// new object (by deep copy)
//Description: Copies a Clients_Info_BST object
//
//*************************************************************************************
void Clients_Info_BST::Copy(BST_Node * & copy, BST_Node * source)
{
	if (source == 0)
	{
		copy = 0;
	}
	else
	{
		copy = new BST_Node;
		copy->lastname = source->lastname;
		copy->firstname = source->firstname;
		copy->address = source->address;
		copy->phone_number = source->phone_number;

		Copy(copy->lchild, source->lchild);
		Copy(copy->rchild, source->rchild);
	}
}

//*************************************************************************************
//Name: Insert
//Precondition: A string variable is properly initialized
//Postcondition: "s" is inserted at the proper location in the sorted BST
//Description: This function inserts the string passed to the proper location in the 
//sorted BST
//
//*************************************************************************************
void Clients_Info_BST::Insert(const string & s)
{
	Insert_Aux(root, s);
};

//*************************************************************************************
//Name: Insert_Aux
//Precondition: Insert is called
//Postcondition: "s" is inserted at the proper location in the sorted BST
//Description: This function inserts the string passed to the proper location in the 
//sorted BST
//
//*************************************************************************************
void Clients_Info_BST::Insert_Aux(BST_Node * & loc_ptr, const string & s)
{
	string a = s.substr(0);
	string lastname, firstname, address, phone_number;
	int loc = -1;

	for (unsigned int i = 0; i < a.length(); i++)
	{
		if (a[i] == ' ')
		{
			loc = i;
			break;
		}
	}

	lastname = a.substr(0, loc);
	a = a.substr(loc + 1);

	for (unsigned int i = 0; i < a.length(); i++)
	{
		if (a[i] == ' ')
		{
			loc = i;
			break;
		}
	}

	firstname = a.substr(0, loc);
	a = a.substr(loc + 1);

	address = a.substr(0, a.length() - 9);
	phone_number = a.substr(a.length() - 8);


	if (loc_ptr == 0)
	{
		loc_ptr = new BST_Node;
		loc_ptr->lchild = loc_ptr->rchild = 0;
		loc_ptr->lastname = lastname;
		loc_ptr->firstname = firstname;
		loc_ptr->address = address;
		loc_ptr->phone_number = phone_number;
	}
	else if (loc_ptr->lastname > lastname)
	{
		Insert_Aux(loc_ptr->lchild, s);
	}
	else if (loc_ptr->lastname < lastname)
	{
		Insert_Aux(loc_ptr->rchild, s);
	}
	else if (loc_ptr->lastname == lastname && loc_ptr->firstname > firstname)
	{
		Insert_Aux(loc_ptr->lchild, s);
	}
	else if (loc_ptr->lastname == lastname && loc_ptr->firstname < firstname)
	{
		Insert_Aux(loc_ptr->rchild, s);
	}
	else if (loc_ptr->lastname == lastname && loc_ptr->firstname == firstname)
	{
		cout << "the item is already in the tree\n";
	}
}


//*************************************************************************************
//Name: Remove
//Precondition: A Clients_Info_BST object has been declared and initialized properly
//Postcondition: The specified node is deleted while still maintaining order
//Description: This function removes the specified node while still maintaining order
//
//*************************************************************************************
void Clients_Info_BST::Remove(const string & s)
{
	Remove_Aux(root, s);
}

//*************************************************************************************
//Name: Remove_Aux
//Precondition: Remove is called
//Postcondition: The specified node is deleted while still maintaining order
//Description: This function removes the specified node while still maintaining order
//
//*************************************************************************************
void Clients_Info_BST::Remove_Aux(BST_Node * & loc_ptr, const string & s)
{
	if (loc_ptr == 0)
	{
		cout << "item not in tree\n";
	}
	else
	{
		string name = loc_ptr->lastname + " " + loc_ptr->firstname;

		if (name > s)
			Remove_Aux(loc_ptr->lchild, s);
		else if (name < s)
			Remove_Aux(loc_ptr->rchild, s);
		else if (name == s)
		{
			BST_Node * ptr;

			if ((loc_ptr->lchild == 0) && (loc_ptr->rchild == 0))
			{
				delete loc_ptr;
				loc_ptr = 0;
			}
			else if (loc_ptr->lchild == 0)
			{
				ptr = loc_ptr->rchild;
				delete loc_ptr;
				loc_ptr = ptr;
			}
			else if (loc_ptr->rchild == 0)
			{
				ptr = loc_ptr->lchild;
				delete loc_ptr;
				loc_ptr = ptr;
			}
			else
			{
				ptr = Inorder_Succ(loc_ptr);
				loc_ptr->lastname = ptr->lastname;
				loc_ptr->firstname = ptr->firstname;
				loc_ptr->address = ptr->address;
				loc_ptr->phone_number = ptr->phone_number;
				Remove_Aux(loc_ptr->rchild, ptr->lastname + " " + ptr->firstname);
			}
		}
	}
}

//*************************************************************************************
//Name: RemoveForDtor
//Precondition: A Clients_Info_BST object has been declared and initialized properly
//Postcondition: Deletes a leaf of a BST
//Description: This function removes leaves of a BST
//
//*************************************************************************************
void Clients_Info_BST::RemoveForDtor(BST_Node * & loc_ptr)
{
	if (loc_ptr == 0)
	{
		cout << "Error: tree is empty\n";
	}
	else
	{
		if ((loc_ptr->lchild == 0) && (loc_ptr->rchild == 0))
		{
			delete loc_ptr;
			loc_ptr = 0;
		}
		else if (loc_ptr->lchild != 0)
		{
			RemoveForDtor(loc_ptr->lchild);
		}
		else if (loc_ptr->rchild != 0)
		{
			RemoveForDtor(loc_ptr->rchild);
		}
	}
}

//*************************************************************************************
//Name: Inorder_Succ
//Precondition: A Clients_Info_BST object is initialized properly
//Postcondition: The node that is the inorder successor of the node passed is returned.
//Description: Returns the node that is the inorder successor of the node passed.
//
//*************************************************************************************
BST_Node * Clients_Info_BST::Inorder_Succ(BST_Node * loc_ptr)
{
	BST_Node *ptr = loc_ptr->rchild;

	while (ptr->lchild != 0)
	{
		ptr = ptr->lchild;
	}
	return ptr;
}

//*************************************************************************************
//Name: Update
//Precondition: A Client_Address_Book function is properly initialized
//Postcondition: A node in one Clients_Info_BST object is altered
//Description: This function updates the information stored inside one BST node 
//depending on what change needs to be made [what number they specify]
//
//*************************************************************************************
void Clients_Info_BST::Update(const string & s)
{
	Update_Aux(root, s);
}

//*************************************************************************************
//Name: Update_Aux
//Precondition: Update is called
//Postcondition: A node in one Clients_Info_BST object is altered
//Description: This function updates the information stored inside one BST node 
//depending on what change needs to be made [what number they specify]
//
//*************************************************************************************
void Clients_Info_BST::Update_Aux(BST_Node * loc_ptr, const string & s)
{
	string a = s.substr(0);
	string num, lastname, firstname, address, phone_number;
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

	lastname = a.substr(0, loc);
	a = a.substr(loc + 1);

	for (unsigned int i = 0; i < a.length(); i++)
	{
		if (a[i] == ' ')
		{
			loc = i;
			break;
		}
	}

	firstname = a.substr(0, loc);
	a = a.substr(loc + 1);


	if (num == "3")
	{
		address = a.substr(0, a.length() - 9);
		phone_number = a.substr(a.length() - 8);

		BST_Node *p = Search(lastname + " " + firstname);

		if (p != 0)
		{
			p->phone_number = phone_number;
			p->address = address;
		}
	}
	else if (num == "6")
	{
		address = a.substr(0);

		BST_Node *p = Search(lastname + " " + firstname);

		if (p != 0)
		{
			p->address = address;
		}
	}
	else if (num == "7")
	{
		phone_number = a.substr(0);

		BST_Node *p = Search(lastname + " " + firstname);

		if (p != 0)
		{
			p->phone_number = phone_number;
		}
	}
}

//*************************************************************************************
//Name: Print
//Precondition: A Clients_Info_BST object is declared and initialized properly.
//Postcondition: A Clients_Info_BST object is printed.
//Description: Prints a Clients_Info_BST object.
//
//*************************************************************************************
void Clients_Info_BST::Print()
{
	Print_Aux(root);
}

//*************************************************************************************
//Name: Print_Aux
//Precondition: Print is called
//Postcondition: A Clients_Info_BST object is printed.
//Description: Prints a Clients_Info_BST object.
//
//*************************************************************************************
void Clients_Info_BST::Print_Aux(BST_Node * loc_ptr)
{
	if (loc_ptr != 0)
	{
		Print_Aux(loc_ptr->lchild);
		cout << left << setw(15) << loc_ptr->lastname;
		cout << left << setw(15) << loc_ptr->firstname;
		cout << left << setw(30) << loc_ptr->address;
		cout << left << setw(8) << loc_ptr->phone_number << endl;
		Print_Aux(loc_ptr->rchild);
	}
}

//*************************************************************************************
//Name: Print_to_File
//Precondition: A Clients_Info_BST object is declared and initialized properly.
//Postcondition: A Clients_Info_BST object is printed to a file.
//Description: Prints a Clients_Info_BST object to a file.
//
//*************************************************************************************
void Clients_Info_BST::Print_to_File(ofstream & myfile)
{
	Print_to_File_Aux(root, myfile);
}

//*************************************************************************************
//Name: Print_to_File_Aux
//Precondition: Print_to_File is called
//Postcondition: A Clients_Info_BST object is printed to a file.
//Description: Prints a Clients_Info_BST object to a file.
//
//*************************************************************************************
void Clients_Info_BST::Print_to_File_Aux(BST_Node * loc_ptr, ofstream & myfile)
{
	if (loc_ptr != 0)
	{
		Print_to_File_Aux(loc_ptr->lchild, myfile);
		myfile << left << setw(15) << loc_ptr->lastname;
		myfile << left << setw(15) << loc_ptr->firstname;
		myfile << left << setw(30) << loc_ptr->address;
		myfile << left << setw(8)  << loc_ptr->phone_number << endl;
		Print_to_File_Aux(loc_ptr->rchild, myfile);
	}
}

//*************************************************************************************
//Name: Search
//Precondition: A Clients_Info_BST is properly initialized
//Postcondition: No change to the object is made. The function returns the location of
//the item within the BST. If not found, the function returns -1.
//Description: This function traverses the BST in order to find a certain node and
//returns the location in which it is found. If not found, the function returns -1.
//
//*************************************************************************************
BST_Node * Clients_Info_BST::Search(const string & s)
{
	return Search_Aux(root, s);
}

//*************************************************************************************
//Name: Search_Aux
//Precondition: Search is called
//Postcondition: No change to the object is made. The function returns the location of
//the item within the BST. If not found, the function returns -1.
//Description: This function traverses the BST in order to find a certain node and
//returns the location in which it is found. If not found, the function returns -1.
//
//*************************************************************************************
BST_Node * Clients_Info_BST::Search_Aux(BST_Node * loc_ptr, const string & s)
{
	string a = s.substr(0);
	string lastname, firstname;
	int loc = -1;

	for (unsigned int i = 0; i < a.length(); i++)
	{
		if (a[i] == ' ')
		{
			loc = i;
			break;
		}
	}

	lastname = a.substr(0, loc);
	a = a.substr(loc + 1);

	for (unsigned int i = 0; i < a.length(); i++)
	{
		if (a[i] == ' ')
		{
			loc = i;
			break;
		}
	}

	firstname = a.substr(0);


	if (loc_ptr != 0)
	{
		if (loc_ptr->lastname == lastname && loc_ptr->firstname == firstname)
		{
			return loc_ptr;
		}
		else if (loc_ptr->lastname > lastname)
		{
			return Search_Aux(loc_ptr->lchild, s);
		}
		else if (loc_ptr->lastname < lastname)
		{
			return Search_Aux(loc_ptr->rchild, s);
		}
		else if (loc_ptr->lastname == lastname && loc_ptr->firstname > firstname)
		{
			return Search_Aux(loc_ptr->lchild, s);
		}
		else //if (loc_ptr->lastname == lastname && loc_ptr->firstname < firstname)
		{
			return Search_Aux(loc_ptr->rchild, s);
		}
	}
	else
	{
		return loc_ptr;
	}
}

int Clients_Info_BST::countInt()
{
	return countInt_aux(root);
}

int Clients_Info_BST::countInt_aux(BST_Node * loc_ptr)
{
	int count = 0;
	bool wasHere = false;

	if (loc_ptr == 0)
	{
	}
	else
	{
		if ((loc_ptr->lchild == 0) && (loc_ptr->rchild == 0))
		{
		}
		
		if (loc_ptr->lchild != 0)
		{
			count++;
			count += countInt_aux(loc_ptr->lchild);
			wasHere = true;
		}

		if (loc_ptr->rchild != 0)
		{
			if (!wasHere)
				count++;

			count += countInt_aux(loc_ptr->rchild);
		}
	}
	
	return count;

}