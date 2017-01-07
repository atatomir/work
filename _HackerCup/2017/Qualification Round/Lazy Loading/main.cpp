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

#define maxN 111

int t, ti;
int n, i;
int w[maxN];

int solve() {
    int l, r, i;
    int ans;

    sort(w + 1, w + n + 1);

    l = 1; r = n;
    ans = 0;

    while (l <= r) {
        int val = w[r];
        int cnt = r - l + 1;

        if (val * cnt < 50) break;

        cnt = (50 + val - 1) / val;
        cnt--;

        for (i = 1; i <= cnt; i++) l++;
        r--;

        ans++;
    }

    return ans;
}

int main()
{
    freopen("input.in","r",stdin);
    freopen("output.out","w",stdout);

    scanf("%d", &t);
    cerr << "Start solving " << t << " cases.\n";

    for (ti = 1; ti <= t; ti++) {
        cerr << "#" << ti << "\n";

        scanf("%d", &n);
        for (i = 1; i <= n; i++) scanf("%d", &w[i]);
        printf("Case #%d: %d\n", ti, solve());
    }


    return 0;
}
