#ifndef SetSolverSquareSet_h
#define SetSolverSquareSet_h

// Do not add any additional class.
#include <vector>


class SetSolverSquareSet
{
private:
    int value;
public:
    std::vector<int> set;
    SetSolverSquareSet() : value(0), set({1, 2, 3, 4, 5, 6, 7, 8, 9}) {}
    SetSolverSquareSet(int val) : value(val) {
        if (value == 99)
            set = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    }

    void setValue(int val) {
        value = val;
    }

    int getValue() const {
        return value;
    }
    bool isBlack() {
        return value <= 0;
    }
    bool isNotEmpty(){
        return value <10 && value >0;
    }
    bool isEmpty() {
        return value==99;
    }

};

#endif /* SetSolverSquareSet_h */

// William Costales k23081539