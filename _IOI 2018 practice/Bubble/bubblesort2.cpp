#include "bubblesort2.h"
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>

using namespace std;

#define pb push_back
#define ll long long
#define mp make_pair

#define lSon (node << 1)
#define rSon (lSon | 1)

static const int maxN = 1000011;

struct aint {
    int add[maxN * 4 + 11];
    int data[maxN * 4 + 11];

    void init() {
        memset(add, 0, sizeof(add));
        memset(data, 0, sizeof(data));
    }

    void upd(int node, int l, int r, int qL, int qR, int v) {
        if (qL <= l && r <= qR) {
            add[node] += v;
            data[node] += v;
            return;
        }

        int mid = (l + r) >> 1;
        if (qL <= mid) upd(lSon, l, mid, qL, qR, v);
        if (qR > mid) upd(rSon, mid + 1, r, qL, qR, v);
        data[node] = max(data[lSon], data[rSon]) + add[node];
    }
};

static int n, i, q, j;
static int a[maxN];
static int pos[maxN], v[maxN];
static vector<int> sol = {};
static vector< pair<int, int> > ord;
static aint work;

int get_pos(pair<int, int> x) {
    return lower_bound(ord.begin(), ord.end(), x) - ord.begin() + 1;
}

void add_val(int position, int x) {
    int wh = get_pos(mp(x, position));

    work.upd(1, 1, ord.size(), wh, ord.size(), -1);
    work.upd(1, 1, ord.size(), wh, wh, position);
}

void rm_val(int position, int x) {
    int wh = get_pos(mp(x, position));

    work.upd(1, 1, ord.size(), wh, ord.size(), +1);
    work.upd(1, 1, ord.size(), wh, wh, -position);
}

vector<int> count_scans(vector<int> A, vector<int> X, vector<int> V){
	q = X.size();
	n = A.size();
	for (i = 0; i < n; i++) a[i + 1] = A[i], ord.pb(mp(A[i], i + 1));
	for (i = 0; i < q; i++) {
        pos[i + 1] = X[i] + 1;
        v[i + 1] = V[i];
        ord.pb(mp(V[i], pos[i + 1]));
	}

    sort(ord.begin(), ord.end());
    ord.resize(unique(ord.begin(), ord.end()) - ord.begin());

    work.init();
    for (i = 1; i <= n; i++) add_val(i, a[i]);

    for (i = 1; i <= q; i++) {
        rm_val(pos[i], a[pos[i]]);
        a[pos[i]] = v[i];
        add_val(pos[i], a[pos[i]]);

        sol.pb(work.data[1]);
    }

    return sol;
}
