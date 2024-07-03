#ifndef VEC2F_H
#define VEC2F_H

#include <cmath>
#include <iostream>

class Vec2f {
public:
    float x, y;

    Vec2f() : x(0), y(0) {}
    Vec2f(float x, float y) : x(x), y(y) {}

    float& operator[](int i) {
        return i == 0 ? x : y;
    }

    const float& operator[](int i) const {
        return i == 0 ? x : y;
    }

    Vec2f operator+(const Vec2f& other) const {
        return Vec2f(x + other.x, y + other.y);
    }

    Vec2f operator-(const Vec2f& other) const {
        return Vec2f(x - other.x, y - other.y);
    }

    Vec2f operator*(float scale) const {
        return Vec2f(x * scale, y * scale);
    }

    Vec2f operator/(float scale) const {
        return Vec2f(x / scale, y / scale);
    }

    float length() const {
        return std::sqrt(x * x + y * y);
    }

    void normalize() {
        float len = length();
        if (len > 0) {
            x /= len;
            y /= len;
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Vec2f& vec) {
        os << "(" << vec.x << ", " << vec.y << ")";
        return os;
    }
};

#endif // VEC2F_H
