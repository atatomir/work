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

#define maxN 2017

struct circle {
    int x, y, r;

    bool operator<(const circle& who) const {
        return y * who.x < x * who.y;
    }

    bool operator==(const circle& who) const {
        return y * who.x == x * who.y;
    }
};

int n, i, j, x, y, r;
vector<circle> C, aux;
int dp[maxN];

int lns, best, bestcnt;

int solve(int l, int r) {
    int i, j, cnt, deltax, deltay;

    aux.clear();
    for (i = l; i < r; i++) aux.pb(C[i]);
    sort(aux.begin(), aux.end(), [](const circle& a, const circle& b)->bool const {
        return a.x < b.x;
    });

    int ans = 1;

    cnt = aux.size();
    for (i = 0; i < cnt; i++) dp[i] = 1;
    for (i = 0; i < cnt; i++) {
        for (j = 0; j < i; j++) {
            deltax = aux[i].x - aux[j].x;
            deltay = aux[i].y - aux[j].y;

            if (dp[i] < dp[j] + 1)
                if (deltax * deltax + deltay * deltay > aux[i].r * aux[i].r + aux[j].r * aux[j].r + 2 * aux[i].r * aux[j].r)
                    dp[i] = dp[j] + 1;

        }

        ans = max(ans, dp[i]);
    }

    return ans;
}

int main()
{
    freopen("cerc3.in","r",stdin);
    freopen("cerc3.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d%d%d", &x, &y, &r);
        C.pb({x, y, r});
    }

    sort(C.begin(), C.end());
    for (i = 0; i < C.size(); i = j) {
        for (j = i; j < C.size(); j++)
            if (!(C[i] == C[j])) break;

        int act = solve(i, j);

        lns++;

        if (act > best) {
            best = act;
            bestcnt = 0;
        }

        if (act == best)
            bestcnt++;
    }

    printf("%d %d %d\n", lns, best, bestcnt);




    return 0;
}
