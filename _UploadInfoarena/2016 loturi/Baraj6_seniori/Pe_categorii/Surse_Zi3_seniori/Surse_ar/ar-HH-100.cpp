/**
 * Author: Andrei Heidelbacher
 * Task: AR
 * Time complexity: O(E * sqrt(V))
 * Space complexity: O(V + E)
 * Expected score: 100 points
 */

#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

const char IN_FILE[] = "ar.in";
const char OUT_FILE[] = "ar.out";

class BipartiteGraph {
 public:
  enum Side {
    LEFT, RIGHT
  };

  static const int NIL = -1;

  BipartiteGraph(
    const int _size,
    const vector<Side> &_side,
    const vector<pair<int, int>> &_edges):
   size(_size),
   edges(vector<vector<int>>(_size, vector<int>())),
   side(_side) {
    for (const auto &e: _edges) {
      edges[e.first].push_back(e.second);
      edges[e.second].push_back(e.first);
    }
  }

  vector<pair<int, int>> getMaxMatching() const {
    vector<int> pairs = vector<int>(size, NIL);
    for (bool change = true; change; ) {
      change = false;
      auto used = vector<bool>(size, false);
      for (int x = 0; x < size; ++x)
        if (side[x] == Side::LEFT && pairs[x] == NIL && pairUp(x, used, pairs))
          change = true;
    }
    auto matching = vector<pair<int, int>>();
    for (int x = 0; x < size; ++x)
      if (side[x] == Side::LEFT && pairs[x] != NIL)
        matching.push_back(make_pair(x, pairs[x]));
    return matching;
  }

 private:
  int size;
  vector<vector<int>> edges;
  vector<Side> side;

  bool pairUp(const int x, vector<bool> &used, vector<int> &pairs) const {
    if (used[x])
      return false;
    used[x] = true;
    for (const auto &y: edges[x]) {
      if (pairs[y] == NIL || pairUp(pairs[y], used, pairs)) {
        pairs[x] = y;
        pairs[y] = x;
        return true;
      }
    }
    return false;
  }
};

vector<pair<int, int>> solve(const int size, const vector<pair<int, int>> &edges, const int R) {
  auto degrees = vector<int>(size, 0);
  for (const auto &edge: edges) {
    ++degrees[edge.first];
    ++degrees[edge.second];
  }
  auto erasedEdges = vector<pair<int, int>>();
  for (const auto &edge: edges) {
    if (degrees[edge.first] == R && degrees[edge.second] == R) {
      --degrees[edge.first];
      --degrees[edge.second];
      erasedEdges.push_back(edge);
    }
  }
  auto remainingEdges = vector<pair<int, int>>();
  for (const auto &edge: edges)
    if (degrees[edge.first] != degrees[edge.second])
      remainingEdges.push_back(edge);
  vector<BipartiteGraph::Side> sides;
  for (int u = 0; u < size; ++u)
    sides.push_back(degrees[u] == R ? BipartiteGraph::Side::LEFT : BipartiteGraph::Side::RIGHT);
  auto matching = BipartiteGraph(size, sides, remainingEdges).getMaxMatching();
  erasedEdges.insert(erasedEdges.end(), matching.begin(), matching.end());
  return erasedEdges;
}

int main() {
  ifstream in(IN_FILE);
  ofstream out(OUT_FILE);
  int V, E, R;
  in >> V >> E >> R;
  auto edges = vector<pair<int, int>>();
  for (; E > 0; --E) {
    int u, v;
    in >> u >> v;
    edges.push_back(make_pair(u - 1, v - 1));
  }
  auto erasedEdges = solve(V, edges, R);
  out << int(erasedEdges.size()) << "\n";
  for (const auto &edge: erasedEdges)
    out << edge.first + 1 << " " << edge.second + 1 << "\n";
  in.close();
  out.close();
  return 0;
}
