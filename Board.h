#ifndef BOARD_H
#define BOARD_H

#include <iostream>
using namespace std;

class Board {
public:
    string arr[9];

    Board();

    void show_board();

    void set_board(int index, string val);
};

#endif 