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

const int def = 20;
const int mid = 10;
const int limit = 1 << mid;

int n, i, conf, aux, cnt, dim, x;
vector<int> patt[11];
int data[5][1 << def];
ll ans;

void add(int x) {
    int cnt;

    for (cnt = 0; cnt <= 4; cnt++) {
        for (auto e : patt[cnt]) {
            data[cnt][x ^ e]++;
        }
    }
}

void solve(int x) {
    int cnt;

    for (cnt = 0; cnt <= 4; cnt++) {
        for (auto e : patt[cnt]) {
            ans += 1LL * data[4 - cnt][x ^ (e << mid)];
        }
    }
}

int main()
{
    freopen("aiacubiti.in","r",stdin);
    freopen("aiacubiti.out","w",stdout);

    for (conf = 0; conf < limit; conf++) {
        aux = conf; cnt = 0;
        while (aux > 0) {
            aux &= aux - 1;
            cnt++;
        }

        if (cnt <= 4) patt[cnt].pb(conf), dim++;
    }

    //cerr << dim;

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d", &x);
        add(x);
        solve(x);
    }

    printf("%lld", ans);
    cerr << ans;


    return 0;
}
