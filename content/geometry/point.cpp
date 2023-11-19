/**
 * Author: Alex Ponkratov, Fedor Shatokhin, Dmitry Pugachev
 * Date: ?
 * Source: My head with FedShat and Dimanchik
 * Description: Class to handle points in the plane.
 * 	T can be e.g. double or long long. (Avoid int.)
 * Status: Works fine, used a lot
 */

template<typename T>
struct point_t {
    T x, y;
    point_t() : x(0), y(0) {}
    point_t(T _x, T _y) : x(_x), y(_y) {}
    T len_sq() const { return x * x + y * y; }
    ld len() const { return sqrtl(len_sq()); }
    point_t operator*(T k) const { return {x * k, y * k}; }
    void operator*=(T k) { x *= k; y *= k; }
    point_t operator+(const point_t<T> &other) const { return {x + other.x, y + other.y}; }
    point_t operator-(const point_t<T> &other) const { return {x - other.x, y - other.y}; }
    bool operator==(const point_t<T> &other) const { return x == other.x && y == other.y; }
    bool operator!=(const point_t<T> &other) const { return !(*this == other); }
    T operator*(const point_t<T> &other) const { return x * other.x + y * other.y; } // dot product
    T operator%(const point_t<T> &other) const { return x * other.y - y * other.x; } // cross product
};
using Point = point_t<ll>;

template<typename T>
istream &operator>>(istream &is, point_t<T> &vec) {
    is >> vec.x >> vec.y;
    return is;
}

template<typename T>
ostream &operator<<(ostream &os, const point_t<T> &vec) {
    os << vec.x << ' ' << vec.y;
    return os;
}

bool cmp_vectors(Point a, Point b) {
    if ((a.y < 0 || (a.y == 0 && a.x < 0)) && (b.y > 0 || (b.y == 0 && b.x > 0))) {
        return true;
    }
    if ((b.y < 0 || (b.y == 0 && b.x < 0)) && (a.y > 0 || (a.y == 0 && a.x > 0))) {
        return false;
    }
    return (a % b > 0 || (a % b == 0 && a.len_sq() < b.len_sq()));
}

int get_sign(ld x) {
    if (x < -EPS) return -1;
    if (EPS < x) return 1;
    return 0;
}