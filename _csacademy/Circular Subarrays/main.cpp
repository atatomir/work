#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

#define ll long long
#define mp make_pair
#define pb push_back

#define maxN 100011

int n, i, k, v[maxN];
bool used[maxN];
vector<int> now;
int ans;

int main() {
    scanf("%d%d", &n, &k);
    for (i = 1; i <= n; i++) scanf("%d", &v[i]);
    
    for (i = 1; i <= n; i++) {
        if (used[i]) continue;
        
        now.clear();
        for (int j = i; used[j] == false; ) {
            used[j] = true;
            now.pb(v[j]);
            j = (j + k) % n;
            if (j == 0) j = n;
        }
        
        sort(now.begin(), now.end());
        int pos = (1 + now.size()) / 2 - 1;
        
        for (i : now) {
            ans += abs(now[pos] - i);
        }    
    }
    
    printf("%d", ans);
}

