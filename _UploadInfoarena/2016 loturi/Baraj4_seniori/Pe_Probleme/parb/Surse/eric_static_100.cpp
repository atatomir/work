//input:
//N, the number of Nodes
//M, the number of Queries
//N - 1 triplets:
//x y c : we have an edge from x to y labeled with 'c'
//
//M pairs:
//(x, y)
#include <fstream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;

const int MAX_N = 1e5 + 10;
const int MAX_LG = 18;

#define DEBUG 0

#define debug(...) if(DEBUG) fprintf(stderr, __VA_ARGS__);
#define debug2(...) if(DEBUG >= 2) fprintf(stderr, __VA_ARGS__);

struct solver {

  typedef pair<int, int> query;

  struct edge {
    int to;
    char c;
  };

  int n, m;
  int lg;


  vector<edge> G[MAX_N];
  int SFX[MAX_N][MAX_LG];
  int inv[MAX_N][MAX_LG];
  int TT[MAX_N][MAX_LG];


  vector<query> Q;

  //vector<vector<edge>> G;
  //vector<vector<int>> SFX;
  //vector<vector<int>> inv;
  //vector<vector<int>> TT;
  vector<int>         lvl;
  vector<bool>        viz;

  vector<int>         norm;

  void init(int n, int m) {
    this->n = n;
    this->m = m;
    Q.reserve(m);
  }

  void addEdge(int x, int y, char c) {
    G[x].push_back({y, c});
    G[y].push_back({x, c});
  }

  void addQuery(int x, int y) {
    Q.push_back({x, y});
  }

  void DFS(const int nod) {
    viz[nod] = 1;
    for(auto &e: G[nod]) {
      const int son = e.to;
      if(!viz[son]) {
        TT[son][0] = nod;
        SFX[son][0] = e.c - 'a' + 1;
        lvl[son] = lvl[nod] + 1;
        DFS(son);
      }
    }
  }

  void buildSuffix() {

    norm.resize(n + 1, 0);

    for(int j = 1; j <= lg; ++j) {

      for(int i = 1; i <= n; ++i)
        norm[i] = i;

      function<bool(int, int)> comp = [&](int a, int b) {
            if(SFX[a][j - 1] == SFX[b][j - 1]) {
            //they are the same index
            //so we have to compare the second half
              int inc = 1 << (j - 1);
              int na = TT[a][j - 1],
                  nb = TT[b][j - 1];

              return SFX[na][j - 1] < SFX[nb][j - 1];
            } 
            return SFX[a][j - 1] < SFX[b][j - 1];
          };

      sort(norm.begin() + 1, norm.end(), comp);

      int at = 1;
      SFX[norm[1]][j] = 1;

      debug2("SFX[%d][%d] = %d\n", norm[1], j, at);

      for(int i = 2; i <= n; ++i) {
        if(comp(norm[i - 1], norm[i])) 
          at = i;
        
        SFX[norm[i]][j] = at;
        debug2("SFX[%d][%d] = %d\n", norm[i], j, at);
      }

      debug2("\n\n\n");
    }
  }

  void build() {

    for(lg = 0; (1 << lg) <= n; lg++);
     
    viz = vector<bool>        (n + 1, 0);
    //TT  = vector<vector<int>> (n + 1, vector<int> (lg, 0));
    //SFX = vector<vector<int>> (n + 1, vector<int> (lg, 0));
    //inv = vector<vector<int>> (n + 1, vector<int> (lg, 0));
    lvl = vector<int>         (n + 1, 0);

    --lg;

    DFS(1);


    for(int j = 1; j <= lg; ++j) {
      for(int i = 1; i <= n; ++i) {
        TT[i][j] = TT[TT[i][j - 1]][j - 1];
      }
    }

    buildSuffix();

    for(int i = 1; i <= n; ++i) {
      assert(viz[i]);
      debug2("node %d has position %d\n", i, SFX[i][lg]);
    }
  }

  int LCP(int x, int y) {
    int ret = 0;
    for(int i = lg; i >= 0; --i) {
      int cnt = (1 << i);

      if(lvl[x] < cnt ||
          lvl[y] < cnt)
        continue;

      if(SFX[x][i] == SFX[y][i]) {
        ret += cnt;
        x = nthStramos(x, cnt);
        y = nthStramos(y, cnt);
      }
    }
    return ret;
  }

  int nthStramos(int x, int n) {
    int ret = x;
    for(int i = 0; n; ++i) {
      if((1 << i) & n) {
        n ^= (1  << i);
        ret = TT[ret][i];
      }
    }
    return ret;
  }

  int bsearch(int y, int len, int sgn) {
    int step;
    int y0 = y;
    for(step = 1; step < n; step *= 2);
    while(step) {
      int ny = y + sgn * step;
      if(ny <= n && ny >= 1 && LCP(norm[ny], norm[y0]) >= len)
        y = ny;
      step /= 2;
    }
    return y;
  }

  int losearch(int y, int len) {
    return bsearch(y, len, -1);
  }

  int hisearch(int y, int len) {
    return bsearch(y, len, 1);
  }


  int solve(int x, int y) {
    assert(lvl[x] < lvl[y]);
    //x e stramos
    //y e jos

    debug("now solving query %d %d\n", x, y);
    int len = lvl[y] - lvl[x];

    int lo = losearch(SFX[y][lg], len),
        hi = hisearch(SFX[y][lg], len);

    return hi - lo + 1;
  }

  vector<int> solve() {
    build();

    debug("norm is: \n");
    for(int i = 1; i <= n; ++i)
      debug("%d ", norm[i]);
    debug("\n");

    vector<int> ret;
    ret.reserve(m);

    for(auto &i: Q) 
      ret.push_back(solve(i.first, i.second));

    return ret;
  }
};

  solver s;

int main() {
  ifstream in("parb.in");
  int n, m;
  in >> n >> m;

  s.init(n, m);

  int x, y;
  char c;


  for(int i = 1; i < n; ++i) {
    in >> x >> y >> c;
    s.addEdge(x, y, c);
  }

  for(int i = 1; i <= m; ++i) {
    in >> x >> y;
    s.addQuery(x, y);
  }

  in.close();

  auto ans = s.solve();

  ofstream out("parb.out");
  for(auto i: ans)
    out << i << "\n";
  out.close();
  return 0;
}
