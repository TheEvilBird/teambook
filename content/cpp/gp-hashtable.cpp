/**
 * Author: Alex Ponkratov
 * Date: ?
 * Source: http://codeforces.com/blog/entry/60737
 * Description: Hash map with mostly the same API as unordered\_map, but
 * \tilde 3x faster. Uses 1.5x memory. Initial capacity must be a power of
 * 2 (if provided).
 */

#include <ext/pb_ds/assoc_container.hpp> /** keep-include */
#include <ext/pb_ds/tree_policy.hpp>     /** keep-include */
using namespace __gnu_pbds;

const int RANDOM =
    chrono::high_resolution_clock::now().time_since_epoch().count();
struct hasher {
  int operator()(int x) const { return x ^ RANDOM; }
};

gp_hash_table<int, int, hasher> table;
