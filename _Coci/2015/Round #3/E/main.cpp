#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 100011

class aint {
    public:
        void init(long long *_data) {
            data = _data;
        }

        void update(int node, int l, int r, int go, long long v) {
            if (l == r) {
                data[node] = v;
                return;
            }

            int mid = (l + r) >> 1;
            if (go <= mid)
                update(node<<1, l, mid, go, v);
            else
                update((node<<1)|1, mid + 1, r, go, v);

            data[node] = data[node<<1] | data[(node<<1)|1];
        }

        long long get(int node, int l, int r, int qL, int qR) {
            if (qL <= l && r <= qR)
                return data[node];

            long long ans = 0;

            int mid = (l + r) >> 1;
            if (qL <= mid)
                ans |= get(node << 1, l, mid, qL, qR);
            if (qR >  mid)
                ans |= get((node << 1) | 1, mid + 1, r, qL, qR);

            return ans;
        }

    private:
        long long *data;
};

int n, k, m, i, x, need, op, a, b, def_step;

long long aint_data[maxN << 2];
aint work;

int getAns() {
    int i;
    if (work.get(1, 1, n, 1, n) != need)
        return -1;

    int now = n;

    int last = 0;
    for (i = 1; i <= n; i++) {
        int ans = max(i - 1, last);

        for (int step = 1 << def_step; step > 0; step >>= 1) {
            if (ans + step <= n)
                if (work.get(1, 1, n, i, ans + step) != need)
                    ans += step;
        }

        last = ans;
        ans++;
        if (ans == n + 1) break;
        now = min(now, ans - i + 1);
    }

    return now;
}

int main()
{
    freopen("test.in","r",stdin);

    work.init(aint_data);
    scanf("%d%d%d", &n, &k, &m);
    need = (1 << k) - 1;

    def_step = 1;
    while (def_step * 2 <= n) def_step *= 2;

    for (i = 1; i <= n; i++) {
        scanf("%d", &x);
        work.update(1, 1, n, i, 1 << (x - 1));
    }

    for (i = 1; i <= m; i++) {
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d%d", &a, &b);
            work.update(1, 1, n, a, 1 << (b - 1));
        } else {
            printf("%d\n", getAns());
        }
    }

    return 0;
}
