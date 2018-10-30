#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

//#define debug(x) ;
#define debug(x) cerr << #x << " = " << x << "\n";

ostream& operator<<(ostream& cerr, vector<ll> aux) {
    cerr << "[";
    for (auto e : aux) cerr << e << ' ';
    cerr << "]";
    return cerr;
}

const int maxN = 300011;

ll n, m, i, bg, en;
pair<ll, ll> v[maxN];
priority_queue<ll, vector<ll>, greater<ll> > unlocked, used;
ll ans;

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%lld%lld", &n, &m);
    for (i = 1; i <= n; i++) 
        scanf("%lld%lld", &v[i].first, &v[i].second);

    sort(v + 1, v + n + 1);
    
    for (i = 1; i <= n; i++) {
        bg = v[i].first;
        en = bg + v[i].second;

        while (!used.empty()) {
            ll aux = used.top(); 
            if (aux > bg) break;
            unlocked.push(aux);
            used.pop();
        }

        bool found = false;
        while (!unlocked.empty()) {
            ll aux = unlocked.top();
            if (aux + m >= bg) {
                found = true;
                unlocked.pop();
                break;
            }
            unlocked.pop();
        }

        used.push(en);
        if (found) ans++;
    }

    printf("%lld", ans);

    return 0;
}
