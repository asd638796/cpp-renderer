#include "objparser.h"
#include "tgaimage.h"


const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) { 
    bool steep = false; 
    if (std::abs(x0-x1)<std::abs(y0-y1)) { 
        std::swap(x0, y0); 
        std::swap(x1, y1); 
        steep = true; 
    } 
    if (x0>x1) { 
        std::swap(x0, x1); 
        std::swap(y0, y1); 
    } 
    int dx = x1-x0; 
    int dy = y1-y0; 
    int derror2 = std::abs(dy)*2; 
    int error2 = 0; 
    int y = y0; 
    for (int x=x0; x<=x1; x++) { 
        if (steep) { 
            image.set(y, x, color); 
        } else { 
            image.set(x, y, color); 
        } 
        error2 += derror2; 
        if (error2 > dx) { 
            y += (y1>y0?1:-1); 
            error2 -= dx*2; 
        } 
    } 
} 

bool edgeFunction(int v1x, int v1y, int v2x, int v2y, int v3x, int v3y)
{
    return ((v3x - v1x) * (v2y - v1y) - (v3y - v1y) * (v2x - v1x) >= 0);
}

bool inTriangle(int v1x, int v1y, int v2x, int v2y, int v3x, int v3y, int v4x, int v4y)
{
    bool inside = true;
    inside &= edgeFunction(v1x, v1y, v2x, v2y, v4x, v4y);
    inside &= edgeFunction(v2x, v2y, v3x, v3y, v4x, v4y);
    inside &= edgeFunction(v3x, v3y, v1x, v1y, v4x, v4y);

    return inside;
}


int main(){

    objparser obj_parser("african_head.obj");
    TGAImage image(500, 500, TGAImage::RGB);
    

    for(vector<int> face : obj_parser.faces){
        
        vector<float> v1 = obj_parser.vertices[face[0] - 1];
        vector<float> v2 = obj_parser.vertices[face[1] - 1];
        vector<float> v3 = obj_parser.vertices[face[2] - 1];
        TGAColor colour = TGAColor(rand()%255, rand()%255, rand()%255, 255);

        int v1x = int ((image.get_width() / 2) + image.get_width() / 2 * v1[0]);
        int v1y = int ((image.get_height() / 2) + image.get_height() / 2 * v1[1]);
        int v2x = int ((image.get_width() / 2) + image.get_width() / 2 * v2[0]);
        int v2y = int ((image.get_height() / 2) + image.get_height() / 2 * v2[1]);
        int v3x = int ((image.get_width() / 2) + image.get_width() / 2 * v3[0]);
        int v3y = int ((image.get_height() / 2) + image.get_height() / 2 * v3[1]);

        int minX = min(v3x, min(v1x, v2x));
        int minY = min(v3y, min(v1y, v2y));
        int maxX = max(v3x, max(v1x, v2x));
        int maxY = max(v3y, max(v1y, v2y));

        for(int i =minX; i < maxX; i++){
            for(int j=minY; j < maxY ; j++){
                if(inTriangle(v1x, v1y, v2x, v2y, v3x, v3y, i, j)){
                    image.set(i,j,colour);
                }
            }
        }
        
    }
    
	
    image.flip_vertically();
	image.write_tga_file("output.tga");
    return 0;
}