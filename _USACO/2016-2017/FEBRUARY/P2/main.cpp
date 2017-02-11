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

int n, i;
int a[maxN], b[maxN], wh[maxN];
int aib[maxN];
vector<int> aux;

int zrs(int x) {
    return (x ^ (x - 1)) & x;
}

void upd(int x, int v) {
    while (x <= n) {
        aib[x] = max(aib[x], v);
        x += zrs(x);
    }
}

int que(int x) {
    int ans = 0;

    while (x > 0) {
        ans = max(ans, aib[x]);
        x -= zrs(x);
    }

    return ans;
}

int main()
{
    freopen("nocross.in","r",stdin);
    freopen("nocross.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (i = 1; i <= n; i++) scanf("%d", &b[i]), wh[b[i]] = i;

    for (i = 1; i <= n; i++) {
        int act = a[i];
        int le = max(1, act - 4);
        int ri = min(n, act + 4);

        aux.clear();
        for (int to = le; to <= ri; to++)
            aux.pb(que(wh[to] - 1) + 1);

        for (int to = le; to <= ri; to++)
            upd(wh[to], aux[to - le]);
    }

    printf("%d", que(n));
    cerr << que(n);


    return 0;
}
