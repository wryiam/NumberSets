#ifndef SetSolver_h
#define SetSolver_h

#include <string>
#include <iostream>
#include <vector>
#include "SetSolverSquareSet.h"

using std::vector;
using std::string;
class SetSolver
{
private:
    int boardSize = 9;
    vector<vector<SetSolverSquareSet>> board;

public:
    void PopulateBoard(const vector<string>& skeletonBoard){
        board = vector<vector<SetSolverSquareSet>>(boardSize, vector<SetSolverSquareSet>(boardSize));
        for (int row = 0; row < boardSize; ++row) {
            int col = 0;
            for (size_t i = 0; i < skeletonBoard[row].size(); ++i) {
                char currentChar = skeletonBoard[row][i];
                switch(currentChar){
                    case '0':
                        board[row][col].setValue(0);
                        break;
                    case '*':
                        board[row][col].setValue(99);
                        break;
                    case '-':
                        board[row][col].setValue(-(skeletonBoard[row][++i] - '0'));
                        break;
                    default:
                        board[row][col].setValue(currentChar - '0');
                        break;
                }
                ++col;
            }
        }
    }

    int ReturnValue(int row, int col) {
        if (row < 0 || row >= boardSize || col < 0 || col >= boardSize){
            return -1;
        }
        return board[row][col].getValue();
    }

    bool validateCompartment(int fixindex, int varindex, bool isRow, int num) {
        int minCompartment = 10;
        int maxCompartment = 0;
        int compartmentSize = 1;

        int lower = varindex - 1;
        int upper = varindex + 1;
        bool lowerDone = false;
        bool upperDone = false;

        while (!lowerDone|| !upperDone) {
            if (!lowerDone) {
                if (lower < 0 ||(isRow&& board[fixindex][lower].isBlack()) ||(!isRow && board[lower][fixindex].isBlack())) {
                    lowerDone = true;
                } 
                else {
                    auto &sqr = isRow ? board[fixindex][lower]:board[lower][fixindex];
                    if (sqr.isEmpty()) {
                        compartmentSize++;
                    } else if (sqr.isNotEmpty()) {
                        compartmentSize++;
                        if (sqr.getValue() < minCompartment) {
                            minCompartment = sqr.getValue();
                        }
                        if (sqr.getValue() > maxCompartment) {
                            maxCompartment = sqr.getValue();
                        }
                    }
                }
            }
            if (!upperDone) {
                if (upper >= boardSize || (isRow && board[fixindex][upper].isBlack()) || (!isRow && board[upper][fixindex].isBlack())) {
                    upperDone = true;
                } else {
                    auto &sqr = isRow ? board[fixindex][upper] : board[upper][fixindex];
                    if (sqr.isEmpty()) {
                        compartmentSize++;
                    } else if (sqr.isNotEmpty()) {
                        compartmentSize++;
                        if (sqr.getValue() < minCompartment) {
                            minCompartment = sqr.getValue();
                        }
                        if (sqr.getValue() > maxCompartment) {
                            maxCompartment = sqr.getValue();
                        }
                    }
                }
            }
            lower--;
            upper++;
        }

        if (minCompartment != 10 && maxCompartment != 0) {
            int upperBound = minCompartment + (compartmentSize - 1);
            int lowerBound = maxCompartment - (compartmentSize - 1);
            if (num > upperBound || num < lowerBound) {
                return false;
            }
        }

        return true;
    }

    bool checkPlace(int row, int col, int num) {
        int boardSize = 9;
        for (int i = 0; i < boardSize; ++i) {
            if (board[row][i].getValue() == num|| board[i][col].getValue() == num ||board[row][i].getValue() ==-num ||board[i][col].getValue() ==-num) {
                return false;
            }
        }
        return validateCompartment(row, col, true, num) && validateCompartment(col, row, false, num);
    }

    void Solve() {  
        if (boardSolver()) {
            return;
        }
    }

    bool boardSolver() {
        for (int i = 0; i <boardSize * boardSize; ++i) {
            int row = i / boardSize;
            int col = i% boardSize;

            if (board[row][col].isEmpty()) {
                if (!tryNumbersInCell(row, col)) {
                    return false;
                }
            }
        }
        return true;
    }

    bool tryNumbersInCell(int row, int col) {
        for (int num : board[row][col].set) {
            if (checkPlace(row, col, num)) {
                board[row][col].setValue(num);

                if (boardSolver()) {
                    return true;
                }
                board[row][col].setValue(99);
            }
        }
        return false;
    }

    /*void DebuggingPrintBoard() const {
        std::cout << "Solved Board:\n";
        for (int row = 0; row < boardSize; ++row) {
            for (int col = 0; col < boardSize; ++col) {
                int value = board[row][col].getValue();
                std::cout << "[" << value << "] ";
            }
            std::cout << "\n";
        }
        std::cout << std::endl;
    }*/

    void PrintBoard() const {
        for (int row = 0; row < boardSize; ++row) {
            for (int col = 0; col < boardSize; ++col) {
                std::cout << board[row][col].getValue() << " ";
            }
            std::cout << "\n";
        }
    }
};

#endif /* SetSolver_h */

// William Costales k23081539