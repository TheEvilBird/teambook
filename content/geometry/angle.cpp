/**
 * Author: Alex Ponkratov, Fedor Shatokhin, Dmitry Pugachev
 * Date: ?
 * Description: Some stuff with angles.
 */

template <typename T> ld angle(const point_t<T> &a, const point_t<T> &b) {
  return fabsl(atan2(a % b, a * b) / PI * 180);
}

template <typename T> ld angle_rad(const point_t<T> &a, const point_t<T> &b) {
  return (atan2(a % b, a * b));
}

template <typename T> ld angle_rad(const point_t<T> &a) {
  return atan2(a.y, a.x);
}

template <typename T> point_t<ld> rotate(const point_t<T> &a, ld alpha) {
  return {a.x * cos(alpha) - a.y * sin(alpha),
          a.x * sin(alpha) + a.y * cos(alpha)};
}