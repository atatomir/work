#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

#define maxN 100011
#define mp make_pair
#define ll long long
#define inf 1000000000000000000LL

int n, i, t, j;
int v[maxN];

int pos;
pair<int, int> marbles[maxN];

ll no_change[maxN];
ll one_add_l[maxN];
ll one_add_r[maxN];

ll compute(ll val, ll how) {
    return ((how + val - 1) / val) * val;
}

int main() {
    for (scanf("%d", &t); t; t--) {
        scanf("%d", &n);
        for (i = 1; i <= n; i++)
            scanf("%d", &v[i]);
            
        sort(v + 1, v + n + 1);
        pos = 0;
        
        for (i = 1; i <= n; i++) {
            pos++;
            marbles[pos] = mp(v[i], 1);
            
            for (j = i + 1; j <= n && v[i] == v[j]; j++, marbles[pos].second++); 
            i = j - 1;
        }
        
        //! compute...
        n = pos;
        
        no_change[0] = 0;
        one_add_l[0] = inf;
        one_add_r[n + 1] = inf;
        
        
        for (i = 1; i <= n; i++)
            no_change[i] = no_change[i - 1] + compute(marbles[i].first, marbles[i].second);
        
        one_add_l[1] = compute(marbles[1].first, marbles[1].second + 1);
        for (i = 2; i <= n; i++)
            one_add_l[i] = min(one_add_l[i - 1] + compute(marbles[i].first, marbles[i].second),
                               no_change[i - 1] + compute(marbles[i].first, marbles[i].second + 1));
                               
        one_add_r[n] = compute(marbles[n].first, marbles[n].second + 1);
        for (i = n - 1; i >= 1; i--)
            one_add_r[i] = min(one_add_r[i + 1] + compute(marbles[i].first, marbles[i].second),
                               no_change[n] - no_change[i] + compute(marbles[i].first, marbles[i].second + 1));
                    
                   
        //! now solve
        ll ans = inf;
        for (i = 1; i <= n; i++)
            if (marbles[i].first != 1)
                ans = min(ans, no_change[n] - compute(marbles[i].first, marbles[i].second) +
                               compute(marbles[i].first, marbles[i].second - 1) + 1);
            else
                ans = min(ans, no_change[n] - compute(marbles[i].first, marbles[i].second) +
                               compute(marbles[i].first, marbles[i].second - 1) + 2);
                
                               
        for (i = 1; i <= n; i++) {
            ll aux = no_change[i - 1] + compute(marbles[i].first, marbles[i].second - 1) + one_add_r[i + 1];
            ll aux2 = no_change[n] - no_change[i] + compute(marbles[i].first, marbles[i].second - 1) + one_add_l[i - 1];
            
            if (i == n)
                aux = inf;
            if (i == 1)
                aux2 = inf;
            
            aux = min(aux, aux2);
            ans = min(ans, aux);
        }
        
        printf("%lld\n", ans);
    }
    
}

