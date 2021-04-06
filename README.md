# cryptarithmetic-puzzle-solver

A program to solve 2-operand cryptoarithmic addition puzzle.
It uses DFS or BFS to solve the puzzle
Prints duration, created node count, visited node count and solution if found


Istanbul Technical University
BLG 336E Analysis of Algorithms II
Homework I


compile and link:
g++ -std=c++11  -Wall -Werror main.cpp -o puzzle_solver

Run: ./puzzle_solver [Algorithm] [Operand1] [Operand2] [Result] [OutputFilePath]

Example use: ./puzzle_solver DFS TWO TWO FOUR solution.txt
