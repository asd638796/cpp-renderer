#include "objparser.h"


objparser::objparser(string filename){
    file.open(filename);
    
    if(file.fail()){
        cout << "file failed to open" << endl;        
    }

    string line;
    float vertex[3];

    while(getline(file, line)){
        if(line.at(0) == 'v'){
            for(int i = 0; i < 3; i++){
                
            }
        }
    }

    //parse vertices




}