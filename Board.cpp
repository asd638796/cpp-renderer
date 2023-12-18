#include <iostream>
#include "Board.h"
using namespace std;




Board::Board(){
    for(int i =0; i < 9; i++){
        arr[i] = "0";
    }
}

void Board::show_board(){  
cout << this->arr[0] + " | " + this->arr[1] + " | " + this->arr[2] << endl;
cout << this->arr[3] + " | " + this->arr[4] + " | " + this->arr[5] << endl;
cout << this->arr[6] + " | " + this->arr[7] + " | " + this->arr[8] << endl;
}

void Board::set_board(int index, string val){
    this->arr[index] = val;
}


bool Board::check_win(string board[], string icon){
    if(board[0] == icon & board[1] == icon & board[2] == icon){
        return false;
    }else if (board[3] == icon & board[4] == icon & board[7] == icon){
        return false;
    }else if (board[6] == icon & board[7] == icon & board[8] == icon){
        return false;
    }else if (board[0] == icon & board[3] == icon & board[6] == icon){
        return false;
    }else if (board[1] == icon & board[4] == icon & board[7] == icon){
        return false;
    }else if (board[2] == icon & board[5] == icon & board[8] == icon){
        return false;
    }else if (board[0] == icon & board[4] == icon & board[8] == icon){
        return false;
    }else if (board[6] == icon & board[4] == icon & board[2] == icon){
        return false;
    }
    
}


