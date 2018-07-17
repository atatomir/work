#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

const int maxN = 40;
const ll mod = 1000000007;
const ll base = 27;

const ll mod2 = 666013;
const ll base2 = 29;

int n, i, limit, conf, cnt;
char s[maxN];
string a, b;
map< string , ll> M[maxN];
ll ans;

pair<ll, ll> get_hash(string& act) {
    ll ans = 0;
    ll ans2 = 0;

    for (auto e : act) {
        ans = (ans * base + e - 'a') % mod;
        ans2 = (ans * base2 + e - 'a') % mod2;
    }

    return mp(ans, ans2);
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d\n%s", &n, s);
    limit = 1 << n;

    for (conf = 0; conf < limit; conf++) {
        a.clear();
        b.clear();

        cnt = 0;
        for (i = 0; i < n; i++) {
            if ((conf >> i) & 1)
                a += s[i], cnt++;
            else
                b += s[i];
        }

        reverse(b.begin(), b.end());
        a += b;

        //cerr << a << ' ' << cnt << '\n';

        M[cnt][a]++;
    }

    //cerr << "\n\n";

    for (conf = 0; conf < limit; conf++) {
        a.clear();
        b.clear();

        cnt = 0;
        for (i = 0; i < n; i++) {
            if ((conf >> i) & 1)
                a += s[n + i], cnt++;
            else
                b += s[n + i];
        }

        reverse(b.begin(), b.end());
        b += a;
        
        //cerr << b << ' ' << cnt << '\n';

        ans += M[n - cnt][b];
    }

    printf("%lld", ans);

    return 0;
}
