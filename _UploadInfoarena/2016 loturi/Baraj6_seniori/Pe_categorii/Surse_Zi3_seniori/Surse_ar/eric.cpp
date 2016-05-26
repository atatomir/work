#include <fstream>
#include <functional>
#include <cassert>
#include <cstring>
#include <vector>
#include <unordered_set>

using namespace std;

const int MAX_N = 20000;
const int MAX_M = 200000;

#define DEBUG 0

#define debug(...) if(DEBUG)fprintf(stderr, __VA_ARGS__);

#define debug2(...) if(DEBUG >= 2)fprintf(stderr, __VA_ARGS__);

int main() {
  ifstream in("ar.in");
  int n, m, r;
  in >> n >> m >> r;

  assert(1 <= n && n <= MAX_N);
  assert(1 <= m && m <= MAX_M);

  vector<unordered_set<int>> G(n + 1);

  for(int i = 1; i <= m; ++i) {
    int a, b;
    in >> a >> b;
    G[a].insert(b);
    G[b].insert(a);
  }
  in.close();

  auto checkIsR = [&] (int r) -> bool {
    for(int i = 1; i <= n; ++i) {
      if((int)G[i].size() == r  || 
          (int)G[i].size() == r - 1)
        continue;
      return false;
    }
    return true;
  };

  assert(checkIsR(r));

  auto isRs = [&](int x) {
    return (int)G[x].size() == r;
  };

  auto isRms = [&](int x) {
    return (int)G[x].size() == r - 1;
  };

  vector<pair<int, int>> erased;

  auto removeEdge = [&](int a, int b) {
    debug("rm %d - %d\n", a, b);
    G[a].erase(b);
    G[b].erase(a);
    erased.push_back({a, b});
  };

  //first we remove all the R-R edges
  debug2("Removing R - R edges\n");
  for(int i = 1; i <= n; ++i) {
    if(!isRs(i))
      continue;

    for(auto e: G[i]) {
      if(isRs(e)) {
        removeEdge(i, e);
        break;
      }
    }
  }

  vector<vector<int>> RRmGraph(n + 1);

  auto addRRmEdge = [&](int a, int b) {
    debug2("add %d - %d\n", a, b);
    RRmGraph[a].push_back(b);
  };

  debug2("Adding R - Rm edges\n");

  for(int i = 1; i <= n; ++i) {
    if(!isRs(i))
      continue;
    for(auto e: G[i]) {
      if(isRms(e)) 
        addRRmEdge(i, e);
    }
  }

  vector<int> L(n + 1), R(n + 1);

  vector<uint32_t> viz((n + 1) / 32 + 1);

  auto set = [&] (const int x) {
    viz[x / 32] |= 1u << (x % 32);
  };

  auto get = [&] (const int x) {
    return viz[x / 32] & (1 << (x % 32));
  };

  auto reset = [&] () {
    memset(viz.data(), 0, sizeof(viz[0]) * viz.size());
  };

  function<bool(int)> tryMatch;

  tryMatch = [&] (int nod) -> bool {

    debug2("trying to match %d\n", nod);
    if(get(nod))
      return false;
    set(nod);

    auto checkAll = [&](function<bool(int)> ok) {
      for(auto e: RRmGraph[nod]) {
        debug2("trying to match with %d\n", e);
        if(ok(e)) {
          debug2("matched %d with %d\n", nod, e);
          L[nod] = e;
          R[e] = nod;
          return true;
        }
      }
      return false;
    };

    if(checkAll([&](int e) {
          return !R[e];
          })) {
      return true;
    }

    if(checkAll([&](int e) {
          return tryMatch(R[e]);
          })) {
      return true;
    }

    return false;
  };

  vector<int> Rs;
  Rs.reserve(n);

  for(int i = 1; i <= n; ++i) {
    if(isRs(i))
      Rs.push_back(i);
  }

  bool go_on = 1;
  while(go_on) {
    go_on = 0;
    reset();
    for(auto i: Rs) {
      if(get(i) || L[i])
        continue;
      if(tryMatch(i)) {
        go_on = 1;
      }
    }
  }

  for(auto i: Rs) {
    if(L[i])
      removeEdge(i, L[i]);
  }


  assert(checkIsR(r - 1));

  ofstream out("ar.out");
  out << erased.size() << "\n";
  for(auto e: erased)
    out << e.first << " " << e.second << "\n";

  out.close();
  return 0;
}
