/**
 * Author: Andrei Heidelbacher
 * Task: Purification
 * Time complexity: O(N^2)
 * Space complexity: O(N)
 * Expected score: 0 points
 */

#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

const char IN_FILE[] = "purification.in";
const char OUT_FILE[] = "purification.out";
const int NIL = -1;

vector<int> solve(const vector<int> &fathers, const vector<int> &weights) {
  const int size = int(fathers.size());
  vector<vector<int>> tree = vector<vector<int>>(size, vector<int>());
  for (int u = 0; u < size; ++u)
    if (fathers[u] != NIL)
      tree[fathers[u]].push_back(u);
  vector<int> order;
  priority_queue<pair<int, int>> heap;
  for (int u = 0; u < size; ++u)
    if (fathers[u] == NIL)
      heap.push(make_pair(weights[u], u));
  while (!heap.empty()) {
    const int u = heap.top().second;
    heap.pop();
    order.push_back(u);
    for (const int &v: tree[u])
      heap.push(make_pair(weights[v], v));
  }
  return order;
}

vector<int> optimize(const vector<int> &fathers, const vector<int> &weights, vector<int> order) {
  const int size = int(fathers.size());
  for (bool swapped = true; swapped; ) {
    swapped = false;
    for (int i = 0; i + 1 < size; ++i) {
      if (weights[order[i]] < weights[order[i + 1]] && fathers[order[i + 1]] != order[i]) {
        swap(order[i], order[i + 1]);
        swapped = true;
      }
    }
  }
  return order;
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
  vector<int> order = optimize(fathers, weights, solve(fathers, weights));
  int totalCost = 0;
  for (int i = 0; i < int(order.size()); ++i)
    totalCost += (i + 1) * weights[order[i]];
  out << totalCost << "\n";
  in.close();
  out.close();
  return 0;
}
