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

const int maxN = 200011;

int n, i, l, r;
int a[maxN];
ll ans;

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) scanf("%d", &a[i]);
    
    l = r = n + 1;
    for (i = n; i >= 1; i--) {
        if (i < l) {
            ans += 1LL * a[i];
            l = i - a[i];
            r = i;

            if (l < 1) {
                printf("-1");
                return 0;
            }
        } else {
            if (a[i] == i - l) continue;
            if (a[i] < i - l) {
                printf("-1");
                return 0;
            }

            l = i - a[i];
            r = i;
            if (l >= 1) {
                ans += 1LL * a[i];
            } else {
                printf("-1");
                return 0;
            }
        }
    }

    printf("%lld", ans);


    return 0;
}
