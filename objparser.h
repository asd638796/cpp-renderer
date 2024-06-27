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
    deque<vector<int>> faces;
    ifstream file;
    objparser(string filename);

private:
    void parseVertexLine(const string& line);
    void parseFaceLine(const string& line);
};

#endif // OBJPARSER_H
