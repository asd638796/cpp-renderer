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
    ifstream file;
    objparser(string filename);

};

#endif 