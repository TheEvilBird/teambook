/**
 * Author: Alex Ponkratov
 * Date: ?
 * Description: Iterating through all the submasks and overmasks.
 * Time: O(3^{n})
 */

for (int submask = mask;; submask = (submask - 1) & mask) {
  // use submask
  if (submask == 0)
    break;
}

for (int overmask = mask;; overmask = (overmask + 1) | mask) {
  // use overmask
  if (overmask == maxmask)
    break;
}