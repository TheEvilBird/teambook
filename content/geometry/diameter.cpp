/**
 * Author: Alex Ponkratov
 * Date: ?
 * Description: Rotating calipers.
 * Time: O(n)
 */

ll diameter_of_polygon(Polygon &poly) {
    int n = sz(poly), x = 1;
    ll ans = 0;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        while (true) {
            Point ac = poly[x] - poly[i], ab = poly[j] - poly[i], cd = poly[(x + 1) % n] - poly[x];
            ans = max(ans, ac.len_sq());
            if ((ab % cd) <= 0) {
                break;
            }
            x++;
            x %= n;
        }
    }
    return sqrtl(ans);
}