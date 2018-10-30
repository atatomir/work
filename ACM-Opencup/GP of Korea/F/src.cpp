#include <iostream>
#include <map>
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

ostream& operator<<(ostream& cerr, vector<ll> aux) {
    cerr << "[";
    for (auto e : aux) cerr << e << ' ';
    cerr << "]";
    return cerr;
}

ll t, ti;
ll n;
vector< pair<ll, ll> > ans;
map<ll, ll> M;

ll run(ll n) {
    if (M.count(n) > 0) 
        return M[n];

    ll n2 = run(n / 2);
    ll n1 = run((n + 1) / 2);
    ans.pb(mp(n1, n2));
    M[n] = ans.size() - 1;

    return ans.size() - 1;
}

int main()
{
    //freopen("test.in","r",stdin);
    
    scanf("%lld", &t);
    for (ti = 1; ti <= t; ti++) {
        scanf("%lld", &n);
        ans = {mp(-1, -1)};
        M.clear();
        M[1] = 0;
    
        run(n);
    
        //debug(M[2]);
        //debug(M[1]);
        //debug(M[3]);
        

        printf("%d\n", ans.size());
        for (auto e : ans)
            printf("%lld %lld\n", e.first, e.second);
        printf("%lld\n", ans.size() - 1);
    } 



    return 0;
}
