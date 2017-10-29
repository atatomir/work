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

#define maxN 1000011

int t, ti;
int n, i, tot;
char a[maxN], b[maxN];

int suml[maxN], sumr[maxN], sumu[maxN], ini;
deque<int> L, R, U;
ll ans;

void change_min(deque<int>& to) {
    pair<int, int> ans = mp(n + 1, 0);

    if (!L.empty())
        ans = min(ans, mp(L.front(), 1));
    if (!R.empty())
        ans = min(ans, mp(R.front(), 2));
    if (!U.empty())
        ans = min(ans, mp(U.front(), 3));

    ini = ans.first;
    if (ans.second == 1) L.pop_front();
    if (ans.second == 2) R.pop_front();
    if (ans.second == 3) U.pop_front();

    to.push_back(ini);
}

void move_it(deque<int>& act) {
    int pos = 0;
    int wh;

    if (act.empty()) {
        change_min(act);
    }

    wh = act.back();

    if (!L.empty()) pos += suml[min(wh, L.back())] - suml[ini];
    if (!R.empty()) pos += sumr[min(wh, R.back())] - sumr[ini];
    if (!U.empty()) pos += sumu[min(wh, U.back())] - sumu[ini];

    ans += 1LL * (tot - pos);

    act.pop_back();
}

ll solve() {
    int i;

    while (!L.empty()) L.pop_back();
    while (!R.empty()) R.pop_back();
    while (!U.empty()) U.pop_back();

    for (i = 1; i <= n; i++) {
        suml[i] = suml[i - 1];
        sumr[i] = sumr[i - 1];
        sumu[i] = sumu[i - 1];

        if (a[i] == 'L') {
            suml[i]++;
            L.push_back(i);
        }

        if (a[i] == 'R') {
            sumr[i]++;
            R.push_back(i);
        }

        if (a[i] == 'U') {
            sumu[i]++;
            U.push_back(i);
        }
    }

    ans = 0; ini = 0; tot = n;
    for (i = n; i > 0; i--, tot--) {
        char act = b[i];

        if (act == 'L')
            move_it(L);

        if (act == 'R')
            move_it(R);

        if (act == 'U')
            move_it(U);
    }

    return ans;
}

int main()
{
    freopen("lru.in","r",stdin);
    freopen("lru.out","w",stdout);

    scanf("%d", &t);
    for (ti = 1; ti <= t; ti++) {
        scanf("%d\n%s\n%s", &n, a + 1, b + 1);
        printf("%lld\n", solve());
    }


    return 0;
}
