/**
 * Author: Andrei Heidelbacher
 * Task: Purification
 * Time complexity: O(N * N!)
 * Space complexity: O(N)
 * Expected score: 10 points
 */

#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

const char IN_FILE[] = "purification.in";
const char OUT_FILE[] = "purification.out";
const int NIL = -1;

vector<int> solve(const vector<int> &fathers, const vector<int> &weights) {
  const int size = int(fathers.size());
  vector<int> order;
  for (int u = 0; u < size; ++u)
    order.push_back(u);
  vector<int> minCostOrder = order;
  do {
    bool isValid = true;
    vector<bool> used = vector<bool>(size, false);
    for (int i = 0; i < size && isValid; ++i) {
      const int u = order[i];
      used[u] = true;
      if (fathers[u] != NIL && !used[fathers[u]])
        isValid = false;
    }
    if (isValid) {
      int minCost = 0, currentCost = 0;
      for (int i = 0; i < size; ++i) {
        minCost += (i + 1) * weights[minCostOrder[i]];
        currentCost += (i + 1) * weights[order[i]];
      }
      if (currentCost < minCost)
        minCostOrder = order;
    }
  } while (next_permutation(order.begin(), order.end()));
  return minCostOrder;
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
  vector<int> order = solve(fathers, weights);
  int totalCost = 0;
  for (int i = 0; i < int(order.size()); ++i)
    totalCost += (i + 1) * weights[order[i]];
  out << totalCost << "\n";
  in.close();
  out.close();
  return 0;
}
