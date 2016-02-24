#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 30000

int n, m, A, B, i, v;
vector<int> vx, vy;
ll ans;

int sel_x, sel_y;

struct cmp {
    bool operator()(const pair<int, int> &a, const pair<int, int> &b) {
        return a > b;
    }
};

priority_queue< pair<int, int>, vector< pair<int, int> >, cmp > H_x, H_y;

int main()
{
    freopen("fencedin.in","r",stdin);
    freopen("fencedin.out","w",stdout);

    scanf("%d%d%d%d", &A, &B, &n, &m);

    vx.pb(0);
    vx.pb(A);

    vy.pb(0);
    vy.pb(B);

    for (i = 1; i <= n; i++) {
        scanf("%d", &v);
        vx.pb(v);
    }
    sort(vx.begin(), vx.end());

    for (i = 1; i <= m; i++) {
        scanf("%d", &v);
        vy.pb(v);
    }
    sort(vy.begin(), vy.end());

    for (i = 1; i < vx.size(); i++)
        H_x.push(mp( vx[i] - vx[i - 1], i ));

    for (i = 1; i < vy.size(); i++)
        H_y.push(mp( vy[i] - vy[i - 1], i ));

    sel_x = vx.size() - 2;
    sel_y = vy.size() - 2;

    auto now = H_x.top(); H_x.pop();
    ans += 1LL * now.first * sel_y;

    now = H_y.top(); H_y.pop();
    ans += 1LL * now.first * sel_x;

    while (H_x.empty() == false || H_y.empty() == false) {
        int id, from;

        if (H_x.empty() == false) {
            id = H_x.top().second;
            from = 1;

            if (H_y.empty() == false) {
                if (H_y.top().first < H_x.top().first) {
                    id = H_y.top().second;
                    from = 2;
                }
            }
        } else {
            id = H_y.top().second;
            from = 2;
        }

        if (from == 1) {
            ans += 1LL * sel_y * H_x.top().first;
            int pos = H_x.top().second;

            sel_x--;

            H_x.pop();
        } else {
            ans += 1LL * sel_x * H_y.top().first;
            int pos = H_y.top().second;

            sel_y--;

            H_y.pop();
        }
    }

    printf("%lld", ans);

    return 0;
}
