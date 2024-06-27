#ifndef VERTEX_H
#define VERTEX_H

class Vertex {
public:
    float x, y, z;

    // Constructors
    Vertex();
    Vertex(float x, float y);        // 2D constructor for screen coordinates
    Vertex(float x, float y, float z); // 3D constructor for world coordinates

    // Operator overloads
    Vertex operator-(const Vertex &other) const;
    Vertex operator^(const Vertex &other) const; // Cross product
    
    
    float dot(const Vertex &other) const; // Dot product

    // Methods
    void normalize();
};

#endif // VERTEX_H
