//*******************************************************************************************************************************************************************//
//***************************************************************************************************************************//
//																															*//
// File name : BSTMUSIC.cpp																									*//
//																															*//
// Author: Ajinkya Nawarkar    		                	 date created: 09 / 25 / 2016										*//
//														 last updated : 11 / 21 / 2016										*//
//																															*//
// Program Description : This program defines two classes with respective methods and one main function as follows:			*//
//																															*//
//  1. BST class: This class defines node structure which stores the nodes with objects of movie class and also defines		*//
//                other methods which implement the Movie Database Application.												*//
//																															*//
//  2. Movie class: This class defines objects which store all the information of all the movies read in from the text file	*//
//                and define methods which return the required values which the objects point to.							*//
//																															*//
//  3. The populate tree methods reads a list of all movies from a text file. The data of all movies was retrieved from     *//
//                IMDb website. Can be accesed here --> http://www.imdb.com/list/ls057823854/ 
//***************************************************************************************************************************//
//*********************************************************************************************************************************************************************//


//Binary Search Tree Program

#include <iostream>	 //iostream library included to make its methods accessible
#include <cstdlib>	//cstdlib library included to make its methods accessible
#include <fstream>	//fstream library included to make its methods accessible
#include <istream>	//istream library included to make its methods accessible
#include <iomanip>	//iomanip library included to make its methods accessible
#include <stdio.h>	//stdio library included to make its methods accessible	
#include <string>	//string library included to make its methods accessible

using namespace std;

class movie
{
	//define all the variables required
private:
	string name;
	int year;
	int time;
	float rating;
	//string a[10];

//define all the methods to be used by this class
public:
	movie();
	movie(string name, int year, int time, float rating);
	string getName();
	int getyear();
	int gettime();
	float getrating();
	void setName(string name);
	void setyear(int year);
	void settime(int time);
	void setrating(float rating);
};

class BST
{
//define the structure TreeNode with the rewuired variables
private:
	struct TreeNode
	{
		TreeNode* left;
		TreeNode* right;
		movie data;
	};
	TreeNode* root;

	//define all the methods to be used by this class
public:
	BST()
	{
		root = NULL;
	}

	bool isEmpty() const
	{ 
		return root == NULL;
	}
	void print_tree();
	void printtree(TreeNode*);
	void insert(movie);
	void ddelete(string);
 	void find_by_name(string);
	void find_by_year(int);
	void f_year(TreeNode*, int);
	void find_by_rating(float);
	void f_rating(TreeNode*, float);
	void find_by_duration(int);
	void f_time(TreeNode*, int);
};

//define the constructor
movie::movie()
{
}

//define the constructor with parameters
movie::movie(string name1, int year1, int time1, float rating1)
{
	//initialize all the parmeters
	name = name1;
	time = time1;
	year = year1;
	rating = rating1;
}

//returns name 
string movie::getName()
{
	return name;
}

//returns year of release
int movie::getyear()
{
	return year;
}

//returns the duration of the movie
int movie::gettime()
{
	return time;
}

//returns the rating of the movie
float movie::getrating()
{
	return rating;
}

//resets the name 
void movie::setName(string name1)
{
	name = name1;
}

//resets the year 
void movie::setyear(int year1)
{
	year = year1;
}

//resets the duration 
void movie::settime(int time1)
{
	time = time1;
}

//resets the rating 
void movie::setrating(float rating1)
{
	rating = rating1;
}


//Define the insert method

/********************************************************************
*
* When the insert method is called with an object of movie class 
* as a paramter, the method searches for the correct position 
* by comparing the title of the movie and its ASCII values for 
* each charabter in the title in fact.
*
********************************************************************/

void BST::insert(movie x)
{
	//define the required variables
	TreeNode* y = new TreeNode;
	TreeNode* parent_current;
	y->data = x;
	y->left = NULL;
	y->right = NULL;
	parent_current = NULL;

	//check for new tree?
	if (isEmpty())
		root = y;
	else
	{
		//All insertions are as leaf nodes
		TreeNode* current;
		current = root;
		
		//Find the parent of the node
		while (current)
		{
			parent_current = current;

			if (y->data.getName() > current->data.getName())
				current = current->right;
			else 
				current = current->left;	
		}
		
		//insert the node as a leaf node into the tree
		if (y->data.getName() < parent_current->data.getName())
			parent_current->left = y;
		else 
			parent_current->right = y;
	}
}

//Define the delete method

/********************************************************************
*
* When the ddelete method is called with a string as a paramter,
* the method searches for the parent of the node to be deleted
* by comparing the title of the movie and its ASCII values 
* with each of the movie titles already present in the Tree
*
* Then it checks for the folowing three cases:
*
* 1. Node to be deleted is a leaf node
* 2. Node to be deleted is a one degree node
* 3. Node to be deleted is a two degree node
*
* With each case, the methods implements appropriate steps to
* shift pointers and successfullt delete the given node
*
********************************************************************/

void BST::ddelete(string z)
{

	//Locate the element
	int flag = 0;
	if (isEmpty())
	{
		cout << " This Tree is empty! " << endl;
		return;
	}

	//Define the variables
	TreeNode* current;
	TreeNode* parent;
	current = root;
	parent = NULL;

	//Find the parent of the node to be deleted 
	while (current != NULL)
	{
		if (current->data.getName() == z)
		{
			flag = 1;
			break;
		}
		else
		{
			parent = current;
			if (z < current->data.getName())
				current = current->left;
			else
				current = current->right;
		}
	}

	if (flag == 0)
	{
		cout << " Data not found! " << endl;
		return;
	}

	//1. Removing a leaf node
	if (current->left == NULL && current->right == NULL)
	{
		if (parent->left == current)
			parent->left = NULL;
		else
			parent->right = NULL;
		delete current;	//delete the leaf node
		return;
	}

	// Node with single child
	if ((current->left == NULL && current->right != NULL) || (current->left != NULL
		&& current->right == NULL))
	{
		//find if the node to be deleted has a left or right child
		
		if (current->left != NULL && current->right == NULL)	//left child present, no right child
		{
			if (parent->left == current)
			{
				parent->left = current->left;
				delete current;
			}
			else
			{
				parent->right = current->left;
				delete current;
			}
		}
		else // right child present, no left child
		{
			if (parent->left == current)
			{
				parent->left = current->right;
				delete current;
			}
			else
			{
				parent->right = current->right;
				delete current;
			}
		}
		return;
	}

	//Node with 2 children
	// replace node with smallest value in right subtree
	if (current->left != NULL && current->right != NULL)
	{
		TreeNode* chap;
		chap = current->right;
		if ((chap->left == NULL) && (chap->right == NULL))
		{
			current = chap;
			delete chap;
			current->right = NULL;
		}
		else // right child has children
		{
			//if the node's right child has a left child
			// Move all the way down left to locate smallest element

			if ((current->right)->left != NULL)
			{
				TreeNode* lcurr;
				TreeNode* lcurrp;
				lcurrp = current->right;
				lcurr = (current->right)->left;
				while (lcurr->left != NULL)
				{
					lcurrp = lcurr;
					lcurr = lcurr->left;
				}
				current->data = lcurr->data;
				delete lcurr;
				lcurrp->left = NULL;
			}
			else
			{
				TreeNode* tmp;
				tmp = current->right;
				current->data = tmp->data;
				current->right = tmp->right;
				delete tmp;
			}

		}
		return;
	}

}

//Define the recursive function which makes the recursive calls
void BST::print_tree()
{
	printtree(root);
}

//Define the function which does the inorder traversal
void BST::printtree(TreeNode* t)
{
	if (t != NULL)
	{
		if (t->left)	//Go left
			printtree(t->left);
		
		cout << setw(80) << t->data.getName() << setw(8) << t->data.getyear() << setw(8) << t->data.gettime() << setw(6) << t->data.getrating() << "\t\t\t\t" << endl;

		if (t->right)	//Go right
			printtree(t->right);
	}
	else return;
}

//Define the function which finds all records of a given movie

/********************************************************************
*
* This methods calls a recursive method in turn with the parameter
* passed as the given data by the user. The recursive method finds 
* all the movies which matches the data and prints it
*
********************************************************************/

void BST::find_by_name(string given)
{
	//Locate the element
	int flag = 0;
	if (isEmpty())
	{
		cout << " This Tree is empty! " << endl;
		return;
	}

	TreeNode* current;
	TreeNode* parent;
	current = root;

	while (current != NULL)
	{
		//Print all details of the movie when found
		if (current->data.getName() == given)	//check for the same name and print details
		{
			flag = 1;
			cout << endl << " Title:\t\t\t" << current->data.getName() << endl;
			cout << " Year of release:\t" << current->data.getyear() << endl;
			cout << " Duration:\t\t" << current->data.gettime() << endl;
			cout << " Rating:\t\t" << current->data.getrating() << endl;
			break;
		}
		else
		{
			parent = current;
			if (given < current->data.getName())
				current = current->left;	//Go left
			else
				current = current->right;	//Go right
		}
	}
	if (flag == 0)
	{
		cout << " Data not found! " << endl;
		return;
	}
}

//Define the methods which prints all the movie with same ratings

/********************************************************************
*
* This methods calls a recursive method in turn with the parameter
* passed as the given data by the user. The recursive method finds
* all the movies which matches the data and prints it
*
********************************************************************/

void BST::find_by_rating(float given)
{
	//Locate the element
	int count=0;

	if (isEmpty())
	{
		cout << " This Tree is empty! " << endl;
		return;
	}

	TreeNode* current;
	current = root;
	
	cout << endl << "All the movies with rating " << given << " are:" << endl << endl;
	cout << setw(80) << "Name" << setw(8) << " Year" << setw(8) << " Duration" << setw(6) << " rating" << endl;

	f_rating(current, given);	//Call the recursive function
}

//Define the recursive function which traverses the tree using inorder traversal and finds out the movies with the same rating
void BST::f_rating(TreeNode* current, float given)
{
	if (current != NULL)
	{
		if (current->left)
			f_rating(current->left, given);

		if (current->data.getrating() == given)	//check for the same rating and print
			cout << setw(80) << current->data.getName() << setw(8) << current->data.getyear() << setw(8) << current->data.gettime() << setw(6) << current->data.getrating() << endl;
		
		if (current->right)
			f_rating(current->right, given);
	}
	else
		return;
}

//Define the methods which prints all the movie names released in the same given year

/********************************************************************
*
* This methods calls a recursive method in turn with the parameter
* passed as the given data by the user. The recursive method finds
* all the movies which matches the data and prints it
*
********************************************************************/

void BST::find_by_year(int given)
{
	//Locate the element
	int count = 0;

	if (isEmpty())
	{
		cout << " This Tree is empty! " << endl;
		return;
	}

	TreeNode* current;
	current = root;

	cout << endl << "All the movies released in the year " << given << " are:" << endl << endl;
	cout << setw(80) << "Name" << setw(8) << " Year" << setw(8) << " Duration" << setw(6) << " rating" << endl;

	f_year(current, given);
	/*
	count = f_year(current, count, given);

	if (count == 0)
	{
		cout << "Sorry, Data not found! " << endl;
		return;
	}*/
}

//Define the recursive function which traverses the tree using inorder traversal and finds out the movies released in the same year
void BST::f_year(TreeNode* current, int given)
{
	if (current != NULL)
	{
		if (current->left)
			f_year(current->left, given);

		if (current->data.getyear() == given)	//check for the same year of release and print
			cout << setw(80) << current->data.getName() << setw(8) << current->data.getyear() << setw(8) << current->data.gettime() << setw(6) << current->data.getrating() << "\t\t\t\t" << endl;
		
		if (current->right)
			f_year(current->right, given);
	}
	else
		//return count;
		return;
}

//Define the methods which prints all the movies with the same duration

/********************************************************************
*
* This methods calls a recursive method in turn with the parameter
* passed as the given data by the user. The recursive method finds
* all the movies which matches the data and prints it
*
********************************************************************/

void BST::find_by_duration(int given)
{
	//Locate the element
	int count = 0;

	if (isEmpty())
	{
		cout << " This Tree is empty! " << endl;
		return;
	}

	TreeNode* current;
	current = root;

	cout << endl << "All the movies with duration " << given << " mins are:" << endl << endl;
	cout << setw(80) << "Name" << setw(8) << " Year" << setw(8) << " Duration" << setw(6) << " rating" << endl;

	f_time(current, given);
}

//Define the recursive function which traverses the tree using inorder traversal and finds out the movies of same duration
void BST::f_time(TreeNode* current, int given)
{
	if (current != NULL)
	{
		if (current->left)
			f_time(current->left, given);

		if (current->data.gettime() == given)	//check for the same duration and print
			cout << setw(80) << current->data.getName() << setw(8) << current->data.getyear() << setw(8) << current->data.gettime() << setw(6) << current->data.getrating() << "\t\t\t\t" << endl;
		
		if (current->right)
			f_time(current->right, given);
	}
	else
		return;
}


/********************************************************************
*
* Define the populate tree method which initiales the tree with
* a list of movies by reading in from a text file
*
********************************************************************/

void populateTree(BST *b)
{
	ifstream in;
	in.open("movies.txt");

	//variables used to load data into the tree
	string name;
	string key;
	int year;
	int time;
	float rating;
	movie m;
	string line;
	
	if (in.is_open())
	{
		cout << setw(80) << "Name" << setw(8) << " Year" << setw(8) << " Duration" << setw(6) << " rating" << endl;
		while (getline(in, line))
		{
			int i = 0, flag = 0, pos = 0;
			while (line[i] != '\n')	//end the loop when the line is fully traversed
			{
				//cout << " 1"<<endl;
				if (line[i] == '\t')
					i++;
				pos = i;

				while (line[i] != '\t')
					i++;

				key = line.substr(pos, i - pos);	//store each variables data ; use flags
				flag++;

				if (flag == 1)
					name = key;

				if (flag == 2)
					year = stoi(key);

				if (flag == 3) 
					rating = stof(key);

				if (flag == 4)
				{
					time = stoi(key);
					break;
				}
			}

				m.setName(name);
				m.setyear(year);
				m.settime(time);
				m.setrating(rating);
				cout << setw(80) << m.getName() << setw(8) << m.getyear() << setw(8) << m.gettime() << setw(6) << m.getrating() << "\t\t\t\t" << endl;
				(*b).insert(m);
				cout << endl;
		}
	}
	else
	{
		cout << "File not open....";
	}
	
	in.close();
}

/********************************************************************
*
* Define the main method
*
* It uses switch case to provide users with options to select 
* function from. 
*
* It also had some appropriate check to have valid input by the user
*
*********************************************************************/

int main()
{
	//Define all the required variables
	BST b;
	int i;
	string name;
	string key;
	int key1;
	float key2;
	int year;
	int time;
	float rating;
	movie t;

	populateTree(&b);	//Call the populateTree method 
	
	while (true)
	{
		cout << endl << endl;
		cout << " BST Movie Database Operations " << endl;
		cout << " ----------------------------- " << endl;
		cout << " 1. Find all records of the movie " << endl;
		cout << " 2. Insertion of a new movie to the list " << endl;
		cout << " 3. All Movies Information " << endl;
		cout << " 4. Removal of movie from the list " << endl;
		cout << " 5. Find all movies by year " << endl;
		cout << " 6. Find all movies by duration " << endl;
		cout << " 7. Find all movies by rating " << endl;
		cout << " 8. Exit " << endl;
		cout << " Enter your choice : ";
		cin >> i;
		cin.ignore();

		switch (i)
		{
		case 1: cout << endl << " Enter the name of the movie: ";
			getline(cin, key);
			b.find_by_name(key);
			break;

		case 2: cout << endl << " Enter name of the movie to be inserted: ";
			getline(cin, name);
			
			do{
				cout << endl << " Enter year of release before 2016: ";
				cin >> year;
			} while (year > 2016);

			do {
				cout << endl << " Enter the duration of the movie(in mins): ";
				cin >> time;
			} while (time <= 0);

			cout << endl << " Enter the ratings of the movie between 0 and 10: ";
			cin >> rating;
			
			t.setName(name);
			t.setyear(year);
			t.settime(time);
			t.setrating(rating);
			b.insert(t);
			break;

		case 3: cout << endl;
			cout << " All movies Information " << endl;
			cout << " ------------------------" << endl;
			cout << setw(80) << "Name" << setw(8) << " Year" << setw(8) << " Duration" << setw(6) << " rating" << endl;
			b.print_tree();
			break;

		case 4: cout << endl << " Enter the name of the movie to be deleted : ";
			getline(cin, key);
			b.ddelete(key);
			break;

		case 5:
			do {
				cout << endl << " Enter the year of the movies released in (in or before 2016): ";
				cin >> key1;
			} while (key1 > 2016);

			b.find_by_year(key1);
			break;

		case 6: 
			do {
				cout << endl << " Enter the duration of the movie(in mins): ";
				cin >> key1;
			} while (key1 <= 0);
			b.find_by_duration(key1);
			break; 

		case 7: cout << endl << " Enter the rating of the movies: ";
			cin >> key2;
			b.find_by_rating(key2);
			break;

		case 8: return 0;
		}
	}
}
