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
    int random_number_init = random_number;

    Board board;
    Player player1("x");
    Player player2("o");

    board.show_board();


    while(1){
        
        int next_move;
        if((random_number - random_number_init) == 9){
            cout << "draw" << endl;
        }

        if(random_number % 2 == 0){
            cout << "Enter a number" << endl;
            cin >> next_move;
            int move_validator = board.set_board(next_move, player1.icon);
            while(move_validator == 0){
                cout << "Enter a number" << endl;
                cin >> next_move;
                move_validator = board.set_board(next_move, player1.icon);
            }

            board.set_board(next_move, player1.icon);
            
            board.show_board();

            if(! (board.check_win(board.arr, player1.icon))){
                cout << "x won" << endl;
                break;
            }
            random_number++;
            
        }else{
            cout << "Enter a number" << endl;
            cin >> next_move;
            int move_validator = board.set_board(next_move, player2.icon);
            while(move_validator == 0){
                cout << "Enter a number" << endl;
                cin >> next_move;
                move_validator = board.set_board(next_move, player2.icon);
            }

            board.set_board(next_move, player2.icon);
            board.show_board();
            if(!(board.check_win(board.arr, player2.icon))){
                cout << "o won" << endl;
                break;
            }
            random_number++;
        }
        
        
    }
    
    
    return 0;
}