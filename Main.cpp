#include <iostream>
#include "Board.h"
#include "Player.h"
#include <random>


using namespace std;


int main() {
    
    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(1, 10);

    
    int random_number = distribution(gen);
    

    Board board;
    Player player1("x");
    Player player2("o");

    board.show_board();

    while(1){
        
        int next_move;
        

        if(random_number % 2 == 0){
            cout << "Enter a number" << endl;
            cin >> next_move;
            board.set_board(next_move, player1.icon);
            board.show_board();
            board.check_win(board.arr, player1.icon);
            
        }else{
            cout << "Enter a number" << endl;
            cin >> next_move;
            board.set_board(next_move, player2.icon);
            board.show_board();
            board.check_win(board.arr, player2.icon);
        }
        
        

        
        

    }
    
    
    return 0;
}