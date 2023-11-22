/**
 * Author: Alex Ponkratov, Fedor Shatokhin, Dmitry Pugachev
 * Date: ?
 * Description: Calc the distance between everything.
 */

ld from_point_to_line(const Point &p, const Point &a,
                      const Point &b) { // point p, line ab
  Point ba = a - b, ap = p - a;
  return fabs((ba % ap) / ba.len());
}

ld from_point_to_ray(const Point &p, const Point &a,
                     const Point &b) { // point p, ray ab
  Point ba = a - b, ap = p - a, ab = b - a;
  if ((ab * ap) < 0) {
    return ap.len();
  } else {
    return fabs((ba % ap) / ba.len());
  }
}

ld from_point_to_segment(const Point &p, const Point &a,
                         const Point &b) { // point p, segment ab
  Point ab = b - a, ap = p - a, bp = p - b, ba = a - b;
  if ((ab * ap) < 0) {
    return fabsl(ap.len());
  } else if ((ab * bp) > 0) {
    return fabsl(bp.len());
  } else {
    return fabsl((ba % ap) / ba.len());
  }
}

ld from_segment_to_segment(const Point &a, const Point &b, const Point &c,
                           const Point &d) { // segment ab, segment cd
  if (segment_intersection(a, b, c, d)) {
    return 0;
  }
  return min({from_point_to_segment(a, c, d), from_point_to_segment(b, c, d),
              from_point_to_segment(c, a, b), from_point_to_segment(d, a, b)});
}

ld from_segment_to_ray(const Point &a, const Point &b, const Point &c,
                       const Point &d) { // segment ab, ray cd
  if (ray_segment_intersection(c, d, a, b)) {
    return 0;
  }
  return min({from_point_to_ray(a, c, d), from_point_to_ray(b, c, d),
              from_point_to_segment(c, a, b)});
}

ld from_segment_to_line(const Point &a, const Point &b, const Point &c,
                        const Point &d) { // segment ab, line cd
  Point cd = d - c, ca = a - c, cb = b - c;
  if (get_sign(cd % ca) * get_sign(cd % cb) <= 0) {
    return 0;
  }
  return min(from_point_to_line(a, c, d), from_point_to_line(b, c, d));
}

ld from_ray_to_ray(const Point &a, const Point &b, const Point &c,
                   const Point &d) { // ray ab, ray cd
  if (rays_intersection(a, b, c, d)) {
    return 0;
  }
  return min(from_point_to_ray(a, c, d), from_point_to_ray(c, a, b));
}

ld from_ray_to_line(const Point &a, const Point &b, const Point &c,
                    const Point &d) { // ray ab, line cd
  if (line_ray_intersection(c, d, a, b)) {
    return 0;
  }
  return from_point_to_line(a, c, d);
}

ld from_line_to_line(const Point &a, const Point &b, const Point &c,
                     const Point &d) { // line ab, line cd
  if (lines_intersection(a, b, c, d)) {
    return 0;
  }
  return from_point_to_line(a, c, d);
}