#include "objparser.h"



int main(){

    objparser obj_parser("african_head.obj");

    for (int i = 0; i < obj_parser.lines.size(); i++) {
        cout << "Line " << i + 1 << ": " << obj_parser.lines[i] << endl;
    }

    return 0;
}