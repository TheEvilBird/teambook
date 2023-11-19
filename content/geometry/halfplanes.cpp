/**
 * Author: USACO
 * Description: half-plane intersection area
 * Time: O(N\log N)
 * Source: USACO
 * HALF PLANES: ax + by >= c, not ax + by + c >= 0
 */

using Half = array<ld, 3>; // half-plane, ax + by >= c
using vH = vector<Half>;

PointLD hp_point(const Half &h) { return {h[0], h[1]}; } // direction of half-plane
PointLD isect(const Half &h0, const Half &h1) { // Cramer's rule to intersect half-planes
    array<ld, 3> vals{};
    for (int i = -1; i <= 1; ++i) {
        int x = (i == 0 ? 2 : 0), y = (i == 1 ? 2 : 1);
        vals[1 + i] = h0[x] * h1[y] - h0[y] * h1[x];
    }
    assert(fabsl(vals[0]) > EPS);
    return {vals[1] / vals[0], vals[2] / vals[0]};
}

ld eval(const Half &h, ld x) { // evaluate half-plane at x-coordinate
    assert(fabsl(h[1]) > EPS);
    return (h[2] - h[0] * x) / h[1];
}

ld x_isect(const Half &h0, const Half &h1) { return isect(h0, h1).x; } // x-coordinate of intersection

vH construct_lower(PointLD x, vH planes) { // similar to convex hull (by duality)
    sort(all(planes), [](const Half &a, const Half &b) {
        return hp_point(a) % hp_point(b) > EPS;
    });
    vH res{{1, 0, x.x}}; // >= x.f
    planes.push_back({-1, 0, -x.y}); // <= x.s
    auto lst_x = [&](Half a, Half b) {
        if (fabsl(hp_point(a) % hp_point(b)) <= EPS) { // parallel half-planes, remove lower one
            return a[2] / a[1] <= b[2] / b[1] ? x.x : x.y;
        }
        return x_isect(a, b);
    };
    for (auto t : planes) {
        while (sz(res) > 1 && lst_x(res.back(), t) <= lst_x(res[sz(res) - 2], res.back())) {
            res.pop_back();
        }
        res.push_back(t);
    }
    return res;
}

ld isect_area(vH planes) {
    const ld BIG = 1e9;
    PointLD x{-BIG, BIG};
    planes.push_back({0, 1, -BIG}); // y >= -BIG
    planes.push_back({0, -1, -BIG}); // -y >= -BIG
    vH upper, lower;
    for (auto &t : planes) {
        if (fabsl(t[1]) <= EPS) { // vertical line
            ld quo = t[2] / t[0];
            if (t[0] > 0) {
                if (quo > x.x) x.x = quo;
            } else { // -x >=
                if (quo < x.y) x.y = quo;
            }
        } else if (t[1] > 0) {
            lower.push_back(t);
        } else {
            upper.push_back(t);
        }
    }
    if (x.x >= x.y) return 0;
    lower = construct_lower(x, lower);
    for (auto &t : upper) {
        t[0] *= -1;
        t[1] *= -1;
    }
    upper = construct_lower({-x.y, -x.x}, upper);
    for (auto &t : upper) {
        t[0] *= -1;
        t[1] *= -1;
    }
    reverse(all(upper));
    int iu = 1, il = 1;
    ld lst = x.x, lst_dif = eval(upper[1], lst) - eval(lower[1], lst);
    ld ans = 0;
    while (iu < sz(upper) - 1 && il < sz(lower) - 1) { // sweep vertical line through lower and upper hulls
        ld nex_upper = x_isect(upper[iu], upper[iu + 1]);
        ld nex_lower = x_isect(lower[il], lower[il + 1]);
        ld nex = min(nex_upper, nex_lower);
        ld nex_dif = eval(upper[iu], nex) - eval(lower[il], nex);
        auto avg_val = [](ld a, ld b) -> ld {
            if (a > b) swap(a, b);
            if (b <= 0) return 0;
            if (a >= 0) return (a + b) / 2;
            return b / (b - a) * b / 2;
        };
        ans += (nex - lst) * avg_val(lst_dif, nex_dif);
        assert(x.x <= nex && nex <= x.y);
        lst = nex, lst_dif = nex_dif;
        iu += fabsl(lst - nex_upper) <= EPS;
        il += fabsl(lst - nex_lower) <= EPS;
    }
    return ans;
}

Half plane_right(PointLD a, PointLD b) { // half-plane to right of a -> b
    return {b.y - a.y, a.x - b.x, (b.y - a.y) * a.x + (a.x - b.x) * a.y};
}

Half plane_through(PointLD p, PointLD dir) { // half-plane through p in direction dir
    return {dir.x, dir.y, p * dir};
}