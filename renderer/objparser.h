#ifndef OBJPARSER_H
#define OBJPARSER_H

#include <iostream>
#include <fstream>
#include <deque>
using namespace std;

class objparser {
public:
    
    deque<string> lines;
    deque<float> vertices;
    ifstream file;
    objparser(string filename);

};

#endif 