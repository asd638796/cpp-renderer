#include "objparser.h"

objparser::objparser(string filename) {
    file.open(filename);
    
    if (file.fail()) {
        cout << "File failed to open" << endl;        
    }

    string line;
    while (getline(file, line)) {
        if (!line.empty() && line.substr(0, 2) == "v ") {
            parseVertexLine(line);
        } else if (!line.empty() && line.substr(0, 2) == "f ") {
            parseFaceLine(line);
        }
    }
}

void objparser::parseVertexLine(const string& line) {
    vector<float> vertex;
    istringstream iss(line.substr(2));
    float val;
    
    while (iss >> val) {
        vertex.push_back(val);
    }

    vertices.push_back(vertex);
}

void objparser::parseFaceLine(const string& line) {
    vector<int> face;
    istringstream iss(line.substr(2));
    string triple;
    while (iss >> triple) {
        int slashPos = triple.find('/');
        int index = stoi(triple.substr(0, slashPos));
        face.push_back(index);
    }
    
    // Check if face needs to be reversed
    if (face.size() == 3) {
        swap(face[1], face[2]);
    }
    
    faces.push_back(face);
}
