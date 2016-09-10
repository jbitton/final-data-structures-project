#ifndef CLIENT_INFO
#define CLIENT_INFO

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class BST_Node  //node in a BST
{
  public:

    string lastname, firstname, address, phone_number;

    BST_Node  *lchild, *rchild;   //left and right children pointers
};

class Clients_Info_BST //Binary Search Tree
{
   public:
	   //default constructor
        Clients_Info_BST();
		//copy constructor
        Clients_Info_BST(const Clients_Info_BST &);
		//destructor
        ~Clients_Info_BST();
		//copy assignment operator
		Clients_Info_BST & operator=(const Clients_Info_BST & item);
		//copy function
		void Copy(BST_Node * & copy, BST_Node * source);
		//insert function -- calls aux func
        void Insert(const string & s);
		//real insert function
		void Insert_Aux(BST_Node * & loc_ptr, const string & s);
		//remove function -- calls aux func
        void Remove(const string & s);
		//real remove function - by name
		void Remove_Aux(BST_Node * & loc_ptr, const string & s);
		//remove a leaf -- for destructor
		void RemoveForDtor(BST_Node * & loc_ptr);
		//inorder succession function
		BST_Node * Inorder_Succ(BST_Node * loc_ptr);
		// update function -- calls aux func
        void Update(const string & s);
		//real update function
		void Update_Aux(BST_Node * loc_ptr, const string & s);
		//print function -- calls aux func
		void Print();
		//real print function (screen)
		void Print_Aux(BST_Node * loc_ptr);
		//print function -- calls aux func
		void Print_to_File(ofstream & myfile);
		//real print function (file)
		void Print_to_File_Aux(BST_Node * loc_ptr, ofstream & myfile);
		//search function -- calls aux func
        BST_Node * Search(const string & s);
		//real search function
		BST_Node * Search_Aux(BST_Node * loc_ptr, const string & s);
		//count nodes
		int countInt();
		//count nodes aux
		int countInt_aux(BST_Node * loc_ptr);

    private:
       BST_Node *root; //---state information
};

#endif
