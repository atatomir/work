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

#define maxVal 211
#define maxDim 75011
#define inf 100000

int n, g, i, x;
int how[maxVal];

int ss, dd;
int dp[2][maxDim];
int prov[2][maxDim];
int mask[maxDim];
deque< pair<int, int> > Work;
int limi;

int last_pos = -1;

vector< pair<int, int> > ans;
int def_limit = 205;
vector<int> sol;

void make_mask(int c1, int c2, int step) {
    for (int i = c2; i >= c1; i--) {
        if (i + step > c2)
            mask[i] = 0;
        else
            mask[i] = mask[i + step] + 1;
    }
}

void add_work(int how, int pos) {
    while (!Work.empty()) {
        auto last = Work.back();
        if (last.first < how) break;
        Work.pop_back();
    }

    Work.push_back(mp(how, pos));
    auto now = Work.front();
    if (now.second < pos - limi)
        Work.pop_front();
}

void solve_tasks(int c1, int c2, int step, int modd) {
    int i, start;

    start = c1 - (c1 % step) - 2 * step + modd;
    while (start < c1)
        start += step;

    while (!Work.empty()) Work.pop_back();
    limi = how[step] * step;

    for (i = start; i <= c2; i += step) {
        add_work(dp[ss][i] + mask[i], i);
        dp[dd][i] = Work.front().first - mask[i];
        prov[dd][i] = prov[ss][Work.front().second];
    }
}

void solve(int l1, int c1, int l2, int c2) {
    int i, j;

    if (l1 + 1 == l2) {
        return;
    }

    //! initializare
    ss = 0;
    dd = 1;
    for (i = c1 + 1; i <= c2; i++)
        dp[ss][i] = inf;
    dp[ss][c1] = 0;

    //! prima jumatate

    int mid = (l1 + l2) >> 1;

    for (i = l1 + 1; i <= mid; i++) {
        //! calculeaza linia

        make_mask(c1, c2, i);
        for (j = 0; j < i; j++)
            solve_tasks(c1, c2, i, j);

        swap(ss, dd);
    }

    //! initializez prov
    for (i = c1; i <= c2; i++)
        prov[ss][i] = i;


    //! a doua jumatate

    for (i = mid + 1; i <= l2; i++) {
        //! calculeaza linia

        make_mask(c1, c2, i);
        for (j = 0; j < i; j++)
            solve_tasks(c1, c2, i, j);

        swap(ss, dd);
    }

    //! concluzii

    int best = c2;
    while (best > c1 && dp[ss][best] >= inf) best--;

    if (last_pos == -1) last_pos = best;
    c2 = best;
    int wh = prov[ss][c2];

    solve(l1, c1, mid, wh);
    ans.pb(mp(mid, wh));
    solve(mid, wh, l2, c2);
}

int main()
{
    freopen("ghiozdan.in","r",stdin);
    freopen("ghiozdan.out","w",stdout);

    scanf("%d%d", &n, &g);
    for (i = 1; i <= n; i++) {
        scanf("%d", &x);
        how[x]++;
    }

    ans.pb(mp(0, 0));
    solve(0, 0, def_limit, g);
    ans.pb(mp(def_limit, g));

    ans[ ans.size() - 1 ].second = last_pos;

    sol.clear();
    for (i = 1; i <= def_limit; i++) {
        int diff = ans[i].second - ans[i - 1].second;
        diff /= i;

        while (diff-- > 0)
            sol.pb(i);
    }

    printf("%d %d\n", last_pos, sol.size());
    for (auto e : sol)
        printf("%d\n", e);


    return 0;
}
