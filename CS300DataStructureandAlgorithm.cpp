//============================================================================
// Name        : ProjectTWo.cpp
// Author      : Jessica Bains
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <algorithm>
#include <climits>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

const unsigned int DEFAULT_SIZE = 8;
// forward declarations
double strToDouble(string str, char ch);
// define a structure to hold course information
struct Course {
 string courseId; // unique identifier
 string title;
 string key;
 vector<string> preReqs{"",""};
 Course() {
 }
};

/**
 * Define a class containing data members and methods to

 */
class HashTable {
private:
 // Define structures to hold bids
 struct Node {
 Course course;
 unsigned int key;
 Node *next;
 // default constructor
 Node() {
 key = UINT_MAX;
 next = nullptr;
 }
 // initialize with a course
 Node(Course aCourse) : Node() {
	 course = aCourse;
	  }
	  // initialize with a course and a key
	  Node(Course aCourse, unsigned int aKey) : Node(aCourse) {
	  key = aKey;
	  }
	  };
	  vector<Node> nodes;
	  unsigned int tableSize = DEFAULT_SIZE;
	  unsigned int hash(int key);
	  int partition(int lowIndex, int highIndex);
	  void quickSort(int lowIndex, int highIndex);
	 public:
	  HashTable();
	  HashTable(unsigned int size);
	  virtual ~HashTable();
	  void Insert(Course course);
	  void PrintAll();
	  vector<Course> courses;
	  Course Search(string courseId);
	 };
	 /**
	  * Default constructor
	  */
	 HashTable::HashTable() {
	  // Initalize node structure by resizing tableSize
	  nodes.resize(tableSize);
	  courses.resize(tableSize);
	 }

	 HashTable::HashTable(unsigned int size) {
	  // invoke local tableSize to size with this->
	  this->tableSize = size;
	  // resize nodes size
	  nodes.resize(size);
	  courses.resize(size);
	 }
	 /**
	  * Destructor
	  */
	 HashTable::~HashTable() {
	  // erase nodes beginning
	  nodes.erase(nodes.begin());
	 }
	 unsigned int HashTable::hash(int key) {
	  // return key tableSize
	  return key % tableSize;
	 }

	 void HashTable::Insert(Course course) {
	  // Create the key for the given course
	  unsigned int tempKey = hash(stoi(course.key));

	  if (nodes.at(tempKey).key == UINT_MAX) {
	  // Add a newly created node with course and key to the bucket
	  nodes.at(tempKey) = Node(course, tempKey);
	  }

	  else{

	  Node* currNode = &nodes.at(tempKey);
	  // Loop through the linked list to find the tail
	  while (currNode->next != nullptr) {
	  // Move on to next node
	  currNode = currNode->next;
	  }

	  currNode->next = new Node(course, tempKey);
	  }
	 }

	 void displayCourse(Course course) {
	  cout << course.courseId << ": " << course.title << " | " << "Prerequisits: ";
	  if (course.preReqs.at(0) != ""){
	  cout << course.preReqs.at(0) << " " << course.preReqs.at(1) << endl;
	  } else{
	  cout << "None" << endl;
	  }
	 }
	 void HashTable::PrintAll() {
	  // Sort the courses vector in order to get it in alphanumerical order
	  quickSort(0, courses.size()-1);
	  // Use the for loop to display all the courses
	  for (int i = 0; i < courses.size(); ++i) {

		  displayCourse(courses.at(i));
		   }
		  }
		  Course HashTable::Search(string courseId) {
		   // Create new empty course struct to return if nothing found
		   Course course;
		   // create the key for the given course using the last three digits of the
		  course id
		   Node* cursor = &nodes.at(hash(stoi(courseId.substr(4,7))));
		   // while node not equal to nullptr
		   while (cursor != nullptr) {
		   // if the current node matches, return it
		   if (cursor->course.courseId == courseId) {
		   // if entry found for the key
		   // return node course
		   return cursor->course;
		   }
		   //node is equal to next node
		   cursor = cursor->next;
		   }

		   return course;
		  }

		  int HashTable::partition(int lowIndex, int highIndex) {
		   // Pick middle element as pivot
		   int midpoint = lowIndex + (highIndex - lowIndex) / 2;
		   string pivot = courses.at(midpoint).courseId;
		   bool done = false;
		   while (!done) {
		   // Increment lowIndex while numbers[lowIndex] < pivot
		   while (courses.at(lowIndex).courseId < pivot) {
		   lowIndex += 1;
		   }
		   // Decrement highIndex while pivot < numbers[highIndex]
		   while (pivot < courses.at(highIndex).courseId) {
		   highIndex -= 1;
		   }

		   if (lowIndex >= highIndex) {
		   done = true;
	  }
		   }
		    else {
		    // Swap numbers[lowIndex] and numbers[highIndex]
		    Course temp = courses.at(lowIndex);
		    courses.at(lowIndex) = courses.at(highIndex);
		    courses.at(highIndex) = temp;
		    // Update lowIndex and highIndex
		    lowIndex += 1;
		    highIndex -= 1;
		    }
		    }
		    return highIndex;
		    }

		   void HashTable::quickSort(int lowIndex, int highIndex) {
		    // If the lowIndex is greater than the highIndex then the partition is sorted
		    if (lowIndex >= highIndex) {
		    return;
		    }
		    // Partition the data in the vector, the value returned is the index of the low
		    // partition's last element.
		    int lowEndIndex = partition(lowIndex, highIndex);
		    // Recursively sort the low partition
		    quickSort(lowIndex, lowEndIndex);
		    // Recursively sort the high partition
		    quickSort(lowEndIndex + 1, highIndex);
		   }

		   void loadCourses(string filePath, HashTable* hashTable) {
		    cout << "Loading course data from file " << filePath << endl;
		    // Create the input stream
		    ifstream inputStream;
		    // Open the file
		    inputStream.open(filePath);
		    // Create a variable to hold the number of items in the read in line
		    int lineItemCount;
		    // Create variables to hold the size of the title for reference use, the read
		   in line, and a course object
		    int titleCount;
		    string line;
		    Course currentCourse;
		    int index = 0;
		     // Here we loop through the lines of the file
		     while (!inputStream.fail()){

		    always going to be there
		     lineItemCount = -2;
		     titleCount = 0;

		     getline(inputStream,line);

		    items in the line
		     for (int i = 0; i < line.size(); ++i) {
		     if (line.at(i) == ','){
		     lineItemCount += 1;
		     }
		     if (lineItemCount == -1 && i > 7){
		     titleCount += 1;
		     }
		     }
		     // If statement prevents duplicate at the end of file
		     if (currentCourse.courseId == line.substr(0,7)){
		     break;
		     }

		    last
		     currentCourse.key = line.substr(4,3);
		     currentCourse.courseId = line.substr(0,7);
		     currentCourse.title = line.substr(8,titleCount);
		     if (line.size() > 8 + titleCount){
		     currentCourse.preReqs.at(0) = line.substr(titleCount + 9, 7);
		     } else{
		     currentCourse.preReqs.at(0) = "";
		     }
		     if (line.size() > 16 + titleCount){
		     currentCourse.preReqs.at(1) = line.substr(titleCount + 17, 23);
		     }else{
		     currentCourse.preReqs.at(1) = "";
		     }
		     // Insert the course into a courses
		     hashTable->courses.at(index) = currentCourse;
		     index += 1;
		     hashTable->Insert(currentCourse);
		     }
		     // Close the file
		     inputStream.close();
		    }
		    /**
		     * The one and only main() method
		     */
		    int main(int argc, char* argv[]) {
		     // Define a hash table to hold all the bids
		     HashTable* bidTable;
		     // Define a course object, file path, choice, and course name to facilitate
		     menu choices
		      Course course;
		      string filePath;
		      string courseName;
		      int choice = 0;
		      // run the menu until user chooses to exit.
		      while (choice != 4) {
		      cout << "Menu:" << endl;
		      cout << " 1. Load Data Structure" << endl;
		      cout << " 2. Print Course List" << endl;
		      cout << " 3. Print Course" << endl;
		      cout << " 4. Exit" << endl;
		      cout << " What would you like to do?" << endl;
		      cin >> choice;
		      switch (choice) {
		      case 1:
		      bidTable = new HashTable();
		      cout << "Enter course data file name or enter 1 to use the default
		     file" << endl;
		      cin >> filePath;
		      if (filePath == "1"){
		      loadCourses("courselist.txt", bidTable);
		      } else{
		      // Complete the method call to load the bids
		      loadCourses(filePath, bidTable);
		      }
		      break;
		      case 2:
		      bidTable->PrintAll();
		      break;
		      case 3:
		      cout << "What course do you want to know about?" << endl;
		      cin >> courseName;
		      course = bidTable->Search(courseName);
		      if (!course.courseId.empty()) {
		      displayCourse(course);
		      } else {
		      cout << "Course Id " << courseName << " not found." << endl;
		      }
		      break;
		      }
		      if (choice > 4 || choice < 1){
		      cout << choice << " is not a valid option." << endl;
		      }
		      }
		      cout << "Thank you for using the course planner!" << endl;
		      return 0;
		     }
