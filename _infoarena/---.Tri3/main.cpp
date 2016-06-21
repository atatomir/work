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

#define maxN 100011
#define T pair<int, int>
#define lSon (node << 1)
#define rSon (lSon | 1)

T A, B;


bool cmp2(const pair<int, int>& a, const pair<int, int>& b) {
    return mp(a.first, -a.second) < mp(b.first, -b.second);
}

ll cross(const T& A, T B, T C) {
    B.first -= A.first;
    B.second -= A.second;

    C.first -= A.first;
    C.second -= A.second;

    return 1LL * B.first * C.second - 1LL * B.second * C.first;
}

struct aint {
    int n;
    vector< T > *data;
    T *from;


    void compute(int node, int l, int r) {
        int i, pos;

        data[node].resize(r - l + 1);
        for (i = l; i <= r; i++) data[node][i - l] = from[i];
        sort(data[node].begin(), data[node].end(), cmp2);

        pos = 0;
        for (i = 1; i < data[node].size(); i++) {
            while (pos >= 1) {
                if (cross(data[node][pos - 1], data[node][pos], data[node][i]) >= 0) break;
                pos--;
            }

            data[node][++pos] = data[node][i];
        }

        data[node].resize(pos + 1);
    }

    void build(int node, int l, int r) {
        if (l == r) {
            data[node] = {from[l]};
            return;
        }

        int mid = (l + r) >> 1;
        build(lSon, l, mid);
        build(rSon, mid + 1, r);

        compute(node, l, r);
    }

    void init(int _n, vector< T > *_data, pair<int, int> *_from) {
        n = _n;
        data = _data;
        from = _from;

        build(1, 1, n);
    }

    bool solve(int node) {
        if (A > B) swap(A, B);
        if (A.first == B.first)
            swap(A, B);

        int low = 0;
        int high = data[node].size() - 1;
        int m1, m2;

        while (low + 2 < high) {
            //m1 = (2 * low + high) / 3;
            //m2 = (low + 2 * high) / 3;
            m1 = (low + high) / 2;
            m2 = m1 + 1;

            if (cross(A, B, data[node][m1]) < cross(A, B, data[node][m2]))
                high = m2;
            else
                low = m1;
        }

        for (int i = low; i <= high; i++)
            if (cross(A, B, data[node][i]) < 0)
                return true;

        return false;
    }

    bool query(int node, int l, int r, int qL, int qR) {
        if (qL <= l && r <= qR)
            return solve(node);

        int mid = (l + r) >> 1;
        if (qL <= mid)
            if (query(lSon, l, mid, qL, qR))
                return true;
        if (qR > mid)
            if (query(rSon, mid + 1, r, qL, qR))
                return true;

        return false;
    }


};

int n, m, i;
pair<int, int> P[maxN];
vector< T > aint_data[maxN << 2];

aint work;
T p1, p2;
int pos1, pos2;

bool cmp(const pair<int, int>& a, const pair<int, int>& b) {
    return cross(mp(0, 0), a, b) > 0;
}

int cb(pair<int, int> p) {
    int i;
    int ans = 0;

    for (int step = (1 << 16); step > 0; step >>= 1)
        if (ans + step <= n)
            if (cross(mp(0, 0), p, P[ans + step]) <= 0)
                ans += step;

    return ans;
}


int main()
{
    freopen("tri3.in","r",stdin);
    freopen("tri3.out","w",stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) scanf("%d%d", &P[i].first, &P[i].second);
    sort(P + 1, P + n + 1, cmp);

    work.init(n, aint_data, P);
    for (i = 1; i <= m; i++) {
        scanf("%d%d%d%d", &p1.first, &p1.second, &p2.first, &p2.second);

        pos1 = cb(p1);
        pos2 = cb(p2);
        if (pos1 > pos2) swap(pos1, pos2);
        pos1++;

        A = p1;
        B = p2;

        if (mp(A.first, -A.second) > mp(B.first, -B.second)) swap(A, B);

        if (work.query(1, 1, n, pos1, pos2))
            printf("Y\n");
        else
            printf("N\n");
    }

    return 0;
}
