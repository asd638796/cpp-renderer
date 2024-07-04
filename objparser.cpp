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
        }else if(!line.empty() && line.substr(0,2) == "vt"){
            parseVtLine(line);
        }
    }
}

void objparser::parseVtLine(const string& line) {
    vector<float> coords;
    istringstream iss(line.substr(3)); // Start reading after "vt "
    float u, v;
    
    // Read the first two values
    iss >> u >> v;
    
    // Store the coordinates
    coords.push_back(u);
    coords.push_back(v);

    vt.push_back(coords);
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
    vector<int> texCoords; // Vector to store texture coordinate indices
    istringstream iss(line.substr(2));
    string triple;
    while (iss >> triple) {
        int firstSlashPos = triple.find('/');
        int secondSlashPos = triple.find('/', firstSlashPos + 1);

        int vertexIndex = stoi(triple.substr(0, firstSlashPos));
        int texCoordIndex = stoi(triple.substr(firstSlashPos + 1, secondSlashPos - firstSlashPos - 1));

        face.push_back(vertexIndex);
        texCoords.push_back(texCoordIndex);
    }
    
    // Check if face needs to be reversed
    if (face.size() == 3) {
        swap(face[1], face[2]);
        swap(texCoords[1], texCoords[2]); // Also swap the texture coordinates
    }
    
    faces.push_back(face);
    faceTexCoords.push_back(texCoords); // Store the texture coordinate indices
}
