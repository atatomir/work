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

#define maxN 1000011

struct frac {
    int a, b;

    frac(int _a, int _b) { a = _a, b = _b; }
    bool operator==(const frac& who)const { return 1LL * a * who.b == 1LL * b * who.a; }
    bool operator<(const frac& who)const { return 1LL * a * who.b < 1LL * b * who.a; }
    bool operator>(const frac& who)const { return 1LL * a * who.b > 1LL * b * who.a; }
};

int n, m, i, x, y, xx, yy, pos;
vector<frac> delim;
vector< pair<frac, int> > baraj;

int cnt;
int ans[maxN];

int main()
{
    freopen("nn.in","r",stdin);
    freopen("nn.out","w",stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) {
        scanf("%d%d", &x, &y);
        delim.pb(frac(y, x));
    }

    for (i = 1; i <= m; i++) {
        scanf("%d%d%d%d", &x, &y, &xx, &yy);
        if (frac(y, x) > frac(yy, xx)) {
            swap(x, xx);
            swap(y, yy);
        }
        baraj.pb(mp(frac(y, x), -i));
        baraj.pb(mp(frac(yy, xx), i));
    }

    sort(delim.begin(), delim.end());
    sort(baraj.begin(), baraj.end());

    pos = 0;
    for (auto b : baraj) {
        while (pos < delim.size()) {
            frac now = delim[pos];

            if (b.first < now) break;
            if (b.first == now && b.second < 0) break;

            cnt++; pos++;
        }

        if (b.second > 0)
            ans[b.second] += cnt;
        else
            ans[-b.second] -= cnt;
    }

    for (i = 1; i <= m; i++) printf("%d\n", max(0, ans[i] - 1));


    return 0;
}
