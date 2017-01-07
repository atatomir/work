#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <bitset>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 77

int n, i, j, test;
char s[maxN][maxN];
bitset<maxN> B[maxN];

bitset<maxN> target, zero, checker, to_use[10];
vector<int> act, best;

vector<int> greedy() {
    int i, j, cnt;
    pair<int, int> best;
    vector<int> ans = {};
    vector<int> act = {};

    for (i = 1; i <= n; i++) act.pb(i);

    while (!act.empty()) {
        best = mp(-1, -1);
        for (auto e : act) {
            cnt = 0;
            for (auto e2 : act)
                if (B[e][e2])
                    cnt++;
            best = max(best, mp(cnt, e));
        }

        for (i = 0; i < act.size(); i++) {
            if (B[best.second][act[i]] == 0) continue;
            act[i] = act.back();
            act.pop_back(); i--;
        }

        ans.pb(best.second);
    }

    return ans;
}

void back() {
    bitset<maxN>& conf = to_use[act.size()];
    bitset<maxN>& aux = to_use[act.size() + 1];

    if (act.size() >= best.size()) return;
    if (target == conf) {
        best = act;
        return;
    }
    if (act.size() + 1 == best.size()) return;

    for (int i = act.back() + 1; i <= n; i++) {
        act.pb(i);

        aux = conf | B[i];
        back();

        act.pop_back();
    }

}

int main()
{
    //freopen("test.in","r",stdin);
    act.reserve(10);

    while (scanf("%d\n", &n) == 1) {
        for (i = 1; i <= n; i++) scanf("%s\n", s[i] + 1);
        printf("Case %d: ", ++test);
        target.reset();

        for (i = 1; i <= n; i++) {
            target[i] = 1;
            B[i].reset();

            for (j = 1; j <= n; j++)
                if (s[i][j] == '1' || i == j)
                    B[i][j] = 1;
        }

        best = greedy();
        back();

        checker.reset();
        for (auto e : best)
            checker |= B[e];
        if (checker != target)
            cerr << "ERR";

        printf("%d ", best.size());
        sort(best.begin(), best.end());
        for (auto e : best)
            printf("%d ", e);

        printf("\n");
    }


    return 0;
}
