/**
 * Author: Andrei Heidelbacher
 * Task: Purification
 * Time complexity: O(N * logN)
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
  vector<int> degrees = vector<int>(size, 0);
  for (int u = 0; u < size; ++u)
    if (fathers[u] != NIL)
      ++degrees[fathers[u]];
  vector<int> order;
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> heap;
  for (int u = 0; u < size; ++u)
    if (degrees[u] == 0)
      heap.push(make_pair(weights[u], u));
  while (!heap.empty()) {
    const int u = heap.top().second;
    heap.pop();
    order.push_back(u);
    if (fathers[u] != NIL) {
      --degrees[fathers[u]];
      if (degrees[fathers[u]] == 0)
        heap.push(make_pair(weights[fathers[u]], fathers[u]));
    }
  }
  reverse(order.begin(), order.end());
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
  vector<int> order = solve(fathers, weights);
  int totalCost = 0;
  for (int i = 0; i < int(order.size()); ++i)
    totalCost += (i + 1) * weights[order[i]];
  out << totalCost << "\n";
  in.close();
  out.close();
  return 0;
}
