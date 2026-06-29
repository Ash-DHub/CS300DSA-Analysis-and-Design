/*
 * Name		  : ProjectTwo.cpp
 * Author     : Asha Donnon
 * Course     : CS 300 Analysis and Design
 * Assignment : Project Two; ABCU Advising Assistance Program
 * Date       : June 2026
 *
 * Description:
 * This program reads course information from a file and stores the data
 * in a Binary Search Tree. Users will be able to load course data, print
 * a complete course list and view detailed information for an individual
 * course including prerequisites.
 *
 * Menu Options:
 * 1. Load Data Structure
 * 2. Print Course List
 * 3. Print Course Information
 * 9. Exit Program
 */

 #include <algorithm>
 #include <cctype>
 #include <fstream>
 #include <iostream>
 #include <sstream>
 #include <string>
 #include <vector>

 using namespace std;

 /*
  * Course Structure
  * Stores the course number, title and prerequisite information for a single
  * course from the input file
  */

 struct Course {
	 string courseNumber;
	 string courseTitle;
	 vector<string> prerequisites;

	 //Default constructor
	 Course() {
		 courseNumber = "";
		 courseTitle = "";
	 }
 };
 /* Tree Node Structure
  * Each node stores one Course object and pointers to the left and right child.
  */
 struct Node {
	 Course course;
	 Node* left;
	 Node* right;

	 Node() {
		 left = NULL;
		 right = NULL;
	 }

	 Node(Course aCourse) {
		 course = aCourse;
		 left = NULL;
		 right = NULL;
	 }
 };

 /* Binary Search Tree Class
  * Stores course records in sorted order based on the course number.
  */
 class BinarySearchTree {
 private:
	 Node* root;

	 // Helper function used to print the tree in sorted order
	 void InOrder(Node* node);

 public:
	 // Constructor starts the tree as empty
	 BinarySearchTree() {
		 root = NULL;
	 }

	 // Inserts a course into the tree
	 void Insert(Course course);

	 // Searches the tree for a course number
	 Course Search(string courseNumber);

	 // Prints all courses in aplhanumeric order
	 void InOrder();
 };

 /* Insert
  * Adds a course to the Binary Search Tree based on course number.
  * Courses with smaller course numbers go to the left.
  * Courses with larger course numbers go to the right.
  */
  void BinarySearchTree::Insert(Course course) {

	  // Create a new node for the course.
	  Node* newNode = new Node(course);

	  // If the tree is empty, the new node becomes the root
	  if (root == NULL) {
		  root = newNode;
		  return;
	  }

	  // Start comparing at the root node
	  Node* current = root;

	  while (current != NULL) {

		  // Move left if the new course number comes before the current course
		  if (course.courseNumber < current->course.courseNumber) {

			  if (current->left == NULL) {
				  current->left = newNode;
				  return;
			  }

			  current = current->left;
		  }

		  // Move right if the new course number comes after or equals current
		  else {

			  if (current->right == NULL) {
				  current->right = newNode;
				  return;
			  }

			  current = current->right;
		  }
	  }
  }
/*
 * Search
 * Finds and returns a course from the Binary Search Tree.
 * If the course is not found, an empty Course object is returned.
 */
 Course BinarySearchTree::Search(string courseNumber) {

	 // Start searching at the root of the tree
	 Node* current = root;

	 // Continue moving through the tree until the course is found or search ends
	 while (current != NULL) {

		 if (current->course.courseNumber == courseNumber) {
			 return current->course;
		 }

		 else if (courseNumber < current->course.courseNumber) {
			 current = current->left;
		 }

		 else {
			 current = current->right;
		 }
	 }

	 // Return an empty course if no match was found
	 Course course;
	 return course;
 }
/* InOrder Helper Function
 * Recursively traverses the tree in sorted order.
 */
 void BinarySearchTree::InOrder(Node* node) {

	 if (node != NULL) {

		 // Visit left subtree
		 InOrder(node->left);

		 // Display current course
		 cout << node->course.courseNumber << ", "
			  << node->course.courseTitle << endl;

		 // Visit right subtree
		 InOrder(node->right);
	 }
 }

 /*
  * Public InOrder Function
  * Starts traversal from the root node
  */
  void BinarySearchTree::InOrder() {
	  InOrder(root);
  }
  /*
   * loadCourses
   * Reads course data from a comma separated file, creates Course objects,
   * and inserts each course into the Binary Search Tree.
   */
  void loadCourses(string fileName, BinarySearchTree* courseTree) {

	  ifstream inputFile(fileName.c_str());

	  // Check whether the file opened successfully
	  if (!inputFile.is_open()) {
		  cout << "Error: The file could not be opened." << endl;
		  return;
	  }

	  string line;

	  // Read the file one line at a time
	  while (getline(inputFile, line)) {

		  stringstream ss(line);
		  string item;
		  vector<string> tokens;

		  // Separate the line by commas
		  while (getline(ss, item, ',')) {
			  tokens.push_back(item);
		  }

		  // Each valid line must have at least a course number and title
		  if (tokens.size() < 2) {
			  cout << "Error: Invalid course entry found." << endl;
			  continue;
		  }

		  Course course;
		  course.courseNumber = tokens[0];
		  course.courseTitle = tokens[1];

		  // Any remaining values are prerequisites
		  for (unsigned int i = 2; i < tokens.size(); i++) {
			  course.prerequisites.push_back(tokens[i]);
		  }

		  // Store the course in the Binary Search Tree
		  courseTree->Insert(course);
	  }

	  inputFile.close();

	  cout << "Course data loaded successfully." << endl;
  }
  int main() {

 	 // Create the Binary Search Tree
 	 BinarySearchTree courseTree;

 	 // Tracks whether course data has been loaded
 	 bool dataLoaded = false;

 	 int choice = 0;
 	 string fileName;
 	 string courseNumber;

 	 // Display welcome message when program starts
 	 cout << "Welcome to the course planner." << endl;

 	 while (choice != 9) {

 		 cout << endl;
 		 cout << "1. Load Data Structure." << endl;
 		 cout << "2. Print Course List." << endl;
 		 cout << "3. Print Course." << endl;
 		 cout << "9. Exit" << endl;
 		 cout << endl;
 		 cout << "What would you like to do? ";

 		 cin >> choice;

 		 if (choice == 1) {
 			 cout << "Enter the file name: ";
 			 cin.ignore();
 			 getline(cin, fileName);

 			 loadCourses(fileName, &courseTree);
 			 dataLoaded = true;
 		 }

 		 else if (choice == 2) {
 			 if (dataLoaded == false) {
 				 cout << "Please load the course data first." << endl;
 			 }
 			 else {
 				 cout << "Here is a sample schedule:" << endl;
 				 cout << endl;
 				 courseTree.InOrder();
 			 }
 		 }

 		 else if (choice == 3) {
 			 if (dataLoaded == false) {
 				 cout << "Please load the course data first." << endl;
 			 }
 			 else {
 				 cout << "What course do you want to know about?";
 				 cin >> courseNumber;

 				 // Convert user input to uppercase so searches work with lowercase input
 				 transform(courseNumber.begin(), courseNumber.end(), courseNumber.begin(), (int (*)(int))toupper);

 				 // Search for the requested course
 				 Course course = courseTree.Search(courseNumber);

 				 if (course.courseNumber == "") {
 					 cout << "Course not found." << endl;
 				 }
 				 else {
 					 cout << course.courseNumber << ", " << course.courseTitle << endl;

 					 if (course.prerequisites.size() == 0) {
 						 cout << "Prerequisites: None" << endl;
 					 }
 					 else {
 						 cout << "Prerequisites:" << endl;

 						 for (unsigned int i = 0; i < course.prerequisites.size(); i++) {

 							 Course prerequisiteCourse = courseTree.Search(course.prerequisites[i]);

 							 if (prerequisiteCourse.courseNumber !="") {
 								 cout << prerequisiteCourse.courseNumber << ", ";
 								 cout << prerequisiteCourse.courseTitle << endl;
 							 }
 							 else {
 								 cout << course.prerequisites[i] << endl;
 							 }
 						 }
 				     }
 				 }
 			 }
 		 }
 		 	 	 	  else if (choice == 9) {
 			             cout << "Thank you for using the course planner!" << endl;
 		             }


 		             else {
 			             cout << choice << " is not a valid option." << endl;
 		             }
 	     }
 		 return 0;

   }
