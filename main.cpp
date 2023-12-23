#include "objparser.h"



int main(){

    objparser obj_parser("african_head.obj");

    for(vector<float> v : obj_parser.vertices){
        std::cout << std::to_string(v[0]) + " , " + std::to_string(v[1]) + " , " + std::to_string(v[2]) << std::endl;
    }

    return 0;
}