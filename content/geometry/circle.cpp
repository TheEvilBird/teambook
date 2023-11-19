/**
 * Author: Alex Ponkratov, Fedor Shatokhin, Dmitry Pugachev
 * Date: ?
 * Source: FedShat and Dimanchik
 * Description: Class to handle circle in the plane.
 * 	T can be e.g. double or long long. (Avoid int.)
 */

template<typename T>
struct circle_t {
    point_t<T> c;
    T r;

    circle_t() {}

    circle_t(point_t<T> _c, T _r) : c(_c), r(_r) {}

    int point_in(const point_t<T> &a) {
        if (is_same<T, ll>()) {
            ll dist = (a - c).len_sq();
            if (dist > r * r) {
                return 0;
            } else if (dist < r * r) {
                return 1;
            } else {
                return 2;
            }
        } else {
            ld dist = (a - c).len();
            if (dist > r + EPS) {
                return 0;
            } else if (dist + EPS < r) {
                return 1;
            } else {
                return 2;
            }
        }
    }

    vector<PointLD> tangent_from_point(const point_t<T> &a) {
        PointLD p(a.x, a.y);
        PointLD vec(c.x - p.x, c.y - p.y);
        ld dist = vec.len();
        if (dist + EPS < r) {
            return {};
        }
        if (abs(r - dist) < EPS) {
            return {p};
        }
        vec.x /= dist;
        vec.y /= dist;
        ld k = sqrtl(dist * dist - r * r);
        ld alpha = atan2(r, k);
        PointLD t1 = p + rotate(vec, alpha) * k, t2 = p + rotate(vec, -alpha) * k;
        return {t1, t2};
    }
};

template<typename T>
istream &operator>>(istream &is, circle_t<T> &c) {
    is >> c.c >> c.r;
    return is;
}