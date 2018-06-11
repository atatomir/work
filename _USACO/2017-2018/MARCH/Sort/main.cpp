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

const int maxN = 100011;

int n, i;
int v[maxN];
vector< pair<int, int> > ord;

int cnt_black, le, p;
bool black[maxN];

int when[maxN];
vector< pair<int, int> > upds;

ll ans, act;

void add_split(int pos) {
    black[pos] = true;
    if (black[pos + 1]) act--;
    if (black[pos - 1]) act--;
}

int main()
{
    freopen("sort.in","r",stdin);
    freopen("sort.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d", &v[i]);
        ord.pb(mp(v[i], i));
    }

    sort(ord.begin(), ord.end());
    reverse(ord.begin(), ord.end());

    cnt_black = 0;
    le = n + 1;
    p = n + 1;

    i = n;
    for (auto act : ord) {
        int pos = act.second;
        i--;

        cnt_black++;
        le = min(le, pos);
        black[pos] = true;
        while (p - 1 > 0 && black[p - 1]) {
            p--;
            cnt_black--;
        }

        if (le > i)
            when[i] = 0;
        else
            when[i] = cnt_black;
    }

    for (i = 1; i < n; i++)
        upds.pb(mp(when[i], i));

    sort(upds.begin(), upds.end());
    memset(black, 0, sizeof(black));
    p = 0;
    act = n;

    black[0] = black[n] = true;
    for (i = 0; act > 0; i++) {
        while (p < upds.size()) {
            if (upds[p].first > i) break;
            add_split(upds[p].second);
            p++;
        }

        if (i == 0)
            ans += n;
        else
            ans += act;
    }

    printf("%lld", ans);


    return 0;
}
