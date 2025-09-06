#pragma once

#include <compare>

namespace geom {

struct Vec2D {
    Vec2D() = default;
    Vec2D(double x, double y)
        : x(x)
        , y(y) {
    }

    Vec2D& operator*=(double scale) {
        x *= scale;
        y *= scale;
        return *this;
    }

    bool operator==(const Vec2D& other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Vec2D& other) const {
        return !(*this == other);
    }

    bool operator<(const Vec2D& other) const {
        if (x != other.x) {
            return x < other.x;
        }
        return y < other.y;
    }

    bool operator<=(const Vec2D& other) const {
        return !(*this > other);
    }

    bool operator>(const Vec2D& other) const {
        return other < *this;
    }

    bool operator>=(const Vec2D& other) const {
        return !(*this < other);
    }

    double x = 0;
    double y = 0;
};

inline Vec2D operator*(Vec2D lhs, double rhs) {
    return lhs *= rhs;
}

inline Vec2D operator*(double lhs, Vec2D rhs) {
    return rhs *= lhs;
}

struct Point2D {
    Point2D() = default;
    Point2D(double x, double y)
        : x(x)
        , y(y) {
    }

    Point2D& operator+=(const Vec2D& rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    // Операторы сравнения
    bool operator==(const Point2D& other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Point2D& other) const {
        return !(*this == other);
    }

    bool operator<(const Point2D& other) const {
        if (x != other.x) {
            return x < other.x;
        }
        return y < other.y;
    }

    bool operator<=(const Point2D& other) const {
        return !(*this > other);
    }

    bool operator>(const Point2D& other) const {
        return other < *this;
    }

    bool operator>=(const Point2D& other) const {
        return !(*this < other);
    }

    double x = 0;
    double y = 0;
};

inline Point2D operator+(Point2D lhs, const Vec2D& rhs) {
    return lhs += rhs;
}

inline Point2D operator+(const Vec2D& lhs, Point2D rhs) {
    return rhs += lhs;
}

}  // namespace geom
