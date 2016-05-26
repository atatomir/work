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

using namespace std;

const char IN_FILE[] = "purification.in";
const char OUT_FILE[] = "purification.out";
const int NIL = -1;
const int INF = 0x3f3f3f3f;

vector<int> optimize(const vector<int> &weights, const vector<int> &fathers, vector<int> order) {
  const int size = int(order.size());
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

vector<int> mergeOrders(
    const vector<int> &weights,
    const vector<int> &fathers,
    const vector<int> &first,
    const vector<int> &second) {
  const int n = int(first.size());
  const int m = int(second.size());
  vector<int> order;
  int i = 0, j = 0;
  while (i < n && j < m) {
    if (weights[first[i]] > weights[second[j]]) {
      order.push_back(first[i]);
      ++i;
    } else {
      order.push_back(second[j]);
      ++j;
    }
  }
  for (; i < n; ++i)
    order.push_back(first[i]);
  for (; j < m; ++j)
    order.push_back(second[j]);
  return optimize(weights, fathers, order);
}

vector<int> dfs(
    const vector<vector<int>> &tree,
    const vector<int> &weights,
    const vector<int> &fathers,
    const int u) {
  vector<int> order;
  for (const int &v: tree[u])
    order = mergeOrders(weights, fathers, order, dfs(tree, weights, fathers, v));
  order.insert(order.begin(), u);
  return order;
}

int main() {
  ifstream in(IN_FILE);
  ofstream out(OUT_FILE);
  int n;
  in >> n;
  const int root = n;
  vector<int> weights = vector<int>(n + 1, 0);
  for (int u = 0; u < n; ++u)
    in >> weights[u];
  vector<vector<int>> tree = vector<vector<int>>(n + 1, vector<int>());
  vector<int> fathers = vector<int>(n + 1, NIL);
  for (int u = 0; u < n; ++u) {
    in >> fathers[u];
    if (fathers[u] == NIL)
      fathers[u] = root;
    tree[fathers[u]].push_back(u);
  }
  vector<int> order = dfs(tree, weights, fathers, root);
  int totalCost = 0;
  for (int i = 0; i < int(order.size()); ++i)
    totalCost += i * weights[order[i]];
  out << totalCost << "\n";
  in.close();
  out.close();
  return 0;
}
