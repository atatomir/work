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

vector<int> mergeOrders(
    const vector<int> &weights,
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
  return order;
}

vector<int> dfs(
    const vector<vector<int>> &tree,
    const vector<int> &weights,
    const int u) {
  vector<int> order;
  for (const int &v: tree[u])
    order = mergeOrders(weights, order, dfs(tree, weights, v));
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
  for (int u = 0; u < n; ++u) {
    int father;
    in >> father;
    if (father == NIL)
      father = root;
    tree[father].push_back(u);
  }
  vector<int> order = dfs(tree, weights, root);
  int totalCost = 0;
  for (int i = 0; i < int(order.size()); ++i)
    totalCost += i * weights[order[i]];
  out << totalCost << "\n";
  in.close();
  out.close();
  return 0;
}
