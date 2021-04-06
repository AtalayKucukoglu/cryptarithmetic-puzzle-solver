//
// Created by Atalay Kucukoglu on 02/04/2021.
// Student ID: 150170074
//

/*
 * Istanbul Technical University
 * BLG 336E Analysis of Algorithms II
 * Homework I
 *
 * A program to solve 2-operand cryptoarithmic addition puzzle.
 * It uses DFS or BFS to solve the puzzle
 * Prints duration, created node count, visited node count and solution if found
 *
 * compile and link:
 * g++ -std=c++11  -Wall -Werror main.cpp -o puzzle_solver
 *
 * Run: ./puzzle_solver [Algorithm] [Operand1] [Operand2] [Result] [OutputFilePath]
 * Example use: ./puzzle_solver DFS TWO TWO FOUR solution.txt
 *
 */

#include <iostream>
#include <cstdio>
#include <ctime>
#include <vector>
#include <map>
#include <fstream>
#include <string>

#include "SearchTree.h"
#include "ConstraintsChecker.h"


using std::cout;

int main(int argCount, char** args) {
    // get command line arguments
    string searchAlgo = args[1];    // DFS or BFS
    string operand1 = args[2];
    string operand2 = args[3];
    string result = args[4];
    string outputFileName = args[5];

    // start timer
    std::clock_t start;
    double duration;
    start = std::clock();

    // create constraints checker class. this class will check solutions,
    // prevents creating wrong nodes that do not satisfy basic constraints,
    // and do other check operations
    // it is static because we want only one instance of it
    static ConstraintsChecker* checker = new ConstraintsChecker(operand1, operand2, result);

    // creating tree with unique chars in puzzle and the checker class
    SearchTree* puzzle = new SearchTree(checker->getUniqueChars(), checker);
    if (searchAlgo == "DFS") puzzle->searchDfs(puzzle->getRoot());
    if (searchAlgo == "BFS") puzzle->searchDfs(puzzle->getRoot()); // TODO
    // print results
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    cout << "Duration: " << duration << " seconds." << endl;
    puzzle->printResults();
    // write resuls to specified output file
    puzzle->write2File(outputFileName);
    return 0;
}
