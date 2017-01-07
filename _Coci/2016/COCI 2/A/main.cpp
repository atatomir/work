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

#define maxN 77

int n, i, need, c, act;
char s[maxN];

int ans;
int best;
char s_best[maxN];

int get_cnt() {
    int ans = 0;

    while (c >= need) {
        c -= need;
        c += 2;
        ans++;
    }

    return ans;
}

int main()
{
    //freopen("test.in","r",stdin);

    best = -1;

    scanf("%d\n", &n);
    for (i = 1; i <= n; i++) {
        memset(s, 0, sizeof(s));
        scanf("%s\n%d%d\n", s + 1, &need, &c);

        act = get_cnt();
        ans += act;
        if (act > best) {
            best = act;
            memcpy(s_best, s, sizeof(s));
        }
    }

    printf("%d\n%s", ans, s_best + 1);


    return 0;
}
