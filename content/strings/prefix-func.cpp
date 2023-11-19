/**
 * Author: Alex Ponkratov
 * Date: ?
 * Source: https://ru.algorithmica.org/cs/string-searching/prefix-function/
 * Description: Prefix function.
 */

vector<int> prefix_function(string &s) {
    int n = (int) s.size();
    vector<int> p(n, 0);
    for (int i = 1; i < n; i++) {
        int cur = p[i - 1];
        while (s[i] != s[cur] && cur > 0) {
            cur = p[cur - 1];
        }
        if (s[i] == s[cur]) {
            p[i] = cur + 1;
        }
    }
    return p;
}