// Your First C++ Program

#include <iostream>
using namespace std;

class Board{
public:
    
    string arr[9];
    
    Board(){
        for(int i =0; i < 9; i++){
            arr[i] = '0';
        }
    }

    void show_board(){  
    cout << this->arr[0] + " | " + this->arr[1] + " | " + this->arr[2] << endl;
    cout << this->arr[3] + " | " + this->arr[4] + " | " + this->arr[5] << endl;
    cout << this->arr[6] + " | " + this->arr[7] + " | " + this->arr[8] << endl;
    }

    void set_board(int index, string val){
        this->arr[index] = val;
    }

};

