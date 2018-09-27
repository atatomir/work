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

//#define debug(x) ;
#define debug(x) cerr << #x << " = " << x << "\n";

const int maxN = 100011;
const int inf = 2000000001;
const ll mod = 1000000007;

ostream& operator<<(ostream& cerr, vector<ll> aux) {
    cerr << "[";
    for (auto e : aux) cerr << e << ' ';
    cerr << "]";
    return cerr;
}


ostream& operator<<(ostream& cerr, vector< pair<int, int> > aux) {
    cerr << "[";
    for (auto e : aux) cerr << e.first << ',' << e.second << ' ';
    cerr << "]";
    return cerr;
}

int n, m, i, cnt;
int x[maxN], y[maxN];
vector< pair<int, int> > robots;
vector<int> coords;
ll aib[maxN];

void add(ll& a, ll b) {
    a += b;
    if (a >= mod) a -= mod;
}

int zrs(int x) {
    return (x ^ (x - 1)) & x;
}

void add_aib(int pos, ll v) {
    while (pos <= cnt) {
        add(aib[pos], v);
        pos += zrs(pos);
    }
}

ll sum_aib(int pos) {
    ll ans = 0;
    while (pos > 0) {
        add(ans, aib[pos]);
        pos -= zrs(pos);
    }
    return ans;
}

int get_id(int x) {
    return lower_bound(coords.begin(), coords.end(), x) - coords.begin() + 1;
}

void solve () {
    int i, j, k;

    sort(robots.begin(), robots.end());
    robots.resize(unique(robots.begin(), robots.end()) - robots.begin());

    coords = {0, inf};
    for (auto e : robots) coords.pb(e.second);
    sort(coords.begin(), coords.end());
    coords.resize(unique(coords.begin(), coords.end()) - coords.begin());
    cnt = coords.size();


    add_aib(1, 1);
    for (i = 0; i < robots.size(); i = j) {
        if (robots[i].first >= inf) break;

        for (j = i; j < robots.size(); j++)
            if (robots[i].first != robots[j].first)
                break;

        for (k = j - 1; k >= i; k--) {
            int pos = get_id(robots[k].second);
            add_aib(pos, sum_aib(pos - 1));
        }
    }

    cout << sum_aib(cnt - 1);
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) scanf("%d", &x[i]);
    for (i = 1; i <= m; i++) scanf("%d", &y[i]);

    y[0] = -inf;
    y[m + 1] = inf;

    for (i = 1; i <= n; i++) {
        int pos = lower_bound(y + 1, y + m + 1, x[i]) - y - 1;
        if (pos == 0 || pos == m) {
            if (pos == 0)
                robots.pb(mp(inf, y[1] - x[i]));
            else
                robots.pb(mp(x[i] - y[m], inf));
        } else {
            robots.pb(mp(x[i] - y[pos], y[pos + 1] - x[i]));
        }
    }


    solve();

    return 0;
}
