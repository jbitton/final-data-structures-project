#include <iostream>
#include <iomanip>
#include <string>
#include "client_info.h"
#include "client_address_book.h"
using namespace std;

int main()
{
	Client_Address_Book My_Book;
	cout << "before insert: " << endl;
	My_Book.Print_BST("Z");
	cout << endl;
	int count = My_Book.countInts("Z");
	cout << "This BST has " << count << " internal nodes" << endl;
	My_Book.Insert("Bullard Lofton 777 Glades Road 207-2780");
	cout << endl << "after insert: " << endl;
	My_Book.Print_BST("B");
	cout << endl << "before remove: " << endl;
	My_Book.Print_BST("H");
	My_Book.Remove("Harper Babara");
	cout << endl << "after remove: " << endl;
	My_Book.Print_BST("H");
	cout << endl;

	/*******************************************************************************
	Notes for Update Function:

	1.  My_Book_Update(g1 James Clark Lofton Bullard 777 Glades Run 527-6623h);
	If first character is a 1, this means all three fields will be changed.
	2.   My_Book_Update(g2 James Clark Lofton Bullard 777 Glades Runh);
	If first character is a 2, this means the Name and Address fields will be changed.
	3.   My_Book_Update(g3 James Clark 777 Glades Run 555-6666h);
	If first character is a 3, this means the Address and Phone Number fields will be changed.
	4.   My_Book_Update(g4 James Clark Lofton Bullard 555-6666h);
	If first character is a 4, this means the Name and Phone Number fields will be changed.
	5.   My_Book_Update(g5 James Clark Lofton Bullardh);
	If first character is a 5, this means the Name field will be changed.
	6.   My_Book_Update(g6 James Clark 777 Glades Runh);
	If first character is a 6, this means the Address field will be changed.
	7.   My_Book_Update(g7 James Clark 555-6666h);
	If first character is a 7, this means the Phone Number field will be changed.

	********************************************************************************/

	cout << endl << "before update: " << endl;
	My_Book.Print_BST("B");
	cout << endl << endl;
	My_Book.Print_BST("C");
	cout << endl;
	My_Book.Update("1 Bullard Lofton Comb Harry 555 Palmetto Park Road 555-3444");
	cout << endl << "after update: " << endl;
	My_Book.Print_BST("B");
	cout << endl << endl;
	My_Book.Print_BST("C");
	cout << endl << endl;
	My_Book.Print_Hash_Table();
	My_Book.Print_Hash_Table_to_File("sortbst_client_data.txt");

	Client_Address_Book Your_Book = My_Book; //Invoke the copy constructor
	Your_Book.Print_Hash_Table();
	Your_Book.Print_Hash_Table_to_File("sorted_client_address_bk.txt");
	return 0;
}