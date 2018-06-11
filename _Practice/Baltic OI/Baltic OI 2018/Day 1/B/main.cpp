#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

const int maxN = 200011;

struct aint {
    int data[maxN * 2 + 11];

    int frm(int l, int r) {
        return (l + r) | (l != r);
    }

    void upd(int l, int r, int qL, int qR, int val) {
        if (l > r) return;
        int node = frm(l, r);

        if (qL <= l && r <= qR) {
            data[node] = max(data[node], val);
            return;
        }

        int mid = (l + r) >> 1;
        if (qL <= mid) upd(l, mid, qL, qR, val);
        if (qR > mid) upd(mid + 1, r, qL, qR, val);
    }

    int que(int l, int r, int pos) {
        int node = frm(l, r);

        if (l == r) return data[node];
        int mid = (l + r) >> 1;

        if (pos <= mid) return max(data[node], que(l, mid, pos));
        return max(data[node], que(mid + 1, r, pos));
    }
};

int n, k, r, i, j, x, y, limit;
int v[maxN];
int rest[maxN];
vector<int> wh[maxN];
aint work;
int ans;

void add(vector<int>& data, int cnt) {
    int i;

    work.upd(1, n, 1, data[0], data[cnt - 1]);
    for (i = 1; i + cnt - 1 < data.size(); i++)
        work.upd(1, n, data[i - 1] + 1, data[i], data[i + cnt - 1]);
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d%d%d", &n, &k, &r);
    for (i = 1; i <= n; i++) {
        scanf("%d", &v[i]);
        wh[v[i]].pb(i);
    }

    for (i = 1; i <= r; i++) {
        scanf("%d%d", &x, &y);
        rest[x] = y;
    }

    limit = n;
    for (i = 0; i <= k; i++) {
        if (rest[i] == 0) continue;
        if (rest[i] > wh[i].size()) {
            printf("impossible");
            return 0;
        }

        limit = min(limit, wh[i][wh[i].size() - rest[i]]);
        add(wh[i], rest[i]);
    }

    ans = n;
    for (i = 1; i <= limit; i++) {
        ans = min(ans, work.que(1, n, i) - i + 1);
        //cerr << work.que(1, n, i) << ' ';
    }

    ans = max(ans, 1);
    printf("%d", ans);




    return 0;
}
