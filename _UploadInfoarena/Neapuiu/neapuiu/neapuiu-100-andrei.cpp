#include <cstdio>
#include <vector>
#include <cassert>

using namespace std;

const int NMAX = 200000, MMAX = 200000;

#define x first
#define y second

#define ADD 0
#define DELETE 1
#define QUERY 2

int n, m, nmax, ind, nrs, sub;
bool fst[NMAX + 5];
int nodepoz[NMAX + 5][2], which[NMAX + 5], depth[NMAX + 5], pozeuler[NMAX + 5];
pair<int, int> euler[20][2 * NMAX + 5];

pair<int, pair<int, int>> aint[500000], op[NMAX + 5], rez;
int sum[500000];

vector<int> v[NMAX + 5];

void df(int node, int d) {
  fst[node] = 1;
  depth[node] = d;

  pozeuler[node] = ++ind;
  euler[0][ind] = make_pair(depth[node], node);

  nodepoz[node][0] = ++nrs;
  which[nrs] = node;

  for (auto next : v[node]) {
    if (!fst[next]) {
      df(next, d + 1);
      euler[0][++ind] = make_pair(depth[node], node);
    }
  }
  nodepoz[node][1] = nrs;
}

void update(int left, int right, int poz, int node, int op) {
  if (left == right) {
    if (op == ADD) {
      aint[poz].x = depth[which[node]];
      sum[poz]++;
    } else {
      aint[poz].x = 0;
      sum[poz]--;
    }
    aint[poz].y = make_pair(which[node], which[node]);

    return ;
  }

  int mid = (left + right) / 2;
  if (node <= mid) {
    update(left, mid, 2 * poz, node, op);
  } else {
    update(mid + 1, right, 2 * poz + 1, node, op);
  }

  if (aint[2 * poz].x > aint[2 * poz + 1].x) {
    aint[poz] = aint[2 * poz];
  } else if (aint[2 * poz].x < aint[2 * poz + 1].x) {
    aint[poz] = aint[2 * poz + 1];
  } else {
    aint[poz] = aint[2 * poz];
    aint[poz].y.y = aint[2 * poz + 1].y.y;
  }

  sum[poz] = sum[2 * poz] + sum[2 * poz + 1];
}

void query(int left, int right, int poz, int ql, int qr) {
  if (ql <= left && right <= qr) {
    sub += sum[poz];

    if (aint[poz].x > rez.x) {
      rez = aint[poz];
    } else if (aint[poz].x == rez.x) {
      rez.y.y = aint[poz].y.y;
    }

    return ;
  }

  if (ql > right || qr < left) {
    return ;
  }

  int mid = (left + right) / 2;

  query(left, mid, 2 * poz, ql, qr);
  query(mid + 1, right, 2 * poz + 1, ql, qr);
}

int lca(int x, int y) {
  int p1 = pozeuler[x], p2 = pozeuler[y];

  if (p1 > p2) {
    swap(p1, p2);
  }

  int l = p2 - p1 + 1;

  int j = 0;
  for (; (1 << j) <= l; j++); j--;

  if (euler[j][p1].x < euler[j][p2 - (1 << j) + 1].x) {
    return euler[j][p1].y;
  }
  return euler[j][p2 - (1 << j) + 1].y;
}

int main() {
  freopen("neapuiu.in", "rt", stdin);
  freopen("neapuiu.out", "wt", stdout);

  assert(scanf("%d%d", &n, &m) == 2);
  assert(1 <= n && n <= NMAX / 2);
  assert(1 <= m && m <= MMAX / 2);

  for (int i = 1; i < n; i++) {
    int x, y;
    assert(scanf("%d%d", &x, &y) == 2);
    assert(1 <= x && x <= n);
    assert(1 <= y && y <= n);

    v[x].push_back(y);
    v[y].push_back(x);
  }

  for (int i = 1; i <= m; i++) {
    assert(scanf("%d", &op[i].x) == 1);

    switch (op[i].x) {
      case ADD:
        assert(scanf("%d%d", &op[i].y.x, &op[i].y.y) == 2);
        assert(1 <= op[i].y.y && op[i].y.y <= n + m);
        v[op[i].y.x].push_back(op[i].y.y);
        nmax = max(nmax, op[i].y.y);
        break;
      case DELETE:
        assert(scanf("%d", &op[i].y.y) == 1);
        break;
      case QUERY:
        assert(scanf("%d", &op[i].y.x) == 1);
        break;
      default:
        assert(true);
    }
  }

  df(1, 1);

  for (int i = 1; (1 << i) <= ind; i++) {
    for (int j = 1; j + (1 << i) - 1 <= ind; j++) {
      euler[i][j] = min(euler[i - 1][j], euler[i - 1][j + (1 << (i - 1))]);
    }
  }

  for (int i = 1; i <= n; i++) {
    update(1, nmax, 1, nodepoz[i][0], ADD);
  }

  for (int i = 1; i <= m; i++) {
    switch (op[i].x) {
      case ADD:
      case DELETE:
        update(1, nmax, 1, nodepoz[op[i].y.y][0], op[i].x);
        break;
      case QUERY: {
        int node = op[i].y.x;

        // variabile globale pentru query-ul pe aint
        rez.x = 0;
        sub = 0;
        query(1, nmax, 1, nodepoz[node][0], nodepoz[node][1]);

        printf("%d\n", sub - 1 - (depth[lca(rez.y.x, rez.y.y)] - depth[node]));
      }
    }
  }

  return 0;
}
