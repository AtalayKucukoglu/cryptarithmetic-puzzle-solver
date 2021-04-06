//
// Created by Atalay Kucukoglu on 03/04/2021.
// Student ID: 150170074
//

#ifndef HW1_CONSTRAINTSCHECKER_H
#define HW1_CONSTRAINTSCHECKER_H

#include <map>
#include <string>

#include "Node.h"

using namespace std;

class ConstraintsChecker {
    const string operand1;
    const string operand2;
    const string result;
    // global constraints
    map<char, int[10]> constraints;  // 1: allowed, 0: not allowed
    map<char, int> foundChars;  //  keeps track of found chars

    void findConstraints();
    void initConstraints();
public:
    ConstraintsChecker(string operand1, string operand2, string result)
    : operand1(operand1), operand2(operand2), result(result)
    {
        initConstraints();
        findConstraints();
    }
    string getUniqueChars();    // return unique chars in operand1, operand2 and result
//    Node createNodeWithConstraints(Node* parent);
    bool isSolution(Node *candidate);
    bool checkConstraints(Node* parent, char ch, int number);
    bool isSolvable(Node *node);
};

string ConstraintsChecker::getUniqueChars() {
    string uniqueChars = "";
    string allChars = operand1 + operand2 + result;
    for (unsigned int i = 0; i < allChars.size(); i++) {
        // if character does not occur in unique chars
        if (uniqueChars.find(allChars[i]) == string::npos) {
            uniqueChars.push_back(allChars[i]);
        }
    }
    return uniqueChars;
}

// inits all constraints to allowed
void ConstraintsChecker::initConstraints() {
    string uniqueChars = getUniqueChars();
    // traverse in all unique chars
    for (unsigned int i = 0; i < uniqueChars.size(); i++) {
        for (int j = 0; j < 10; j++) {
            // set all values to allowed
            constraints[uniqueChars[i]][j] = 1;
        }
    }
}

// finds basic constraints
void ConstraintsChecker::findConstraints() {
    // first letters are always non-zero
    constraints[operand1[0]][0] = 0;
    constraints[operand2[0]][0] = 0;
    constraints[result[0]][0] = 0;
    // if result has more digits, result's first letter is 1
    if (result.size() > max(operand1.size(), operand2.size())) {
        foundChars[result[0]] = 1;
    }
}

/*
 * checks if candidate node is the solution for the puzzle
 * @params candidate: node to be checked
 * @retuns true if candidate is the solution, else false
 */
bool ConstraintsChecker::isSolution(Node* candidate) {
    int lastCarry = 0;
    int iOp1 = 0;   // index of operand1
    int iOp2 = 0;   // index of operand2

    // number of carries = result.size()
    // this for loop checks all constraints in summation
    for (unsigned int i = 0; i < result.size(); i++) {
        int sum = 0;
        // indexes of each operand
        iOp1 = operand1.size() - 1 - i;
        iOp2 = operand2.size() - 1 - i;
        // current chars to be added
        char charOp1 = operand1[iOp1], charOp2 = operand2[iOp2];
        char resChar = result[result.size() - 1 - i];
        // add guesses to sum
        sum += iOp1 >= 0 ? candidate->getGuessByChar(charOp1) : 0;
        sum += iOp2 >= 0 ? candidate->getGuessByChar(charOp2) : 0;
        // set new carry
        int newCarry = lastCarry + sum >= 10 ? 1 : 0;
        // check if summation is a correct one
        if (lastCarry + sum == candidate->getGuessByChar(resChar) + 10*newCarry) {
            // correct for this step. continue checking
        } else {
            // not correct. return false immediately
            return false;
        }
        lastCarry = newCarry; // update carry
    }
    // if function survives up to here, then all the constraints are satisfied
    return true;
}

/*
 * while creating the tree, this node will create a child tree base on parent
 */
bool ConstraintsChecker::checkConstraints(Node* parent, char ch, int number) {
    // is character - number tuple allowed?
    if (!constraints[ch][number]) return false;
    // is character found before? if so, is number matches found value?
    if (foundChars.find(ch) != foundChars.end() && foundChars[ch] != number) return false;
    // is the number reserved before in parent?
    if (parent && parent->reserved[number]) return false;
    // if candidate node passes all constraints, return true
    return true;
}

// returns false if a guess is -1 ( not initialized yet)
bool ConstraintsChecker::isSolvable(Node* node) {
    for( char ch : getUniqueChars()) {
        if (node->getGuessByChar(ch) == -1) return false;
    }
    return true;
}

#endif //HW1_CONSTRAINTSCHECKER_H
