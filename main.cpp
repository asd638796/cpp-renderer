#include "objparser.h"
#include "tgaimage.h"
#include "vec3f.h"
#include "vec2f.h"
#include <algorithm>
#include <cmath>
#include <limits>

Vec3f triangleNormal(const Vec3f &v1, const Vec3f &v2, const Vec3f &v3) {
    Vec3f edge1 = v2 - v1;
    Vec3f edge2 = v3 - v1;
    Vec3f normal = edge1 ^ edge2;  // Cross product
    normal.normalize();
    return normal;
}

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

void line(Vec2f v0, Vec2f v1, TGAImage &image, TGAColor color) { 
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

Vec3f barycentric(const Vec3f &A, const Vec3f &B, const Vec3f &C, const Vec3f &P) {
    Vec3f s[2];
    for (int i = 2; i--;) {
        s[i][0] = C[i] - A[i];
        s[i][1] = B[i] - A[i];
        s[i][2] = A[i] - P[i];
    }
    Vec3f u = s[0] ^ s[1];
    if (std::abs(u[2]) > 1e-2) // Avoid degenerate triangles
        return Vec3f(1.f - (u.x + u.y) / u.z, u.y / u.z, u.x / u.z);
    return Vec3f(-1, 1, 1); // In this case generate negative coordinates, it will be outside of the triangle
}

void triangle(Vec3f *pts, float *zbuffer, TGAImage &image, Vec2f *tex, TGAImage &texture) {
    Vec2f bboxmin( std::numeric_limits<float>::max(),  std::numeric_limits<float>::max());
    Vec2f bboxmax(-std::numeric_limits<float>::max(), -std::numeric_limits<float>::max());
    Vec2f clamp(image.get_width() - 1, image.get_height() - 1);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            bboxmin[j] = std::max(0.f,      std::min(bboxmin[j], pts[i][j]));
            bboxmax[j] = std::min(clamp[j], std::max(bboxmax[j], pts[i][j]));
        }
    }

    
    Vec3f P;
    for (P.x = bboxmin.x; P.x <= bboxmax.x; P.x++) {
        for (P.y = bboxmin.y; P.y <= bboxmax.y; P.y++) {
            Vec3f bc_screen = barycentric(pts[0], pts[1], pts[2], P);
            if (bc_screen.x < 0 || bc_screen.y < 0 || bc_screen.z < 0) continue;
            P.z = 0;
            for (int i = 0; i < 3; i++) P.z += pts[i][2] * bc_screen[i];
            int idx = int(P.x + P.y * image.get_width());
            if (zbuffer[idx] < P.z) {
                zbuffer[idx] = P.z;
                Vec2f texCoord = tex[0] * bc_screen.x + tex[1] * bc_screen.y + tex[2] * bc_screen.z;
                TGAColor color = texture.get(texCoord.x * texture.get_width(), texCoord.y * texture.get_height());
                image.set(P.x, P.y, color);
                
            }
        }
    }
}

Vec3f world2screen(Vec3f v, int width, int height) {
    return Vec3f(int((v.x + 1.) * width / 2. + .5), int((v.y + 1.) * height / 2. + .5), v.z);
}

int main() {
    objparser obj_parser("african_head.obj");
    TGAImage image(500, 500, TGAImage::RGB);
    Vec3f light_dir(0, 0, -1); // define light_dir

    TGAImage texture;
    texture.read_tga_file("african_head_diffuse.tga"); // Load the texture
    texture.flip_vertically(); // Make sure the texture is oriented correctly

    int width = image.get_width();
    int height = image.get_height();
    float* zbuffer = new float[width * height];


    for (int i = 0; i < width * height; ++i) {
        zbuffer[i] = -std::numeric_limits<float>::infinity();
    }

    for (size_t i = 0; i < obj_parser.faces.size(); ++i) {
        
        const vector<int>& face = obj_parser.faces[i];
        const vector<int>& texCoords = obj_parser.faceTexCoords[i];

        
        Vec3f v1w(obj_parser.vertices[face[0] - 1][0], 
                  obj_parser.vertices[face[0] - 1][1], 
                  obj_parser.vertices[face[0] - 1][2]);
        Vec3f v2w(obj_parser.vertices[face[1] - 1][0], 
                  obj_parser.vertices[face[1] - 1][1], 
                  obj_parser.vertices[face[1] - 1][2]);
        Vec3f v3w(obj_parser.vertices[face[2] - 1][0], 
                  obj_parser.vertices[face[2] - 1][1], 
                  obj_parser.vertices[face[2] - 1][2]);

        Vec3f v1s = world2screen(v1w, width, height);
        Vec3f v2s = world2screen(v2w, width, height);
        Vec3f v3s = world2screen(v3w, width, height);

        Vec2f vt1(obj_parser.vt[texCoords[0] - 1][0], obj_parser.vt[texCoords[0] - 1][1]);
        Vec2f vt2(obj_parser.vt[texCoords[1] - 1][0], obj_parser.vt[texCoords[1] - 1][1]);
        Vec2f vt3(obj_parser.vt[texCoords[2] - 1][0], obj_parser.vt[texCoords[2] - 1][1]);

        Vec3f screen_coords[3] = { v1s, v2s, v3s };
        Vec2f tex_coords[3] = { vt1, vt2, vt3 };

        Vec3f normal = triangleNormal(v1w, v2w, v3w);
        float intensity = normal.dot(light_dir);

        if (intensity > 0) {
            
            triangle(screen_coords, zbuffer, image, tex_coords, texture);
        }
    }

    image.flip_vertically();
    image.write_tga_file("output.tga");

    delete[] zbuffer; // Clean up Z-buffer memory
    return 0;
}
