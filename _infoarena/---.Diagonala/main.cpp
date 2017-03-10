#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <functional>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 200011

struct slid {
    deque< pair<int, int> > data;
    function<bool(int a, int b)> cmp;

    void init(function<bool(int a, int b)> _cmp) {
        while (!data.empty()) data.pop_back();
        cmp = _cmp;
    }

    void add(pair<int, int> act) {
        while (!data.empty()) {
            if (cmp(data.back().first, act.first)) break;
            data.pop_back();
        }
        data.push_back(act);
    }
};

int n, i;
int x[maxN], y[maxN];

slid mini, maxi;

int solve(int tp) {
    int i, pos;
    int ans = 1;

    mini.init([](int a, int b)->bool const {
        return a < b;
    });

    maxi.init([](int a, int b)->bool const {
        return a > b;
    });

    mini.add(mp(y[1] + tp, 1));
    maxi.add(mp(x[1] + tp, 1));

    pos = 1;
    for (i = 2; i <= n; i++) {
        mini.add(mp(y[i] + tp * i, i));
        maxi.add(mp(x[i] + tp * i, i));

        while (mini.data.front().first < maxi.data.front().first) {
            pos++;
            if (mini.data.front().second < pos)
                mini.data.pop_front();
            if (maxi.data.front().second < pos)
                maxi.data.pop_front();
        }

        ans = max(ans, i - pos + 1);
    }

    return ans;
}

int main()
{
    freopen("diagonala.in","r",stdin);
    freopen("diagonala.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) scanf("%d%d", &x[i], &y[i]);

    int ans = max(solve(-1), solve(+1));

    printf("%d", ans);
    cerr << ans;


    return 0;
}
