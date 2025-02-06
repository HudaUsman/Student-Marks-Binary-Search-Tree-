#include <iostream>
#include <string>
#include <limits>

using namespace std;


struct Node {
    string name;
    int grade;
    Node* left;
    Node* right;

    
    Node(string n, int g) {
        name = n;
        grade = g;
        left = NULL;
        right = NULL;
    }
};


class StudentGradesBST {
private:
    Node* root;

    Node* insert(Node* node, string name, int grade) {
        if (node == NULL) {
            return new Node(name, grade);
        }

        if (grade < node->grade) {
            node->left = insert(node->left, name, grade);
        } else {
           
            node->right = insert(node->right, name, grade);
        }

        return node;
    }


    // Helper function to search for a student record by grade
    Node* searchByGrade(Node* node, int grade) {
        if (node == NULL || node->grade == grade) {
            return node;
        }

        if (grade < node->grade) {
            return searchByGrade(node->left, grade);
        } else {
            return searchByGrade(node->right, grade);
        }
    }

    // Helper function to search for a student record by name
    Node* searchByName(Node* node, string name) {
        if (node == NULL || node->name == name) {
            return node;
        }

        Node* foundNode = searchByName(node->left, name);
        if (foundNode == NULL) {
            foundNode = searchByName(node->right, name);
        }

        return foundNode;
    }

    // Helper function to find the minimum value node
    Node* findMin(Node* node) {
        while (node && node->left != NULL) {
            node = node->left;
        }
        return node;
    }

    // Helper function to delete a student record by name
    Node* deleteByName(Node* root, string name) {
        if (root == NULL) return root;

        if (name < root->name) {
            root->left = deleteByName(root->left, name);
        } else if (name > root->name) {
            root->right = deleteByName(root->right, name);
        } else {
            if (root->left == NULL) {
                Node* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == NULL) {
                Node* temp = root->left;
                delete root;
                return temp;
            }

            Node* temp = findMin(root->right);
            root->name = temp->name;
            root->grade = temp->grade;
            root->right = deleteByName(root->right, temp->name);
        }
        return root;
    }

    // Helper function to perform in-order traversal
    void inorder(Node* root) {
        if (root != NULL) {
            inorder(root->left);
            cout << "Name: " << root->name << ", Grade: " << root->grade << endl;
            inorder(root->right);
        }
    }

public:
    StudentGradesBST() : root(NULL) {}

    void insert(string name, int grade) {
        root = insert(root, name, grade);
    }

    void searchByGrade(int grade) {
        Node* result = searchByGrade(root, grade);
        if (result != NULL) {
            cout << "Found student: Name: " << result->name << ", Grade: " << result->grade << endl;
        } else {
            cout << "No student found with grade: " << grade << endl;
        }
    }

    void searchByName(string name) {
        Node* result = searchByName(root, name);
        if (result != NULL) {
            cout << "Found student: Name: " << result->name << ", Grade: " << result->grade << endl;
        } else {
            cout << "No student found with name: " << name << endl;
        }
    }

    void deleteByName(string name) {
        root = deleteByName(root, name);
    }

    void displayAll() {
        inorder(root);
    }
};

// Function to display the menu and get user choice
void displayMenu() {
    cout << "\nStudent Grades BST Menu:" << endl;
    cout << "1. Add Record" << endl;
    cout << "2. Search by Grade" << endl;
    cout << "3. Search by Name" << endl;
    cout << "4. Delete by Name" << endl;
    cout << "5. Display All Records" << endl;
    cout << "6. Exit" << endl;
    cout << "Enter your choice: ";
}

// Function to get a valid integer input from the user
int getValidInt() {
    int input;
    while (true) {
        cin >> input;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid integer: ";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            return input;
        }
    }
}

// Function to get a valid string input from the user
string getValidString() {
    string input;
    getline(cin, input);
    return input;
}

int main() {
    StudentGradesBST bst;
    int choice;
    string name;
    int grade;

    do {
        displayMenu();
        choice = getValidInt();

        switch (choice) {
            case 1:
               
                cout << "Enter student name: ";
                name = getValidString();
                cout << "Enter student grade: ";
                grade = getValidInt();
                bst.insert(name, grade);
                break;

            case 2:
               
                cout << "Enter grade to search: ";
                grade = getValidInt();
                bst.searchByGrade(grade);
                break;

            case 3:
                
                cout << "Enter name to search: ";
                name = getValidString();
                bst.searchByName(name);
                break;

            case 4:
               
                cout << "Enter name to delete: ";
                name = getValidString();
                bst.deleteByName(name);
                break;

            case 5:
               
                cout << "All Student Records:" << endl;
                bst.displayAll();
                break;

            case 6:
                
                cout << "Exiting the program." << endl;
                break;

            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }

    } while (choice != 6);

    return 0;
}
