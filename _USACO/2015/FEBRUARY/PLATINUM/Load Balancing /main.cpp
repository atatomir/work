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
#define maxV 1000011

class aib {
    public:
        void init(int _n) {
            n = _n;
            data = vector<int>(n + 10, 0);
        }

        void add(int pos, int val) {
            while (pos <= n) {
                data[pos] += val;
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

        int search(int v) {
            int ans = 0;

            for (int step = 1 << 20; step > 0; step >>= 1) {
                if (ans + step <= n)
                    if (data[ans + step] <= v)
                        ans += step, v -= data[ans];
            }

            return ans;
        }

    private:
        int n;
        vector<int> data;

        int zrs(int x) {
            return (x & (x - 1)) ^ x;
        }
};

int n, i, j;
pair<int, int> P[maxN];
aib _left, _right;
int best;

void try_now(int how_left) {
    int how_right = n - how_left;

    int ans = 0;
    for (int step = 1 << 17; step > 0; step >>= 1) {
        if (ans + step <= how_left || ans + step <= how_right) {
            int p1 = _left.search(ans + step);
            int p2 = _right.search(ans + step);

            int pp = min(p1, p2);

            int s1 = _left.sum(pp);
            int s2 = _right.sum(pp);

            int aux = max( max( s1, s2 ), max(how_left - s1, how_right - s2) );
            if (aux > ans + step) ans += step;
        }
    }

    best = min(best, ans + 1);
}

int main()
{
    freopen("balancing.in","r",stdin);
    freopen("balancing.out","w",stdout);

    scanf("%d", &n);

    best = n;
    _left.init(1000000);
    _right.init(1000000);

    for (i = 1; i <= n; i++) {
        scanf("%d%d", &P[i].first, &P[i].second);
        _right.add(P[i].second, + 1);
    }

    sort(P + 1, P + n + 1);

    try_now(0);
    for (i = 1; i <= n; ) {
        for (j = i; P[j].first == P[i].first && j <= n; j++) {
            _left.add(P[j].second, +1);
            _right.add(P[j].second, -1);
        }
        i = j;

        try_now(i - 1);
    }

    printf("%d", best);

    return 0;
}
