#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

#define maxN 100011
#define ll long long

int n, i;
ll v[maxN], ans;

int main() {
    scanf("%d", &n);
    
    for (i = 1; i <= n; i++)
        scanf("%lld", &v[i]);
    sort(v + 1, v + n + 1);
    
    if (v[n] < 0 && n % 2 == 1) {
        ll c1, c2;
        
        c1 = c2 = 0;
        for (i = 1; i <= n; i++)
            if (i & 1)
                c1 += v[i];
            else
                c2 += v[i];
        
        c2 += v[n];
        printf("%lld", max(c1, c2));
        return 0
    }
    
    for (i = 2; i <= n && v[i] < 0; i += 2)
        ans += v[i];
        
    for (i = 1; i <= n; i++)
        if (v[i] > 0)
            ans += v[i];
        
    printf("%lld", ans);
}

