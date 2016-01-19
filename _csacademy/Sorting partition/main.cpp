#include <cstdio>
#include <iostream>

using namespace std;

#define maxN 100011

int n, i;
int v[maxN];
int mini[maxN], maxi[maxN];
int ans;

int main() {
    scanf("%d", &n);
    for (i = 1; i <= n; i++)
        scanf("%d", &v[i]);
        
    maxi[1] = v[1];
    for (i = 2; i <= n; i++)
        maxi[i] = max(maxi[i - 1], v[i]);
        
    mini[n] = v[n];
    for (i = n - 1; i >= 1; i--)
        mini[i] = min(mini[i + 1], v[i]);
        
    for (i = 1; i < n; i++)
        if (maxi[i] <= mini[i + 1])
            ans++;
            
    printf("%d", ans + 1);
}

