#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include "Player.h"
using namespace std;

class Board {
public:
    
    string arr[9];

    Board();

    void show_board();

    int set_board(int index, string val);

    bool check_win(string board[], string icon);

    int* blanks(string board[]);

    bool isFull(string board[]);

};

#endif 