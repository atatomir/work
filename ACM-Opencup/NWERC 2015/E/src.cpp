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

#define debug(x) ;
//#define debug(x) cerr << #x << " = " << x << "\n";

const int maxN = 2511 * 3;

ostream& operator<<(ostream& cerr, vector<ll> aux) {
    cerr << "[";
    for (auto e : aux) cerr << e << ' ';
    cerr << "]";
    return cerr;
}

int n, i;
pair<ll, ll> v[maxN];
vector<ll> pos;

int l[maxN], r[maxN];
vector<int> list[maxN];
bool us[maxN];

int get_id(ll x) {
    return lower_bound(pos.begin(), pos.end(), x) - pos.begin() + 1;
}

bool pairUp(int node) {
    if (us[node]) return false;
    us[node] = true;

    for (auto to : list[node])
        if (r[to] == 0)
            {l[node] = to; r[to] = node; return true;}


    for (auto to : list[node])
        if (pairUp(r[to]))
            {l[node] = to; r[to] = node; return true;}

    return false;
}

void print_ec(ll x, ll y, ll rez) {

    debug(x);
    debug(y);
    debug(rez);

    if (x + y == rez) {
        printf("%lld + %lld = %lld\n", x, y, rez);
        return;
    }
    if (x - y == rez) {
        printf("%lld - %lld = %lld\n", x, y, rez);
        return;
    }
    if (x * y == rez) {
        printf("%lld * %lld = %lld\n", x, y, rez);
        return;
    }
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%lld%lld", &v[i].first, &v[i].second);
        pos.pb(v[i].first + v[i].second);
        pos.pb(v[i].first - v[i].second);
        pos.pb(v[i].first * v[i].second);
    }

    debug(v[4].first);

    sort(pos.begin(), pos.end());
    pos.resize(unique(pos.begin(), pos.end()) - pos.begin());
    
    for (i = 1; i <= n; i++) {
        list[i].pb(get_id( v[i].first + v[i].second ));
        list[i].pb(get_id( v[i].first - v[i].second ));
        list[i].pb(get_id( v[i].first * v[i].second ));
    }

    bool ok = true;
    while (ok) {
        ok = false;
        memset(us, 0, sizeof(us));
    
        for (i = 1; i <= n; i++)
            if (!l[i])
                ok |= pairUp(i);
    }
   
    for (i = 1; i <= n; i++)
        if (l[i] == 0)
            {printf("impossible"); return 0;}

    for (i = 1; i <= n; i++) {
        print_ec(v[i].first, v[i].second, pos[l[i] - 1]);
    }


    return 0;
}
