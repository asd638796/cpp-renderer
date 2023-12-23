#include "objparser.h"


objparser::objparser(string filename){
    file.open(filename);
    
    if(file.fail()){
        cout << "file failed to open" << endl;        
    }

    string line;
    

    while(getline(file, line)){
        
        //parse vertices


        if(!line.empty() && line.at(0) == 'v' && line.at(1) == ' '){
            vector<float> vertex;
            line.erase(0,2);
            istringstream iss(line);
            float val;
            
            while(iss >> val){
                vertex.push_back(val);
            }

            vertices.push_back(vertex);

        }
    }


}