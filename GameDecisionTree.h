#ifndef GAMEDECISIONTREE_H
#define GAMEDECISIONTREE_H

#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Node.h"
#include "Story.h"
template <typename T>
class GameDecisionTree {
private:
    Node<T>* root; // Starting point root of the story tree

public:
    GameDecisionTree() : root(nullptr) {} // Constructor that sets the root to null at the beginning
    // Read text file that contains story events and builds a binary decision tree from it
    void loadStoryFromFile(const string& filename, char delimiter) {
        // To open file using the provided filename
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Not able to open file: " << filename << endl;
            return;
        }

        // Use map as a dictionary to temporarily store all story nodes using their event number
        map<int, Node<T>*> nodeMap;

        string line;
        while (getline(file, line)) {
            // Skip empty lines
            if (line.empty()) continue;
            // Break current line into parts using delimiter ","
            stringstream ss(line);
            string idStr, desc, leftStr, rightStr;

            getline(ss, idStr, delimiter);
            getline(ss, desc, delimiter);
            getline(ss, leftStr, delimiter);
            getline(ss, rightStr, delimiter);
            // Convert string values to integers for IDs
            int id = stoi(idStr);
            int left = stoi(leftStr);
            int right = stoi(rightStr);
            // Create a story object and wrap it in new node
            T story(desc, id, left, right);
            Node<T>* newNode = new Node<T>(story);
            // Store the node using its event number
            nodeMap[id] = newNode;
        }

        // Connect each node to its left and right child (linking branches of the tree)
        typename map<int, Node<T>*>::iterator it;
        for (it = nodeMap.begin(); it != nodeMap.end(); ++it) {
            Node<T>* current = it->second;

            int leftID = current->data.leftEventNumber;
            int rightID = current->data.rightEventNumber;

            if (nodeMap.count(leftID) > 0) {
                current->left = nodeMap[leftID];
            }

            if (nodeMap.count(rightID) > 0) {
                current->right = nodeMap[rightID];
            }
        }

        // Set the root with ID = 1 where the story start
        if (nodeMap.count(1) > 0) {
            root = nodeMap[1];
        } else {
            root = nullptr;
        }
        // Close file after we're done reading
        file.close();
    }

    void playGame() {
        // Check if the story tree is build
        if (root == nullptr) {
            cout << "No story loaded." << endl;
            return;
        }
        // Start the game at the root event
        Node<T>* current = root;
        // Continue to run the story until we reach the end
        while (current != nullptr) {
            cout << current->data.description << endl;

            // When we reach the end of story which is two null child nodes this will print out the text
            if (current->left == nullptr && current->right == nullptr) {
                cout << "[You make a wise choices ^_^]" << endl;
                break;
            }
            // Ask for user input 1 or 2 as left or right
            int choice;
            cout << "Make your decision (1 or 2): ";
            cin >> choice;
            // After taking user input this function will move to the next part of story
            if (choice == 1 && current->left != nullptr) {
                current = current->left;
            } else if (choice == 2 && current->right != nullptr) {
                current = current->right;
            } else {
                // This text will print when user input is out of reach
                cout << "@_@ number should be 1 or 2. Please try again!" << endl;
            }
        }
    }
};

#endif // GAMEDECISIONTREE_H
