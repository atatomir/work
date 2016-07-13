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

int t, ti;
int n, i;
char s[maxN];
int x[maxN];

vector<int> aux;
int ans;

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d", &t);
    for (ti = 1; ti <= t; ti++) {
        scanf("%d\n%s\n", &n, s + 1);
        for (i = 1; i <= n; i++) scanf("%d", &x[i]);

        ans = 0;

        for (i = 1; s[i] == '0'; i++);
        ans += x[i] - x[1];

        for (i = n; s[i] == '0'; i--);
        ans += x[n] - x[i];

        aux.clear();
        for (i = 1; i <= n; i++)
            if (s[i] == '1')
                aux.pb(i);

        for (i = 1; i < aux.size(); i++) {
            int l = aux[i - 1];
            int r = aux[i];

            if (l + 1 == r) continue;

            ans += x[r] - x[l];

            int aux = -1;
            for (int j = l + 1; j <= r; j++)
                aux = max(aux, x[j] - x[j - 1]);

            ans -= aux;
        }

        printf("%d\n", ans);
    }



    return 0;
}
