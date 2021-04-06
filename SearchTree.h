//
// Created by Atalay Kucukoglu on 02/04/2021.
// Student ID: 150170074
//

#ifndef HW1_SEARCHTREE_H
#define HW1_SEARCHTREE_H

#include <vector>
#include <map>
#include <string>
#include <queue>
#include "Node.h"
#include "ConstraintsChecker.h"
#include <cmath>
#include <fstream>


class SearchTree {
    Node* root;     // root of tree
    string inputChars;  // unique chars
    ConstraintsChecker* checker;   // static checker class
    Node* solution = nullptr;   // solution node
    int totalVisited = 0;   // total nodes visited during search
    int totalNodeCount = 1; // include root
public:
    SearchTree(string inputChars, ConstraintsChecker* checker)
    : inputChars(inputChars), checker(checker) {
        root = new Node(inputChars);
        createTree(root, nullptr, inputChars);
    };
    ~SearchTree() {
        this->deleteTree(root);
    }
    void createTree(Node *root, Node* parent, string inputChars);
    Node* searchDfs(Node* root);
    Node* searchBfs(Node* root);
    void deleteTree(Node* root);
    Node *getRoot();
    void setSolution(Node *node);
    void printResults();
    void write2File(string filename);
};

void SearchTree::createTree(Node *root, Node* parent, string inputChars) {
    if (inputChars == "" || !root) return;
    char ch = inputChars[0];   // first char of inputChars
    // the rest of the string will be passed recursively
    string rest = inputChars.substr(1, string::npos);
    // traverse among the children
    for (int i = 0; i < 10; i++) {
        // check if candidate node satisfies base constraints
        // if false, do not create the node. else create
        if (!checker->checkConstraints(root, ch, i)) continue;
        // create a new node
        Node* current = new Node(this->inputChars, root);
        // increment total node count
        totalNodeCount++;
        // set ch in guess to i
        current->setGuess(ch, i);
        // assign new node to ith children of root
        root->setChild(current, i);
        // call function with the children, root and rest of the string
        createTree(root->children[i], root, rest);
    }
}

/*
 * clears allocated memory
 * @params root: root of tree to be deleted
 */
void SearchTree::deleteTree(Node* root) {
    if (!root) return;
    for (int i = 0; i < 10; i++) {
        deleteTree(root->children[i]);
    }
    delete root;
    return;
}

Node *SearchTree::getRoot() {
    return root;
}

Node* SearchTree::searchDfs(Node* root) {
    // if root is a nullptr, return
    if (!root) {
        return nullptr;
    }
    // increment visited node count
    totalVisited++;

    // if root is the solution we want, set solution and return root
    for (int i = 0; i < 10; i++) {
        // if solution is already found, return
        // this makes all recursions stop immediately after finding a solution
        if (solution) return solution;
        searchDfs(root->children[i]);
    }
    if (checker->isSolvable(root) && checker->isSolution(root)) {
        setSolution(root);
        return root;
    }
    return nullptr;
}

void SearchTree::setSolution(Node *node) {
    solution = node;
    return;
}

void SearchTree::printResults() {
    cout << "Total nodes kept in memory: " << totalNodeCount << endl;
    cout << "Total nodes visited: " << totalVisited << " (" << (double(totalVisited) / double(totalNodeCount))*100 << " %)" << endl;
    cout << "Solution: " << endl;
    if (solution) solution->printNode();
    else cout << "no solution found." << endl;
}

void SearchTree::write2File(string filename) {
    ofstream fileOut;   // file pointer
    fileOut.open(filename); // open file

    // if error, print and exit program
    if (!fileOut.is_open()) {
        cout << "Output file cannot be opened for writing results. Please give file name including '.txt'." << endl;
        exit(1);
    }
    // print numbers as first row
    for (int i = 0; i < 10; i++) {
        fileOut << "\t" << i;
    }
    fileOut << endl;
    // for each row, print the chars and matrix
    for (char ch : checker->getUniqueChars()) {
        int value = solution ? solution->getGuessByChar(ch) : -1;
        fileOut << ch;
        for (int i = 0; i < 10; i++) {
            if (i == value) fileOut << "\t" << 1;
            else fileOut <<  "\t" << ".";
        }
        fileOut << endl;
    }
    // close file
    fileOut.close();
}


#endif //HW1_SEARCHTREE_H





























