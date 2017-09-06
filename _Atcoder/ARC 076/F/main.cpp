#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 500011

int n, m, i, l, r, fr, la, p, ans;
vector< pair<int, int> > data;
multiset<int> S;

int main()
{
    freopen("test.in","r",stdin);

    fr = 1 << 30;
    la = - 1 << 30;

    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) {
        scanf("%d%d", &l, &r);
        r = m + 1 - r;

        if (l == 0 && r == 0) continue;

        data.pb(mp(-l, r - 1));
        fr = min(fr, -l);
        la = max(la, r - 1);
    }

    sort(data.begin(), data.end());
    p = 0;
    for (i = fr; i <= la; i++) {
        while (p < data.size()) {
            if (data[p].first > i) break;
            S.insert(data[p].second);
            p++;
        }

        while (!S.empty()) {
            if (*S.begin() >= i) break;
            S.erase(S.begin());
        }

        if (S.empty()) continue;
        S.erase(S.begin()); ans++;
    }

    ans = min(ans, m);
    cout << n - ans;



    return 0;
}
