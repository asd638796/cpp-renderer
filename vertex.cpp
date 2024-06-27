#include "vertex.h"
#include <cmath>

// Default constructor
Vertex::Vertex() : x(0), y(0), z(0) {}

// 2D constructor
Vertex::Vertex(float x, float y) : x(x), y(y), z(0) {}

// 3D constructor
Vertex::Vertex(float x, float y, float z) : x(x), y(y), z(z) {}

// Subtraction operator
Vertex Vertex::operator-(const Vertex &other) const {
    return Vertex(x - other.x, y - other.y, z - other.z);
}

// Cross product operator
Vertex Vertex::operator^(const Vertex &other) const {
    return Vertex(
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    );
}

// Normalize the vector
void Vertex::normalize() {
    float length = std::sqrt(x * x + y * y + z * z);
    if (length != 0) {
        x /= length;
        y /= length;
        z /= length;
    }
}

// Dot product
float Vertex::dot(const Vertex &other) const {
    return x * other.x + y * other.y + z * other.z;
}
