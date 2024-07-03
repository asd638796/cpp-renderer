#ifndef VEC3F_H
#define VEC3F_H

#include <cmath>
#include <iostream>

class Vec3f {
public:
    float x, y, z;

    Vec3f() : x(0), y(0), z(0) {}
    Vec3f(float x, float y, float z) : x(x), y(y), z(z) {}

    float& operator[](int i) {
        return i == 0 ? x : (i == 1 ? y : z);
    }

    const float& operator[](int i) const {
        return i == 0 ? x : (i == 1 ? y : z);
    }

    Vec3f operator+(const Vec3f& other) const {
        return Vec3f(x + other.x, y + other.y, z + other.z);
    }

    Vec3f operator-(const Vec3f& other) const {
        return Vec3f(x - other.x, y - other.y, z - other.z);
    }

    Vec3f operator*(float scale) const {
        return Vec3f(x * scale, y * scale, z * scale);
    }

    Vec3f operator/(float scale) const {
        return Vec3f(x / scale, y / scale, z / scale);
    }

    Vec3f operator^(const Vec3f& other) const {
        return Vec3f(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }

    float dot(const Vec3f& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    float length() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    void normalize() {
        float len = length();
        if (len > 0) {
            x /= len;
            y /= len;
            z /= len;
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Vec3f& vec) {
        os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
        return os;
    }
};

#endif // VEC3F_H
