/**
 * Author: Andrei Heidelbacher
 * Task: Purification
 * Time complexity: O(N * 2^N)
 * Space complexity: O(2^N)
 * Expected score: 20 points
 */

#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

const char IN_FILE[] = "purification.in";
const char OUT_FILE[] = "purification.out";
const int NIL = -1;
const int INF = 0x3f3f3f3f;

inline int getBit(const int mask, const int bit) {
  return (mask >> bit) & 1;
}

int solve(const vector<int> &fathers, const vector<int> &weights) {
  const int size = int(fathers.size());
  vector<int> dp = vector<int>(1 << size, INF);
  dp[0] = 0;
  for (int mask = 1; mask < (1 << size); ++mask) {
    int bitCount = 0;
    for (int u = 0; u < size; ++u)
      if (getBit(mask, u) == 1)
        ++bitCount;
    for (int last = 0; last < size; ++last)
      if (getBit(mask, last) == 1 && (fathers[last] == NIL || getBit(mask, fathers[last]) == 1))
        dp[mask] = min(dp[mask], dp[mask ^ (1 << last)] + bitCount * weights[last]);
  }
  return dp[(1 << size) - 1];
}

int main() {
  ifstream in(IN_FILE);
  ofstream out(OUT_FILE);
  int n;
  in >> n;
  vector<int> weights = vector<int>(n);
  for (int u = 0; u < n; ++u)
    in >> weights[u];
  vector<int> fathers = vector<int>(n);
  for (int u = 0; u < n; ++u)
    in >> fathers[u];
  out << solve(fathers, weights) << "\n";
  in.close();
  out.close();
  return 0;
}
