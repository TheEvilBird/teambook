/**
 * Author: Alex Ponkratov, Fedor Shatokhin, Dmitry Pugachev
 * Date: ?
 * Description: Minkowski sum of two polygons and its applications.
 * Time: O(|A| + |B|)
 */

Polygon minkowski_sum(Polygon &a, Polygon &b) {
  // a[0], b[0]: y - max, y1 = y2 => x - max. counter clockwise
  int n = sz(a), m = sz(b);
  assert(n >= 3 && m >= 3);
  Point high_a = a[0], high_b = b[0];
  Polygon va(n), vb(m);
  for (int i = 0; i < n; ++i) {
    va[i] = a[(i + 1) % n] - a[i];
  }
  for (int i = 0; i < m; ++i) {
    vb[i] = b[(i + 1) % m] - b[i];
  }
  // sort(all(va), cmp_vectors);
  // sort(all(vb), cmp_vectors);
  Polygon vc(sz(va) + sz(vb));
  merge(all(va), all(vb), vc.begin(), cmp_vectors);
  Point high_c(high_a.x + high_b.x, high_a.y + high_b.y);
  Polygon c(sz(vc) + 1);
  c[0] = high_c;
  for (int i = 0; i < sz(c) - 1; ++i) {
    c[i + 1] = c[i] + vc[i];
  }
  return c;
}

ld from_polygon_to_polygon(Polygon a, Polygon b) {
  for (auto &i : b) {
    i *= -1;
  }
  int pos = 0;
  for (int i = 1; i < sz(b); ++i) {
    if ((b[i].y > b[pos].y) || (b[i].y == b[pos].y && b[i].x > b[pos].x)) {
      pos = i;
    }
  }
  rotate(b.begin(), b.begin() + pos, b.end());
  Polygon c = minkowski_sum(a, b);
  int n = sz(c);
  Point p(0, 0);
  ld ans = 1e20;
  for (int i = 0; i < n - 1; ++i) {
    ans = min(ans, from_point_to_segment(p, c[i], c[i + 1]));
  }
  return ans;
}

ld diameter_of_polygon_minkowski(Polygon &a) {
  Polygon ra = a;
  for (auto &i : ra) {
    i *= -1;
  }
  int pos = 0;
  for (int i = 1; i < sz(a); ++i) {
    if ((a[i].y > a[pos].y) || (a[i].y == a[pos].y && a[i].x > a[pos].x)) {
      pos = i;
    }
  }
  rotate(a.begin(), a.begin() + pos, a.end());
  pos = 0;
  for (int i = 1; i < sz(a); ++i) {
    if ((ra[i].y > ra[pos].y) ||
        (ra[i].y == ra[pos].y && ra[i].x > ra[pos].x)) {
      pos = i;
    }
  }
  rotate(ra.begin(), ra.begin() + pos, ra.end());
  Polygon c = minkowski_sum(a, ra);
  int n = sz(c);
  ll ans = 0;
  for (int i = 0; i < n; ++i) {
    ans = max(ans, c[i].len_sq());
  }
  return sqrtl(ans);
}