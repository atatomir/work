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

#define maxN 1111

int n, i;
char s[maxN], rez[maxN];
ll le[maxN], ri[maxN];

int mv(int pos) {
    char base = rez[pos];

    while (rez[pos - 1] == base) pos--;
    rez[pos] = '.'; pos++;

    while (rez[pos] == base) pos++;
    if (rez[pos] == '.' || rez[pos] == '\0') {
        rez[pos] = base;
        return 1;
    }

    int ans = mv(pos);
    rez[pos] = base;
    return ans + 1;
}

void solve(ll *data) {
    int i, j;

    for (i = 1; i <= n; i++) {
        memcpy(rez, s, sizeof(s));
        while (rez[i] != '.')
            data[i] += mv(i);
    }
}

int main()
{
    freopen("slide.in","r",stdin);
    freopen("slide.ok","w",stdout);

    scanf("%s", s + 1);
    n = strlen(s + 1);

    solve(le);
    reverse(s + 1, s + n + 1);
    solve(ri);
    reverse(ri + 1, ri + n + 1);

    ll ans = 0;
    for (i = 1; i <= n; i++)
        ans += min(le[i], ri[i]);

    printf("%lld", ans);

    return 0;
}
