#include "objparser.h"
#include "tgaimage.h"
#include "vertex.h"
#include <algorithm>
#include <cmath>

Vertex triangleNormal(const Vertex &v1, const Vertex &v2, const Vertex &v3) {
    Vertex edge1 = v2 - v1;
    Vertex edge2 = v3 - v1;
    Vertex normal = edge1 ^ edge2;  // Cross product
    normal.normalize();
    return normal;
}

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

void line(Vertex v0, Vertex v1, TGAImage &image, TGAColor color) { 
    int x0 = v0.x, y0 = v0.y;
    int x1 = v1.x, y1 = v1.y;

    bool steep = false; 
    if (std::abs(x0 - x1) < std::abs(y0 - y1)) { 
        std::swap(x0, y0); 
        std::swap(x1, y1); 
        steep = true; 
    } 
    if (x0 > x1) { 
        std::swap(x0, x1); 
        std::swap(y0, y1); 
    } 
    int dx = x1 - x0; 
    int dy = y1 - y0; 
    int derror2 = std::abs(dy) * 2; 
    int error2 = 0; 
    int y = y0; 
    for (int x = x0; x <= x1; x++) { 
        if (steep) { 
            image.set(y, x, color); 
        } else { 
            image.set(x, y, color); 
        } 
        error2 += derror2; 
        if (error2 > dx) { 
            y += (y1 > y0 ? 1 : -1); 
            error2 -= dx * 2; 
        } 
    } 
} 

bool edgeFunction(Vertex v1, Vertex v2, Vertex v3) {
    return ((v3.x - v1.x) * (v2.y - v1.y) - (v3.y - v1.y) * (v2.x - v1.x) >= 0);
}

bool inTriangle(Vertex v1, Vertex v2, Vertex v3, Vertex v4) {
    bool inside = true;
    inside &= edgeFunction(v1, v2, v4);
    inside &= edgeFunction(v2, v3, v4);
    inside &= edgeFunction(v3, v1, v4);
    return inside;
}

int main() {
    objparser obj_parser("african_head.obj");
    TGAImage image(500, 500, TGAImage::RGB);
    Vertex light_dir(0, 0, -1); // define light_dir

    for (const auto& face : obj_parser.faces) {
        Vertex v1s((image.get_width() / 2) * (obj_parser.vertices[face[0] - 1][0] + 1),
                   (image.get_height() / 2) * (obj_parser.vertices[face[0] - 1][1] + 1));
        Vertex v2s((image.get_width() / 2) * (obj_parser.vertices[face[1] - 1][0] + 1),
                   (image.get_height() / 2) * (obj_parser.vertices[face[1] - 1][1] + 1));
        Vertex v3s((image.get_width() / 2) * (obj_parser.vertices[face[2] - 1][0] + 1),
                   (image.get_height() / 2) * (obj_parser.vertices[face[2] - 1][1] + 1));

        Vertex v1w(obj_parser.vertices[face[0] - 1][0], 
                   obj_parser.vertices[face[0] - 1][1], 
                   obj_parser.vertices[face[0] - 1][2]);

        Vertex v2w(obj_parser.vertices[face[1] - 1][0], 
                   obj_parser.vertices[face[1] - 1][1], 
                   obj_parser.vertices[face[1] - 1][2]);

        Vertex v3w(obj_parser.vertices[face[2] - 1][0], 
                   obj_parser.vertices[face[2] - 1][1], 
                   obj_parser.vertices[face[2] - 1][2]);

        TGAColor colour = TGAColor(rand() % 255, rand() % 255, rand() % 255, 255);

        int minX = std::min({static_cast<int>(v1s.x), static_cast<int>(v2s.x), static_cast<int>(v3s.x)});
        int minY = std::min({static_cast<int>(v1s.y), static_cast<int>(v2s.y), static_cast<int>(v3s.y)});
        int maxX = std::max({static_cast<int>(v1s.x), static_cast<int>(v2s.x), static_cast<int>(v3s.x)});
        int maxY = std::max({static_cast<int>(v1s.y), static_cast<int>(v2s.y), static_cast<int>(v3s.y)});
        
        Vertex normal = triangleNormal(v1w, v2w, v3w);
        float intensity = normal.dot(light_dir);
        
        if (intensity > 0) {
            TGAColor color = TGAColor(intensity * 255, intensity * 255, intensity * 255, 255);

            for (int i = minX; i <= maxX; i++) {
                for (int j = minY; j <= maxY; j++) {
                    Vertex p(i, j);
                    if (inTriangle(v1s, v2s, v3s, p)) {
                        image.set(i, j, color);
                    }
                }
            }
        }
    }

    image.flip_vertically();
    image.write_tga_file("output.tga");
    return 0;
}
