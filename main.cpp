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

void fillBottomFlatTriangle(int v1_x, int v1_y, int v2_x, int v2_y, int v3_x, int v3_y, TGAImage &image, TGAColor color){
    float invslope1 = (v2_x - v1_x) / (v2_y - v1_y);
    float invslope2 = (v3_x - v1_x / (v3_y - v1_y));

    float curx1 = v1_x;
    float curx2 = v1_x;

    for(int scanlineY = v1_y; scanlineY <= v2_y; scanlineY++){
        line((int) curx1, scanlineY, (int) curx2, scanlineY, image, color);
        curx1 += invslope1;
        curx2 += invslope2;
    }


}

void fillTopFlatTriangle(int v1_x, int v1_y, int v2_x, int v2_y, int v3_x, int v3_y, TGAImage &image, TGAColor color){
    float invslope1 = (v3_x - v1_x) / (v3_y - v1_y);
    float invslope2 = (v3_x - v2_x) / (v3_y - v2_y);

    float curx1 = v3_x;
    float curx2 = v3_x;

    for(int scanlineY = v3_y; scanlineY > v1_y; scanlineY--){
        line((int) curx1, scanlineY, (int) curx2, scanlineY, image, color);
        curx1 -= invslope1;
        curx2 -= invslope2;
    }


}


void drawTriangle(int v1_x, int v1_y, int v2_x, int v2_y, int v3_x, int v3_y, TGAImage &image, TGAColor color)
{
   /* at first sort the three vertices by y-coordinate ascending so v1 is the topmost vertice */
  if(v1_y > v2_y){  
    swap(v1_y, v2_y);
    swap(v1_x, v2_x);
  }
  
  if(v2_y > v3_y){
    swap(v2_y, v3_y);
    swap(v2_x, v3_x);
  }

  if(v1_y > v2_y){
    swap(v1_y, v2_y);
    swap(v1_x, v2_x);
  }

  
  /* check for trivial case of bottom-flat triangle */
  if (v2_y == v3_y)
  {
    fillBottomFlatTriangle(v1_x, v1_y, v2_x, v2_y, v3_x, v3_y, image, color);
  }
  /* check for trivial case of top-flat triangle */
  else if (v1_y == v2_y)
  {
    fillTopFlatTriangle(v1_x, v1_y, v2_x, v2_y, v3_x, v3_y, image, color);
  }
  else
  {
    /* general case - split the triangle in a topflat and bottom-flat one */
    int v4_x = (int)(v1_x + ((float)(v2_y - v1_y) / (float)(v3_y - v1_y)) * (v3_x - v1_x));
    int v4_y = v2_y;

    
    fillBottomFlatTriangle(v1_x, v1_y, v2_x, v2_y,  v4_x, v4_y, image, color);
    //fillTopFlatTriangle(v2_x, v2_y, v4_x, v4_y, v3_x, v3_y, image, color);

    
  }
}

int main(){

    objparser obj_parser("african_head.obj");
    TGAImage image(500, 500, TGAImage::RGB);

    /*for(vector<int> face : obj_parser.faces){
        
        vector<float> v1 = obj_parser.vertices[face[0] - 1];
        vector<float> v2 = obj_parser.vertices[face[1] - 1];
        vector<float> v3 = obj_parser.vertices[face[2] - 1];

        int v1x = int ((image.get_width() / 2) + image.get_width() / 2 * v1[0]);
        int v1y = int ((image.get_height() / 2) + image.get_height() / 2 * v1[1]);
        int v2x = int ((image.get_width() / 2) + image.get_width() / 2 * v2[0]);
        int v2y = int ((image.get_height() / 2) + image.get_height() / 2 * v2[1]);
        int v3x = int ((image.get_width() / 2) + image.get_width() / 2 * v3[0]);
        int v3y = int ((image.get_height() / 2) + image.get_height() / 2 * v3[1]);

        
        drawTriangle(v1x, v1y, v2x, v2y, v3x, v3y, image, 
        TGAColor(rand()%255, rand()%255, rand()%255, 255));
        
        
    }*/

    drawTriangle(200, 200, 150, 150, 78, 78, image, 
        TGAColor(rand()%255, rand()%255, rand()%255, 255));

    

    
    
	
    image.flip_vertically();
	image.write_tga_file("output.tga");
    return 0;
}