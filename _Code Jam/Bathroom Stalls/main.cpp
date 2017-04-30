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

int t, ti;
ll n, k;
vector< pair<ll, ll> > data;

void fast_forward(ll cnt) {
    ll aux, i, pos;

    while (data.back().second <= cnt) {
        auto act = data.back();
        data.pop_back();

        aux = (act.first - 1) / 2;
        data.pb(mp(aux, act.second));
        data.pb(mp(act.first - 1 - aux, act.second));

        cnt -= act.second;
        sort(data.begin(), data.end());

        pos = 1;
        for (i = 1; i < data.size(); i++) {
            if (data[i].first == data[pos - 1].first)
                data[pos - 1].second += data[i].second;
            else
                data[pos++] = data[i];
        }

        data.resize(pos);
    }
}

int main()
{
    freopen("test.in","r",stdin);
    freopen("test.out", "w", stdout);

    scanf("%d", &t);
    for (ti = 1; ti <= t; ti++) {
        scanf("%lld%lld", &n, &k);
        data = {mp(n, 1)};

        fast_forward(k - 1);

        ll aux = (data.back().first - 1) / 2;
        printf("Case #%d: %lld %lld\n", ti, data.back().first - 1 - aux, aux);
    }


    return 0;
}
