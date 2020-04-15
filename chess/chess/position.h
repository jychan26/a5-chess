#ifndef POSITION_H
#define POSITION_H
#include <string>
#include <sstream>
using namespace std;

struct Position {
    int row;
    char col;
    Position(string str) {
        col = str.front();
        str = str.back();
        istringstream iss(str);
        iss >> row;
    }
    bool isValid() {
        return (row >= 0 && row <= 7) && (col >= 'a' && col <= 'h');
    }
};

#endif
