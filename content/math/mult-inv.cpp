/**
 * Author: Alex Ponkratov
 * Date: ?
 * Description: Calc multiplicative inverse.
 * Source: https://ru.algorithmica.org/cs/modular/reciprocal and
 * http://e-maxx.ru/algo/reverse_element
 */

int inv(int a, int m) {
  if (a == 1)
    return 1;
  return (1 - inv(m % a, a) * m) / a + m;
}

f[0] = 1;
for (int i = 1; i < N; i++) {
  f[i] = i * f[i - 1] % mod;
}
r[N - 1] = inv(f[N - 1]);
for (int i = N - 1; i >= 1; i--) {
  r[i - 1] = r[i] * i % mod;
}
// ---------------------------
r[1] = 1;
for (int i = 2; i < m; ++i) {
  r[i] = (m - (m / i) * r[m % i] % m) % m;
}