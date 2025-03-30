[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/jIKk4bke)
# CS210 Data Structures SP25
## Programming Assignment 2: Text-Based RPG Using Decision Trees

### **Student Name:** `Duy Dao`
### **Student ID:** `131609826`

---

## **1. Project Overview**
This project is a simple text-based RPG game that uses a binary decision tree to tell a story. Each point in the story is stored as a node, and players move through the game by picking between two choices at each step. The tree is built using data from a text file, and the game ends when the player reaches a node with no further paths.
At each step, the player is asked to choose either option "1" or "2", which sends them down the left or right path in the tree. Once they hit a leaf node (a node that doesn't lead anywhere else), the story ends and the game finishes.
---

## **2. Folder & File Structure**
- **`main.cpp`** → This is where the program starts. It creates a GameDecisionTree object using the Story class, loads the story data from story.txt, and then runs the game using playGame().

- **`GameDecisionTree.h`** → This file defines the main tree structure and handles how the story is built and played. It includes the constructor, the method to load the story from the file, and the method to walk through the tree based on the user's choices.

- **`Node.h`** → This describes the Node class. Each node holds a piece of story data and has pointers to its left and right child nodes.

- **`Story.h`** → Contains the Story class, which stores the description and decision data for each event in the game. It includes constructors to initialize this data.

- **`story.txt`** → This file contains the actual story. Each line has the format: eventNumber | description | leftEventNumber | rightEventNumber. The game reads and parses each line to create story nodes.

---

## **3. Decision Tree Construction**
The decision tree is built by reading the story file line-by-line. Each line is split using a delimiter (|) into four parts: the event number, the description, and the event numbers for the left and right options.
Each story line is turned into a Story object, which is then wrapped in a node and stored in a map. After all nodes are created, I loop through the map and connect the nodes based on the left and right event numbers. If a node's left or right number is -1, that means it's a dead end and we set the pointer to nullptr.
---

## **4. Game Traversal**
When the game starts, it begins at the root of the tree and displays the current story description. The player will be ask to picks either 1 or 2 to continue down the left or right branch of the tree.

If a node has no children (both left and right are nullptr), it means the story has ended, and the game prints a final message. Some nodes can be reached through different paths, which makes the story more interesting and allows for different endings depending on the choices.

---

## **5. File Parsing & Data Loading**
The game reads the story from a file using ifstream, and each line is broken down into smaller parts using a delimiter. These parts are then used to create Story objects, which are stored in a map for fast access by event number.

While parsing, I had to make sure to handle errors like blank lines or missing fields. Adding checks helped avoid crashes and made the program more stable.

---

## **6. Debugging Process (Errors & Fixes)**
One of the biggest bugs I had was an infinite loop and I realized one of the nodes was pointing back to itself. I checked my story file and found that I had copied the same event number by accident.

Another big issue was getting a SIGABRT error. It turned out I was trying to link a node to another one that didn’t exist in the story file. So I added checks to make sure every node I was linking to actually existed in the map. After that, the game stopped crashing and worked fine.

---

## **7. Sample Output & Walkthrough**

You awaken in a magical forest filled with glowing trees and floating islands. Do you follow the flower path or climb the cloud stairs?

Make your decision (1 or 2): 1 (left)

On the flower path, you meet a fairy offering you a mysterious potion. Do you drink it or politely decline?

Make your decision (1 or 2): 1 (left)

Drinking the potion, you suddenly gain the power of flight. Do you fly toward the floating city or the enchanted mountains?

Make your decision (1 or 2): 1 (left)

In the floating city, you're offered the role of sky guardian. Do you accept or seek adventure elsewhere?

Make your decision (1 or 2): 1 (left)

Accepting the role, you become a legendary guardian, respected by all.

[You make a wise choices ^_^]

---

## **8. Big-O Analysis of Core Methods**
- **Loading the tree from the file** → This is `O(n)` because each line in story.txt is one story event, and we go through the file line by line to process them all. For each line, we parse the data and create a node, then store it in a map. Once all the nodes are created, we go back and link them using the event numbers. Since we only go through each event once and do constant-time work per line, the overall time is linear — O(n), where n is the total number of events in the story.
- **Searching for an event in the tree** → `O(log n)` In a balanced tree, each choice cuts the path in half. So finding a specific event follows a binary pattern, making it log-based on average.
- **Game traversal efficiency** → `O(log n)`, As the player moves through choices, they go from root to leaf. The number of steps depends on tree height, which is about log n in a balanced structure.

---

## **9. Edge Cases & Testing**
I tested what happens when two different choices lead to the same node (shared paths). It worked fine with no duplicated nodes and the game didn’t crash.

I also checked what happens if the story file is messed up or missing data. The game printed an error message instead of crashing, which is what I wanted.

---

## **10. Justification of Additional Features (If Any)**
There is no extra additional feature that I add for this Programming.

---

## **Final Notes**
- **README is mandatory** → `(-10 points deduction if missing).`
- **Code must compile and run** → `(Code that does not run will receive a 0).`
- **Do not modify provided skeleton code** → `(You may only add to it).
