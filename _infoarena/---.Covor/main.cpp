#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stack>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 2016

int n, i, j;
char s[maxN];
int up[maxN], le[maxN], ri[maxN];
stack<int> S;
ll ans;

int main()
{
    freopen("covor.in","r",stdin);
    freopen("covor.out","w",stdout);

    scanf("%d\n", &n);
    for (i = 1; i <= n; i++) {
        scanf("%s\n", s + 1);
        for (j = 1; j <= n; j++)
            up[j] = (s[j] == '0' ? up[j] + 1 : 0);

        up[0] = up[n + 1] = -1;

        // left
        while (!S.empty()) S.pop();
        S.push(0);

        for (j = 1; j <= n; j++) {
            while (up[S.top()] >= up[j]) S.pop();
            le[j] = j - S.top();
            S.push(j);
        }

        // right
        while (!S.empty()) S.pop();
        S.push(n + 1);

        for (j = n; j >= 1; j--) {
            while (up[S.top()] > up[j]) S.pop();
            ri[j] = S.top() - j;
            S.push(j);
        }

        // add sol
        for (j = 1; j <= n; j++)
            ans += 1LL * le[j] * ri[j] * up[j];
    }

    printf("%lld", ans);

    return 0;
}
