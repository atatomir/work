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

#define maxN 15
#define eps 1e-5

int n, i, m, p, h, how;
double dp[1 << maxN];
short order[1 << maxN];

int act_sum;
int def_state, now_state;

double best;
int id;

int lim;
char cnt[1 << maxN];

bool eq(double a, double b) {
    return -eps < a - b && a - b < eps;
}

bool better(int s1, int s2) {
    vector<int> aux1, aux2;
    aux1.clear();
    aux2.clear();

    while (order[s1] != 0) {
        for (int i = 0; i < n; i++)
            if (order[s1] & (1 << i))
                aux1.pb(i);
        s1 ^= order[s1];
    }

    while (order[s2] != 0) {
        for (int i = 0; i < n; i++)
            if (order[s2] & (1 << i))
                aux2.pb(i);
        s2 ^= order[s2];
    }

    for (i = 0; i < aux1.size(); i++) {
        if (aux1[i] < aux2[i]) return true;
        if (aux1[i] > aux2[i]) return false;
    }

    return true;
}

void _back(int pos) {
    if (pos == n) {
        if (now_state == 0) return;

        if (now_state == 16 && def_state == 997) {
            pos--; pos++;
        }

        int comb = def_state | now_state;
        double act_cost = dp[def_state] + p + (1.00 * act_sum) / (1.00 * cnt[now_state]);
        if (cnt[now_state] == 1) act_cost -= p;

        if (eq(dp[comb], act_cost)) {
            order[lim] = now_state;

            if (better(lim, comb))
                order[comb] = now_state;
        } else
        if (dp[comb] == 0 || dp[comb] > act_cost) {
            dp[comb] = act_cost;
            order[comb] = now_state;
        }

        return;
    }

    _back(pos + 1);

    now_state ^= 1 << pos;
    act_sum += pos + 1;
    if (act_sum <= n) _back(pos + 1);
    act_sum -= pos + 1;
    now_state ^= 1 << pos;

    def_state ^= 1 << pos;
    _back(pos + 1);
    def_state ^= 1 << pos;
}

void print_state(int s) {
    while (s != 0) {
        for (int i = 0; i < n; i++)
            if (order[s] & (1 << i))
                printf("%d ", i + 1);
        s ^= order[s];
    }
}

int main()
{
    freopen("scara2.in","r",stdin);
    freopen("scara2.out","w",stdout);

    scanf("%d%d%d%d", &h, &how, &n, &p);
    lim = 1 << n;


    for (i = 0; i < lim; i++)
        for (int j = 0; j < n; j++)
            if (i & (1 << j))
                cnt[i]++;

    _back(0);

    best = 100000000.00 ;
    for (int state = 0; state < lim; state++) {
        if (cnt[state] != how) continue;

        int act_sum = 0;
        for (i = 0; i < n; i++)
            if (state & (1 << i))
                act_sum += i + 1;

        if (act_sum != h) continue;

        if (best > dp[state]) {
            best = dp[state];
            id = state;
        } else
        if (eq(best, dp[state])) {
            if (better(state, id)) {
                best = dp[state];
                id = state;
            }
        }
    }

    printf("%.2lf\n", best);
    print_state(id);

    return 0;
}
