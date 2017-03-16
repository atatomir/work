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

const int def = 10000;

struct aib {
    int n;
    vector<int> data;

    void init(int _n) {
        n = _n;
        data = vector<int>(n + 10, 0);
    }

    int zrs(int x) {
        return (x ^ (x - 1)) & x;
    }

    void add(int pos, int v) {
        while (pos <= n) {
            data[pos] += v;
            pos += zrs(pos);
        }
    }

    int sum(int pos) {
        int ans = 0;
        while (pos > 0) {
            ans += data[pos];
            pos -= zrs(pos);
        }
        return ans;
    }

    int cb(int T) {
        int ans = 0;

        for (int step = 1 << 15; step > 0; step >>= 1)
            if (ans + step <= n)
                if (data[ans + step] <= T)
                    ans += step, T -= data[ans];

        return ans;
    }
};

struct girl {
    int c, t, id;

    bool operator<(const girl& who)const {
        return c > who.c;
    }
};

int n, T, i, j, min_t;
girl G[maxN];
aib aib_t, aib_cnt;

int ans[maxN];

int check(int T) {
    int pos = aib_t.cb(T);
    int ans = aib_cnt.sum(pos);

    T -= aib_t.sum(pos);
    if (pos != def)
        ans += T / (pos + 1);

    return ans;
}

int main()
{
    freopen("dlboss.in","r",stdin);
    freopen("dlboss.out","w",stdout);

    scanf("%d", &n);
    scanf("%d", &T);
    for (i = 1; i <= n; i++) {
        scanf("%d%d", &G[i].t, &G[i].c);
        G[i].id = i;
    }



    aib_t.init(10000);
    aib_cnt.init(10000);
    sort(G + 1, G + n + 1);

    for (i = 1; i <= n; i = j) {
        min_t = def + 11;
        for (j = i; G[i].c == G[j].c; j++) {
            min_t = min(min_t, G[j].t);
            ans[G[j].id] = check(T);
        }

        aib_t.add(min_t, min_t);
        aib_cnt.add(min_t, 1);
    }

    for (i = 1; i <= n; i++)
        printf("%d\n", ans[i]);


    return 0;
}
