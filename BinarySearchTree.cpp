// BinarySearchTree.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Creates a binary search tree from an inputted array of integers
// Author: Pranav Sharma
//Date: 12/9/20

#include <iostream>
#include <cstring>
#include <math.h>
#include<fstream>
#include <string>
using namespace std;

// instead of creating a seperate class, I used a struct for nodes
struct Node {
public: 
    int data;
    Node* right;
    Node* left;
};

// functions
Node* createTree(int array[], int start, int end);
void printTree(Node* head, int spacing);
void sortArray(int array[], int numbers);
Node* deleteNode(Node* root, int value);
bool search(Node* head, int num, bool &result);
void readFile(int array[], char file[], int numbers);
Node* addNode(Node* root, int value);
Node* minValueNode(Node* root);

int main()
{
    // variables in the program
    int numbers;
    char* input = new char();
    int array[100];
    memset(array, -1, 100);
    // gets the user to enter how many numbers they would like in their binary tree and how they would like to input them
    cout << "Hello! This program creates a binary search tree based on inputted numbers.\n";
    cout << "How many numbers would you like to enter?\n";
    cin >> numbers;
    cin.get();
    cout << "Great! How would you like to input these numbers? enter FILE or CONSOLE\n";
    cin.getline(input, 80, '\n');

    //if user wnats to use console...
    if (strcmp(input, "CONSOLE") == 0) {
        int num;
        //... reads in the amount of numbers specified
        cout << "Enter " << numbers << " numbers seperated by a space\n";
        for (int i = 0; i < numbers; i++) {
            cin >> num;
            array[i] = num;
        }
        cin.get();
    }
    // if user wants to use a file...
    else if (strcmp(input, "FILE") == 0) {
        cout << "Enter the file you would like to open, in this program there is a file called 'Number.txt'\n";
        char file[20];
        cin.getline(file, 80, '\n');
        //... readfile function is called after file is entered
        readFile(array, file, numbers+1);
    }
    // else they didnt type a proper command, boo!
    else {
        cout << "No proper command was entered :(";
        return 0;
    }
  // sorts the array of number
  //sortArray(array, numbers); --
  // generated a binary tree with head at the root (old way of creating tree)
    Node* head = NULL;
    for (int i = 0; i < numbers; i++) {
        head = addNode(head, array[i]);
    }
  //Node* head = createTree(array, 0, numbers - 1); (old way of creating tree)
  cout << "Awesome! The binary tree generated is as follows:\n";
  // prints the tree
  printTree(head, 0);
  bool playing = true;
  // asks users what they would like to do next
  while (playing) {
      cout << "What would you like to do? (ADD, REMOVE, SEARCH, or QUIT): ";
      cin.getline(input, 80, '\n');
      // if they would like to add
      if (strcmp(input, "ADD") == 0) {
          int num;
          cout << "What number would you like to add?: ";
          cin >> num;
          cin.get();
          head = addNode(head, num);
          printTree(head, 0);
      }
      // if they would like to remove a node
      else if (strcmp(input, "REMOVE") == 0) {
          int num;
          cout << "Which number would you like to remove?: ";
          cin >> num;
          cin.get();
          // remove function is called
          head = deleteNode(head, num);
          // tree is printed
          printTree(head, 0);
      }
      // if they would like to search
      else if (strcmp(input, "SEARCH") == 0) {
          int num;
          bool result = false;
          cout << "Which number would you like to search for?: ";
          cin >> num;
          cin.get();
          // results are printed using search function
          if (search(head, num, result) == true) {
              cout << "This number is in the binary tree!\n";
          }
          else {
              cout << "It looks like this number is not in the binary tree.\n";
          }
      }
      // else they want to stop
      else if (strcmp(input, "QUIT") == 0) {
          playing = false;
      }
  }
  cout << "Have a great day!";

}

Node* addNode(Node* root, int value) {
    if (root == NULL) {
        Node* node = new Node();
        node->data = value;
        return node;
    }
    else {
        if (value < root->data) {
            root->left = addNode(root->left, value);
        }
        else {
            root->right = addNode(root->right, value);
        }
    }
    return root;
}
// code taken from my heap project; reads in a file of numbers
void readFile(int array[], char file[], int numbers) {
    FILE* pfile = NULL;
    char line[1000];
    // opens the file with the given name from user
    pfile = fopen(file, "r");
    // alerts if file is unreadable
    if (pfile == NULL)
    {
        cout << "Error in opening the file Numbers.txt";
        return;
    }

    // goes through each line, and stores whats beween the commas in the integer array
    int index = 0;
    bool reading = true;
    while (fgets(line, 1000, pfile) && reading == true) {
        char* buffer = new char[20];
        memset(buffer, '\0', 20);
        int pos = 0;
        while (buffer != NULL && reading == true) {
            buffer = strchr(line + pos, ',');
            if (buffer != NULL) {
                char lineBuffer[20];
                memset(lineBuffer, '\0', 20);
                strncpy(lineBuffer, line + pos, sizeof(line - buffer));
                array[index] = stoi(lineBuffer);
                index++;
                if (index == numbers - 1) {// stops when intended numbers are read
                    reading = false;
                    return;
                }
                pos = (buffer - line) + 1;
            }
        }
    }
}
// searches for a number int he binary tree using recursion
bool search(Node* head, int num, bool &result) {
    // follows the pathway of the tree, if the number is bigger than the root it goes right and left if it is smaller
    if (head != NULL) {
        if (head->data == num) {
            result = true;
        }
        else if (head->data < num) {
            search(head->right, num, result);
        }
        else {
            search(head->left, num, result);
        }
    }
    return result;
}
// finds the lowest value node by following the left pathway of a subtree
Node* minValueNode(Node* root) {
    Node* current = root;
    while (current != NULL && current->left != NULL) {
        current = current->left;
    }
    return current;
}
// deletes a node and return the new head. Idea from geekforgeeks.com
Node* deleteNode(Node* root, int value) {
    // stops if the tree us empty
    if (root == NULL) {
        return root;
    }
    // checks if node is in the left subtree, if it does then it follows down 
    if (value < root->data) {
        root->left = deleteNode(root->left, value);
    }
    // checks if node is in right subtree
    else if (value > root->data) {
        root->right = deleteNode(root->right, value);
    }
    // once the node is found
    else {
        // bumps up if the root has no or one children
        if (root->left == NULL) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        // runs for nodes with two children, gets the smalles in the subtree
        Node* temp = minValueNode(root->right);
        // copys the childs content to the root
        root->data = temp->data;
        // deletes the sucessor
        root->right = deleteNode(root->right, temp->data);

    }
    return root;
}
// sorts the aray in numerical order
void sortArray(int array[], int n) {
    for (int i = 0;i < n; i++) {
        for (int j = i + 1;j < n; j++) {
            // compared each number with every other number
            if (array[i] > array[j]){
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }

}
// creates the binary tree given a sorted array of integers
Node* createTree(int array[], int start, int end) {
    if (start > end) {
        return NULL;
    }
    // makes the middle of the array the root and repeats for children
    int middle = (start + end) / 2;
    Node* head = new Node();
    head->data = array[middle];
    head->left = createTree(array, start, middle - 1);
    head->right = createTree(array, middle + 1, end);
    return head;
}

// prints the binary tree (sideways) using spaces
void printTree(Node* head, int spacing) {
    if (head != NULL) {
        spacing = spacing + 10;
        printTree(head->right, spacing);
        cout << endl;
        for (int i = 10; i < spacing; i++) {
            cout << " ";
        }
        cout << head->data << endl;
        printTree(head->left, spacing);
    }
}
