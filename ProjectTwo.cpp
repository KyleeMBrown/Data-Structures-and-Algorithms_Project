//==============================================================================
// Name        : ProjectTwo.cpp
// Author      : Kylee Brown
// Version     : 1.0
// Description : Load and analyze ABCUs course data using a Binary Search Tree
//==============================================================================

#include <iostream>
#include <fstream>
#include<sstream>
#include <vector>

using namespace std;

//========================//
//***** Declarations ****//
//======================//

// define a structure to hold course information
struct Course {

	string courseId; // unique ID
	string title; // course title
	vector<string> prerequisites; // list of prerequisites

	// default constructor
	Course() {
		courseId = ""; // initialize course Id to an empty string
	}
};

// internal structure or tree node
struct Node {
	Course course; // course object
	Node* left; // left child (pointer)
	Node* right; // right child (pointer)

	// default constructor
	Node() {
		left = nullptr; // assign left child pointer to null
		right = nullptr; // assign right child pointer to null
	}

	// initialize node with a course
	Node(Course aCourse) :
		// call default constructor
		Node() {
		course = aCourse; // assign member var course with param aCourse
	}
};

//=====================================
// BINARY SEARCH TREE DEFINITION
//=====================================

class BinarySearchTree {
private:
	Node* root;
	void addNode(Node* node, Course course);
	void inOrder(Node* node);

public:
	BinarySearchTree();
	void InOrder();
	void Insert(Course course);
	void Search(string courseId);

};


/*
* Default Constructor
*/
BinarySearchTree::BinarySearchTree() {
	// initialize root variable to null
	this->root = nullptr;
}

// =============================================== //
// ===== Print the Data in Alphanumeric Order ==== //

/*
* inserts a node into the bst 
* by using th addNode recursive function
* 
* @param course the course to be added to the tree
*/
void BinarySearchTree::Insert(Course course) {
	// initialize a new node that holds the course data
	Node* newNode = new Node(course);

	// if the root node is null
	if (this->root == nullptr) {
		// the root is equal to the new node
		this->root = newNode;
	}
	// else
	else {
		// add course to root node
		addNode(root, course);
	}
}

/*
* Add a node to another node recursively (private)
* 
* @param node the node to add to
* @param course the course being added
*/
void BinarySearchTree::addNode(Node* node, Course course) {
	

	// if node is larger then add to left
	if (course.courseId < node->course.courseId) {
		// if left node is null
		if (node->left == nullptr) {
			// this node becomes the left child
			node->left = new Node(course);
		}
		// else
		else {
			/* traverse down the left side of tree recursively
			or subtree until a null pointer is found */
			addNode(node->left, course);
		}
	}
	// else
	else if(course.courseId > node->course.courseId){
		// if the right node is null
		if (node->right == nullptr) {
			// this node becomes the right child
			node->right = new Node(course);
		}
		//else
		else {
			/* traverse down the right side of tree recursively
			or subtree until a null pointer is found */
			addNode(node->right, course);
		}
	}

};

// =============================================== //
// ===== Print the Data in Alphanumeric Order ==== //

/**
 * displays the tree in alphanumeric order
 */
void BinarySearchTree::InOrder() {
	if (this->root == nullptr) {
		cout << "no information to display" << endl;
	}
	// call inOrder function and pass the root node to start 
	inOrder(this->root);
}

/*
* function to recursively print the tree nodes in order (private)
* 
* @param node the node to start the traversal
*/
void BinarySearchTree::inOrder(Node* node) {
	unsigned int i; // to iterate through the prerequisites

	//if node is not equal to null ptr
	if (node != nullptr) {
		// traverse down left side of tree
		inOrder(node->left);
		//output courseId, title and prerequisites
		cout << node->course.courseId << ", " << node->course.title;

		// if the prerequisites list is NOT empty
		if (!node->course.prerequisites.empty()) {
			cout << " | Prerequisites: ";
			// iterate through each prerequisite and output
			for (i = 0; i < node->course.prerequisites.size(); i++) {
				// display the prerequisites
				cout << node->course.prerequisites[i] << " ";
			}	
		}
		cout << endl;

		// traverse down right side of tree
		inOrder(node->right);
	};

}
// ===============================================//
// ===== Search and print course information ==== //

/**
 * Search for a specific course in the Binary Search Tree recursively
 * 
 * @param courseId the course to find
 */
void BinarySearchTree::Search(string courseId) {
	// initialize the current node to node
	Node* cur = this->root;

	unsigned int i; // iterator for prerequisite list

	// while the current node is not null
	while (cur != nullptr) {
		// if the current course matches the course to find
		if (courseId == cur->course.courseId) {
			// display that course and exit the function
			cout << "Course Found!: " << cur->course.courseId << ", " << cur->course.title;
			// if the prerequisites list is NOT empty
			if (!cur->course.prerequisites.empty()) {
				cout << " | Prerequisites: ";
				// iterate through each prerequisite and output
				for (i = 0; i < cur->course.prerequisites.size(); i++) {
					// display the prerequisites
					cout << cur->course.prerequisites[i] << " ";
				}
			}
			cout << endl;
			return;
		}
		// if the current course Id is greater than the course Id to find
		if (courseId < cur->course.courseId) {
			// set current node to left child
			cur = cur->left;
		}
		// else the course Id is larger
		else {
			// set current node to right child
			cur = cur->right;
		}
		
	}

	// display course not found to user
	cout << "Course Not Found, Please Try Again!" << endl;
	return;
};

//===================================================================================================
/************************************* STATIC METHODS **********************************************/
//===================================================================================================

/*
* checks the format of the id and title
*
* @param id the course id
* @param title the title of the course
*
* @returns a boolean value
*/

 static bool checkFormat(string item) {
	bool valid = false;// initialize a variable to false
	int pos = item.size() - 3; // initialize position to the 3rd char from the end
	unsigned int i = 0;

	// check that the last three characters of the string are numbers
	for (i = pos; i < item.size(); i++) {
		if (isdigit(item[i])) {
			// uncomment for testing: cout << c << endl;
			// set valid to true if digit is found for the last 3 chars
			valid = true;
		}
		else {
			// set valid to false if not every char is a number
			valid = false;
		}
	}

	// return the resulting boolean
	return valid;
}

/*
* generates a vector of valid courses and
* checks the file for format errors
*
* @param pathToFile path to the chosen file
*
* @returns vector of valid course Ids
*/

static vector<string> generateValidCourseVector(string pathToFile) {
	ifstream inFS; // input file stream
	vector<string> validCourses; // vector to hold valid course IDs
	string line, courseId;// single file line and id of course


	// output generating valid course vector to user 
	//uncomment for testing: cout << "generating valid course vector" << endl;

	// open the file
	inFS.open(pathToFile);

	// handle errors opening the file
	// if the file is not opening
	if (!inFS.is_open()) {
		// output the error to user and exit the function
		cout << "error opening file please make sure file path is valid" << endl;
		return {};
	}
	// while end of file is not reached
	while (getline(inFS, line)) {
		// if file is producing errors
		if (!inFS.good()) {
			// output error to user
			cout << "error reading file" << endl;
			// exit the function
			return {};
		}

		// create an input stream using the line
		istringstream iss(line);

		// get the first item in the line up to the ','
		getline(iss, courseId, ',');

		// if course ID is not empty and formatting is correct
		if (!courseId.empty() && checkFormat(courseId)) {
			// add course ID to the vector
			validCourses.push_back(courseId);
		}
		// else wrong formatting in one of the first two items
		else {
			// output error to user 
			// uncomment for testing: cout << "error generating valid courses, please fix format in courseId column" << endl;
			// exit the function
			return {};
		}
	}
	return validCourses;
};


/*
* searches the vector for the ke
* 
* @param key item to search for in vector
* @param aVector vector of strings to search through
*
* @returns a boolean value representing if the key was found
*/

static bool searchVector(string key, vector<string> aVector) {
	unsigned int i;// iterator that loops through vector

	// iterate through the vector
	for (i = 0; i < aVector.size(); i++) {
		// if the current vector item equals the key t find
		if (aVector[i] == key) {
			// return true
			return true;
		}
	}

	// return false if nothing is found
	return false;
}

// ===================================== //
// ===== Read Course Data from file ==== //

/*
* Parses a comma separated file and
* transfers its contents to a vector
* for analyzing
*
* @param filePath path to chosen file
* @return fileContents vector of containing rows of data from the file
*/
static vector<vector<string>> csvParser(string pathToFile) {
	ifstream inFS; // input file stream

	vector<string> validCourses, row; // vector to hold all valid course IDs and row vector to hold each row
	vector<vector<string>> fileContents; // a file vector to store row vectors

	char sep = ','; // initialize the separator to a comma
	string courseId, courseTitle; // id and title of the course
	string line, token; // holds the file line and word



	// output the file is opening to user
	//uncomment for testing: cout << "Opening file..." << endl;

	// generate valid course vectors and check id format
	validCourses = generateValidCourseVector(pathToFile);

	// open the file
	inFS.open(pathToFile);

	// if the file is not opening or the validCourse vector is empty
	if (validCourses.empty() || !inFS.is_open()) {
		// output the error to user and exit the function
		cout << "error parsing file" << endl;
		return {};
	}

	// while end of file is not reached
	while (getline(inFS, line)) {
		// if file is producing errors
		if (!inFS.good()) {
			// output error to user and exit the function
			cout << "error reading file" << endl;
			return {};
		}

		// create an input stream using the line
		istringstream iss(line);

		// get the first item in the line up to the ','
		getline(iss, courseId, sep);
		// get the second item in the line up to the ','
		getline(iss, courseTitle, sep);

		// if course title is not empty and formatting is correct
		if (!courseTitle.empty() && !checkFormat(courseTitle)) {
			// push the course ID to the row vector 
			// (already checked format during validCourse generation)
			row.push_back(courseId);

			// push the course title to the row vector
			row.push_back(courseTitle);
		}
		// else wrong formatting in one of the first two items
		else {
			// output the error to the user and exit function
			cout << "error: empty value or wrong formatting in course title column" << endl;
			return {};
		}

		/* 
		*  get the rest of the items (prerequisites)
		*  separated by a comma and push them into the row
		*/
		while (getline(iss, token, sep)) {
			// if the prereq is not empty
			if (!token.empty()) {
				// if the prereq exists in the valid course vector
				if (searchVector(token, validCourses)) {
					// push the token (prereq) to the row vector
					row.push_back(token);
				}
				else {
					cout << "error prerequisite not included in course Ids" << endl;
				}
			}
		}

		// if the row has at least 2 items
		if (row.size() >= 2) {
			// push row to file contents
			fileContents.push_back(row);
			// clear the row vector to use again
			row.clear();
		}
		// there was not enough info provided
		else {
			// output the error to the user and exit function
			cout << "error not enough course information" << endl;
			return {};
		}
	}

	// close the file
	inFS.close();

	// return the parsed file contents
	return fileContents;
};

// ===================================== //
// ===== Loading the Data Structure ==== //

/*
* Loads a comma separated file containing
* course data into a binary search tree
*
* @param filePath path to chosen file
* @param bst the binary search tree the data will be loaded into
* 
*/

void loadCourses(string filePath, BinarySearchTree* bst) {
	vector<vector<string>> file; // vector to hold file contents
	unsigned int i;
	unsigned int j;

	cout << "Loading CSV..." << endl;

	// parse the csv
	file = csvParser(filePath);
	if (!file.empty()) {
		//uncomment for testing: cout << "success" << endl;
	}
	
	for (i = 0; i < file.size(); i++) {
		Course course; // create an empty course object

		// set course Id to the first value in the row vector
		course.courseId = file[i][0]; 
		// set course Id to the second value in the row vector
		course.title = file[i][1];

		//cout << course.courseId << " " << course.title << " ";
		
		// if the vector size is greater than 2
		if (file[i].size() > 2) {
			// iterate through the last few items and add them to the prereq vector
			for (j = 2; j < file[i].size(); j++) {
				// push the prerequisites to the course object prereqs list
				course.prerequisites.push_back(file[i][j]);

				//cout << file[i][j] << " ";
			}
		}

		// insert the course into the binary search tree
		bst->Insert(course);
	}
}

//====================
// MAIN DRIVER METHOD
//====================

void main(int argc, char* argv[]) {
	// process command line arguments
	string csvPath, courseId; // the path to the cvs file and the course Id to be found when searching
	switch (argc) {
	// only the file path is provided
	case 2:
		csvPath = argv[1];
		courseId = "MATH201";
		break;
	// both the file path and the course Id are provided
	case 3:
		csvPath = argv[1];
		courseId = argv[2];
	// neither commands are provided
	default:
		csvPath = "CS 300 ABCU_Advising_Program_Input.csv";// TODO: shorten the path
		courseId = "MATH201";
	}
	
	// initialize the Binary Search Tree
	BinarySearchTree* bst; 
	bst = new BinarySearchTree();

	string key;// courseId user will search for

	int choice = 0;// holds the users menu choice

	// while choice does not equal 9
	while (choice != 9) {
		// display menu and prompt user for choice
		cout << "Menu:" << endl;
		cout << "  1. Load Courses" << endl;
		cout << "  2. Display Courses in order" << endl;
		cout << "  3. Find and display Course" << endl;
		cout << "  9. Exit" << endl;
		cout << "Enter choice: ";

		// take user input
		cin >> choice;

		switch (choice) {
		// choice equals 1
		case 1:
			// load the course data into the BST
			cout << endl;
			loadCourses(csvPath, bst);
			cout << endl;
			break;
			
		// choice equals 2
		case 2:
			// print the BST alphanumerically
			cout << endl;
			bst->InOrder();
			cout << endl;
			break;
		// choice equals 3
		case 3:
			// prompt the user for input
			cout << "What course do you want to know about?: ";
			// get input course Id from user
			cin >> key;
			cout << endl;
			// search the bst using the users input and print the result
			bst->Search(key);
			cout << endl;
			break;
		// choice equals 9
		case 9:
			// exit the loop
			break;
		// invalid input
		default:
			// output error message and try again
			cout << "Sorry! " << choice << " is not a valid option, please try again" << endl;
			break;
		}

	}

	// output goodbye to the user and exit program
	cout << "Goodbye, thank you for using the planner!" << endl;
	return;

}
