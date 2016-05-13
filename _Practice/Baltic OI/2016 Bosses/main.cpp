#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>


using namespace std;


#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 50011

int n, m, i, j, x, k;
vector<int> list[maxN];
queue<int> Q;

int dist[maxN];
ll sum, ans;

int cnt;

int main() {
    
    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d", &k);
        for (j = 1; j <= k; j++) {
            scanf("%d", &x);
            list[x].pb(i);
        }
    }
    
    ans = 1LL << 60;
    
    for (i = 1; i <= n; i++) {
        memset(dist, 0, sizeof(dist));
        sum = 0;
        cnt = 0;
        
        dist[i] = 1;
        sum = 1;
        Q.push(i);
        
        while (!Q.empty()) {
            int node = Q.front(); Q.pop();
            cnt++;
            
            for (int to : list[node])
                if (dist[to] == 0)
                    dist[to] = dist[node] + 1, sum += 1LL * dist[to], Q.push(to);
        }
        
        if (cnt == n)
            ans = min(ans, sum);
    
    }
    
    printf("%lld", ans);
    
    return 0;
}
