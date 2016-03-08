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

int n, m, id, divi, i;
int v[maxN];
int now;

int gcd(int a, int b) {
    if (a < b) swap(a, b);
    while (b) {
        a %= b;
        swap(a, b);
    }
    
    return a;
}

int main() {
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) {
        scanf("%d", &v[i]);
        if (i == 1) 
            now = v[i];
        else
            now = gcd(now, v[i]);
    }
    
    for (i = 1; i <= m; i++) {
        scanf("%d%d", &id, &divi);
        v[id] /= divi;
        now = gcd(now, v[id]);
        
        printf("%d", now);
    }
    
    
}

