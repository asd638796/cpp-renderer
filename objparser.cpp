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
        //parse faces
        }else if(!line.empty() && line.at(0) == 'f'){
            vector<int> face;
            vector<string> triples;
            line.erase(0,2);
            istringstream iss(line);
            string triple;
            int index;
            while(iss >> triple){
                triples.push_back(triple);
            }

            for(int i =0; i<=2; i++){
                int slashpos = triples[i].find('/');
                index = stoi(triples[i].substr(0, slashpos));
                face.push_back(index);
            }

            faces.push_back(face);

        }
    }


}