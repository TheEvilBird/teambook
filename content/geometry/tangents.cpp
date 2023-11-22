/**
 * Author: Alex Ponkratov
 * Date: ?
 * Description: Returns id of tangent point: (left tangent, right tangent)
 * (maybe (right, left), but i believe no).
 */

pii tangent_from_point(const Point &p, const Polygon &poly) {
  int n = sz(poly);
  int i_min = 0;
  int i_max = 0;
  for (int k = 17; k >= 0; --k) {
    {
      int l = (i_min + (1 << k)) % n;
      int r = ((i_min - (1 << k)) % n + n) % n;
      i_min = min({l, r, i_min}, [&poly, &p](int i, int j) {
        return ((poly[i] - p) % (poly[j] - p)) < 0 ||
               (((poly[i] - p) % (poly[j] - p)) == 0 &&
                (poly[i] - p).len_sq() < (poly[j] - p).len_sq());
      });
    }
    {
      int l = (i_max + (1 << k)) % n;
      int r = ((i_max - (1 << k)) % n + n) % n;
      i_max = max({l, r, i_max}, [&poly, &p](int i, int j) {
        return ((poly[i] - p) % (poly[j] - p)) < 0 ||
               (((poly[i] - p) % (poly[j] - p)) == 0 &&
                (poly[i] - p).len_sq() > (poly[j] - p).len_sq());
      });
    }
  }
  return {i_min, i_max};
}