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

#define maxN 100011

struct Point {
    int x, y, id;

    bool operator<(const Point& who)const {
        return mp(x + y, y - x) < mp(who.x + who.y, who.y - who.x);
    }
};

int n, i, cnt;
Point P[maxN];
set< pair<int, int> > S;

int ans[maxN];




int main()
{
    freopen("posta.in","r",stdin);
    freopen("posta.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++)
        scanf("%d%d", &P[i].x, &P[i].y), P[i].id = i;

    sort(P + 1, P + n + 1);
    S.clear();

    for (i = 1; i <= n; i++) {
        auto it = S.lower_bound(mp(P[i].y - P[i].x, cnt + 1));

        if (it == S.begin()) {
            cnt++;
            S.insert(mp(P[i].y - P[i].x, cnt));
            ans[P[i].id] = cnt;
        } else {
            it--;
            ans[P[i].id] = it->second;

            S.erase(it);
            S.insert(mp(P[i].y - P[i].x, ans[P[i].id]));
        }
    }

    printf("%d\n", cnt);
    for (i = 1; i <= n; i++)
        printf("%d ", ans[i]);

    return 0;
}
