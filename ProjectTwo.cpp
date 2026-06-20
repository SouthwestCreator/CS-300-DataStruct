#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

// course object
// this holds one full row from the csv file
struct Course {
	string courseId;
	string title;
	vector<string> prerequisites;

	// default constructor
	Course() {}
};

// node for bst
// stores course data + left/right pointers
struct Node {
	Course course;
	Node* left;
	Node* right;

	// default setup
	Node() {
		left = nullptr;
		right = nullptr;
	}

	// create node with a course already inside
	Node(Course aCourse) : Node() {
		this->course = aCourse;
	}
};

// BST Class
class BinarySearchTree {
private:
	Node* root;

	// helper functions for BST
	void addNode(Node* node, Course course);
	void inOrder(Node* node);

public:
	BinarySearchTree();
	virtual ~BinarySearchTree();

	void Insert(Course course);
	void PrintSortedCourseList();
	Course Search(string courseNumber);
};

// start empty tree
BinarySearchTree::BinarySearchTree() {
	this->root = nullptr;
}

// destructor (not fully used yet)
BinarySearchTree::~BinarySearchTree() {
	// could clean up nodes here if needed
}

// insert a new course into the tree
void BinarySearchTree::Insert(Course course) {
	if (root == nullptr) {
		root = new Node(course);
	}
	else {
		this->addNode(root, course);
	}
}

// helper func. that inserts courses into the bst
void BinarySearchTree::addNode(Node* node, Course course) {

	// go left if smaller
	if (course.courseId < node->course.courseId) {
		if (node->left == nullptr) {
			node->left = new Node(course);
		}
		else {
			this->addNode(node->left, course);
		}
	}
	// otherwise go right
	else {
		if (node->right == nullptr) {
			node->right = new Node(course);
		}
		else {
			this->addNode(node->right, course);
		}
	}
}

// in-order traversal (this prints sorted list)
//bst stores smaller values on left and larger on right
void BinarySearchTree::inOrder(Node* node) {
	if (node != nullptr) {

		// left side first (smaller values)
		inOrder(node->left);

		// print current node
		cout << node->course.courseId << ", " << node->course.title << endl;

		// right side next (larger values)
		inOrder(node->right);
	}
}

// prints full sorted course list
void BinarySearchTree::PrintSortedCourseList() {
	if (root == nullptr) {
		cout << "Error: Tree is empty. Load data first." << endl;
		return;
	}

	inOrder(root);
}

// search for a course in the tree
Course BinarySearchTree::Search(string courseNumber) {

	Node* current = root;

	while (current != nullptr) {

		// found it
		if (current->course.courseId == courseNumber) {
			return current->course;
		}

		// go left if search value is smaller
		if (courseNumber < current->course.courseId) {
			current = current->left;
		}
		// otherwise go right
		else {
			current = current->right;
		}
	}

	// not found, return empty course
	Course emptyCourse;
	return emptyCourse;
}

// ssplit csv row into seperate pieces
vector<string> split(const string& s, char delimiter) {
	vector<string> tokens;
	string token;
	istringstream tokenStream(s);

	while (getline(tokenStream, token, delimiter)) {
		tokens.push_back(token);
	}

	return tokens;
}

// load file into bst
void loadCourses(string fileName, BinarySearchTree* bst) {

	ifstream file(fileName);

	if (!file.is_open()) {
		cout << "ERROR: File could not be opened." << endl;
		return;
	}

	string line;

	while (getline(file, line)) {

		// skip blank lines
		if (line.empty()) {
			continue;
		}

		// split line into parts
		vector<string> tokens = split(line, ',');

		// basic validation check
		if (tokens.size() < 2) {
			cout << "Invalid line format, Skipping." << endl;
			continue;
		}

		// create course object from csv
		Course course;
		course.courseId = tokens[0];
		course.title = tokens[1];

		// grab prereqs if they exist
		for (size_t i = 2; i < tokens.size(); ++i) {
			if (!tokens[i].empty()) {
				course.prerequisites.push_back(tokens[i]);
			}
		}

		// insert into bst
		bst->Insert(course);
	}

	file.close();
	cout << "Load Complete." << endl;
}

// main menu
int main() {

	BinarySearchTree* bst = new BinarySearchTree();

	string csvPath = "";
	string menuSelection = "";
	string userSearchQuery = "";

	cout << "Welcome to the Course Planner" << endl;

	while (menuSelection != "9") {

		cout << "\n1. Load Data" << endl;
		cout << "2. Print Course List" << endl;
		cout << "3. Find Course" << endl;
		cout << "9. Exit" << endl;

		cout << "Enter Choice: ";
		cin >> menuSelection;

		if (menuSelection == "1") {

			cout << "Enter File Name: ";
			cin >> csvPath;

			loadCourses(csvPath, bst);
		}
		else if (menuSelection == "2") {

			cout << "Course List:" << endl;
			bst->PrintSortedCourseList();
		}
		else if (menuSelection == "3") {

			cout << "Enter Course ID: ";
			cin >> userSearchQuery;

			// normalize input so lowercase still works
			transform(userSearchQuery.begin(),
				userSearchQuery.end(),
				userSearchQuery.begin(),
				::toupper);

			Course found = bst->Search(userSearchQuery);

			if (!found.courseId.empty()) {

				cout << found.courseId << ", " << found.title << endl;

				if (found.prerequisites.empty()) {
					cout << "Prerequisites: None" << endl;
				}
				else {
					cout << "Prerequisites:" << endl;

					for (size_t i = 0; i < found.prerequisites.size(); ++i) {

						Course prereqCourse = bst->Search(found.prerequisites[i]);

						if (!prereqCourse.courseId.empty()) {
							cout << prereqCourse.courseId
								<< ", "
								<< prereqCourse.title
								<< endl;
						}
						else {
							cout << found.prerequisites[i] << endl;
						}
					}
				}
			}
			else {
				cout << "Course not Found: " << userSearchQuery << endl;
			}
		}
		else if (menuSelection == "9") {
			cout << "GoodBye :)" << endl;
		}
		else {
			cout << "Invalid Option. Please select 1,2,3,9" << endl;
		}
	}

	delete bst;
	return 0;
}