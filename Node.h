//
// Created by Atalay Kucukoglu on 02/04/2021.
// Student ID: 150170074
//

#ifndef HW1_NODE_H
#define HW1_NODE_H


#include <vector>
#include <map>
#include <string>

using namespace std;

class Node {
public:
    int reserved[10] = {0};     // reserved[i] = 1 is the number is used before
    map<char, int> guess;       // all the guesses for characters
    Node* children[10] = {nullptr}; // children
    // constructor
    Node() {}   // default constructor
    Node(string inputChars, Node* parent = nullptr) {
        if (parent) {
            guess = parent->guess;
            // copy reserved
            for (int i = 0; i < 10; i++) reserved[i] = parent->reserved[i];
        }
        // travers among chars
        for(unsigned int i = 0; i < inputChars.size(); i++) {
            // if parent node has a value for the char, do not reset that
            if (parent && parent->guess[inputChars[i]] != -1) continue;
            guess[inputChars[i]] = -1;
        }
    }
    int getGuessByChar(char a);
    void setGuess(char letter, int number);
    void setChild(Node *node, int index);
    void printNode();
};

// sets number to char
void Node::setGuess(char letter, int number) {
    this->guess[letter] = number;
    reserved[number] = 1;
}

// returns guess of char
int Node::getGuessByChar(char a) {
    return guess[a];
}

// assignes node to the children at index
void Node::setChild(Node *node, int index) {
    this->children[index] = node;
}

/*
 * prints the guesses of characters
 */
void Node::printNode() {
    for(auto ite : guess) {
        cout << ite.first << ": " << ite.second << ", ";
    }
    cout << endl;
}



#endif //HW1_NODE_H
