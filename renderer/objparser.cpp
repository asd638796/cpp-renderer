#include "objparser.h"


objparser::objparser(string filename){
    file.open(filename);
    
    if(file.fail()){
        cout << "file failed to open" << endl;        
    }

    string line;

    while(getline(file, line)){
        lines.push_back(line);
    }

    //parse vertices

    


}