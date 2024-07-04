#ifndef OBJPARSER_H
#define OBJPARSER_H

#include <iostream>
#include <fstream>
#include <deque>
#include <sstream>
#include <vector>

using namespace std;

class objparser {
public:
    deque<string> lines;
    deque<vector<float>> vertices;
    deque<vector<float>> vt;
    deque<vector<int>> faces;
    deque<vector<int>> faceTexCoords; // Container for face texture coordinate indices
    ifstream file;
    objparser(string filename);

private:
    void parseVertexLine(const string& line);
    void parseFaceLine(const string& line);
    void parseVtLine(const string& line);
};

#endif // OBJPARSER_H
