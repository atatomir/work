/**
 * Author: Andrei Heidelbacher
 * Task: Purification
 * Time complexity: O(N^2)
 * Space complexity: O(N^2)
 * Expected score: 100 points
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
  vector<vector<int>> dp = vector<vector<int>>(n + 1, vector<int>(m + 1, INF));
  vector<vector<int>> fathers = vector<vector<int>>(n + 1, vector<int>(m + 1, -1));
  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j <= m; ++j) {
      if (i == 0 && j == 0) {
        dp[i][j] = 0;
        fathers[i][j] = -1;
      } else {
        if (i > 0 && dp[i - 1][j] + (i + j) * weights[first[i - 1]] < dp[i][j]) {
          dp[i][j] = dp[i - 1][j] + (i + j) * weights[first[i - 1]];
          fathers[i][j] = 0;
        }
        if (j > 0 && dp[i][j - 1] + (i + j) * weights[second[j - 1]] < dp[i][j]) {
          dp[i][j] = dp[i][j - 1] + (i + j) * weights[second[j - 1]];
          fathers[i][j] = 1;
        }
      }
    }
  }
  vector<int> order;
  for (int i = n, j = m; i != 0 || j != 0; ) {
    if (fathers[i][j] == 0) {
      order.push_back(first[i - 1]);
      --i;
    } else if (fathers[i][j] == 1) {
      order.push_back(second[j - 1]);
      --j;
    }
  }
  reverse(order.begin(), order.end());
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
