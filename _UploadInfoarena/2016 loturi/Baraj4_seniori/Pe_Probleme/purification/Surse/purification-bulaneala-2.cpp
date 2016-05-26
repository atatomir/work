/**
 * Author: Andrei Heidelbacher
 * Task: Purification
 * Time complexity: O(K * N^2)
 * Space complexity: O(N)
 * Expected score: 0 points
 */

#include <cstdlib>
#include <ctime>
#include <cassert>

#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

const char IN_FILE[] = "purification.in";
const char OUT_FILE[] = "purification.out";
const int NIL = -1;
const int MAX_STEPS = 5000000;

int iterations = 0;

vector<int> optimize(const vector<int> &fathers, const vector<int> &weights, vector<int> order) {
  const int size = int(fathers.size());
  for (bool swapped = true; swapped; ) {
    ++iterations;
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

vector<int> getRandomOrder(const vector<int> &fathers, const vector<int> &weights) {
  const int size = int(fathers.size());
  vector<int> degrees = vector<int>(size, 0);
  for (int u = 0; u < size; ++u)
    if (fathers[u] != NIL)
      ++degrees[fathers[u]];
  vector<int> order, leaves;
  for (int u = 0; u < size; ++u)
    if (degrees[u] == 0)
      leaves.push_back(u);
  while (!leaves.empty()) {
    swap(leaves[rand() % int(leaves.size())], leaves[int(leaves.size()) - 1]);
    const int u = leaves.back();
    leaves.pop_back();
    order.push_back(u);
    if (fathers[u] != NIL) {
      --degrees[fathers[u]];
      if (degrees[fathers[u]] == 0)
        leaves.push_back(fathers[u]);
    }
  }
  reverse(order.begin(), order.end());
  return order;
}

inline int getOrderCost(const vector<int> &order, const vector<int> &weights) {
  const int size = int(order.size());
  int cost = 0;
  for (int i = 0; i < size; ++i)
    cost += (i + 1) * weights[order[i]];
  return cost;
}

vector<int> solve(const vector<int> &fathers, const vector<int> &weights) {
  const int size = int(fathers.size());
  vector<int> minCostOrder = optimize(fathers, weights, getRandomOrder(fathers, weights));
  for (int step = 1; size * iterations < MAX_STEPS; ++step) {
    vector<int> order = optimize(fathers, weights, getRandomOrder(fathers, weights));
    if (getOrderCost(order, weights) < getOrderCost(minCostOrder, weights))
      minCostOrder = order;
  }
  return minCostOrder;
}

int main() {
  srand(time(0));
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
  out << getOrderCost(order, weights) << "\n";
  in.close();
  out.close();
  return 0;
}
