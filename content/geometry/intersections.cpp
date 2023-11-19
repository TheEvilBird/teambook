/**
 * Author: Alex Ponkratov, Fedor Shatokhin, Dmitry Pugachev
 * Date: ?
 * Description: Intersect everything.
 */

bool point_on_line(const Point &p, const Point &a, const Point &b) { // point p, line ab
    Point ab = b - a, ap = p - a;
    return (ab % ap) == 0;
}

bool point_on_ray(const Point &p, const Point &a, const Point &b) { // point p, ray ab
    Point ab = b - a, ap = p - a;
    return ((ab % ap) == 0 && (ab * ap) > 0) || (a == p);
}

bool point_on_segment(const Point &p, const Point &a, const Point &b) { // point p, segment ab
    Point ap = p - a, bp = p - b, ab = b - a;
    return (ap * bp) <= 0 && (ap % ab) == 0;
}

bool point_in_angle(const Point &p, const Point &a, const Point &o, const Point &b) { // point p, angle aob
    Point oa = a - o, ob = b - o, op = p - o;
    if ((oa % ob) < 0) swap(oa, ob);
    return ((oa % op) >= 0 && (ob % op) <= 0);
}

bool segment_intersection(const Point &a, const Point &b, const Point &c, const Point &d) { // segment ab, segment, cd
    Point ab = b - a, cd = d - c, ac = c - a, ad = d - a, cb = b - c, ca = a - c;
    if (get_sign((ab % ac)) * get_sign((ab % ad)) <= 0 && get_sign((cd % ca)) * get_sign((cd % cb)) <= 0) {
        ll x1 = max(min(a.x, b.x), min(c.x, d.x)), x2 = min(max(a.x, b.x), max(c.x, d.x));
        ll y1 = max(min(a.y, b.y), min(c.y, d.y)), y2 = min(max(a.y, b.y), max(c.y, d.y));
        return (x1 <= x2 && y1 <= y2);
    }
    return false;
}

bool lines_intersection(const Point &a, const Point &b, const Point &c, const Point &d) { // line ab, line cd
    Point ab = b - a, cd = d - c, ac = c - a;
    return ((ab % cd) != 0 || (ab % ac == 0));
}

bool line_ray_intersection(const Point &a, const Point &b, const Point &c, const Point &d) { // line ab, ray cd
    if (!lines_intersection(a, b, c, d)) {
        return false;
    }
    Point ab = b - a, dp = d + (a - c), ac = c - a;
    if (get_sign(ab % (dp - a)) * get_sign(ab % ac) <= 0) {
        return true;
    }
    return false;
}

Point get_inf(const Point &a, const Point &b) { // returns inf point on ray ab
    if (a.x == b.x) {
        if (a.y < b.y) {
            return {a.x, INFLL};
        } else {
            return {a.x, -INFLL};
        }
    }
    if (a.x < b.x) {
        if (a.y < b.y) {
            return {INFLL, INFLL};
        } else if (a.y == b.y) {
            return {INFLL, a.y};
        } else {
            return {INFLL, -INFLL};
        }
    }
    // a.x > b.x
    if (a.y < b.y) {
        return {-INFLL, INFLL};
    } else if (a.y == b.y) {
        return {-INFLL, a.y};
    } else {
        return {-INFLL, -INFLL};
    }
}

bool rays_intersection(const Point &a, const Point &b, const Point &c, const Point &d) { // ray ab, ray cd
    if (line_ray_intersection(a, b, c, d) && line_ray_intersection(c, d, a, b)) {
        Point bp = get_inf(a, b), dp = get_inf(c, d);
        ll x1 = max(min(a.x, bp.x), min(c.x, dp.x)), x2 = min(max(a.x, bp.x), max(c.x, dp.x));
        ll y1 = max(min(a.y, bp.y), min(c.y, dp.y)), y2 = min(max(a.y, bp.y), max(c.y, dp.y));
        return (x1 <= x2 && y1 <= y2);
    }
    return false;
}

bool segment_line_intersection(const Point &a, const Point &b, const Point &c, const Point &d) { // segment ab, line cd
    Point cd = d - c, ca = a - c, cb = b - c;
    if (get_sign(cd % ca) * get_sign(cd % cb) <= 0) {
        return true;
    }
    return false;
}

bool ray_segment_intersection(const Point &a, const Point &b, const Point &c, const Point &d) { // ray ab, segment cd
    if (line_ray_intersection(c, d, a, b) && segment_line_intersection(c, d, a, b)) {
        Point bp = get_inf(a, b);
        ll x1 = max(min(a.x, bp.x), min(c.x, d.x)), x2 = min(max(a.x, bp.x), max(c.x, d.x));
        ll y1 = max(min(a.y, bp.y), min(c.y, d.y)), y2 = min(max(a.y, bp.y), max(c.y, d.y));
        return (x1 <= x2 && y1 <= y2);
    }
    return false;
}